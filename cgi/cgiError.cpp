#include "cgiError.h"
#include <iostream>
const char *CGI::Exception::what()const noexcept{
    if(errormessage.empty()){
        return "CGI::Exception";
    }
    return ("CGI::Exception "+errormessage).c_str();
}
void CGI::Error(const std::string &str){
    std::cerr << str;
}
