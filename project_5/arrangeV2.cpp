#include <iostream>
#include <fstream>

#include <sstream>
#include <streambuf>
#include <cstring>
#include <cassert>
using namespace std;

// #include <afxstr.h>

using namespace std;
int arrange(int lineLength, istream &inf, ostream &outf);
bool convertTokens(char buffer[], istream &inf);
void clearCstring(char arr[], int n);

void testArrange(int lineLength, const char input[], const char expectedOutput[], int expectedReturnValue)
{
    istringstream iss(input);
    ostringstream oss;
    ostringstream dummy;
    streambuf *origcerr = cerr.rdbuf(dummy.rdbuf());
    int retval = arrange(lineLength, iss, oss);
    cerr.rdbuf(origcerr);
    if (!dummy.str().empty())
        cerr << "WROTE TO cout INSTEAD OF THIRD PARAMETER FOR: " << input << endl;
    else if (retval != expectedReturnValue)
        cerr << "WRONG RETURN VALUE FOR: " << input << endl;
    else if (retval == 1)
    {
        if (!oss.str().empty())
            cerr << "WROTE OUTPUT WHEN LINELENGTH IS " << lineLength << endl;
    }
    else if (oss.str() != expectedOutput)
        cerr << "WRONG RESULT FOR: " << input << endl;
}

int main()
{
    // const int MAX_FILENAME_LENGTH = 100;
    // // cerr << "Enter input file name (or q to quit): ";
    // // char filename[MAX_FILENAME_LENGTH+1];
    // // cin.getline(filename, MAX_FILENAME_LENGTH);
    // // if (strcmp(filename, "q") == 0)
    // //     break;
    // ifstream infile("input.txt");
    // if (!infile)
    // {
    //     cerr << "Cannot open " << "input.txt" << "!" << endl;
    //     /// continue;
    // }
    // ofstream outfile("results.txt"); // outfile is a name of our choosing.
    // if (!outfile)                    // Did the creation fail?
    // {
    //     cerr << "Error: Cannot create results.txt!" << endl;
    //     // ... return with failure ...
    // }
    // cerr << "Enter maximum line length: ";
    // int len;
    // cin >> len;
    // cin.ignore(10000, '\n');
    // int returnCode = arrange(len, infile, outfile);
    // cerr << "Return code is " << returnCode << endl;
    // // char word[50];
    // // int i = 0;
    // // while(convertTokens(word, infile)){
    // //     for (int j = 0; j < 10; j++){
    // //         cerr << "raw word char: " << word[j] << " ";
    // //     }
    // //         // cerr << "Yippe: " << word << endl;
    // //         clearCstring(word, 50);
    // // }
    // // cerr << "EOF"<< endl;

    testArrange(7, "This\n\t\tis a\ntest\n", "This is\na test\n", 0);
    testArrange(8, "  This is a test  \n", "This is\na test\n", 0);
    testArrange(-5, "irrelevant", "irrelevant", 1);
    testArrange(6, "Testing it\n", "Testin\ng it\n", 2);
    cerr << "Tests complete" << endl;
}
void clearCstring(char arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        arr[i] = '\0';
    }
}

void substring(char source[], char dest[], int start, int end)
{

    if (start < 0 || end > 125)
    {
        cerr << "error";
    }
    int i = 0;
    for (i = start; i <= end; i++)
    {
        dest[i - start] = source[i];
    }
    dest[i - start] = '\0';
}

void handleOverflow(char portion[], int lineLength, int &charCount, ostream &outf, bool &overflow)
{
    int j = strlen(portion);
    char temp[125];

    while (j > lineLength)
    {
        strncpy(temp, portion, lineLength);
        temp[lineLength] = '\0';
        outf << temp << "\n";

        // SAFE replace of substring(portion, portion, ...)
        int remain = j - lineLength;
        memmove(portion, portion + lineLength, remain);
        portion[remain] = '\0';

        j = remain; // update length
        overflow = true;
        charCount = j; // leftover counts toward next line
    }
}

int arrange(int lineLength, istream &inf, ostream &outf)
{
    if (lineLength < 1)
        return 1;
    char c;
    char portion[125];
    int charCount = 0;
    char prevPortion[125];
    char temp[125];
    int i;
    bool prevParagraph = false;
    bool overflow = false;
    // bool firstRun = true;
    if (!convertTokens(prevPortion, inf))
    {
        return 0;
    }
    int j = strlen(prevPortion);
    char lastChar = prevPortion[j - 1];
    if (lastChar == '.' || lastChar == '?' || lastChar == ':')
    {
        // prevPortion[j + 1] = ' ';
        // prevPortion[j] = ' ';
        // prevPortion[j + 2] = '\0';
        charCount += 2;
    }
    else
    {
        charCount++;
        // prevPortion[j + 1] = '\0';
        // prevPortion[j] = ' ';
    }
    //
    // cerr << "Modified first poriton: " << prevPortion << "....." <<endl;

    charCount += strlen(prevPortion);
    for (;;)
    {

        if (!convertTokens(portion, inf))
        {
            // outf << "Final word: " << prevPortion;
            handleOverflow(prevPortion, lineLength, charCount, outf, overflow);
            outf << prevPortion << '\n';
            break;
        }

        if (strcmp(portion, "<P>") == 0 && !prevParagraph)
        {
            // cerr << "Paragraph found" << endl;
            outf << prevPortion;
            outf << "\n\n";
            charCount = 0;
            prevParagraph = true;
        }
        // not space
        else if (strcmp(prevPortion, "<P>") != 0)
        {
            int len;
            len = strlen(portion);
            int prevlen;
            prevlen = strlen(prevPortion);
            // check for overflow:
            // cerr << "charCount: " << charCount << " LEN: " << len << endl;
            // cerr << charCount << ',' << lineLength << endl;
            handleOverflow(prevPortion, lineLength, charCount, outf, overflow);
            charCount += len; // i is index, leng
            if (charCount > lineLength)
            {
                outf << prevPortion;
                outf << '\n';
                charCount = len;
            }
            // cerr << "Last index of portion: " << i << " with val " << portion[i] << endl;
            else if (prevPortion[prevlen - 1] == '.' || prevPortion[prevlen - 1] == '?' || prevPortion[prevlen - 1] == ':')
            {
                outf << prevPortion << "  ";
                charCount += 2;
            }
            else
            {
                outf << prevPortion << " ";
                charCount++; // gets the whitespace
            }
        }
        strcpy(prevPortion, portion);
        prevParagraph = false;
    }
    cerr << '\n';
    // cerr << "Total Chars Printed: " << charCount << endl;
    if (overflow)
        return 2;
    return 0;
}

bool convertTokens(char buffer[], istream &inf)
{
    char c;
    int i = 0;
    // EOF return false
    if (!inf)
    {
        return false;
    }

    while (inf.get(c) && (c == ' ' || c == '\n'))
        ;

    buffer[i] = c;
    if (c == ' ')
    {
        buffer[0] = '\0';
    }

    if (c == '-')
    {
        buffer[i + 1] = '\0';
        return true;
    }
    i++;

    while (inf.get(c) && c != ' ' && c != '\n')
    {

        buffer[i] = c;
        if (c == '-')
        {
            buffer[i + 1] = '\0';
            return true;
        }
        i++;
    }
    buffer[i] = '\0';
    // debug print
    if (strcmp(buffer, " ") == 0)
    {
        cerr << "Space found!";
    }
    // cerr << "Buffer: " << buffer << endl;
    return true;

    // else fill buffer with word
}
