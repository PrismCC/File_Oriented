#ifndef FILE_ORIENTED_REGISTER_H
#define FILE_ORIENTED_REGISTER_H

enum class R_Type{
    R1,R2,R3,R4,PC,LF
};

class Register {
public:
    [[nodiscard]] R_Type get_id () const { return id; };

    [[nodiscard]] int read_data () const { return data; };

    void write_data (const int x) { data = x; };

private:
    R_Type id;
    int data;
};


#endif //FILE_ORIENTED_REGISTER_H
