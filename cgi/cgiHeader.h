#ifndef _CGIHEADER_H_
#define _CGIHEADER_H_

#include <string>
#include <vector>


namespace CGI {

enum Response_Header{
    Accept_Rangesm,
    Age,
    Allow,
    Cache_Control,
    Content_Encoding,
    Content_Language,
    Content_Length,
    Content_Location,
    Content_Disposition,
    Content_MD5,
    Content_Range,
    Content_Type,
    Date,
    ETag,
    Expires,
    Last_Modified,
    Link,
    Location,
    Pragma,
    Proxy_Authenticate,
    Refresh,
    Retry_After,
    Server,
    Set_Cookie,
    Trailer,
    Transfer_Encoding,
    Vary,
    Via,
    Warning,
    WWW_Authenticate
};

class Header{
    friend void PrintHeader(Header &p);
    friend void InitHeader(Header &p);
public:
    explicit Header():_header(){} //-1 weichushihua
    Header(const Header &r):_header(r._header){}
    Header &operator= (const Header &r){_header = r._header;return *this;}
    ~Header() = default;

    template <typename A,typename B, typename ...Rest>
    void Push(A p,B &q, Rest ...rest);

    void AddResponseHeader(const std::string&);

private:
    const std::string GenerateResponseHeader(CGI::Response_Header,std::string);
    inline void Push(){}

    std::vector<std::string> _header;

};



void PrintHeader(Header &);

} //CGI

using CGI::Accept_Rangesm;
using CGI::Age;
using CGI::Allow;
using CGI::Cache_Control;
using CGI::Content_Encoding;
using CGI::Content_Language;
using CGI::Content_Length;
using CGI::Content_Location;
using CGI::Content_Disposition;
using CGI::Content_MD5;
using CGI::Content_Range;
using CGI::Content_Type;
using CGI::Date;
using CGI::ETag;
using CGI::Expires;
using CGI::Last_Modified;
using CGI::Link;
using CGI::Location;
using CGI::Pragma;
using CGI::Proxy_Authenticate;
using CGI::Refresh;
using CGI::Retry_After;
using CGI::Server;
using CGI::Set_Cookie;
using CGI::Trailer;
using CGI::Transfer_Encoding;
using CGI::Vary;
using CGI::Via;
using CGI::Warning;
using CGI::WWW_Authenticate;


#endif
