#include <stdio.h>
#include <stdlib.h>

int global_var = 1;
int global_uninit_var;

int main() {
  static int static_var = 1;
  static int uninit_static_var;
  int local_var = 1;
  void* heap_var = malloc(4);
  printf("Global Var: %p\n", &global_var);
  printf("Static Var: %p\n", &static_var);
  printf("Global Uninitialized Var: %p\n", &global_uninit_var);
  printf("Uninitialized Static Var: %p\n", &uninit_static_var);
  printf("Local Var: %p\n", &local_var);
  printf("Heap Var: %p\n", heap_var);
  return 0;
}
