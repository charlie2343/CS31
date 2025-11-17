#include <iostream>
#include <fstream>
#include <sstream>
#include <streambuf>
#include <cstring>
#include <cassert>

using namespace std;

using namespace std;
int arrange(int lineLength, istream &inf, ostream &outf);
bool convertTokens(char buffer[], istream &inf);
void clearCstring(char arr[], int n);

void testArrange(int lineLength, const char input[], const char expectedOutput[], int expectedReturnValue)
{
    istringstream iss(input);
    ostringstream oss;
    ostringstream dummy;
    streambuf *origcout = cout.rdbuf(dummy.rdbuf());
    int retval = arrange(lineLength, iss, oss);
    cout.rdbuf(origcout);
    if (!dummy.str().empty())
        cout << "WROTE TO cout INSTEAD OF THIRD PARAMETER FOR: " << input << endl;
    else if (retval != expectedReturnValue)
        cout << "WRONG RETURN VALUE FOR: " << input << endl;
    else if (retval == 1)
    {
        if (!oss.str().empty())
            cout << "WROTE OUTPUT WHEN LINELENGTH IS " << lineLength << endl;
    }
    else if (oss.str() != expectedOutput)
        cout << "WRONG RESULT FOR: " << input << endl;
}

int main()
{
    // const int MAX_FILENAME_LENGTH = 100;
    // // cerr << "Enter input file name (or q to quit): ";
    // // char filename[MAX_FILENAME_LENGTH+1];
    // // cin.getline(filename, MAX_FILENAME_LENGTH);
    // // if (strcmp(filename, "q") == 0)
    // //     break;
    ifstream infile("input.txt");
    if (!infile)
    {
        cerr << "Cannot open " << "input.txt" << "!" << endl;
        /// continue;
    }
    ofstream outfile("results.txt"); // outfile is a name of our choosing.
    if (!outfile)                    // Did the creation fail?
    {
        cerr << "Error: Cannot create results.txt!" << endl;
        // ... return with failure ...
    }
    cerr << "Enter maximum line length: ";
    int len;
    cin >> len;
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
    int j = arrange(len, infile, outfile);
    cerr << "Arrange return value: " << j << endl;
    // testArrange(7, "This\n\t\tis a\ntest\n", "This is\na test\n", 0);
    // testArrange(3, "s-----. ", "s-\n- -\n- -\n.\n", 0);
    // testArrange(10, ". . .", ".  .  .\n", 0);
    // //testArrange(40, "It always does seem to me that I am doing more work than\n  I should do. It is not that I object to the work, mind you;\nI like work: it fascinates me.       I can sit and look at it for hours.\nI love to keep     it by me: the idea of getting\nrid\nof it nearly breaks my heart. <P> You cannot give me too\nmuch work; to accumulate work has almost become\n\n\na passion with me: my study is so full of it now, that there is hardly change newline/any other excape chars to their excape chars\nan inch of room for any more.\n","It always does seem to me that I am\ndoing more work than I should do.  It is\nnot that I object to the work, mind you;\nI like work:  it fascinates me.  I can\nsit and look at it for hours.  I love to\nkeep it by me:  the idea of getting rid\nof it nearly breaks my heart.\n\nYou cannot give me too much work; to\naccumulate work has almost become a\npassion with me:  my study is so full of\nit now, that there is hardly an inch of\nroom for any more.\n", 0);
    // testArrange(8, "  This is a test  \n", "This is\na test\n", 0);
    // testArrange(-5, "irrelevant", "irrelevant", 1);
    // testArrange(6, "Testing it\n", "Testin\ng it\n", 2);
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

void handleOverflow(char portion[], int lineLength, int &charsPrinted, ostream &outf, bool &overflow)
{
    int j = strlen(portion);
    char temp[125];
    // cerr << "length: " <<j << endl;
    while (j > lineLength)
    {
        strncpy(temp, portion, lineLength);
        temp[lineLength] = '\0';
        outf << temp << "\n";

        // SAFE replace of substring(portion, portion, ...)
        int remain = j - lineLength;
        memmove(portion, portion + lineLength, remain);
        portion[remain] = '\0';
        // cerr << "new cut portion: " <<portion << endl;
        overflow = true;
        charsPrinted = remain; // update length

        // update j
        j = strlen(portion);
    }
}
//!
int arrange(int lineLength, istream &inf, ostream &outf)
{
    if (lineLength < 1)
        return 1;
    char c;
    char portion[125];
    int charsPrinted = 0;
    char prevPortion[125] = "";
    char temp[125];
    int i;
    bool paragraphFound = false;
    bool nextIsParagraph = false; 
    bool overflow = false;
    // bool firstRun = true;

    // if (!convertTokens(prevPortion, inf))
    // {
    //     return 0;
    // }
    // int j = strlen(prevPortion);
    // char lastChar = prevPortion[j - 1];
    // if (lastChar == '.' || lastChar == '?' || lastChar == ':')
    // {
    //     // prevPortion[j + 1] = ' ';
    //     // prevPortion[j] = ' ';
    //     // prevPortion[j + 2] = '\0';
    //     charsPrinted += 2;
    // }
    // else
    // {
    //     charsPrinted++;
    //     // prevPortion[j + 1] = '\0';
    //     // prevPortion[j] = ' ';
    // }
    // //
    // // cerr << "Modified first poriton: " << prevPortion << "....." <<endl;
    // //!! enter loop
    // charsPrinted += strlen(prevPortion);
    for (;;)
    {
        //if prevPortion buffer not loaded (first iteration)
        if (strcmp(prevPortion, "") == 0)
        {
            // cerr << "asdfasdf" << endl;
            if (!convertTokens(prevPortion, inf))
            {
                return 0;
            }

            //catch edge case if first portion is <P> 
            if (strcmp(prevPortion, "<P>") == 0)
            {
                paragraphFound = true;
            }
        }

        handleOverflow(prevPortion, lineLength, charsPrinted, outf, overflow);

        //EOF detection
        if (!convertTokens(portion, inf))
        {
            // outf << "Final word: " << prevPortion;
            //! check this I dont think this logic is right

            // edge case if <P> is only input, output is null 
            if (strcmp(prevPortion, "<P>") == 0 && charsPrinted == 0)
            {
                break;
            }
            //case if last poriton is <P>, dont write it out
            else if (strcmp(prevPortion, "<P>") == 0)
            {
                outf << '\n';
                break;
            }
            else
            {
                outf << prevPortion << '\n';
            }
            break;
        }

        // // single Paragraph logic
        // if (strcmp(portion, "<P>") == 0)
        // {
        //     paragraphFound = true;
        // }

        // if (paragraphFound)
        // {
        //     if (strcmp(prevPortion, "<P>") != 0)
        //     {
        //         outf << prevPortion; 
        //     }
        //     outf << "\n\n";
        //     charsPrinted = 0;
        //     strcpy(prevPortion, portion);
        //     paragraphFound = false;
        //     continue;
        // }

        //! trying to get consecutive paragraph case. 
        paragraphFound = (strcmp(prevPortion, "<P>") == 0); 
        nextIsParagraph = (strcmp(portion, "<P>") == 0);

        if(paragraphFound && nextIsParagraph){ 
            strcpy(prevPortion, portion);
            continue;
        }

        //dont have to do (paragraphFound and !nextIsParagraph) bc nextisParagraph is only changing one and is checked above
        if (paragraphFound)
        {
            //if only one <P> in sequence (prev is valid word)
            if (strcmp(prevPortion, "<P>") != 0)
            {
                outf << prevPortion; 
            }
            //otherwise output two newline
            outf << "\n\n";
            charsPrinted = 0;
            strcpy(prevPortion, portion);
            paragraphFound = false;
            continue;
        }

        // CHeck EOL condition
        if (charsPrinted + strlen(portion) > lineLength)
        {
            outf << prevPortion << '\n';
            charsPrinted = 0;
            strcpy(prevPortion, portion);
            continue;
        } // if next is <P> just output it., this allows sequence to reassign prevPortion, and just do two newline, not worrying about word it had to write before sequence. 
        else if(nextIsParagraph){
            outf << prevPortion; 
        }
        // otherwise if normal word
        // add 2 spaces or one space from puntuation 
        //! EOL dont add any spaces
       // else if (strcmp(prevPortion, "<P>") != 0)
       else
        {
            int prevlen = 0;
            prevlen = strlen(prevPortion);
            if (prevPortion[prevlen - 1] == '.' || prevPortion[prevlen - 1] == '?' || prevPortion[prevlen - 1] == ':')
            {
                outf << prevPortion << "  ";
                charsPrinted += 2 + prevlen;
            }
            else
            {
                outf << prevPortion << " ";
                charsPrinted += 1 + prevlen; // gets the whitespace
            }
            // cerr << "Prev portion: " << prevPortion << " Chars printed: " << charsPrinted << endl;
        }

        // update prevPortion
        strcpy(prevPortion, portion);
    }
    if (overflow)
        return 2;
    return 0;
}

bool convertTokens(char buffer[], istream &inf)
{
    char c;
    int i = 0;

    if (!inf)
        return false;

    // Skip spaces, newlines, tabs
    while (inf.get(c) && (c == ' ' || c == '\n' || c == '\t'))
        ;

    // If we hit EOF while skipping whitespace
    if (!inf)
        return false;

    buffer[i++] = c;

    // If the word portion is just "-"
    if (c == '-')
    {
        buffer[i] = '\0';
        return true;
    }

    // Read rest of portion until space/newline/tab OR a hyphen
    while (inf.get(c) && c != ' ' && c != '\n' && c != '\t')
    {
        buffer[i++] = c;
        if (c == '-')
        {
            buffer[i] = '\0';
            return true;
        }
    }

    buffer[i] = '\0';
    cerr << "buffer: " << buffer << endl;
    return true;
}