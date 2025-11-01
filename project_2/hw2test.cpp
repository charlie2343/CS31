// #include <iostream>
// 	using namespace std;

// 	int main()
// 	{
// 	    int side;

// 	    cout << "Enter a number: ";
// 	    cin >> side;

// 	    for (int i = 0; i < side; i++)
//         {
//             int j = i; 
//             while(j >= 0)
//             {
//                 cout << "#";
//                 j--; 
//             }
//             cout << "\n";
// 	    }
// 	}

#include <iostream>
	using namespace std;

	int main()
	{
	    int side;

	    cout << "Enter a number: ";
	    cin >> side;

	    for (int i = 0; i < side; i++)
	    {
		for (int j = i; j >= 0; j--)
		{
		    cout << "#";
		}
		cout << "\n";
	    }
	}
