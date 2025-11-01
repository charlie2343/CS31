#include <string>
#include <iostream>
using namespace std;

bool isSyntacticallyCorrect(string dance);
int translateDance(string dance, string &instructions, int &badBeat);
bool isValidDir(char c);
bool isValidBeat(string s);

int main()
{
    for (;;)
    {
        cout << "Enter dance: ";
        string d;
        getline(cin, d);
        if (d == "quit")
            break;
        cout << "isSyntacticallyCorrect returns " << endl;
        string inst = "ad";
        int temp = 0;
        if (isSyntacticallyCorrect(d))
            cout << "true";
        else
            cout << "false";
        cout << endl;
    }
}

bool isSyntacticallyCorrect(string dance)
{
    int length = static_cast<int>(dance.size());
    string temp = "";
    bool containsSlash = false; 
    for (int i = 0; i < length; i++)
    {
        //cout << "Temporary: " << temp << endl;
        if (dance[i] == '/')
        {
            containsSlash = true; 
            if (!isValidBeat(temp))
            {

                return false;
            }
            temp = "";
        }
        else
        {
            temp += dance[i];
        }
    }
    //two edge cases are if dance has no '/' or if last char is no '/'
    if(!containsSlash || dance[length-1] != '/'){ 
        return false; 
    }
        return true;
}

bool isValidBeat(string s)
{
    int length = static_cast<int>(s.size());
    if (s == "")
    {
        //cout << "Bypassed " << endl;
        return true;
    }
    if (length > 3)
    {
        return false;
    }
    else if (length == 3)
    {
        if (isdigit(s[0]) && isdigit(s[1]) && isValidDir(s[2]))
        {
            ;
        }
        else
        {
            return false;
        }
    }
    else if (length == 2)
    {
        if (isdigit(s[0]) && isValidDir(s[1]))
        {
            ;
        }
        else
        {
            return false;
        }
    }
    else
    {
        if (isValidDir(s[0]))
        {
            ;
        }
        else
        {
            return false;
        }
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
