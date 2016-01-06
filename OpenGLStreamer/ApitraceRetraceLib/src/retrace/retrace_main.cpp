/**************************************************************************
 *
 * Copyright 2011 Jose Fonseca
 * Copyright (C) 2013 Intel Corporation. All rights reversed.
 * Author: Shuang He <shuang.he@intel.com>
 * All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 **************************************************************************/
#include <cstdint>
#include "retrace_main.hpp"
#include "retrace.hpp"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

retrace::Retracer retracer;

namespace retrace {

trace::AbstractParser *parser;
trace::Profiler profiler;


int verbosity = 0;
unsigned debug = 0;
bool forceWindowed = true;
bool dumpingState = false;
bool dumpingSnapshots = false;

Driver driver = DRIVER_DEFAULT;
const char *driverModule = NULL;

bool doubleBuffer = true;
unsigned samples = 1;

bool profiling = false;
bool profilingGpuTimes = false;
bool profilingCpuTimes = false;
bool profilingPixelsDrawn = false;
bool profilingMemoryUsage = false;
bool useCallNos = true;
bool singleThread = false;

unsigned frameNo = 0;
unsigned callNo = 0;

void
frameComplete(trace::Call &call) {
    ++frameNo;
}

/**
 * Retrace one call.
 *
 * Take snapshots before/after retracing (as appropriate) and dispatch it to
 * the respective handler.
 */
static void
retraceCall(trace::Call *call) {
    retracer.retrace(*call);
}


void init()
{
    setUp();
    addCallbacks(retracer);
    parser = new trace::Parser;
    parser->open(nullptr);
}

void processCall(const char *callData, uint64_t length)
{
    assert(callData && length);

    parser->setData(callData, length);
    trace::Call *call = nullptr;
    while ((call = parser->parse_call())) {
        retraceCall(call);
        delete call;
    }
}

} /* namespace retrace */

#ifdef __EMSCRIPTEN__
extern "C"
int main()
{
    retrace::init();
    EM_ASM(connectWebSocket(););
}
#endif
