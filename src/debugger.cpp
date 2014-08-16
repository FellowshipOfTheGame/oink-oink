#include "debugger.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <sys/wait.h>
#include <unistd.h>

void backtrace()
{
	char pid[30];
	char name[128];
	char date[128];
	char logging[128];

    time_t now = time(0);

    struct tm tstruct;

    tstruct = *localtime(&now);
	strftime(date, 128, GDB_LOGFILE_FORMAT, &tstruct);

	sprintf(pid, "--pid=%d", getpid());
	sprintf(logging, "set logging on %s", date);

	name[readlink("/proc/self/exe", name, 511)] = 0;

	int child = fork();

	if (!child) {
		dup2(2, 1);

		fprintf(stdout, "== GDB Invoked =================================================================\n");
		fprintf(stdout, "Stack backtrace for %s pid=%s\n", name, pid);

		execlp("gdb", "gdb", "--batch",
			"-ex", logging,
			"-ex", "printf \"== Short Backtrace =============================================================\"",
			"-ex", "thread apply all bt",
			"-ex", "printf \"\n== Full Backtrace ==============================================================\"",
			"-ex", "thread apply all bt full",
			name, pid, NULL
		);

		abort();
	} else {
		waitpid(child, NULL, 0);
	}
}

void capture_segfault(int signal, siginfo_t *info, void *arg)
{
	fprintf(stdout, "== Segmentation Fault ==========================================================\n");
	printf("Caught segmentation fault at address %p, invoking GDB\n", info->si_addr);

	backtrace();
	exit(0);
}

void install_debugger()
{
	struct sigaction action;

	memset(&action, 0, sizeof(struct sigaction));
	sigemptyset(&action.sa_mask);
	action.sa_sigaction = capture_segfault;
	action.sa_flags = SA_SIGINFO;

	sigaction(SIGSEGV, &action, NULL);
}

#ifdef ALLOW_SEGFAULT_SIMULATION
void simulate_segfault()
{
	int *p = 0;
	*p = 0;
}
#endif
