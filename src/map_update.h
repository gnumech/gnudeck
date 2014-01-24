#ifndef MAP_UPDATE_H
#define MAP_UPDATE_H

#include <curses.h>
#include "constants.h"

int map_panel_display(WINDOW *map_panel, int y, int x) {
  // Declare position variables
  int map_panel_leftmost, map_panel_topmost;

  // Center about x
  if ( x < map_panel_width/2 )
    map_panel_leftmost = 0;
  if ( ( x >= map_panel_width/2 ) && ( x < map_width - map_panel_width/2 ) )
    map_panel_leftmost = x - map_panel_width/2;
  if ( x >= map_width - map_panel_width/2 )
    map_panel_leftmost = map_width - map_panel_width+1;

  // Center about y
  if ( y < map_panel_height/2 )
    map_panel_topmost = 0;
  if ( ( y >= map_panel_height/2 ) && ( y <= map_height - map_panel_height/2 ) )
    map_panel_topmost = y - (int)(map_panel_height/2);
  if ( y > map_height - map_panel_height/2 )
    map_panel_topmost = map_height - map_panel_height;

  // Refresh
  prefresh(map_panel,map_panel_topmost,map_panel_leftmost,1,1,map_panel_height,map_panel_width);

  return 0;
}

#endif /* MAP_UPDATE_H */
