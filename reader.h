#pragma once

#include <QObject>

#include "request.h"

class QSocketNotifier;

class Reader : public QObject
{
    Q_OBJECT

public:
    Reader();

signals:
    void received(const Request &req);

private slots:
    void read();

private:
    QSocketNotifier *stdinNotifier;
};
