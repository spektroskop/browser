#include <QTextStream>
#include "reader.h"

Reader::Reader() {
    stdinNotifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
    connect(stdinNotifier, SIGNAL(activated(int)), SLOT(read()));
}

void Reader::read() {
    QTextStream qin(stdin);
    QString line = qin.readLine();
    emit received(line);
}
