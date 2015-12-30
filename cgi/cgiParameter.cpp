#include "cgiParameter.h"
#include <iostream>
char *CGI::GetParameter(){
    return getenv("QUERY_STRING");
}
void
CGI::Parameter::Push(){

    std::string::size_type n = 0;int f = 0, t = 0;
    while(1){
        n = str.find('&',n);
        if(n == std::string::npos)
            break;
        else {
            for(t = 0;str[f+t] != '&'; ++t) ;
             PushinMap(str.substr(f,t));
            f = ++n;
        }
    }
    PushinMap(str.substr(f));
}
void
CGI::Parameter::PushinMap(const std::string &str){
    int n = str.find('=',0);
    std::string first = str.substr(0,n);
    std::string second = str.substr(n+1);
    map.insert(std::map<std::string,std::string>::value_type(first,second));
}
const char *CGI::Parameter::getvalue(const std::string &_str){
    return map[_str].c_str();
}
const char *CGI::Parameter::getkey(const std::string &_str){
     std::map<std::string,std::string>::iterator p = map.begin();
     for(;p!=map.end(); ++p){
         if(p->second == _str){
             break;
         }
     }return p->first.c_str();
 }
