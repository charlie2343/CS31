#include <iostream>
using namespace std;

string institution;
float basisAmt;
string type;
float settlementAmt = 0;
void getSettlementAmt();
float getMin(float a, float b);

int main()
{
    //get institution
    cout << "Institution: ";
    getline(cin, institution);
    if (institution == "")
    {
        cout << "---" << endl;
        cout << "You must enter an institution." << endl;
        return 1;
    }

    //get basis
    cout << "Basis amount (in trillions): ";
    cin >> basisAmt;
    if (basisAmt <= 0)
    {
        cout << "---" << endl;
        cout << "The basis amount must be positive." << endl;
        return 1;
    }

    //get type
    cin.ignore(10000, '\n');
    cout << "Institution type: ";
    getline(cin, type);
    if (type == "")
    {
        cout << "---" << endl;
        cout << "You must enter an institution type." << endl;
        return 1;
    }

    else
    {
        cout.setf(ios::fixed);
        cout.precision(1);
        getSettlementAmt();
        cout << "---" << endl;
        cout << "The settlement amount for " << institution << " is P" << settlementAmt << " trillion." << endl;
    }
}

void getSettlementAmt()
{
    settlementAmt += getMin(160 * 0.07, basisAmt * 0.07);
    if (basisAmt > 160)
    {
        if (type == "university" || type == "media")
        {
            settlementAmt += getMin(600 * 0.17, (basisAmt - 160) * 0.17);
        }
        else
        {
            settlementAmt += getMin(600 * 0.09, (basisAmt - 160) * 0.09);
        }
    }
    if (basisAmt > 760)
    {
        settlementAmt += (basisAmt - 760) * 0.11;
    }
}

float getMin(float a, float b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}