#pragma once

#include <QObject>
#include <iostream>
#include <optional>
#include "config.h"
#include "request.h"

class QAuthenticator;
class QUrl;
class QWebEngineView;

class Browser : public QObject
{
    Q_OBJECT

public:
    Browser(const Config&, const UrlRequest&);
   ~Browser();

public slots:
    void dispatch(const Request&);

private slots:
    void authenticate(const QUrl&, QAuthenticator*);
    void screenshot();

private:
    void loadUrl(const UrlRequest&);
    void lock();
    void unlock();

private:
    QWebEngineView *webengine;
};
