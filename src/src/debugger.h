#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <signal.h>

#define GDB_LOGFILE_FORMAT "./debug/gdb-%Y.%m.%d-%H.%M.%S.log"

void backtrace();
void capture_segfault(int signal, siginfo_t *info, void *arg);
void install_debugger();

#ifdef ALLOW_SEGFAULT_SIMULATION
void simulate_segfault();
#endif

#endif
