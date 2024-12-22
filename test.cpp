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
class base2{
    arr obj;
    public:
    base2(){
        cout << "construc base2"<< endl;
    }
    void push() {
        cout << "push  meee"<< endl;
    }
    ~base2() {cout << "destruc base2"<< endl;}
};

int main() {
    
    base2 obj;
    return 0;
}