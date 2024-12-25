//this file is for testing certain function only:)))
#include <iostream>

using namespace std;
class arr {
    public:
    int **arr2d;
    arr(){
        cout << "construc arr"<< endl;
    }
    void print() {cout << "No Print" << endl;}
    void push() {cout << "No Push" << endl;}
    ~arr() {
        for(int i = 0; i < 4; i++) {
            delete[] arr2d[i];
        }
        delete[] arr2d;
        cout << "destruct successful";
    }
};

int main() {
    arr** doublePointer = new arr*[4];
    for(int i = 0; i < 4; i++) {
        doublePointer[i] = new arr[4];
    }
    doublePointer[3][3].print();
    return 0;
}