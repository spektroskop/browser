#pragma once

#include <QColor>

class Config
{
public:
    Config(const QString&);

private:
    void readStartUnlocked();
    void readScreenshotInterval();
    void readBackgroundColor();

public:
    bool startUnlocked;
    unsigned int screenshotInterval;
    QColor backgroundColor;

private:
    QString prefix;
};
