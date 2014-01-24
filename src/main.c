#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

#include "constants.h"
#include "map_update.h"
#include "info_update.h"
#include "term_update.h"

// Main loop
int loop(WINDOW *map_panel, WINDOW *info_panel, int y, int x) {
  int keyChar;
  while ( keyChar != 'q') {
    keyChar = wgetch(stdscr);
    // Remove original character position
    mvwprintw(map_panel,y,x," ");

    // Arrow key movement
    if ( (keyChar == KEY_UP) && (y > 0) ) y -= 1;
    if ( (keyChar == KEY_DOWN) && (y < map_height-1) ) y += 1;
    if ( (keyChar == KEY_LEFT) && (x > 0) ) x -= 1;
    if ( (keyChar == KEY_RIGHT) && (x < map_width-1) ) x += 1;
    // "Running"
    if ( keyChar == KEY_SR ) { if ((y-5) > 0) y -= 5; else y = 0; }
    if ( keyChar == KEY_SF ) { if ((y+5) < map_height-1) y += 5; else y = map_height-1; }
    if ( keyChar == KEY_SLEFT ) { if ((x-5) > 0) x -= 5; else x = 0; }
    if ( keyChar == KEY_SRIGHT ) { if ((x+5) < map_width-1) x += 5; else x = map_width-1; }
    // Construction
    if ( keyChar == '.' ) {
        // char *tile_confirmation_string = "Please choose a direction in which to place a tile (up, down, left, right)";
        // term_print(working_directory, tile_confirmation_string);
        nodelay(stdscr, FALSE);
        keyChar = getch();
        if ( (keyChar == KEY_UP) && (y > 0) ) mvwprintw(map_panel,y-1,x,symb_tile);
        if ( (keyChar == KEY_DOWN) && (y < map_height-1) ) mvwprintw(map_panel,y+1,x,symb_tile);
        if ( (keyChar == KEY_LEFT) && (x > 0) ) mvwprintw(map_panel,y,x-1,symb_tile);
        if ( (keyChar == KEY_RIGHT) && (x < map_width-1) ) mvwprintw(map_panel,y,x+1,symb_tile);
        nodelay(stdscr, TRUE);
    }

    // Update info display
    info_panel_display(info_panel, y, x);

    // Replace character position
    mvwprintw(map_panel,y,x,symb_user);
    map_panel_display(map_panel, y, x);

  }

  return 0;
}

int panel_display() {
  // Initialize curses screen
  WINDOW *background = initscr();
  cbreak(); noecho(); curs_set(0); nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE);

  // Create map panel with border 1 char around it
  WINDOW *map_panel_container = derwin(background,map_panel_container_height,map_panel_container_width,0,0);
  wborder(map_panel_container,0,0,0,0,0,0,0,0);
  WINDOW *map_panel = newpad(map_height,map_width);

  // Create terminal panel with border 1 char around it
  WINDOW *term_panel_container = derwin(background,term_panel_container_height,term_panel_container_width,map_panel_container_height,0);
  wborder(term_panel_container,0,0,0,0,0,0,0,0);
  //WINDOW *term_panel = derwin(term_panel_container,term_panel_height,term_panel_width,1,1);

  // Create info panel
  WINDOW *info_panel_container = derwin(background,info_panel_container_height,info_panel_container_width,0,map_panel_container_width);
  wborder(info_panel_container,0,0,0,0,0,0,0,0);
  WINDOW *info_panel = derwin(info_panel_container,info_panel_height,info_panel_width,1,1);

  // User locator variables
  int x = map_width/2, y = map_height/2;

  // Initialize loop
  loop(map_panel, info_panel, y, x);

  return 0;
}

int main() {
  //char *working_directory
  //sprintf(working_directory, "home/%s", USER);
  panel_display();
  endwin();
  return 0;
}
