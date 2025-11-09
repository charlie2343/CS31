#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int repeat(string a[], int n);
int detectMatch(const string a[], int n, string target);
int detectMax(const string a[], int n);
int circleLeft(string a[], int n, int pos);
int enumerateRuns(const string a[], int n);
int flip(string a[], int n);
int detectDifference(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int detectAny(const string a1[], int n1, const string a2[], int n2);
int split(string a[], int n, string splitter);

int main()
{
    //! repeat
    // string stuff[6] = {"mahi", "bon", "cous", "", "tar", "mur"};
    // int j = repeat(stuff, 6); // returns 6
    // for (int i = 0; i < 6; i++){
    //     cout << stuff[i] << endl;
    // }
    string a[4] = {"ma", "can", "tu", "do"};
    string a1[4] = {"ma", "can", "tu", "do"};
    string a2[4] = {"ma", "can", "tu", "do"};
    assert(repeat(a, 3) == 3 && a[0] == "mama" && a[3] == "do");
    assert(repeat(a1, -2) == -1 && a1[0] == "ma" && a1[3] == "do");

    //! detect match
    string b[7] = {"will", "yoshi", "shohei", "freddie", "", "max", "shohei"};
    assert(detectMatch(b, 7, "shohei") == 2);
    assert(detectMatch(b, 2, "shohei") == -1);
    //! detect Max
    assert(detectMax(b, 7) == 1);
    string people[5] = {"freddie", "will", "shohei", "yoshi", "mookie"};
    assert(detectMax(people, 5) == 3); // returns 3, since  yoshi  is latest
    assert(detectMax(people, 0) == -1);

    //! circle left
    string d[4] = {"will", "yoshi", "freddie", "max"};
    string d1[5] = {"freddie", "will", "shohei", "yoshi", "mookie"};
    assert(circleLeft(d, 4, 1) == 1 && d[1] == "freddie" && d[3] == "yoshi");
    assert(circleLeft(d, 4, 5) == -1);
    assert(circleLeft(d1, 4, 0) == 0 && d1[1] == "shohei" && d1[3] == "freddie");

    //! enumerate runs
    string f[5] = {"max", "max", "max", "yoshi", "yoshi"};
    string guys[9] = {
        "teoscar", "tyler", "max", "max", "will", "will", "will", "max", "max"};
    assert(enumerateRuns(guys, 8) == 5);
    assert(enumerateRuns(f, 5) == 2);

    //! flip
    string c[3] = {"max", "shohei", "tommy"};
    // assert(detectAny(b, 7, c, 3) == 2);
    string blue[6] = {"tyler", "andy", "", "blake", "max", "enrique"};
    assert(flip(blue, 6) == 6 && blue[2] == "blake" && blue[5] == "tyler");
    assert(flip(c, 3) == 3 && c[0] == "tommy" && c[2] == "max");

    //! Detect differnece
    string b3[7] = {"will", "yoshi", "shohei", "freddie", "", "max", "shohei"};
    string d3[4] = {"will", "yoshi", "freddie", "max"};
    assert(detectDifference(b3, 4, d3, 4) == 2);
    string g[5] = {"freddie", "will", "shohei", "yoshi", "mookie"};
    string g1[6] = {"freddie", "will", "blake", "yoshi", "mookie", "shohei"};
    assert(detectDifference(g, 5, g1, 6) == 2); //  returns 2
    cout << detectDifference(g, 2, g1, 1) << endl;
    assert(detectDifference(g, 2, g1, 1) == 1);

    //! subsequence
    string dodgers[10] = {"alex", "shohei", "andy", "mookie", "enrique", "tommy"};
    string dodgers1[10] = {"shohei", "andy", "mookie"};
    int t = subsequence(dodgers, 6, dodgers1, 3); // returns 1
    string dodgers2[10] = {"alex", "mookie"};
    string null[2] = {"hi", "bye"};
    int u = subsequence(dodgers, 5, dodgers2, 2); // returns -1
    assert(t == 1);
    assert(u == -1);
    int u2 = subsequence(dodgers2, 5, dodgers1, 2);
    assert(u2 == -1);
    cout << subsequence(null, 0, dodgers1, 2) << endl;
    assert(subsequence(null, 2, dodgers1, 0) == 0);

    //! detect any
    string s0[10] = {"alex", "shohei", "andy", "mookie", "enrique", "tommy"};
    string set1[10] = {"enrique", "emmet", "mookie", "shohei"};
    string set2[10] = {"clayton", "justin"};
    // a1 has "shohei" at index 1, which is in set1 → should return 1
    assert(detectAny(s0, 6, set1, 4) == 1);

    // no common elements between dodgers and set2 → should return -1
    assert(detectAny(s0, 6, set2, 2) == -1);
    assert(detectAny(b, 7, c, 3) == 2);

    //! split
    assert(split(b, 7, "shohei") == 3);
    // cout << "HELLLO" <<  split(set2, 4, "mookie");

    assert(split(set2, 2, "mookie") == 2);
    assert(split(set1, 4, "mookie") == 2);
    for (int i = 0; i < 4; i++)
    {
        cout << set1[i] << " ";
    }
    string champs[6] = {"shohei", "blake", "will", "freddie", "yoshi", "max"};
    int x = split(champs, 6, "miguel"); //  returns 3
    cout << "CHAMPS________" << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << champs[i] << " ";
    }
    assert(x == 3);
    string champs2[4] = {"max", "yoshi", "blake", "shohei"};
    int y = split(champs2, 4, "shohei");
    cout << "CHAMPS2________" << endl;
    for (int i = 0; i < 4; i++)
    {
        cout << champs2[i] << " ";
    }
    assert(y == 2);

    cout << "All tests Passed" << endl;
}

