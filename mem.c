#include <spawn.h>
#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/time.h>
#include <assert.h>

#ifndef _POSIX_SPAWN_DISABLE_ASLR
#define _POSIX_SPAWN_DISABLE_ASLR 0x0100
#endif

double get_time() {
  struct timeval t;
  int rc = gettimeofday(&t, NULL);
  assert(rc == 0);
  return (double) t.tv_sec + (double) t.tv_usec / 1e6;
}

void spin(int howlong) {
  double t = get_time();
  while ((get_time() - t) < (double) howlong) ;
}

int main(int argc, char* argv[]) {
	if (argc == 2 && strcmp(argv[1], "child") == 0) {

    // Child process.
		int stack_v = 0;
		pid_t pid = getpid();
		printf("(PID %d) address of stack_v: %p\n", pid, &stack_v);
		while (1) {
			spin(1);
			stack_v = stack_v + 1;
			printf("(PID %d) stack_v: %d\n", pid, stack_v);
		}

	} else {

    // Disable ASLR and fork program in a child process.
		int ret;
		short ps_flags = 0;
		pid_t pid;
		posix_spawn_file_actions_t actions;
		posix_spawnattr_t attrs;
		posix_spawn_file_actions_init(&actions);
		posix_spawnattr_init(&attrs);

		ps_flags |= POSIX_SPAWN_SETEXEC;
		ps_flags |= _POSIX_SPAWN_DISABLE_ASLR;
		ret = posix_spawnattr_setflags(&attrs, ps_flags);

		if (ret == 0) {
      char *args[] = { argv[0], "child", NULL };
			posix_spawn(&pid, args[0], &actions, &attrs, args, NULL);
		}

	}
	return 0;
}
