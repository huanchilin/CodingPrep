
#include <iostream>
#include <array>
#include <vector>
#include <queue>
using namespace std;

int main() {

    char test[] = "rzrr";
    for (int i = 0; test[i]; i++) {
        if (test[i] == 'z')
            cout<<"gotcha" << endl;
        cout<< test[i] << " ";
    }
    cout<<endl;

    std::queue<std::pair<int, int>> testt;


    return 0;
}