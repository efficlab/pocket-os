#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, const char* argv[]) {
  printf("[pid: %d] Hello, fork()~\n", getpid());
  int ret_val = fork();
  if (ret_val < 0) {
    fprintf(stderr, "Fork failed!\n");
  } else if (ret_val == 0) {
    // Child process goes this way.
    printf("[pid: %d] Child process.\n", getpid());
    close(STDOUT_FILENO);
    open("./execvp.output", O_CREAT | O_WRONLY, S_IRWXU);
    char* args[2];
    args[0] = strdup(argv[1]);
    args[1] = NULL;
    execvp(args[0], args);
  } else {
    // Parent process goes this way.
    int wstatus;
    int terminated_pid = wait(&wstatus);
    if (terminated_pid != -1 && WIFEXITED(wstatus)) {
      printf("[pid: %d] Parent: process %d is terminated.\n", 
        getpid(), 
        terminated_pid);
    }
  }
  return 0;
}
