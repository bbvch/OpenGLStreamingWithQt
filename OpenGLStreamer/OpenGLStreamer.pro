TEMPLATE=subdirs

SUBDIRS=ClientApp ServerApp \
    StreamerLib \
    OpenGlStreamerTest \
    StreamerLibTest

OpenGlStreamerTest.depends = StreamerLib
StreamerLibTest.depends = StreamerLib
