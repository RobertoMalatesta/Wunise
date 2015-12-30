#include "../include/mod_send.h"
#include "../include/mod_time.h"
#include "../include/mod_load.h"
#include "../version.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
int get_file_size(char *filename)
{
    FILE *fp=fopen(filename,"r");
    if(!fp) return 0;
    fseek(fp,0L,SEEK_END);
    int size=ftell(fp);
    fclose(fp);

    return size;
}
char *myitoa(int i)
{
  static char str[12] = {0};
  sprintf(str, "%d", i);
  return str;
}
void create_res(int client,char *path)
{
  char res[1024] = {0};
  send_date(client);
  strcat(res,SERVERVERSION);
  strcat(res,"Content-Length:");
  strcat(res,myitoa(get_file_size(path)));
  strcat(res,"\r\n");
  strcat(res,"Content-Type: text/html;charset=UTF-8\r\n");
  strcat(res,"Pragma: no-cache\r\n\r\n");
  send(client,res,strlen(res),0);


}
int get_cgi_size(char *path)        //lim ：最大行长度
{
	char * p =
	load_file(path);
	int len = strlen(p), flag = 0, z = 0;
	
	for(int i = 0;i < len; ++i){
		if(flag == 1){
			++z;
		}
		if(p[i] == '\n' &&p[i - 2] == '\n'){
			flag = 1;
		}
	}	
	free(p);
	return z;
 }         
void create_cgi_res(int client,char *path)
{
  char res[1024] = {0};
  send_date(client);
  strcat(res,SERVERVERSION);
  strcat(res,"Content-Length:");
  strcat(res,myitoa(get_cgi_size(path)));
  strcat(res,"\r\n");
  strcat(res,"Pragma: no-cache\r\n");
  send(client,res,strlen(res),0);
}
