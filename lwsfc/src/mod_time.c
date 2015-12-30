    /** 
     * @file mod_time.c 
     * 
     *  
     *  
     * @date 2015-12-27
     */       
#include <stdio.h> 
#include <string.h> 
#include <time.h>  
#include <sys/socket.h>
#include "../include/mod_time.h"
    void send_date(int client)  
    {  
        time_t time_utc;  
        struct tm tm_local;  
      
        // Get the UTC time  
        time(&time_utc);  
      
        // Get the local time  
        // Use localtime_r for threads safe  
        localtime_r(&time_utc, &tm_local);  
      
        time_t time_local;  
        struct tm tm_gmt;  
      
        // Change tm to time_t   
        time_local = mktime(&tm_local);  
      
        // Change it to GMT tm  
        gmtime_r(&time_utc, &tm_gmt);  
      
        int time_zone = tm_local.tm_hour - tm_gmt.tm_hour;  
        if (time_zone < -12) {  
            time_zone += 24;   
        } else if (time_zone > 12) {  
            time_zone -= 24;  
        }  
      
        char cur_time[256];  
        
      
        strftime(cur_time,256, "Date: %a, %d %b %Y %H:%M:%S GMT\r\n", &tm_gmt);  
	
      	send(client,cur_time,strlen(cur_time),0);
  	printf("%s",cur_time);
    }  