int repeat(string a[], int n)
{
    if (n < 0)
    {
        return -1;
    }
    for (int i = 0; i < n; i++)
    {
        a[i] += a[i];
    }
    return n;
}

int detectMatch(const string a[], int n, string target)
{
    if (n < 0)
    {
        return -1;
    }
    for (int i = 0; i < n; i++)
    {
        if (a[i] == target)
        {
            return i;
        }
    }
    return -1;
}

int detectMax(const string a[], int n)
{
    if (n <= 0)
    {
        return -1;
    }
    string compare;
    int max = 0;
    bool alwaysGreater = true;
    // loop through, for each index of array loop through array again. check for singular instance of < to trigger flag.
    for (int i = 0; i < n; i++)
    {
        compare = a[i];
        cerr << compare << endl;
        alwaysGreater = true;
        for (int j = 0; j < n; j++)
        {
            if (i != j && compare < a[j])
            {
                alwaysGreater = false;
                cerr << "compare: " << compare << " a[j]: " << a[j] << endl;
            }
        }
        if (alwaysGreater)
        {
            return i;
        }
    }
    return -1;
}

int circleLeft(string a[], int n, int pos)
{
    if (n == 0 && pos == 0)
    {
        return 0;
    }
    if (n < 0 || pos >= n)
    {
        return -1;
    }
    string initial = a[pos];
    for (int i = pos; i < n - 1; i++)
    {
        a[i] = a[i + 1];
    }
    a[n - 1] = initial;
    return pos;
}

int enumerateRuns(const string a[], int n)
{
    int count = 1;
    if (n < 0)
    {
        return -1;
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (a[i] != a[i + 1])
        {
            ++count;
        }
    }
    return count;
}

int flip(string a[], int n)
{
    if (n < 0)
    {
        return -1;
    }
    string temp;
    for (int i = 0; i < n / 2; i++)
    {
        temp = a[n - i - 1];
        a[n - i - 1] = a[i];
        a[i] = temp;
    }
    return n;
}

int min(int a, int b)
{
    if (a <= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int detectDifference(const string a1[], int n1, const string a2[], int n2)
{
    // use min function to find smaller array
    for (int i = 0; i < min(n1, n2); i++)
    {
        if (a1[i] != a2[i])
        {
            return i;
        }
    }
    // if (n1 > n2)
    //     return n1;
    // else if (n2 > n1)
    //     return n2;
    // return n1;
    return min(n1, n2);
}

int subsequence(const string a1[], int n1, const string a2[], int n2)
{
    // n2 is comparing subset, n1 is bigger set.
    if (n1 < 0 || n2 < 0)
    {
        return -1;
    }
    if (n2 == 0)
    {
        return 0;
    }
    if (n1 < n2)
    {
        return -1;
    }

    int pos = 0;
    bool flag;
    for (int j = 0; j < n1 - n2 + 1; j++)
    {
        pos = j;
        for (int i = 0; i < n2; i++)
        {
            if (a1[i + j] != a2[i])
            {
                cerr << "a1[i]: " << a1[i] << " a2[j+i]: " << a2[j + i] << endl;
                cerr << "i: " << i << " j: " << j << endl;
                pos = -1;
            }
        }
        if (pos != -1)
        {
            return pos;
        }
    }
    return pos;
}

int detectAny(const string a1[], int n1, const string a2[], int n2)
{
    if (n1 < 0 || n2 < 0)
    {
        return -1;
    }
    for (int i = 0; i < n1; i++)
    {
        for (int j = 0; j < n2; j++)
        {
            if (a1[i] == a2[j])
            {
                return i;
            }
        }
    }
    return -1;
}

bool check_split(string a[], int n, string splitter, int numless)
{
    // if any element greater than splitter is in half its not supposed to be return flase
    for (int i = 0; i < n; i++)
    {
        if (a[i] >= splitter && i < numless)
        {
            return false;
        }
    }
    //     cout << "__________NEEW_________" << endl;
    //     for (int i = 0; i < 6; i++){
    //     cout << "a: " << a[i] << endl;
    // }

    return true;
    // a b f c e
    //     splitter is d
}
int split(string a[], int n, string splitter)
{
    int numLessThan = 0;
    // count number less than
    for (int i = 0; i < n; i++)
    {
        if (a[i] < splitter)
        {
            numLessThan++;
        }
    }
    bool notSolved = true;
    string temp;
    while (notSolved)
    {
        for (int i = 0; i < n - 1; i++)
        {

            if ((a[i] >= splitter && a[i + 1] < splitter))
            {
                temp = a[i + 1];
                a[i + 1] = a[i];
                a[i] = temp;
            }
        }
        // cout << "notSolved: " << notSolved << endl;
        //  check if it is sorted
        notSolved = !check_split(a, n, splitter, numLessThan);
    }
    for (int i = 0; i < n; i++)
    {
        // if splitter in array place at beginning of > than half.
        if (a[i] == splitter)
        {
            temp = a[i];
            a[i] = a[numLessThan];
            a[numLessThan] = temp;
        }
    }

    return numLessThan;
}
