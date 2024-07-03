#include <stdio.h>
#include <unistd.h>

int main() {
  char buffer[14];
  // Read from standard input.
  read(STDIN_FILENO, buffer, sizeof buffer);
  // Write to standard output.
  write(STDOUT_FILENO, buffer, sizeof buffer);
  // Write to standard error.
  write(STDERR_FILENO, buffer, sizeof buffer);
  return 0;
}
