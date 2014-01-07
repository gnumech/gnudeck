#ifndef LOG_NOTICE_H
#define LOG_NOTICE_H
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int log_notice(char *log_message) {
  char *home_directory = getenv("HOME"), gnudeckrc_file[100], parsed_line[100], *log_file_name; int i;
  sprintf(gnudeckrc_file,"%s/.gnudeckrc",home_directory); FILE *fp = fopen(gnudeckrc_file,"r");
  while ( strstr(parsed_line,"LOG_FILE=") == NULL ) fgets(parsed_line,100,fp); fclose(fp);
  log_file_name = strtok(parsed_line,"="); log_file_name = strtok(NULL,"=");
  for (i=0; i<100; i++) if ( (int)log_file_name[i] == '\n' ) {log_file_name[i] = '\0'; break;}
  FILE *log_file_object = fopen(log_file_name,"a");
  fprintf(log_file_object,"Time: %s\n",log_message); // FIX: Modify to be current time
  fclose(log_file_object);
  return 0;
}

#endif /* LOG_NOTICE_H */
