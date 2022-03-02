#pragma once

#include <QSocketNotifier>

class Reader : public QObject {
    Q_OBJECT
public:
    Reader();
signals:
    void received(QString text);
private slots:
    void read();
private:
    QSocketNotifier *stdinNotifier;
};
