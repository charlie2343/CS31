#include <string>
#include <iostream>
using namespace std;

bool isSyntacticallyCorrect(string dance);
int translateDance(string dance, string &instructions, int &badBeat);
bool isValidDir(char c);
int charToNum(char c); 

string s;
int main()
{
    for (;;)
    {
        cout << "Enter dance: ";
        string d;
        getline(cin, d);
        if (d == "quit")
            break;
        // cout << "isSyntacticallyCorrect returns ";
        // string inst = "ad";
        // int temp = 0; 
        // if (translateDance(d, inst, temp))
        //     cout << "true";
        // else
        //     cout << "false";
        // cout << endl;

        cout << "translateDance returns ";
        string inst = "ad";
        int temp = 0; 
        if (translateDance(d, inst, temp))
            cout << "true";
        else
            cout << "false";
        cout << endl;
    }
}

bool isSyntacticallyCorrect(string dance)
{
    int length = static_cast<int>(dance.size());

    if (dance.size() == 0)
    {
        return true;
    }

    if (length == 1)
    {
        return dance == "/";
    }
    if (dance[length - 1] != '/')
    {
        return false;
    }

    for (int c = 0; c < length; c++)
    {
        // check if character is in accepted input

        if (!(isValidDir(dance[c]) || dance[c] == '/' || isdigit(dance[c])))
        {
            return false;
        }

        // check if validdir char is followed by /
        if (c < length - 1)
        {
            if (isValidDir(dance[c]))
            {
                if (dance[c + 1] == '/')
                {
                    ;
                }
                else
                {
                    return false;
                }
            }
        }


        // check if two digit, followed by dir,  followed by /
            if(isdigit(dance[c])){
                //ensure at least 3 more chars till end of string
                if((c+ 3) < length && isdigit(dance[c+1]) ){ // for case such as 333R/ func returns true,
                    cout << "2 DIGITS found!";
                    if (isValidDir(dance[c + 2]))
                    {
                        if(dance[c+3] == '/'){
                            ;
                        }
                        else{
                            cout << "slash not found"; 
                            return false;
                        }
                    }
                    else{
                        cout << "char after 2 digits not valid d";
                        return false;
                    }
                }
                // if subsequent char not digit, check 
                else if((c+2) < length && isValidDir(dance[c + 1]))
                {
                    if (dance[c + 2] == '/')
                    {
                        ;
                    }
                    else
                    {
                        return false;
                    }
                }
                else{
                    return false; 
                }
            }
        //}


        // // check if digit is followed by dir followed by /
        // if (c < dance.size() - 2)
        // {
        //     if (isdigit(dance[c]))
        //     {
        //         if (isValidDir(dance[c + 1]))
        //         {
        //             if (dance[c + 2] == '/')
        //             {
        //                 ;
        //             }
        //             else
        //             {
        //                 return false;
        //             }
        //         }
        //         else{
        //             return false; 
        //         }
        //     }
        // }

        // end loop
    }
    // check case one digit followed by dir
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
    //  dance not syntacially correc --> return 1
    if(!isSyntacticallyCorrect(dance)){ 
        return 0; 
    }

    // if dance is translatable set instrucitons to translated and return 0
    int length = static_cast<int>(dance.size());
    for (int i = 0; i < length; i++){ 
        if (isdigit(dance[i]))
        {
            int num = charToNum(dance[i]);
            // cout << "Num: " << n
            bool EnoughSlashes = num <= (length - 1)- (i+1);
            if (EnoughSlashes)
            { 
                return 1;
            }
            return 0;
        }
    } 

    // dance is syntactically correct but a beat but freeze len < 2 bad beat set to number of that beat in sequence and funciton returns 2
    // dance is syntactially correct --> freeze in effect >>> but other move in freeze space return 3 and set bad beat to num in array
    // dance is syntactially correc>>/ prematurely ends freeze at end of string >>> bad beat set to 1 more than num of bad beats in string and func returns 4

    return 0;
}

int charToNum(char c){
    int n = c - '0';
    return n; 
}