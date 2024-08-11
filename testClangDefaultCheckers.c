#include <stdlib.h>
#include <string.h>

void test_unix_malloc() {
  int *p = malloc(1);
  free(p);
  free(p); // warn: attempt to free released memory
}

void test_unix_mallocsizeof() {
  long *p = malloc(sizeof(short)); // warn: result is converted to 'long *', which is incompatible with operand type 'short'
  free(p);
}

void test_core_uninitializedbranch() {
  int x;
  if (x) // warn
    return;
}

int test_cstring_nullarg() {
  return strlen(0); // warn
}

void test_deadcode() {
  int x;
  x = 1; // warn
}

int f(int *p) __attribute__((nonnull));

void test_nonnull_paramchecker(int *p) {
  if (!p)
    f(p); // warn
}

void test_dividebyzero(int z) {
  if (z == 0) {
    int x = 1 / z; // warn
  }
}

void test_nulldereference(int *p) {
  if (p)
    return;

  int x = p[0]; // warn
}
