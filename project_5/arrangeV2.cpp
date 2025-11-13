#include <iostream>
#include <fstream>
using namespace std;
int arrange(int lineLength, istream &inf, ostream &outf);
bool convertTokens(char buffer[], istream &inf);
void clearCstring(char arr[], int n); 

int main()
{
    const int MAX_FILENAME_LENGTH = 100;
        // cout << "Enter input file name (or q to quit): ";
        // char filename[MAX_FILENAME_LENGTH+1];
        // cin.getline(filename, MAX_FILENAME_LENGTH);
        // if (strcmp(filename, "q") == 0)
        //     break;
        ifstream infile("input.txt");
        if (!infile)
        {
            cerr << "Cannot open " << "input.txt" << "!" << endl;
            ///continue;
        }
        // cout << "Enter maximum line length: ";
        // int len;
        // cin >> len;
        // cin.ignore(10000, '\n');
        // int returnCode = arrange(len, infile, cout);
        // cout << "Return code is " << returnCode << endl;
        char word[50];
        int i = 0; 
        while(convertTokens(word, infile)){ 
        cout << "Yippe: " << word << endl;
        clearCstring(word, 50);
        }
        cout << "EOF";
}
void clearCstring(char arr[], int n){
    for (int i = 0; i < n; i++){
        arr[i] = '\0'; 
    }
}

int arrange(int lineLength, istream &inf, ostream &outf)
{
    char c;
    while (inf.get(c))
    {
        cout << c;
    }
    return 0;

    // for (;;)
    // {
    //     Attempt to get the next token
    //     if end of file
    //         break;
    //     if it's a paragraph break
    //         process paragraph break
    //     else // an ordinary word
    //         process that word
    // }
}

bool convertTokens(char buffer[], istream &inf)
{
    char c;
    int i = 0; 
    // EOF return false
    if(!inf) return false; 

    while (inf.get(c) && c != ' ' && c != '\n')
    {
        buffer[i] = c;
        i++;
    }
    buffer[i] = '\0'; 
    return true;

    // else fill buffer with word
}
