#ifndef SEND_H___
#define SEND_H___
int get_file_size(char *filename);
char *myitoa(int i);
void create_res(int client,char *path);
void create_cgi_res(int client,char *path);
int get_cgi_size(char *path) ;
#endif
