#ifndef FILE_ORIENTED_REGISTER_H
#define FILE_ORIENTED_REGISTER_H

class Register {
public:
    [[nodiscard]] int get_id () const { return id; };

    [[nodiscard]] long long read_data () const { return data; };

    void write_data (const long long x) { data = x; };

private:
    int id;
    long long data;
};


#endif //FILE_ORIENTED_REGISTER_H
