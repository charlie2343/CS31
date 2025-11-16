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

    cerr << "return value: " << arrange(len, infile, outfile) << endl;
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

void handleOverflow(char portion[], int lineLength, int &charCount, ostream &outf, bool &overflow)
{

    int j = strlen(portion);
    char temp[125];

    while (j > lineLength)
    {
        strncpy(temp, portion, lineLength);
        temp[lineLength] = '\0';
        outf << temp << "\n";
        /// cerr << "PENIS: " << endl;

        // SAFE replace of substring(portion, portion, ...)
        int remain = j - lineLength;
        memmove(portion, portion + lineLength, remain);
        portion[remain] = '\0';

        j = remain; // update length
        overflow = true;
        charCount = j; // leftover counts toward next line
    }
}
//!
int arrange(int lineLength, istream& inf, ostream& outf)
{
    if (lineLength < 1)
        return 1;  // per spec: no output, just return 1

    char token[125];
    int charCount = 0;                 // chars so far on current line
    bool overflowOccurred = false;     // did we ever split a word portion?
    bool seenAnyWord = false;          // have we output any real word portion?
    bool pendingParagraphBreak = false;// saw <P> after some words
    char lastWordLastChar = '\0';      // last char of last printed word portion

    while (convertTokens(token, inf)) {
        // Handle paragraph marker <P>
        if (strcmp(token, "<P>") == 0) {
            // Only matters if we've already had at least one word
            if (seenAnyWord) {
                pendingParagraphBreak = true;
            }
            // ignore leading <P> and multiple consecutive <P>
            continue;
        }

        // Now token is a real word portion
        seenAnyWord = true;
        int L = strlen(token);
        if (L == 0)
            continue;  // defensive guard

        // Apply a pending paragraph break *before* printing this word
        if (pendingParagraphBreak) {
            if (charCount > 0) {
                // finish the current line
                outf << '\n';
                charCount = 0;
            }
            // blank line between paragraphs (but not before first)
            outf << '\n';
            charCount = 0;
            pendingParagraphBreak = false;
        }

        // If this word portion is longer than the line length, split it
        if (L > lineLength) {
            overflowOccurred = true;

            // If there's stuff on the current line, finish it first
            if (charCount > 0) {
                outf << '\n';
                charCount = 0;
            }

            int start = 0;
            // Full-length chunks, each on its own line
            while (L - start > lineLength) {
                for (int i = 0; i < lineLength; i++)
                    outf << token[start + i];
                outf << '\n';
                charCount = 0;
                start += lineLength;
            }

            int remain = L - start;
            if (remain > 0) {
                // Remaining part becomes the start of a new line
                for (int i = 0; i < remain; i++)
                    outf << token[start + i];
                charCount = remain;
                lastWordLastChar = token[L - 1];  // last char of whole portion
            } else {
                // Exactly divisible; we're at line start again
                lastWordLastChar = '\0';
            }

            continue;  // move to next token
        }

        // Normal word portion (L <= lineLength)

        if (charCount == 0) {
            // First word on the line: no leading spaces
            outf << token;
            charCount = L;
            lastWordLastChar = token[L - 1];
        } else {
            // Choose 1 or 2 spaces based on punctuation
            int spaces = (lastWordLastChar == '.' ||
                          lastWordLastChar == '?' ||
                          lastWordLastChar == ':') ? 2 : 1;

            // Would spaces + this word overflow the line?
            if (charCount + spaces + L > lineLength) {
                // Move to next line, no leading spaces
                outf << '\n';
                charCount = 0;
                outf << token;
                charCount = L;
                lastWordLastChar = token[L - 1];
            } else {
                // Same line: print spaces then the word
                for (int i = 0; i < spaces; i++)
                    outf << ' ';
                charCount += spaces;

                outf << token;
                charCount += L;
                lastWordLastChar = token[L - 1];
            }
        }
    }

    // End of input: if there's an unfinished line, terminate it with '\n'
    if (charCount > 0) {
        outf << '\n';
    }

    // If no words at all (only whitespace and/or <P>), we correctly wrote nothing.
    // Just return 0 or 2 depending on overflow.
    if (overflowOccurred)
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
    return true;
}