#include <stdio.h>
#include <curses.h>

#include "constants.h"

int panel_display() {
  // Misc dummy variables
  int keyChar;

  // User locator variables
  int x = map_panel_width/2, y = map_panel_height/2;

  // Initialize curses screen
  WINDOW *background = initscr();
  cbreak(); noecho(); curs_set(0); nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);

  // May or may not be necessary
  //int nrows, ncols;
  //getmaxyx(background,nrows,ncols);

  // Create map panel
  WINDOW *map_panel_container = derwin(background,map_panel_height,map_panel_width,0,0);
  wborder(map_panel_container,0,0,0,0,0,0,0,0);
  WINDOW *map_panel = newpad(map_height,map_width);

  // Dimension fix (is this a universal problem?)
  map_panel_height -= 2; map_panel_width -= 2;

  // Main loop
  while ( keyChar != 'q') {
    keyChar = wgetch(stdscr);
    mvwprintw(map_panel,y,x," ");

    // Arrow key movement
    if ( (keyChar == KEY_UP) && (y > 1) ) y -= 1;
    if ( (keyChar == KEY_DOWN) && (y < map_height) ) y += 1;
    if ( (keyChar == KEY_LEFT) && (x > 1) ) x -= 1;
    if ( (keyChar == KEY_RIGHT) && (x < map_width) ) x += 1;
    // "Running"
    if ( keyChar == KEY_SR ) { if ((y-5) > 1) y -= 5; else y = 1; }
    if ( keyChar == KEY_SF ) { if ((y+5) < map_height) y += 5; else y = map_height; }
    if ( keyChar == KEY_SLEFT ) { if ((x-5) > 1) x -= 5; else x = 1; }
    if ( keyChar == KEY_SRIGHT) { if ((x+5) < map_width) x += 5; else x = map_width; }

    mvwprintw(map_panel,y,x,"@");
    prefresh(map_panel,0,0,1,1,map_panel_height,map_panel_width);
  }

  return 0;
}

int main() {
  panel_display();
  endwin();
  return 0;
}
