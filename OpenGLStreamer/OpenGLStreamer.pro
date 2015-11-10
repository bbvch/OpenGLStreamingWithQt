TEMPLATE=subdirs

SUBDIRS= ClientApp \
         ServerApp \
         StreamerLib \
         StreamerLibTest \
         ApitraceLib \
    ApitraceCommonLib

# subdir of ClientApp, ServerApp and StreamerLibTest are implicitly set.

ClientApp.subdir         = ClientApp
ServerApp.subdir         = ServerApp
StreamerLib.subdir       = StreamerLib
StreamerLibTest.subdir   = StreamerLibTest
ApitraceLib.subdir       = ApitraceLib

# Here's where you build up the hierarchical relationship between components.

StreamerLibTest.depends = StreamerLib
ClientApp.depends = StreamerLib
ServerApp.depends = StreamerLib
StreamerLib.depends = ApitraceLib
