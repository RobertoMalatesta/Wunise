#include "../include/mod_conf.h"
#include "../include/mod_path.h"
#include <stdio.h>
#include <string.h>
#include <dirent.h>
char* to_local_path(char *url, Configuration *p)
{

  DIR *dirptr;
  FILE *fp;
  strcpy(p->Path,p->DefaultDirectory);
  strcat(p->Path,url);

  if((dirptr = opendir(p->Path))){
    if((p->Path)[strlen(p->Path) - 1] == '/'){
      strcat(p->Path,p->DefaultIndex);
      if((fp = fopen(p->Path,"r"))){
	p->flag = 0;
        fclose(fp);
        closedir(dirptr);
        return p->Path;
      }else{
        p->flag = 1;
        closedir(dirptr);
        strcpy(p->Path,p->DefaultDirectory);
        return strcat(p->Path,"/404.html");
      }
    }else {
      (p->Path)[strlen(p->Path)] = '/';
      (p->Path)[strlen(p->Path)+1] = 0;
      strcat(p->Path,p->DefaultIndex);
      if((fp = fopen(p->Path,"r"))){
	p->flag = 0;
        fclose(fp);

        return p->Path;
      }else{
        p->flag = 1;

        strcpy(p->Path,p->DefaultDirectory);
        return strcat(p->Path,"/404.html");
      }
    }
  }



  else{
    if((fp = fopen(p->Path,"r"))){
      p->flag = 0;
      fclose(fp);
      return p->Path;
    }else{
      p->flag = 1;
      strcpy(p->Path,p->DefaultDirectory);

      return strcat(p->Path,"/404.html");
    }
  }
}
