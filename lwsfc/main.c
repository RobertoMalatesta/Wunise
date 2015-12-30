
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <errno.h>
#include "./include/mod_load.h"
#include "./include/mod_conf.h"
#include "./include/mod_log.h"
#include "./include/mod_path.h"
#include "./include/mod_send.h"
#include "./include/mod_page.h"
#include "./include/mod_method.h"
#include "version.h"

static int count = 0;

#define ISspace(x) isspace((int)(x))
int get_line(int sock, char *buf, int size)
{
    int i = 0;
    char c = '\0';
    int n;

    /*把终止条件统一为 \n 换行符，标准化 buf 数组*/
    while ((i < size - 1) && (c != '\n'))
    {
        /*一次仅接收一个字节*/
        n = recv(sock, &c, 1, 0);
        /* DEBUG printf("%02X\n", c); */
        if (n > 0)
        {
            /*收到 \r 则继续接收下个字节，因为换行符可能是 \r\n */
            if (c == '\r')
            {
                /*使用 MSG_PEEK 标志使下一次读取依然可以得到这次读取的内容，可认为接收窗口不滑动*/
                n = recv(sock, &c, 1, MSG_PEEK);
                /* DEBUG printf("%02X\n", c); */
                /*但如果是换行符则把它吸收掉*/
                if ((n > 0) && (c == '\n'))
                    recv(sock, &c, 1, 0);
                else
                    c = '\n';
            }
            /*存到缓冲区*/
            buf[i] = c;
            i++;
        }
        else
            c = '\n';
    }
    buf[i] = '\0';
    printf("%s\n",buf);
    /*返回 buf 数组大小*/
    return(i);
}
void accept_request(int client,  Configuration *conf)
{
char buf[1024];
char method[255];
char url[255];
char path[512],cgi_method_path[256];
size_t i, j;
char *query_string = NULL;
char *file;


/*得到请求的第一行*/
get_line(client, buf, sizeof(buf));
i = 0; j = 0;
/*把客户端的请求方法存到 method 数组*/
while (!ISspace(buf[j]) && (i < sizeof(method) - 1))
{
    method[i] = buf[j];
    i++; j++;
}
method[i] = '\0';




      /*读取 url 地址*/
i = 0;
while (ISspace(buf[j]) && (j < sizeof(buf)))
    j++;
while (!ISspace(buf[j]) && (i < sizeof(url) - 1) && (j < sizeof(buf)))
{
    /*存下 url */
    url[i] = buf[j];
    i++; j++;
}
url[i] = '\0';


//以下为响应与输出

//预处理get中的cgi
    if (strcasecmp(method, "GET") == 0)  
    {  
        /* 待处理请求为 url */  
        query_string = url;  
        while ((*query_string != '?') && (*query_string != '\0'))  
            ++query_string;  
        /* GET 方法特点，? 后面为参数*/  
        if (*query_string == '?')  
        {  
            /*开启 cgi */  
          
            *query_string = '\0';  
            ++query_string;

	    setenv("QUERY_STRING",query_string,1);//cgi 的方法。
	    FILE *fptr = fopen(to_local_path(url,conf),"r");
		if(fptr){
		strcpy(cgi_method_path,to_local_path(url,conf));
		strcat(cgi_method_path, ">/var/log/lwsfc/cgi/temp-");
		strcat(cgi_method_path, myitoa(count++));
		system(cgi_method_path);
       		char cgi_file[256] = {"/var/log/lwsfc/cgi/temp-"};
        	file = load_file(strcat(cgi_file, myitoa(count-1)));
		if(get_file_size(cgi_file) != 0)
        	send(client,"HTTP/1.1 200 OK\r\n",strlen("HTTP/1.1 200 OK\r\n"),0);
		else goto error;
        	create_cgi_res(client,cgi_file);
        	send(client,file,get_file_size(cgi_file),0);
		free(file);
		close(client);
		fclose(fptr);
		return;
		}else{
		 	if(0){
			error:fclose(fptr);
			free(file);}
		send(client,"HTTP/1.1 404 not found\r\n",strlen("HTTP/1.1 404 not found\r\n"),0);
		page404(client);
		close(client);
		return;
		}
        }  
    }  


if (strcasecmp(method, "GET") && strcasecmp(method, "HEAD"))
  {
      send(client,"HTTP/1.1 405 Method not allowed\r\n",strlen("HTTP/1.1 405 Method not allowed\r\n") ,0);
      unimplemented_page(client);
      close(client);
      return;
  }

/*options 的一个单例*/
if( (strcasecmp(url, "*") == 0) && (strcasecmp(method, "OPTIONS") == 0)){
	send(client,"HTTP/1.1 200 OK\r\n",strlen("HTTP/1.1 200 OK\r\n") ,0);
	send_options_res_by_urlstar(client);
	close(client);
	return;
}
/*判断url和method*/
FILE *fp = fopen(to_local_path(url,conf),"r");
if(fp && (strcasecmp(method, "GET") == 0)){
        if(conf->flag == 0){
        fclose(fp);
        send(client,"HTTP/1.1 200 OK\r\n",strlen("HTTP/1.1 200 OK\r\n") ,0);
        create_res(client,to_local_path(url,conf));
        file = load_file(to_local_path(url,conf));
        send(client,file,get_file_size(to_local_path(url,conf)),0);
        free(file);
	close(client);} //free 防泄漏
        else{
        fclose(fp);
        send(client,"HTTP/1.1 404 not found\r\n",strlen("HTTP/1.1 404 not found\r\n"),0);
        create_res(client,to_local_path(url,conf));
        file = load_file(to_local_path(url,conf));
        send(client,file,get_file_size(to_local_path(url,conf)),0);
        free(file);
	close(client);
        }
}else if(fp && (strcasecmp(method, "HEAD") == 0)){  //head method
	if(conf->flag == 0){
        fclose(fp);
        send(client,"HTTP/1.1 200 OK\r\n",strlen("HTTP/1.1 200 OK\r\n"),0);
        create_res(client,to_local_path(url,conf));
        file = load_file(to_local_path(url,conf));
        free(file);
	close(client);} //free 防泄漏
        else{
        fclose(fp);
        send(client,"HTTP/1.1 404 not found\r\n",strlen("HTTP/1.1 404 not found\r\n"),0);
        create_res(client,to_local_path(url,conf));
        file = load_file(to_local_path(url,conf));
        free(file);
	close(client);
        }
}else if(fp && (strcasecmp(method, "OPTIONS") == 0)){
	if(conf->flag == 0){
        fclose(fp);
        send(client,"HTTP/1.1 200 OK\r\n",strlen("HTTP/1.1 200 OK\r\n"),0);
	//method 方法
	send_options_res(client);
	close(client);} //free 防泄漏
	else{
        fclose(fp);
        send(client,"HTTP/1.1 404 not found\r\n",strlen("HTTP/1.1 404 not found\r\n"),0);
	send_options_res(client);
	close(client);
        }
}else{
{
	send(client,"HTTP/1.1 404 not found\r\n",strlen("HTTP/1.1 404 not found\r\n"),0);
	page404(client);
	close(client);
	}
}
}


