#ifndef RETRACE_MAIN_HPP
#define RETRACE_MAIN_HPP

namespace retrace {

void init();
void processCall(const char *callData, uint64_t length);

}

#endif // RETRACE_MAIN_HPP

