#include <iostream>
#include <cctype>
#include <string>
using namespace std;


int main() {
    int i;
    string str;
    cin >> str;
    int counter = 0; 
    do
    {
        counter++; 
        if(islower(str[counter])){
            break; 
        }

    } while (counter < static_cast<int>(str.size()));
    if (counter == static_cast<int>(str.size()))
        cout << "No lowercase character" << endl;
    else
        cout << str[counter] << endl;
}
