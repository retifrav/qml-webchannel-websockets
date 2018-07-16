#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWebView>
#include <QWebChannel>
#include <QWebSocketServer>
//#include <QDesktopServices>
#include <QQmlContext>
#include "websocketclientwrapper.h"
#include "websockettransport.h"
#include "backend.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // don't forget about this
    QtWebView::initialize();

    QWebSocketServer server(
                QStringLiteral("WebSockets example"),
                QWebSocketServer::NonSecureMode
                );
    if (!server.listen(QHostAddress::LocalHost, 55222))
    {
        qFatal("Failed to open web socket server.");
        return 1;
    }
    //qDebug() << server.serverAddress();

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper clientWrapper(&server);

    // setup the channel
    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    // setup the core and publish it to the QWebChannel
    Backend *backend = new Backend();
    channel.registerObject(QStringLiteral("backend"), backend);

    // open a browser window with the client HTML page
//    QUrl baseURL = QUrl(QString("file:/%1").arg(qApp->applicationDirPath()));//QDir::currentPath()
//    QString lastMile = "index.html";
//#if defined(Q_OS_MAC)
//    lastMile = "../../index.html";
//#elif defined(Q_OS_WIN)
//    lastMile = "../index.html";
//#endif
//    QUrl fileURL = QUrl(lastMile);
//    QDesktopServices::openUrl(baseURL.resolved(fileURL));

    //qmlRegisterType<Backend>("io.qt.Backend", 1, 0, "Backend");

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("someObject", backend);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty()) { return -1; }

    return app.exec();
}
