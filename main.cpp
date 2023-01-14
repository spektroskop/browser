#include <QApplication>
#include <QCommandLineParser>
#include <iostream>

#include "browser.h"
#include "config.h"
#include "reader.h"
#include "request.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setApplicationName("browser");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);

    QCommandLineParser commandLine;
    commandLine.addHelpOption();

    QCommandLineOption prefix("prefix", "Environment config prefix", "prefix", "BROWSER");
    commandLine.addOption(prefix);

    commandLine.process(app);

    Config config(commandLine.value(prefix).toUpper()+"_");
    UrlRequest req(commandLine.positionalArguments());
    Browser browser(config, req);
    Reader reader;

    QObject::connect(&reader, &Reader::received, &browser, &Browser::dispatch);
    return app.exec();
}
