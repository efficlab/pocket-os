#include <unistd.h>
#include <assert.h>
#include <fcntl.h>

int main() {
  int fd = open( 
    "./tmp", 
    O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
  assert(fd > -1);
  int rc = write(fd, "Hello, world!\n", 14);
  assert(rc == 14);
  close(fd);
  return 0;
}
