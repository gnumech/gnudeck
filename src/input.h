#ifndef INPUT_H
#define INPUT_H
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "conio.h"

int key_input() {
  bool quit_process = false; char key_press;
  while ( quit_process == false ) {
    key_press = (char)getch();
    if ( key_press == 'q' ) quit_process = true; // Do nothing, will quit out
  }
  return 0;
}

#endif /* INPUT_H */
