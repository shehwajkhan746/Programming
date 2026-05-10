#include <iostream>
using namespace std;

int main() {

    int values[5];

//cout << "Enter " << n << " integers: " << endl;
    for (int i = 0; i < 5; ++i) {
        cin >> values[i];
    }

// cout << "The integers are: ";
    for (int i = 0; i < 5; ++i) {
        cout << values[i] << " ";
    }
    
    cout << endl;
    return 0;
}