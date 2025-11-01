#include <string>
#include <iostream>
#include <cassert>
using namespace std;

bool isSyntacticallyCorrect(string dance);
int translateDance(string dance, string &instructions, int &badBeat);
bool isValidDir(char c);
bool isValidBeat(string s);
int translateDance(string dance, string &instructions, int &badBeat);
double extractDigits(string s);

int main()
{
    //! syntax tester
    // for (;;)
    // {
    //     cout << "Enter dance: ";
    //     string d;
    //     getline(cin, d);
    //     if (d == "quit"),
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
        string instructions = "WOW!";
        int badBeat_ = -999;
        int output = 0;
        output = translateDance(d, instructions, badBeat_);
        cout << "Badbeat num: " << badBeat_ << "\noutput #: " << output << "\nInstructions: " << instructions << endl;
    }

    // assert(isSyntacticallyCorrect("d/u//"));
    // assert(!isSyntacticallyCorrect("d/z//"));
    // string ins;
    // int bb;
    // ins = "WOW";  // so we can detect whether translateDance sets ins
    // bb = -999;    // so we can detect whether translateDance sets bb
    // assert(translateDance("u//d/3r///d/", ins, bb) == 0  &&  ins == "u.dRRRd"  &&  bb == -999);
    // ins = "WOW";  // so we can detect whether translateDance sets ins
    // bb = -999;    // so we can detect whether translateDance sets bb
    // assert(translateDance("5r//", ins, bb) == 3  &&  ins == "WOW"  &&  bb == 3);
    // cerr << "All tests succeeded" << endl;
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
            //performs check on beat when / is hit
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
    if(dance ==""){
        return true; 
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
        // empty string is valid
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
    double freezeCount = 0;
    string instr = "";
    int freezeStopIndex =0;  

    for (int i = 0; i < length; i++)
    {
        if (dance[i] == '/')
        {
            beatIndex++;
            freezeCount = extractDigits(temp);
            // Check for digit error (404 is prev char is / or isalpha)
            if (freezeCount != 404 && freezeCount < 2)
            {
                badBeat = beatIndex;
                return 2;
            }
            //!!!
            //if temp is not "" or length 1. !(/ or dir)
            if(freezeCount != 404){
                freezeStopIndex = freezeCount + i;
                for (int j = i; j < freezeStopIndex; j++)
                { 
                    // check for premature end of freeze end via outofbounds
                    if (j >= length)
                    {
                        //actually counting / at index i twice so dont add 1
                        badBeat = beatIndex;
                        return 4;
                    }
                    else if(dance[j]== '/'){ 
                        //although counting / at index i twice, we miss final slash in this case, thus the count is correct
                        beatIndex++;
                        instr += toupper(temp[temp.size() - 1]);
                    }
                    // check for premature freeze end via unexpected char 
                    else
                    { 
                        badBeat = beatIndex;
                        return 3;
                    }
                }
                //if it is single char add lowercase version
            }
             else if(static_cast<int>(temp.size()) ==1 && isValidDir(dance[i])){
                instr += tolower(dance[i]);
            } 
            ///want to only write . if / not already replaced by uppercase char from freeze
            else if(temp == "" && i >= freezeStopIndex){
                instr += '.';
            }
            temp = "";
        }
        else
        {
            temp += dance[i];
            if(static_cast<int>(temp.size()) ==1 && isValidDir(dance[i])){
                instr += tolower(dance[i]);
            }
        }
    }
    instructions = instr; 
    return 0;
}

double extractDigits(string s)
{
    int length = static_cast<int>(s.size());
    double freezeCount = 0;
    // set unique error code(greter than 99) when extracting digits from dir or / characters. 
    if (s == "" || length == 1)
    {
        freezeCount = 404;
    }
    if (length == 2)
    {
        freezeCount = static_cast<double>(s.at(0) - '0');
    }
    else if (length == 3)
    {
        freezeCount = static_cast<double>(s.at(0) - '0') * 10 + static_cast<int>(s.at(1) - '0');
    }
    return freezeCount;
}
