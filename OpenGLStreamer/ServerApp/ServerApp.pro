include(../config.pri)

QT       += core gui widgets websockets

CONFIG += c++11

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../StreamerLib/release/ -lStreamerLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../StreamerLib/debug/ -lStreamerLib
else:unix: LIBS += -L$$OUT_PWD/../StreamerLib/ -lStreamerLib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StreamerLib/release/libStreamerLib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StreamerLib/debug/libStreamerLib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StreamerLib/release/StreamerLib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../StreamerLib/debug/StreamerLib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../StreamerLib/libStreamerLib.a

INCLUDEPATH += $$PWD/../StreamerLib/src
DEPENDPATH += $$PWD/../StreamerLib

TARGET  = ServerApp

TEMPLATE = app

SOURCES += \
    src/GlWidget.cpp \
    src/main.cpp \
    src/GeometryEngine.cpp

HEADERS += \
    src/GlWidget.h \
    src/GeometryEngine.h


DISTFILES += \
    src/vertexShader.vsh \
    src/fragmentShader.fsh

RESOURCES += \
    src/shaders.qrc \
    src/textures.qrc






