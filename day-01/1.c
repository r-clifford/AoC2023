#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define __STDC_WANT_LIB_EXT2__ 1
#define numLength 9
const char* numbers[numLength] = {"one", "two",   "three", "four", "five",
                                  "six", "seven", "eight", "nine"};
bool isValid(char c) { return c >= '0' && c <= '9'; }
void transformLine(char* ptr) {
  for (size_t i = 0; i < numLength; i++) {
    // Continue searching and replacing until no other matches are found by
    // rechecking the string
    // As we have checked up to the address of c, start search there
    char* c = ptr;
    while ((c = strstr(c, numbers[i]))) {
      if (c != NULL) {
        // use second character to avoid conflicting with beginning/end of other
        // numbers
        *(c + 1) = i + 1 + '0';
      }
    }
  }
}
size_t solution1(char* line, size_t len) {
  // Retrieve first and last digits, concatenate them, and interpret as decimal
  // Could make worst case len/2 if we store found digits in order and stop if
  // i,j overlap
  int first, second;
  int i, j;
  i = 0;
  j = len - 1;
  bool firstFound = false;
  bool secondFound = false;
  while ((i < len) && (j >= 0)) {
    if (!firstFound && isValid(line[i])) {
      first = line[i] - '0';
      firstFound = true;
    }
    if (!secondFound && isValid(line[j])) {
      second = line[j] - '0';
      secondFound = true;
    }
    i++;
    j--;
  }
  return 10 * first + second;
}
int main() {
  FILE* fd = fopen("1.txt", "r");
  char* line;
  int len;
  // getline allocs, len is size of created buffer
  size_t bufSize;
  size_t total = 0;
  while ((len = getline(&line, &bufSize, fd))) {
    if (len != -1) {
      transformLine(line);
      int res = solution1(line, len);
      total += res;
      printf("%d: %ld\n", res, total);
      // free(line);
    } else {
      break;
    }
  }
  printf("%ld\n", total);  // 53389
}
