#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, const char* argv[]) {
  printf("Welcome to my shell!\n");
  while (1) {
    printf("# ");
    char *line = NULL;
    size_t size;
    size_t line_len = getline(&line, &size, stdin);
    if (line_len > 1) {
      // Remove line break character.
      *(line + line_len - 1) = '\0';  
      char* args[2];
      args[0] = line;
      args[1] = NULL;
      // Run command in a separate process.
      int ret_val = fork();
      if (ret_val < 0) {
        fprintf(stderr, "Fork failed!\n");
      } else if (ret_val == 0) {
        // Child process goes this way.
        int ret_code = execvp(args[0], args);
        if (ret_code == -1) {
          printf("Execution failed: %s.\n", strerror(errno));
        }
      } else {
        // Parent process goes this way.
        int wstatus;
        int terminated_pid = wait(&wstatus);
        if (terminated_pid == -1) {
          fprintf(stderr, "Wait failed!\n");
        }
        free(line);
      }
    }
  }
  return 0;
}
