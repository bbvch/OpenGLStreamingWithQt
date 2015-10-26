#include <QApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

#include "GlWidget.h"
#include "OpenGLClient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("OpenGLStreamer client example");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);

    Singleton<OpenGLClient>::createInstance(QUrl(QStringLiteral("ws://localhost:1234")), debug);

    GlWidget w;
    w.show();

    return a.exec();
}
