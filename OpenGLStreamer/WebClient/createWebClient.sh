#! /bin/bash

PATH_COMMON_LIB="../ApitraceCommonLib/src"
PATH_RETRACE_LIB="../ApitraceRetraceLib/src/retrace"
FLAGS="-g3 -std=c++11
	   -DRETRACE 
	   -I$PATH_COMMON_LIB/common 
	   -I$PATH_COMMON_LIB/dispatch 
	   -I$PATH_COMMON_LIB/helpers 
	   -I$PATH_COMMON_LIB/image 
	   -I$PATH_COMMON_LIB/guids
	   -I$PATH_COMMON_LIB/thirdparty/md5
	   -I$PATH_COMMON_LIB/thirdparty/zlib
	   -I$PATH_COMMON_LIB/thirdparty/libpng
	   -I$PATH_COMMON_LIB/thirdparty/snappy
	   -I$PATH_COMMON_LIB/thirdparty/khronos"

source ~/.emscripten 2&>>/dev/null

SRC_COMMON=`find ${PATH_COMMON_LIB} -name "*.cpp"` 
SRC_RETRACE=`find ${PATH_RETRACE_LIB} -name "*.cpp"`

SRC="$SRC_COMMON \
     $SRC_RETRACE"

echo "Compiling the code..."
$EMSCRIPTEN_ROOT/emcc $FLAGS $SRC --post-js script.js --shell-file shell_minimal.html -o index.html -s EXPORTED_FUNCTIONS="['_processCall', '_main']" -s NO_EXIT_RUNTIME=1 
