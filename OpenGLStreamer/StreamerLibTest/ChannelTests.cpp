#include <gtest/gtest.h>
#include "QtWebSockets/qwebsocketserver.h"

#include "Channel.h"


/*TEST(Channel, IsDisconnectedWhenCreated)
{
    Channel ch(QUrl(QStringLiteral("ws://localhost:1234")), true);

    EXPECT_EQ(false, ch.isValid());
}

TEST(Channel, ConnectToServer)
{
    bool connected = false;
    Channel *ch;

    QWebSocketServer server(QStringLiteral("Echo Server"), QWebSocketServer::NonSecureMode, Q_NULLPTR);

    if (server.listen(QHostAddress::Any, 1234))
    {
        QObject::connect(&server, &QWebSocketServer::newConnection, [&](){
            connected = true;
        });
        ch = new Channel(QUrl(QStringLiteral("ws://localhost:1234")), true);
    }

    EXPECT_EQ(true, ch->isValid());
}*/
