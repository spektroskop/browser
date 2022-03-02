#include <QApplication>
#include <QWebEngineView>
#include "reader.h"
#include "browser.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app (argc, argv);

    Reader reader;
    Browser browser;
    QObject::connect(&reader, &Reader::received, &browser, &Browser::loadUrlString);

    return app.exec();
}
