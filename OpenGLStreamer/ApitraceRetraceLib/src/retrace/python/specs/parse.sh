#! /bin/bash

gles2="`cat ../../../../../ApitraceCommonLib/src/thirdparty/khronos/GLES2/gl2.h | grep " gl*"`"
gles2ext="`cat ../../../../../ApitraceCommonLib/src/thirdparty/khronos/GLES2/gl2ext.h | grep " gl*"`"
cat glapi.py | awk -v gles2="${gles2}" '{a=$2; gsub(/"|,/,"",a); if (a ~ /^gl/ && index(gles2, " "a" ") != 0) print $0}' > gles2.cpp.tmp
cat glapi.py | awk -v gles2ext="${gles2ext}" '{a=$2; gsub(/"|,/,"",a); if (a ~ /^gl/ && index(gles2ext, " "a" ") != 0) print $0}' > gles2ext.cpp.tmp
