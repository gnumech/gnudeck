#ifndef DISPLAY_H
#define DISPLAY_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "log_notice.h"
#include "install_scripts.h"
#include "coord_func.h"

int directory_room(char *working_directory) {
  printf("Room is %s.\n",working_directory);
  return 0;
}

int construct_display(char *working_directory, char *user_mode) {
  // Define parameters
  char gnudeck_directory[100]; sprintf(gnudeck_directory,"%s",gnudeck_directory_retrieval());
  char user_disp_file_name[100], ch;
  sprintf(user_disp_file_name,"%s/display/%s/screen",gnudeck_directory,user_mode);
  FILE *user_disp_file = fopen(user_disp_file_name,"a");
  if ( user_disp_file == NULL ) user_initialization(gnudeck_directory, user_mode);
  // No need to try to close user_disp_file, it didn't exist in the first place

  // Display file on screen
  objects_refresh(gnudeck_directory,user_mode);
  user_disp_file = fopen(user_disp_file_name,"r");
  //system("clear");
  while ( (ch=fgetc(user_disp_file)) != EOF ) printf("%c",ch);
  fclose(user_disp_file);
  return 0;
}

#endif /* DISPLAY_H */
