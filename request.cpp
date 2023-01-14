#include "request.h"

Request parse_request(const QStringList &args) {
    if (args.count() == 0) return BadRequest{ "missing kind" };

    const QString kind = args.at(0);
    const QStringList req = QStringList(args.mid(1));

    if (kind.toUpper() == "URL") return UrlRequest(req);
    if (kind.toUpper() == "UNLOCK") return UnlockRequest{};
    if (kind.toUpper() == "LOCK") return LockRequest{};

    return BadRequest{ "unknown kind: " + kind.toStdString() };
}

UrlRequest::UrlRequest(const QStringList &args) : UrlRequest()
{
    if (args.count()==0 || args.count()>2) {
        return;
    }

    if (args.count()>0) {
        QString urlString = args.at(0);
        url = QUrl::fromUserInput(urlString);
    }

    if (args.count()>1) {
        bool ok = true;
        zoom = args.at(1).toDouble(&ok);
        if(!ok) { zoom = 1.0; }
    }
}
