#include <string>
#include <iostream>
using namespace std;

bool isSyntacticallyCorrect(string dance);
int translateDance(string dance, string &instructions, int &badBeat);
bool isValidDir(char c);
bool isValidBeat(string s);
int translateDance(string dance, string &instructions, int &badBeat);
int extractDigits(string s);

int main()
{
    //! syntax tester
    // for (;;)
    // {
    //     cout << "Enter dance: ";
    //     string d;
    //     getline(cin, d);
    //     if (d == "quit")
    //         break;
    //     cout << "isSyntacticallyCorrect returns " << endl;
    //     string inst = "ad";
    //     int temp = 0;
    //     if (isSyntacticallyCorrect(d))
    //         cout << "true";
    //     else
    //         cout << "false";
    //     cout << endl;
    // }

    //! extract digit tester
    // for (;;)
    // {
    //     cout << "string of form "", 'd', 'Xd' or 'XXd': ";
    //     string d;
    //     getline(cin, d);
    //     if (d == "quit")
    //         break;
    //     cout << "extract Digits " << endl;
    //     cout << "Digits extracted: " << (extractDigits(d)) << endl;
    //     }

    //! translate tester
    for (;;)
    {
        cout << "Enter dance: ";
        string d;
        getline(cin, d);
        if (d == "quit")
            break;
        cout << "translateDance returns " << endl;
        string instructions = "";
        int badBeat_ = 0;
        int output = 0;
        output = translateDance(d, instructions, badBeat_);
        cout << "Badbeat num: " << badBeat_ << "\noutput #: " << output << "\nInstructions: " << instructions << endl;
    }
}

bool isSyntacticallyCorrect(string dance)
{
    int length = static_cast<int>(dance.size());
    string temp = "";
    bool containsSlash = false;
    for (int i = 0; i < length; i++)
    {
        // cout << "Temporary: " << temp << endl;
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
    // two edge cases are if dance has no '/' or if last char is no '/'
    if (!containsSlash || dance[length - 1] != '/')
    {
        return false;
    }
    return true;
}

bool isValidBeat(string s)
{
    int length = static_cast<int>(s.size());
    if (s == "")
    {
        // cout << "Bypassed " << endl;
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

int translateDance(string dance, string &instructions, int &badBeat)
{
    int length = static_cast<int>(dance.size());
    //  dance not syntacially correc --> return 1
    if (!isSyntacticallyCorrect(dance))
    {
        return 1;
    }

    //! all syntactically correct at this point
    int beatIndex = 0;
    string temp = "";
    int freezeCount = 0;
    int totalBeats = 0;
    for (int a = 0; a < length; a++)
    {
        if (dance[a] == '/')
        {
            totalBeats++;
        }
    }
    for (int i = 0; i < length; i++)
    {
        if (dance[i] == '/')
        {
            beatIndex++;
            freezeCount = extractDigits(temp);
            // Check for digit error
            if (freezeCount != 404 && freezeCount < 2)
            {
                badBeat = beatIndex;
                return 2;
            }

            // // check for premature freeze end via not enough slashes
            // if (i + freezeCount < length)
            // {
            //     for (int j = i; j < freezeCount; j++)
            //     {
            //         beatIndex++;
            //         if (dance[j] != '/')
            //         {
            //             badBeat = beatIndex;
            //             return 3;
            //         }
            //     }
            // }

            // // check for premature freeze end via outofbounds
            // if (i + freezeCount >= length)
            // {
            //     badBeat = beatIndex;
            //     return 4;
            // }
            // temp = "";

            //!!!
            if(freezeCount != 404){ 
            cout << "I is: " << i << " Dance at i is: " << dance[i] << endl; 
            for (int j = i; j < (i+freezeCount); j++)
            {
                cout << "Dance at j (T1): " << dance[j] << endl; 
                if (j >= length)
                {
                    cout << "TotalBeats: " << totalBeats << endl; 
                    badBeat = totalBeats + 1;
                    return 4;
                }
                else if(dance[j]== '/'){ 
                    beatIndex++;
                } 
                else
                {
                    cout << "Dance at j: " << dance[j] << endl; 
                    badBeat = beatIndex;
                    return 3;
                }
            }
        } 
            

            // check for premature freeze end via outofbounds
            
            temp = "";
        }
        else
        {
            temp += dance[i];
        }
    }

    return 0;

    // but a beat specifies a freeze of length less than 2, badBeat is set to the number of that beat (where the first beat of the whole dance is number 1, etc.), and the function returns 2.
    // but while a freeze is in effect, a beat not consisting of only a slash is present, badBeat is set to the number of that beat (where the first beat of the whole dance is number 1, etc.), and the function returns 3.
    // but ends prematurely with a freeze in effect but too few empty beats at the end of the string to finish the freeze, badBeat is set to one more than the number of beats in the string, and the function returns 4.
    //! translatable at this point
    // the function sets instructions to the translated form of the dance and returns 0.
}

int extractDigits(string s)
{
    int length = static_cast<int>(s.size());
    int freezeCount = 0;
    if (s == "")
    {
        freezeCount = 404;
    }
    if (length == 2)
    {
        freezeCount = static_cast<int>(s.at(0) - '0');
    }
    else if (length == 3)
    {
        freezeCount = static_cast<int>(s.at(0) - '0') * 10 + static_cast<int>(s.at(1) - '0');
    }
    return freezeCount;
}
