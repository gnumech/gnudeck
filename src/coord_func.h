#ifndef COORD_FUNC_H
#define COORD_FUNC_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "log_notice.h"

// Locates pathname of main gnudeck directory
char* gnudeck_directory_retrieval() {
  char *home_directory = getenv("HOME"), gnudeckrc_file[100], parsed_line[100], *parsed_value; int i;
  sprintf(gnudeckrc_file,"%s/.gnudeckrc",home_directory); FILE *fp = fopen(gnudeckrc_file,"r");
  while ( fgets(parsed_line,100,fp) != NULL ) {if ( parsed_line == strstr(parsed_line,"GNUDECK_DIRECTORY=") ) break;}
  fclose(fp);
  sprintf(parsed_value,"%s",strtok(parsed_line,"=")); sprintf(parsed_value,"%s",strtok(NULL,"="));
  for (i=0; i<100; i++) if ( (int)parsed_value[i] == '\n' ) {parsed_value[i] = '\0'; break;}
  return parsed_value;
}

// Create blank display screen in user's directory
int blank_canvas(char *user_mode) {
  char file_path[100], notice_msg[100]; sprintf(notice_msg,"Canvas for %s has been cleared.",user_mode);
  int screen_width = atoi(getenv("COLUMNS")), screen_height = atoi(getenv("LINES")), i,j;
  sprintf(file_path,"%s/display/%s/screen",gnudeck_directory_retrieval(),user_mode);
  FILE *file_stream = fopen(file_path,"w+");
  for (i=0; i<screen_width; i++) fprintf(file_stream,"-"); fprintf(file_stream,"\n");
  for (j=0; j<(screen_height-2); j++) {
    fprintf(file_stream,"|"); for (i=0; i<(screen_width-2); i++) fprintf(file_stream," "); fprintf(file_stream,"|\n");
  }
  for (i=0; i<screen_width; i++) fprintf(file_stream,"-");
  fclose(file_stream);
  log_notice(notice_msg);
  return 0;
}

// Insert character 'c' into 'user_mode's screen at (x,y) (from top-left)
int char_at_coord(char *c, char *user_mode, int x, int y) {
  char file_path[100]; sprintf(file_path,"%s/display/%s/screen",gnudeck_directory_retrieval(),user_mode);
  int file_column=0, file_row=1, i; FILE *file_stream = fopen(file_path,"r+");
  while ( (i = fgetc(file_stream)) != EOF ) {
    if ( i == '\n' ) { ++file_row; file_column = 0; continue;}
    ++file_column;
    if ( file_row == y ) if ( file_column == x) fprintf(file_stream,"%c",*c);
  }
  fclose(file_stream);
  return 0;
}

// Refreshes screen display to most updated symbol locations
int objects_refresh(char *gnudeck_directory, char *user_mode) {
  char self_file[100], dir_file[100], *parsed_self_line, *parsed_dir_line, *parsed_name, *parsed_x, *parsed_y; int i;
  sprintf(self_file,"%s/display/%s/selfcoord",gnudeck_directory,user_mode);
  sprintf(dir_file,"%s/display/%s/dircoord",gnudeck_directory,user_mode);

  // For each name/x/y, grab each and make subdirectory on screen of user_mode
  FILE *fp = fopen(dir_file,"r");
  while ( (int)parsed_dir_line != EOF ) {

   // ERROR IS RIGHT AROUND HERE, HAS TO DO WITH WHILE STATEMENT, CAUSES SEGFAULT

    while ( fgets(parsed_dir_line,100,fp) != NULL ) {if ( parsed_dir_line == strstr(parsed_dir_line,"NAME=") ) break;}
    sprintf(parsed_name,"%s",strtok(parsed_dir_line,"=")); sprintf(parsed_name,"%s",strtok(NULL,"="));
    fgets(parsed_dir_line,100,fp);
    sprintf(parsed_x,"%s",strtok(parsed_dir_line,"=")); sprintf(parsed_x,"%s",strtok(NULL,"="));
    fgets(parsed_dir_line,100,fp);
    sprintf(parsed_y,"%s",strtok(parsed_dir_line,"=")); sprintf(parsed_y,"%s",strtok(NULL,"="));
    char_at_coord("D",user_mode,(int)parsed_x,(int)parsed_y);
  }
  fclose(fp);

  // For each name/x/y, grab each and make symbol on screen of user_mode
  fp = fopen(self_file,"r");
  while ( (int)parsed_self_line != EOF ) {
    while ( fgets(parsed_self_line,100,fp) != NULL ) {if ( parsed_self_line == strstr(parsed_self_line,"NAME=") ) break;}
    sprintf(parsed_name,"%s",strtok(parsed_self_line,"=")); sprintf(parsed_name,"%s",strtok(NULL,"="));
    for (i=0; i<100; i++) if ( (int)parsed_name[i] == '\n' ) {parsed_name[i] = '\0'; break;}
    fgets(parsed_self_line,100,fp);
    sprintf(parsed_x,"%s",strtok(parsed_self_line,"=")); sprintf(parsed_x,"%s",strtok(NULL,"="));
    for (i=0; i<100; i++) if ( (int)parsed_x[i] == '\n' ) {parsed_x[i] = '\0'; break;}
    fgets(parsed_self_line,100,fp);
    sprintf(parsed_y,"%s",strtok(parsed_self_line,"=")); sprintf(parsed_y,"%s",strtok(NULL,"="));
    for (i=0; i<100; i++) if ( (int)parsed_y[i] == '\n' ) {parsed_y[i] = '\0'; break;}
    char_at_coord("@",user_mode,(int)parsed_x,(int)parsed_y);
  }
  fclose(fp);
 
  return 0;
}

#endif /* COORD_FUNC_H */
