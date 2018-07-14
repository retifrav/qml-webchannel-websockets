#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebView>
#include <QWebChannel>
#include <QWebSocketServer>
#include "websockettransport.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // don't forget about this
    QtWebView::initialize();

    qmlRegisterType<WebSocketTransport>("io.decovar.WebSocketTransport", 1, 0, "WebSocketTransport");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) { return -1; }

    return app.exec();
}
