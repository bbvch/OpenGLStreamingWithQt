TEMPLATE=subdirs

SUBDIRS=ClientApp ServerApp \
    StreamerLib \
    OpenGlStreamerTest

OpenGlStreamerTest.depends = StreamerLib
