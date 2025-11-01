#include <string>
#include <iostream>
using namespace std;

bool isSyntacticallyCorrect(string dance);
int translateDance(string dance, string &instructions, int &badBeat);
bool isValidDir(char c);

int main(){ 
for (;;)
    {
        cout << "Enter dance: ";
        string d;
        getline(cin, d);
        if (d == "quit")
            break;
        cout << "isSyntacticallyCorrect returns ";
        string inst = "ad";
        int temp = 0; 
        if (isSyntacticallyCorrect(d))
            cout << "true";
        else
            cout << "false";
        cout << endl;
    }
}

bool isSyntacticallyCorrect(string dance){ 
    char prev = '/';
    int a = 0;
    bool isDoubleDigit = false; 
    for (int i = 1; i < static_cast<int>(dance.size()); i++)
    {
        //check if char is valid first 
        if (!(isValidDir(dance[i]) || dance[i] == '/' || isdigit(dance[i])))
        {
            return false;
        }
        
        //check for valid dir after doubleDIgit flaged
        if(isDoubleDigit && !(isValidDir(dance[i]))){
            return false; 
        }else{
            isDoubleDigit = false; 
        }
        //if current char is '/' then prev must be / or dir 
        if(dance[i] == '/'){ 
            if(!(isValidDir(prev) || prev == '/')){
                return false; 
            }
        }
        
        if(isalpha(dance[i]) && isalpha(prev)){ 
            return false; 
        }

        //flag double digit if prev and current are digits
        if(isdigit(dance[i])){ 
            if(isdigit(prev)){ 
                isDoubleDigit = true; 
            } else if(isalpha(prev)){
                return false;
            }
        }
        a = i - 1;
        prev = dance[a]; 
    }
    return true; 
}

bool isValidDir(char c)
{
    if ((tolower(c) == 'u' || tolower(c) == 'd' || tolower(c) == 'l' || tolower(c) == 'r'))
    {
        return true;
    }
    return false;
}
