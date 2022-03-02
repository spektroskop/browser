#include <QApplication>
#include "reader.h"
#include "browser.h"

QUrl commandLineUrl() {
    const QStringList args = QCoreApplication::arguments();

    for(const QString &arg : args.mid(1)) {
        if(!arg.startsWith(QLatin1Char('-'))) {
            return QUrl::fromUserInput(arg);
        }
    }

    return QUrl(QStringLiteral("about:blank"));
}

int main(int argc, char *argv[]) {
    QCoreApplication::setOrganizationName("Browser");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    Reader reader;
    Browser browser(commandLineUrl());
    QObject::connect(&reader, &Reader::received, &browser, &Browser::loadUrl);

    return app.exec();
}
