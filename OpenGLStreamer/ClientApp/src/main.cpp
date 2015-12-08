#include <QApplication>
#include <QtCore/QCommandLineParser>
//#include <QtCore/QCommandLineOption>

//#include "GlWidget.h"
#include <openglclient.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("OpenGLStreamer client example");
    parser.addHelpOption();

    parser.addOption({QStringList() << "d" << "debug", QCoreApplication::translate("main", "Debug output [default: off].")});
    parser.addOption({{"u", "url"}, "Server address", QStringLiteral("ws://localhost:1234")});

    parser.process(a);
    const bool debug = parser.isSet("debug");
    const QUrl url = QUrl::fromUserInput(parser.value("url"));

    OpenGLClient client(url, debug);
    (void)client;

    return a.exec();
}
