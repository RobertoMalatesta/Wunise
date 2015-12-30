#ifndef _CGIPARAMETER_H_
#define _CGIPARAMETER_H_
#include <map>
#include <string>
#include <utility>
#include <cstdlib>
namespace CGI {
    char* GetParameter();


class Parameter{

public:



    Parameter():map(),str(std::string(getenv("QUERY_STRING"))){Push();}
    Parameter(const std::string &_str):map(),str(_str){Push();}
    Parameter(const Parameter &r):map(r.map),str(r.str){Push();}

    const char *getvalue(const std::string &_str);
    const char *getkey(const std::string &_str);


private:
    void Push();
    void PushinMap(const std::string &);

    std::map <std::string,std::string> map;
    std::string str;


};
}

#endif // CGIPARAMETER

