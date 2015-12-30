

#include <stdio.h>
#include <time.h>
#include <string.h>
#include "../include/mod_log.h"
void create_log ()
{

    time_t rawtime;
    struct tm *timeinfo;
    char logname[34] = "/var/log/lwsfc/lwsfc.log-",date[9];//lwsfc文件夹将会在conf里创建

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime (date,9,"%Y%m%d",timeinfo);
    strcat(logname,date);
    FILE *fp = fopen(logname,"a");
    fclose(fp);

}
void output_log(int code)
{

  time_t rawtime;
  struct tm *timeinfo;
  char logname[34] = "/var/log/lwsfc/lwsfc.log-",date[9];//lwsfc文件夹将会在makefile里创建

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime (date,9,"%Y%m%d",timeinfo);
  strcat(logname,date);
  FILE *fp = fopen(logname,"a");


  time_t timep;
  time (&timep);


  char p[32];
  strcpy(p,ctime(&timep));
  p[strlen(p)- 1] = 0;
  fprintf(fp,"[%s]: %d\n",p,code);

  fclose(fp);

}
