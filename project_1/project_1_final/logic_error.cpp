// Code for Project 1
	// Report poll results
	
#include <iostream>
using namespace std;

int main()
{
    int numberSurveyed;
    int hunters;
    int club;
    int rating; 
    int total_rating = 0; 

    cout << "How many people were surveyed? ";
    cin >> numberSurveyed;
    cout << "How many of them prefer KPop Demon Hunters to The Thursday Murder Club? ";
    cin >> hunters;
    cout << "How many of them prefer The Thursday Murder Club to KPop Demon Hunters? ";
    cin >> club;
    cout << "On average, what did people give Kpop Demon hunters on a scale of 1-5? ";
    cin >> rating;

    for (int i = 0; i < numberSurveyed; i++)
        ;
    {
        total_rating += rating;
    }

    double pctHunters = 100.0 * hunters / numberSurveyed;
    double pctClub = 100.0 * club / numberSurveyed;

    cout.setf(ios::fixed);
    cout.precision(1);

    cout << endl;
    cout << pctHunters << "% say they prefer KPop Demon Hunters." << endl;
    cout << pctClub << "% say they prefer The Thursday Murder Club." << endl;
    cout << total_rating << " is the aggregate rating for Kpop Demon Hunters" << endl;

    if (hunters > club)
        cout << "KPop Demon Hunters is more popular than The Thursday Murder Club." << endl;
    else
        cout << "The Thursday Murder Club is more popular than KPop Demon Hunters." << endl;
}