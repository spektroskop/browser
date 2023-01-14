#include <QProcessEnvironment>
#include <iostream>

#include "config.h"

Config::Config(const QString &prefix)
    : startUnlocked(false),
      screenshotInterval(10),
      backgroundColor("black"),
      prefix(prefix)
{
    readStartUnlocked();
    readScreenshotInterval();
    readBackgroundColor();
}

void Config::readStartUnlocked()
{
    QString valueString = QProcessEnvironment::systemEnvironment().
        value(prefix+"START_UNLOCKED", "false");
    startUnlocked = valueString == "true";

    std::cerr << "environment " << prefix.toStdString()+"START_UNLOCKED="
              << startUnlocked << std::endl;
}

void Config::readScreenshotInterval()
{
    bool ok = true;
    QString valueString = QProcessEnvironment::systemEnvironment().
        value(prefix+"SCREENSHOT_INTERVAL", "0");
    screenshotInterval = valueString.toInt(&ok);

    if(!ok || (screenshotInterval > 0 && screenshotInterval < 5)) {
        screenshotInterval = 5;
    }

    std::cerr << "environment " <<prefix.toStdString()+"SCREENSHOT_INTERVAL="
              << screenshotInterval << std::endl;
}

void Config::readBackgroundColor()
{
    QString valueString = QProcessEnvironment::systemEnvironment().
        value(prefix+"BACKGROUND_COLOR", "black");
    backgroundColor = QColor(valueString);

    std::cerr << "environment " <<prefix.toStdString()+"BACKGROUND_COLOR="
              << backgroundColor.name().toStdString() << std::endl;
}
