#include <iostream>
#include <fstream>
using namespace std;

int arrange(int lineLength, istream &inf, ostream &outf);

int main()
{
    const int MAX_FILENAME_LENGTH = 100;
    for (;;)
    {
        // cout << "Enter input file name (or q to quit): ";
        // char filename[MAX_FILENAME_LENGTH+1];
        // cin.getline(filename, MAX_FILENAME_LENGTH);
        // if (strcmp(filename, "q") == 0)
        //     break;
        ifstream infile("input.txt");
        if (!infile)
        {
            cerr << "Cannot open " << "input.txt" << "!" << endl;
            continue;
        }
        cout << "Enter maximum line length: ";
        int len;
        cin >> len;
        cin.ignore(10000, '\n');
        int returnCode = arrange(len, infile, cout);
        cout << "Return code is " << returnCode << endl;
    }
}

void pringCstring(char arr[]){
    int i = 0; 
    while (arr[i] != '\0')
    {
        cout << arr[i];
        i++; 
    }
}

void clearCstring(char arr[], int n){
    for (int i = 0; i < n; i++){
        arr[i] = '\0'; 
    }
}

bool debug = true;

int arrange(int lineLength, istream &inf, ostream &outf)
{

    const int MAX = lineLength + 1;
    char line[MAX];
    while(){ 
        char portion[MAX];
        int portionLength = 0;
        int numCharsPrinted = 0; 
        for (int i = 0; i < MAX; i++)
        {
            if (debug)
                cout << i << " " << (char)(line[i]) << endl;
            //cout << line[i];
            if(line[i] == ' '){ // currently it doesn't handle the last word of the line or file correctly
                
                // portion[i-numCharsPrinted] = '\0';
                if(numCharsPrinted + portionLength < MAX){
                    pringCstring(portion);
                    cout << " ";
                }else{
                    cout << '\n';
                }
                numCharsPrinted += portionLength;
                numCharsPrinted++; 
                portionLength = 0;
                clearCstring(portion, MAX);
                // ! actually doesnt portion[0] = '\0'; // clears portion
            }
            else
            {
                portionLength++; 
                portion[i - numCharsPrinted] = line[i];
            }
        }
    }

    cout << endl;
    if (lineLength < 1)
    {
        return 1;
    }

    return 0;
}