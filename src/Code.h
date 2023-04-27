#ifndef FILE_ORIENTED_CODE_H
#define FILE_ORIENTED_CODE_H

#include <string>

class Code {
    friend class Interpreter;
public:
    virtual void execute () = 0;

protected:
    int type{};
    int number{};

private:
    static int identify_name (std::string &name);
};

class Load : public Code {

};

#endif //FILE_ORIENTED_CODE_H
