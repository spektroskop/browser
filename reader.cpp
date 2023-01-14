#include <QCoreApplication>
#include <QSocketNotifier>
#include <iostream>

#include "reader.h"

Reader::Reader()
    : QObject(),
      stdinNotifier(nullptr)
{
    stdinNotifier = new QSocketNotifier(fileno(stdin), QSocketNotifier::Read, this);
    connect(stdinNotifier, SIGNAL(activated(int)), SLOT(read()));
}

void Reader::read()
{
    std::string line;

    if(!std::getline(std::cin, line)) {
        QCoreApplication::exit();
        return;
    }

    QStringList args = QString::fromStdString(line)
        .split(QLatin1Char(' '),  Qt::SkipEmptyParts);

    Request req = parse_request(args);
    emit received(req);
}
