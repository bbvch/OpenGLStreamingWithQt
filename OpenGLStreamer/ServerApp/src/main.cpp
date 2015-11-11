#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QApplication>

#include <openglserver.h>

#include "GlWidget.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("OpenGLStreamer server example");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);
    bool debug = parser.isSet(dbgOption);

    OpenGLServer server(1234, true);
    GlWidget w;

    w.show();

    return a.exec();
}
