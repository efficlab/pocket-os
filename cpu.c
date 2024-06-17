#include <stdio.h>
#include <sys/time.h>
#include <assert.h>

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

int main(int argc, char *argv[]) {
  if (argc > 1) {
    while (1) {
      spin(1);
      printf("%s\n", argv[1]);
    }
  }
  return 0;
}
