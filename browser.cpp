#import "browser.h"

Browser::Browser() : QObject(), view(nullptr) {
    view = new QWebEngineView();
}

void Browser::setZoomFactor(qreal factor) {
    view->setZoomFactor(factor);
}

void Browser::loadUrl(QUrl url) {
    view->load(url);
    view->setWindowState(Qt::WindowFullScreen);
    view->show();
}

void Browser::loadUrlString(QString urlString) {
    this->loadUrl(QUrl(urlString));
}