void error_die(const char *sc)
{
    /*出错信息处理 */
    perror(sc);
    exit(1);
}


int startup(u_short port)
{
    int httpd;
    struct sockaddr_in name;

    /*建立 socket */
    httpd = socket(AF_INET, SOCK_STREAM, 0);
    if (httpd < 0)
        error_die("socket");
    bzero(&name, sizeof(name));
    name.sin_family = AF_INET;

    name.sin_addr.s_addr = htonl(INADDR_ANY);

		name.sin_port = htons(port);
    if(bind(httpd, (struct sockaddr *)&name, sizeof(name)) < 0)
        error_die("bind");
    /*如果当前指定端口是 0，则动态随机分配一个端口*/
    //if (port == 0)  /* if dynamically allocating a port */
    //{
    //    socklen_t namelen = sizeof(name);
    //    if (getsockname(httpd, (struct sockaddr *)&name, &namelen) == -1)
    //        error_die("getsockname");
    //    port = ntohs(name.sin_port);
    //}
    /*开始监听*/
    if (listen(httpd, 5) < 0)
        error_die("listen");
    /*返回 socket id */
    return(httpd);
}
int main()
{
    int server_sock = -1;
    int client_sock = -1;
    struct sockaddr_in client_name;
    socklen_t client_name_len = sizeof(client_name);

    Configuration conf;
    create_log();
    Load_configuration_file(&conf);

    server_sock = startup((u_short)conf.Port);


    for(;;){
      client_sock = accept(server_sock,(struct sockaddr *)&client_name,&client_name_len);
        if (client_sock == -1)
            error_die("accept");
      accept_request(client_sock,&conf);
      output_log(0);
    }

}
