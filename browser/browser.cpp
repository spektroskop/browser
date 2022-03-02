#import "browser.h"

Browser::Browser(const QUrl &url) : QObject(), view(nullptr) {
    view = new QWebEngineView();
    view->load(url);
    // view->setWindowState(Qt::WindowFullScreen);
    view->show();
}

void Browser::loadUrl(const QString &urlString) {
    view->load(QUrl(urlString));
}
