#ifndef INSTALL_H
#define INSTALL_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include "log_notice.h"
#include "display.h"
#include "coord_func.h"

int gnudeck_installation() {
  // Identify /home/USER/.bashrc
  printf("Accessing $HOME/.bashrc... ");
  char *home_directory = getenv("HOME");
  const int config_filename_len = strlen(home_directory)+8;
  char config_file[config_filename_len];
  sprintf(config_file,"%s/.bashrc",home_directory);
  printf("Done.\n");

  // Allow accessibility to window width and height
  printf("Exporting window dimensions... ");
  FILE *config_file_object = fopen(config_file,"a");
  fprintf(config_file_object,"\n\n## PGM-SDS add-on ##\nexport COLUMNS LINES\n####################");
  fclose(config_file_object);
  printf("Done.\n");

  // Create gnudeck directory, logfile and .gnudeckrc for configuration specifics
  char gnudeck_directory[100], rc_file_name[100]; int i; DIR *dir; bool bad_pathname = true;
  while ( bad_pathname == true ) { // Read from stdin, tries again if not directory
    bad_pathname = false;
    printf("Pathname for gnudeck directory location? (default %s): ",home_directory);
    fgets(gnudeck_directory,100,stdin);
    for ( i=0; i<100; i++ ) if ( gnudeck_directory[i] == '\n' ) {gnudeck_directory[i] = '\0'; break;}
    if ( *gnudeck_directory == '\0' ) sprintf(gnudeck_directory,"%s/gnudeck",home_directory);
    else if ( !(dir=opendir(gnudeck_directory)) ) { printf("\"%s\" is not a valid directory\n",gnudeck_directory); bad_pathname = true; }
  }
  if ( gnudeck_directory[i-1] == '/' ) gnudeck_directory[i-1] = '\0'; // Truncates trailing '/' if exists
  mkdir(gnudeck_directory, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
  sprintf(rc_file_name,"%s/.gnudeckrc",home_directory);
  config_file_object = fopen(rc_file_name,"w");
  fprintf(config_file_object,"install_complete=true\nlog_file=%s/notices.log",gnudeck_directory);
  fclose(config_file_object);
  log_notice("Log file and ~/.gnudeck initialized from installation.");

  // Construct user and display folder hierarchy (/gnudeck/home/user/, /gnudeck/display/user)
  printf("Constructing utility folder hierarchy... ");
  const int user_home_directory_len = strlen(gnudeck_directory)+5, user_display_directory_len = strlen(gnudeck_directory)+8;
  char user_home_directory[user_home_directory_len], user_display_directory[user_display_directory_len];
  sprintf(user_home_directory,"%s/home",gnudeck_directory);
  sprintf(user_display_directory,"%s/display",gnudeck_directory);
  mkdir(user_home_directory, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
  mkdir(user_display_directory, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
  printf("Done.\n");
  
  printf("Gnudeck has been successfully installed, please check out the README for usage infomation.\n\n");
  return 0;
}

int user_initialization(char *gnudeck_directory, char *user_mode) {
  // Define parameters
  int screen_width = atoi(getenv("COLUMNS")), screen_height = atoi(getenv("LINES"));
  char user_disp_dir_name[100], user_home_dir_name[100], user_screen_file[100], user_selfcoord_file[100], user_dircoord_file[100];
  sprintf(user_home_dir_name,"%s/home/%s",gnudeck_directory,user_mode);
  sprintf(user_disp_dir_name,"%s/display/%s",gnudeck_directory,user_mode);
  sprintf(user_screen_file,"%s/screen",user_disp_dir_name);
  sprintf(user_selfcoord_file,"%s/selfcoord",user_disp_dir_name);
  sprintf(user_dircoord_file,"%s/dircoord",user_disp_dir_name);

  // Construct directory for user in ~/gnudeck/home/$USER
  mkdir(user_disp_dir_name, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
  mkdir(user_home_dir_name, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
  FILE *user_selfcoord_file_stream = fopen(user_selfcoord_file,"w+");
  fprintf(user_selfcoord_file_stream,"NAME=%s\nx=%d\ny=%d\n",user_mode,screen_width/2,screen_height/2);
  fclose(user_selfcoord_file_stream);
  FILE *user_dircoord_file_stream = fopen(user_dircoord_file,"w+");
  fprintf(user_dircoord_file_stream,"NAME=..\nx=%d\ny=%d",((screen_width/2)+1),screen_height/2);
  fclose(user_dircoord_file_stream);

  // Paint display with template
  blank_canvas(user_mode);
  objects_refresh(gnudeck_directory, user_mode);

  return 0;
}

#endif /* INSTALL_H */
