#include "cgiFile.h"
#include <sstream>
#include <iostream>

bool CGI::LoadFile(File &file){

    if(file.in.is_open()){
        std::ostringstream tmp;
        tmp << file.in.rdbuf();
        file.str = tmp.str();
        return true;
    }
    return false;
}
void CGI::PrintFile(File &file){
    std::cout << file.str;
}

void CGI::CloseFile(File &file){
    file.in.close();
}

void CGI::PushVariable(File &){}
void CGI::ReplaceVariable(File &file){
    for(std::vector<std::string>::iterator i = file.vec.begin()
        ;i != file.vec.end(); ++i,++(file.variablenumber)){
        std::stringstream ss;
        ss << file.variablenumber;
        std::size_t n = 0;
        while((n = file.str.find("$cgi["+ss.str()+"]",n)) != std::string::npos){
            file.str.erase(n,6+file.GetDigitsFromVariablenumber(file.variablenumber));
            file.str.insert(n,*i);
        }
    }
}

template <typename ...All>
void CGI::CreateMessageBody(File &file,All...all){
        if(CGI::LoadFile(file)){
            CGI::PushVariable(file,all...);
            CGI::ReplaceVariable(file);
        }else std::cerr << "Failed to open file." << std::endl;
}
void CGI::PrintMessageBody(File &file){
    CGI::PrintFile(file);
}

