//this file is for testing certain function only:)))
#include <iostream>

using namespace std;
class arr {
    public:
    int x = 0;
    arr(){
        cout << "construc arr"<< endl;
    }
    void print() {cout << "No Print" << endl;}
    void push() {cout << "No Push" << endl;}
    ~arr() {cout << "destruc arr"<< endl;}
};

arr* arrInc(arr* obj ,int& currentSize) {
    arr* temp = new arr[currentSize+1];
    for(int i = 0; i < currentSize; i++) {
        temp[i] = obj[i];
    }
    delete[] obj;
    currentSize += 1;
    return temp;
}

int main() {
    int amount = 1;
    arr* arrys = new arr[1];
    arrys[0].x = 9;
    cout << "------------------" << endl;
    arrys = arrInc(arrys,amount);
    cout << "------------------" << endl;
    cout << arrys[0].x << endl;
    delete[] arrys;
    return 0;
}