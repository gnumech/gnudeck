#include <stdio.h>
#include <stdlib.h>

      /////////////////////////////////
        // Gather constant information //
          // CHANGE HERE AS DESIRED      //
            /////////////////////////////////

int main() {
  char *USER = getenv("USER");
  int lines = atoi(getenv("LINES"));
  int columns = atoi(getenv("COLUMNS"));

  int map_height = 100;
  int map_width = 100;
  int map_panel_height = 3*lines/5;
  int map_panel_width = (columns/2);
  int term_panel_height = (2*lines/5)-3;
  int term_panel_width = columns-2;
  int info_panel_height = 3*lines/5;
  int info_panel_width = columns/2 - 3;
  char *symb_user = "@";
  char *symb_tile = ".";

  // Create constants.h file
  FILE *constants_file = fopen("src/constants.h","w+");
  fprintf(constants_file,"#ifndef CONSTANTS_H\n#define CONSTANTS_H\n\n/* Server parameters */\n\n// Panel dimensions\n");
  fprintf(constants_file,"int map_height = %d;\n", map_height);
  fprintf(constants_file,"int map_width = %d;\n", map_width);
  fprintf(constants_file,"int map_panel_height = %d;\n", map_panel_height);
  fprintf(constants_file,"int map_panel_width = %d;\n", map_panel_width);
  fprintf(constants_file,"int map_panel_container_height = %d;\n", map_panel_height+2);
  fprintf(constants_file,"int map_panel_container_width = %d;\n", map_panel_width+2);
  fprintf(constants_file,"int term_panel_height = %d;\n", term_panel_height);
  fprintf(constants_file,"int term_panel_width = %d;\n", term_panel_width);
  fprintf(constants_file,"int term_panel_container_height = %d;\n", term_panel_height+2);
  fprintf(constants_file,"int term_panel_container_width = %d;\n", term_panel_width+2);
  fprintf(constants_file,"int info_panel_height = %d;\n", info_panel_height);
  fprintf(constants_file,"int info_panel_width = %d;\n", info_panel_width);
  fprintf(constants_file,"int info_panel_container_height = %d;\n", info_panel_height+2);
  fprintf(constants_file,"int info_panel_container_width = %d;\n\n", info_panel_width+2);
  fprintf(constants_file,"/* Object symbols */\n");
  fprintf(constants_file,"char *symb_user = \"%s\";\n",symb_user);
  fprintf(constants_file,"char *symb_tile = \"%s\";\n\n",symb_tile);
  fprintf(constants_file,"#endif /* CONSTANTS_H */");
  fclose(constants_file);

  return 0;
}
