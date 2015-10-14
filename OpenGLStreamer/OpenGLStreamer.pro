TEMPLATE=subdirs

SUBDIRS= ClientApp \
         ServerApp \
         StreamerLib \
         StreamerLibTest


StreamerLibTest.depends = StreamerLib
ClientApp.depends = StreamerLib
ServerApp.depends = StreamerLib
