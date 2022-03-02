#pragma once

#include <QWebEngineView>

class Browser : public QObject {
    Q_OBJECT
public:
    Browser(const QUrl &url);
public slots:
    void loadUrl(const QString &urlString);
private:
    QWebEngineView *view;
};
