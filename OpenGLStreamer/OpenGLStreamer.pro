TEMPLATE=subdirs

SUBDIRS=ClientApp ServerApp \
    StreamerLib \
    StreamerLibTest

StreamerLibTest.depends = StreamerLib
