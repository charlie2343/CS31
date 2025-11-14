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
        /// continue;
    }
    ofstream outfile("results.txt");   // outfile is a name of our choosing.
	if ( ! outfile )		   // Did the creation fail?
	{
	    cerr << "Error: Cannot create results.txt!" << endl;
	    // ... return with failure ...   
	}
    cout << "Enter maximum line length: ";
    int len;
    cin >> len;
    cin.ignore(10000, '\n');
    int returnCode = arrange(len, infile, outfile);
    cout << "Return code is " << returnCode << endl;
    // char word[50];
    // int i = 0;
    // while(convertTokens(word, infile)){
    //     for (int j = 0; j < 10; j++){
    //         cout << "raw word char: " << word[j] << " "; 
    //     }
    //         // cout << "Yippe: " << word << endl;
    //         clearCstring(word, 50);
    // }
    // cout << "EOF"<< endl;
}
void clearCstring(char arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = '\0';
    }
}
// int getLastindex(char portion[]){ 
//     int i = 0; 
//     while(portion[i] != '\0'){ 
//         i++; 

//     }
// }
int arrange(int lineLength, istream &inf, ostream &outf)
{
    char c;
    char portion[121];
    // while (inf.get(c))
    // {
    //     cout << c;
    // }
    int charsPrinted = 0;
    char tempPortion[121]; 
    int i;
    for (;;)
    {
        if (!convertTokens(portion, inf))
            break;

        
        if (strcmp(portion, "<P>") == 0)
        {
            //cout << "Paragraph found" << endl;
            outf << "\n\n"; 
            charsPrinted = 0; 

        }
        else if (portion[0] != '\0')
        {
            //cout << "Word: " << portion << endl;
            i = 0; 
            while (portion[i] != '\0')
            {
                //cout << " i: " << i << " char: " << portion[i] << endl;
                i++;
            }
            //cout << " NEW WORD " << endl; 
            charsPrinted+= i;
            if(charsPrinted > lineLength){
                outf << '\n';
                charsPrinted = i;  
            }
            //cout << "Last index of portion: " << i << " with val " << portion[i] << endl; 
            else if(portion[i -1] == '.' || portion[i -1] == '?' || portion[i -1] == ':'){
                outf << portion << "  ";
                charsPrinted += 2; 
            }else{
                outf << portion << " "; 
                charsPrinted++; // gets the whitespace
            }
        }
        //strcpy(tempPortion, portion);
    }
    cout << '\n'; 
    //cout << "Total Chars Printed: " << charsPrinted << endl; 

    return 0;
}


bool convertTokens(char buffer[], istream &inf)
{
    char c;
    int i = 0;
    // EOF return false
    if (!inf)
        return false;

    while (inf.get(c) && c != ' ' && c != '\n')
    {
        buffer[i] = c;
        i++;
    }
    buffer[i] = '\0';
    return true;

    // else fill buffer with word
}
