#include "cgiHeader.h"
#include <iostream>
#include <cstdlib>


const std::string CGI::Header::GenerateResponseHeader(CGI::Response_Header p, std::string q){
    switch (p) {
    case Accept_Rangesm: return "Accept-Rangesm: " + q + "\r\n";
    case Age:return "Age: " + q + "\r\n";
    case Allow:return "Allow: " + q + "\r\n";
    case Cache_Control:return "Cache-Control: " + q + "\r\n";
    case Content_Encoding:return "Content-Encoding: " + q + "\r\n";
    case Content_Language:return "Content-Language: " + q + "\r\n";
    case Content_Length:return "Content-Length: " + q + "\r\n";
    case Content_Location:return "Content-Location: " + q + "\r\n";
    case Content_Disposition:return "Content-Disposition: " + q + "\r\n";
    case Content_MD5:return "Content-MD5: " + q + "\r\n";
    case Content_Range:return "Content-Range: " + q + "\r\n";
    case Content_Type:return "Content-Type: " + q + "\r\n";
    case Date:return "Date: " + q + "\r\n";
    case ETag:return "ETag: " + q + "\r\n";
    case Expires:return "Expires: " + q + "\r\n";
    case Last_Modified:return "Last-Modified: " + q + "\r\n";
    case Link:return "Link: " + q + "\r\n";
    case Location:return "Location: " + q + "\r\n";
    case Pragma:return "Pragma: " + q + "\r\n";
    case Proxy_Authenticate:return "Proxy-Authenticate: " + q + "\r\n";
    case Refresh:return "Refresh: " + q + "\r\n";
    case Retry_After:return "Retry-After: " + q + "\r\n";
    case Server:return "Server: " + q + "\r\n";
    case Set_Cookie:return "Set-Cookie: " + q + "\r\n";
    case Trailer:return "Trailer: " + q + "\r\n";
    case Transfer_Encoding:return "Transfer-Encoding: " + q + "\r\n";
    case Vary:return "Vary: " + q + "\r\n";
    case Via:return "Via: " + q + "\r\n";
    case Warning:return "Warning: " + q + "\r\n";
    case WWW_Authenticate: return "WWW_Authenticate: " + q + "\r\n";
    }
    return q;
}

void CGI::Header::AddResponseHeader(const std::string &p){

    _header.push_back(p+"\r\n");
}


template <typename A,typename B, typename ...Rest>
void CGI::Header::Push(A p,B &q, Rest ...rest){

    _header.push_back(GenerateResponseHeader(p,q));
    Push(rest...);
}
void CGI::PrintHeader(Header &p){

    for(std::vector<std::string>::iterator i = p._header.begin()
        ;i != p._header.end(); ++i){
        std::cout << *i;
    }
    std::cout << "\n";
}



