#include "../include/mod_method.h"
#include "../include/mod_time.h"
#include "../version.h"
#include <sys/socket.h>
void send_options_res(int client)
{

  send_date(client);
  send(client,SERVERVERSION,sizeof(SERVERVERSION) - 1,0);
  send(client,"Allow: GET HEAD OPTIONS\r\n",sizeof"Allow: GET HEAD OPTIONS\r\n" - 1, 0);
  send(client,"Content-Length: 0\r\n",sizeof"Content-Length: 0\r\n" - 1,0);
  send(client,"Content-Type: text/html;charset=UTF-8\r\n",sizeof"Content-Type: text/html;charset=UTF-8\r\n" - 1,0);
  send(client,"Pragma: no-cache\r\n\r\n",sizeof"Pragma: no-cache\r\n\r\n" - 1, 0);
}
void send_options_res_by_urlstar(int client)
{

  send_date(client);
  send(client,SERVERVERSION,sizeof(SERVERVERSION) - 1,0);
  send(client,"Allow: GET HEAD OPTIONS\r\n",sizeof"Allow: GET HEAD OPTIONS\r\n" - 1, 0);
  send(client,"Content-Length: 0\r\n",sizeof"Content-Length: 0\r\n" - 1,0);
  send(client,"Content-Type: text/html;charset=UTF-8\r\n",sizeof"Content-Type: text/html;charset=UTF-8\r\n" - 1,0);
  send(client,"Pragma: no-cache\r\n\r\n",sizeof"Pragma: no-cache\r\n\r\n" - 1, 0);
}
