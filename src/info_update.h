#ifndef INFO_UPDATE_H
#define INFO_UPDATE_H

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

int info_panel_display(WINDOW *info_panel, int y, int x) {
  // Misc dummy variables
  char *USER = getenv("USER");

  // Update coordinate display (soon to be its own function)
  werase(info_panel);
  mvwprintw(info_panel,0,0,"==USERS==");
  mvwprintw(info_panel,1,0,"%s: (%d,%d)",USER,map_height-y,x+1);
  wrefresh(info_panel);

  return 0;
}

#endif /* INFO_UPDATE_H */
