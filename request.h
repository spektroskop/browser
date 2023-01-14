#pragma once

#include <QStringList>
#include <QUrl>
#include <variant>
#include <string>

struct UrlRequest {
    UrlRequest() : url("about:blank"), zoom(1.0) { }
    UrlRequest(const QUrl &url, double zoom) : url(url), zoom(zoom) { }
    UrlRequest(const QStringList&);

    QUrl url;
    double zoom;
};

struct LockRequest {};
struct UnlockRequest {};
using BadRequest = std::string;

using Request = std::variant<
    UrlRequest,
    LockRequest,
    UnlockRequest,
    BadRequest
>;

Request parse_request(const QStringList&);
