/*#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include "OpenGLClient.h"
*/

#include "GlWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GlWidget w;
    w.show();

    return a.exec();
    /*
    QCoreApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);

    OpenGLClient client(QUrl(QStringLiteral("ws://localhost:1234")), debug);
    QObject::connect(&client, &OpenGLClient::closed, &a, &QCoreApplication::quit);

    return a.exec();
*/
}
