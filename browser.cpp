#include <QApplication>
#include <QAuthenticator>
#include <QBuffer>
#include <QDialog>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QProcessEnvironment>
#include <QTimer>
#include <QUrl>
#include <QVBoxLayout>
#include <QWebEngineProfile>
#include <QWebEngineView>
#include <algorithm>
#include <iostream>
#include <unistd.h>

#include "browser.h"
#include "defer.h"

#define ROOT_FLAGS "--kiosk --no-first-run --noerrdialogs --no-sandbox"
#define USER_FLAGS "--kiosk --no-first-run --noerrdialogs"

Browser::Browser(const Config &config, const UrlRequest &req)
    : QObject(), webengine(new QWebEngineView)
{
    std::cerr << "cache path "
              << webengine->page()->profile()->cachePath().toStdString()
              << std::endl;

    std::cerr << "persistent storage path "
              << webengine->page()->profile()->persistentStoragePath().toStdString()
              << std::endl;

    const auto uid = getuid();
    QProcessEnvironment::systemEnvironment().insert(
        "QTWEBENGINE_CHROMIUM_FLAGS",
        uid == 0 ? ROOT_FLAGS : USER_FLAGS
    );

    config.startUnlocked ? unlock() : lock();

    if (config.screenshotInterval > 0) {
        QTimer *timer = new QTimer(this);
        timer->setInterval(std::max((unsigned int)5, config.screenshotInterval) * 1000);
        connect(timer, SIGNAL(timeout()), this, SLOT(screenshot()));
        timer->start();
    }

    webengine->page()->setBackgroundColor(config.backgroundColor);

    connect(webengine->page(), &QWebEnginePage::authenticationRequired, this, &Browser::authenticate);

    loadUrl(req);
    webengine->show();
}

Browser::~Browser()
{
    delete(webengine);
}

void Browser::dispatch(const Request &req)
{
    if (const auto *urlReq = std::get_if<UrlRequest>(&req)) return loadUrl(*urlReq);
    if (std::get_if<UnlockRequest>(&req)) return unlock();
    if (std::get_if<LockRequest>(&req)) return lock();
    if (const auto *badReq = std::get_if<BadRequest>(&req))
        std::cerr << "bad request: " << *badReq << std::endl;
}

void Browser::authenticate(const QUrl &url, QAuthenticator *auth)
{
    std::cerr << "authenticate " << url.toString().toStdString() << std::endl;

    bool wasLocked = !webengine->isEnabled();
    Defer locker([this, wasLocked]() { if (wasLocked) lock(); });
    unlock();

    QDialog dialog(webengine);
    dialog.setWindowTitle("Authentication required");
    dialog.setModal(true);

    QVBoxLayout box(&dialog);

    QLabel header(QString("Enter username and password for \"%1\" at %2")
        .arg(auth->realm())
        .arg(url.toString().toHtmlEscaped()));
    header.setWordWrap(true);
    box.addWidget(&header);

    QFormLayout form;
    form.setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);

    QLineEdit username;
    form.addRow("Username", &username);

    QLineEdit password;
    password.setEchoMode(QLineEdit::Password);
    form.addRow("Password", &password);

    QDialogButtonBox buttons(QDialogButtonBox::Ok|QDialogButtonBox::Cancel, Qt::Horizontal, &dialog);
    QObject::connect(&buttons, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttons, SIGNAL(rejected()), &dialog, SLOT(reject()));
    form.addRow(&buttons);

    box.addLayout(&form);

    if (dialog.exec()==QDialog::Accepted) {
        auth->setUser(username.text());
        auth->setPassword(password.text());
    } else {
        *auth = QAuthenticator();
    }
}

void Browser::loadUrl(const UrlRequest &req)
{
    connect(webengine, &QWebEngineView::loadFinished, this, [this, req] {
        if(req.zoom > 0) { webengine->setZoomFactor(req.zoom); }
        disconnect(webengine, &QWebEngineView::loadFinished, this, nullptr);
    });

    webengine->load(req.url);
}

void Browser::screenshot()
{
    QPixmap pixmap = webengine->grab();
    QImage image = pixmap.toImage();

    QByteArray bytes;
    QBuffer buffer(&bytes);
    image.save(&buffer, "PNG");

    std::cout << bytes.toBase64().toStdString() << std::endl;
}

void Browser::lock()
{
    webengine->setDisabled(true);
    QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));
}

void Browser::unlock()
{
    webengine->setDisabled(false);
    QGuiApplication::restoreOverrideCursor();
}


