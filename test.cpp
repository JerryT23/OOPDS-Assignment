//this file is for testing certain function only:)))
#include <iostream>

using namespace std;
class arr {
    public:
    arr(){
        cout << "construc arr"<< endl;
    }
    virtual void print() {cout << "No Print" << endl;}
    virtual void push() {cout << "No Push" << endl;}
    virtual ~arr() {cout << "destruc arr"<< endl;}
};
class boom : virtual public arr {
    public:
    boom(){
        cout << "construc boom"<< endl;
    }
    virtual void print() = 0;
    virtual ~boom() {cout << "destruc boom"<< endl;}
};
class man : virtual public arr {
    public:
    man(){
        cout << "construc man"<< endl;
    }
    virtual void push() = 0;
    virtual ~man() {cout << "destruc man"<< endl;}
};
class base : public boom {
    public:
    base(){
        cout << "construc base"<< endl;
    }
    void print() {
        cout << "print  meee"<< endl;
    }
    ~base() {cout << "destruc base"<< endl;}
};

int main() {
    arr* arrys = new base;
    arrys->push();
    arrys->print();
    delete arrys;

    return 0;
}