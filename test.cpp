//this file is for testing certain function only:)))
#include <iostream>

using namespace std;
class arr {
    public:
    int size;
    int* data;
    arr() {
        size = 1;
        data = new int(3);
    }
    arr(const arr& obj) {
        this->data = new int();
        *data = obj.data
    }
    ~arr() {
        delete data;
    }
    int getData() {
        return *data;
    }

    void setData(int x) {
        *data = x;
    }
};

int main() {
    arr a;
    arr b(a);
    a.setData(5);
    cout << a.getData() << b.getData();

    return 0;
}