#include "display.h"
#include "input.h"
#include <stdlib.h>
#include <stdio.h>

int main() {
  char *working_directory = getenv("HOME"), *user_mode = getenv("USER");
  construct_display(working_directory, user_mode);
  key_input();
  system("clear");
  return 0;
}
