#ifndef _CGIERROR_H_
#define _CGIERROR_H_

#include <string>

namespace CGI{

class Exception{
public:
    Exception() noexcept = default;
    Exception(const Exception &r)noexcept:errormessage(r.errormessage){}

    Exception &operator=(const Exception &r) noexcept{errormessage = r.errormessage; return *this;}

    Exception(const char *err) noexcept{errormessage = err;}
    Exception(const std::string &err) noexcept{errormessage = err;}

    virtual ~Exception() = default;
    virtual const char *what() const noexcept;
private:
    std::string errormessage;
};


    void Error(const std::string &);

}

#endif // CGIERROR_H

