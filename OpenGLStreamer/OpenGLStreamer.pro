TEMPLATE=subdirs

SUBDIRS= ClientApp \
         ServerApp \
         ApitraceTraceLib \
         ApitraceCommonLib \
         ApitraceRetraceLib

# subdir of ClientApp, ServerApp and StreamerLibTest are implicitly set.
StreamerLibTest.subdir   = StreamerLibTest

# Here's where you build up the hierarchical relationship between components.
ApitraceTraceLib.depends = ApitraceCommonLib
ApitraceRetraceLib.depends = ApitraceCommonLib
ClientApp.depends = ApitraceTraceLib
ServerApp.depends = ApitraceRetraceLib
