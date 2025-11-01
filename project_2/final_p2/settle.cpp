#include <iostream>
using namespace std;

string institution;
double basisAmt;
string type;
double settlementAmt = 0;
void getSettlementAmt();

int main()
{
    cout << "Institution: ";
    getline(cin, institution);
    cout << "Basis amount (in trillions): ";
    cin >> basisAmt;
    cin.ignore(10000, '\n'); //clear buffer from cin
    cout << "Institution type: ";
    getline(cin, type);

    getSettlementAmt();
    cout << "---" << endl;
    cout.setf(ios::fixed); //set decimal precision to 1. 
    cout.precision(1);

    //Message output handling
    if (institution == "")
    {
        cout << "You must enter an institution." << endl;
    }
    else if (basisAmt <= 0)
    {
        cout << "The basis amount must be positive." << endl;
    }
    else if (type == "")
    {
        cout << "You must enter an institution type." << endl;
    }
    else
    {
        cout << "The settlement amount for " << institution << " is P" << settlementAmt << " trillion." << endl;
    }
}

void getSettlementAmt()
//case work for settlments amount. 
{
    if (basisAmt <= 160)
    {
        settlementAmt += basisAmt * 0.07;
    }
    else if (basisAmt <= 760)
    {
        float newBasisAmt = basisAmt - 160;
        if (type == "media" || type == "university")
        {
            settlementAmt += newBasisAmt * 0.17;
        }
        else
        {
            settlementAmt += newBasisAmt * 0.09;
        }
        settlementAmt += 160 * 0.07;
    }
    else
    {
        settlementAmt += 160 * 0.07;
        if (type == "media" || type == "university")
        {
            settlementAmt += 600 * 0.17;
        }
        else
        {
            settlementAmt += 600 * 0.09;
        }
        settlementAmt += (basisAmt - 760) * 0.11;
    }
}