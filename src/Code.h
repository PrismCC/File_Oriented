#ifndef FILE_ORIENTED_CODE_H
#define FILE_ORIENTED_CODE_H

#include <string>
#include <map>

class Code {

public:
    static int identify_name (std::string &name);
    static std::string identify_id(int id);
    Code(const std::string& name, const std::map<std::string, int> &label_map);
    void printInfo();
//    virtual void execute () = 0;

protected:
    int type{};
    int number{};
    int para1,para2,para3;
    std::string path;

private:
    static const std::map<std::string,int> name_id_map;
    static const std::map<int,std::string> id_name_map;

};

class Load : public Code {

};

#endif //FILE_ORIENTED_CODE_H
