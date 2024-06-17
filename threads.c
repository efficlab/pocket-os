#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
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

int counter = 0;

typedef struct {
  pthread_t thread;
  int id;
} ThreadInfo;

void *worker(void *arg) {
  ThreadInfo* threadInfo = (ThreadInfo*) arg;
  while (counter < 10) {
    spin(1);
    counter++;
    printf("[Thread %d] counter value : %d\n", threadInfo->id, counter);
  }
  return NULL;
}

int main() {
  ThreadInfo thread1 = { .id = 1 };
  ThreadInfo thread2 = { .id = 2 };
  pthread_create(&thread1.thread, NULL, worker, &thread1);
  pthread_create(&thread2.thread, NULL, worker, &thread2);
  pthread_join(thread1.thread, NULL);
  pthread_join(thread2.thread, NULL);
  return 0;
}
