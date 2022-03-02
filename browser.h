#pragma once

#include <QWebEngineView>

class Browser : public QObject {
    Q_OBJECT
public:
    Browser();
    void loadUrl(QUrl url);
    void setZoomFactor(qreal factor);
public slots:
    void loadUrlString(QString urlString);
private:
    QWebEngineView *view;
};
