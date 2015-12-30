
#include "../include/mod_load.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *load_file(char *file)
{
  FILE* fp = fopen(file, "rb"); // 应该二进制读
  fseek(fp , 0 , SEEK_END);
  int file_size = ftell(fp);
  fseek(fp , 0 , SEEK_SET);
  char* tmp = (char*)malloc((file_size + 1) * sizeof(char));
  fread(tmp , file_size , sizeof(char) , fp);
  tmp[file_size ] = '\0'; // 应该封闭掉
  printf("%s" , tmp);
  fclose(fp);
  return tmp;//记得free
}



void Load_configuration_file(Configuration *p)
{
     p->flag = 0;
     const char filename[] = "./lwsfc.conf"; //文件名
     FILE *fp;
     char StrLine[1024];             //每行最大读取的字符数
     if((fp = fopen(filename,"r")) == NULL) //判断文件是否存在及可读
     {
         fprintf(stderr, "SHIBAI\n");
         //写入log
     }

     while (!feof(fp))
     {
         fgets(StrLine,1024,fp);  //读取一行
         if(StrLine[0] == '#'||StrLine[0] == '\n')
          continue;

// 读取配置文件


          if(strcmp(StrLine,"[DefaultDirectory]\n") == 0){
            while(1){
            fgets(StrLine,1024,fp);
            if(StrLine[0] == '#'||StrLine[0] == '\n')
             continue;
             if(StrLine[strlen(StrLine) - 2] == '/')
              StrLine[strlen(StrLine) - 2] = 0;
              else StrLine[strlen(StrLine) - 1] = 0;
            strcpy(p->DefaultDirectory,StrLine);
            break;
            }
          }
          if(strcmp(StrLine,"[DefaultIndex]\n") == 0){
            while(1){
            fgets(StrLine,1024,fp);
            if(StrLine[0] == '#'||StrLine[0] == '\n')
             continue;
            StrLine[strlen(StrLine) - 1] = 0;
            strcpy(p->DefaultIndex,StrLine);
            break;
            }
          }



          if(strcmp(StrLine,"[Port]\n") == 0){
            while(1){
            fgets(StrLine,1024,fp);
            if(StrLine[0] == '#'||StrLine[0] == '\n')
             continue;
            StrLine[strlen(StrLine) - 1] = 0;
            p->Port = atoi(StrLine);
            break;
            }
          }


     }


     fclose(fp);                     //关闭文件
   }
