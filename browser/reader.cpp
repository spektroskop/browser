#include <QCoreApplication>
#include <QTextStream>
#include <iostream>
#include "reader.h"

Reader::Reader() {
    stdinNotifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
    connect(stdinNotifier, SIGNAL(activated(int)), SLOT(read()));
}

void Reader::read() {
    std::string line;

    if(!std::getline(std::cin, line)) {
        QCoreApplication::exit();
        return;
    }

    emit received(QString::fromStdString(line));
}
