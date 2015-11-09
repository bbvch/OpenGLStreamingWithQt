TEMPLATE=subdirs

SUBDIRS= ClientApp \
         ServerApp \
         StreamerLib \
         StreamerLibTest \
    ApitraceLib


# subdir of ClientApp, ServerApp and StreamerLibTest are implicitly set.

StreamerLib.subdir         = StreamerLib


# Here's where you build up the hierarchical relationship between components.

StreamerLibTest.depends = StreamerLib
ClientApp.depends = StreamerLib
ServerApp.depends = StreamerLib
