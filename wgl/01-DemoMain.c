#include "hvm.h"

// Books
// #include "input/demo1.h"
// #include "input/sum_rec_book.h"
#include "input/tuples_book.h"
// #include "input/sort_radix_book.h"

int main() {
  printf("WGL Main Start\n");

  hvm_c((u32*) BOOK_BUF);

  printf("WGL Main End\n");
  return 0;
}
