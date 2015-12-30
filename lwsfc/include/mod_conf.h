#ifndef __CONF_H____
#define __CONF_H____
typedef struct configuration{
   char DefaultIndex[256];
   char DefaultDirectory[256];
   int  Port;
   char Path[512];
   int  flag;
}Configuration;

#endif
