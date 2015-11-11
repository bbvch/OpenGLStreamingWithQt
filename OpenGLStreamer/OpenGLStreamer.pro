TEMPLATE=subdirs

SUBDIRS= ClientApp \
         ServerApp \
         StreamerLib \
         StreamerLibTest \
         ApitraceTraceLib \
         ApitraceCommonLib \
         ApitraceRetraceLib

# subdir of ClientApp, ServerApp and StreamerLibTest are implicitly set.
StreamerLibTest.subdir   = StreamerLibTest

# Here's where you build up the hierarchical relationship between components.

StreamerLibTest.depends = StreamerLib
StreamerLib.depends = ApitraceTraceLib
StreamerLib.depends = ApitraceRetraceLib
ApitraceTraceLib.depends = ApitraceCommonLib
ApitraceRetraceLib.depends = ApitraceCommonLib
