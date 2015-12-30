#ifndef _CGIFILE_H_
#define _CGIFILE_H_
#include <string>
#include <fstream>
#include <vector>
namespace CGI {

class File{
    friend bool LoadFile(File &);
    template <typename ...All>
    friend void PushVariable(File &, const std::string & ,All...);
    friend void PushVariable(File &);
    friend void ReplaceVariable(File &);
    friend void PrintFile(File &);
    friend void CloseFile(File &);
public:
    explicit File():in(),str(),vec(),variablenumber(0){in.open("");}
    File(const std::string &filename):in(),str(),vec(),variablenumber(0){in.open(filename);}

    ~File() = default;
private:
    File(const File &);
    File &operator=(const File &);

    std::ifstream in;
    std::string str;
    std::vector<std::string> vec;
    unsigned variablenumber;

    unsigned GetDigitsFromVariablenumber(unsigned _variablenumber){unsigned t=1;while((_variablenumber/=10)!=0)++t;return t;}
};



    bool LoadFile(File &);

    template <typename ...All>
    void PushVariable(File &file,const std::string &str ,All...all){
        file.vec.push_back(str);
        PushVariable(file,all...);
    }
    void PushVariable(File &);

    void ReplaceVariable(File &);

    void PrintFile(File &);
    void CloseFile(File &);




    template <typename ...All>
    void CreateMessageBody(File &file,All...all);

    void PrintMessageBody(File &file);
}

#endif // _CGILOADFILE_H_

