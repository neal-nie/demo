/* demo for string in stl of cpp */

#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    string s0;
    string s1;

    s0 = "demo string";
    s1 = s0;

    // assign
    cout << s0 << endl;
    cout << s1 << endl;

    string s2;
    s2 += s1;
    s2 += s0;
    cout << s2 << endl;


    cout << s2.substr(2, 3) << endl;

    // compare
    string s3 = "test";
    bool flg = s3 > s1;
    bool flg2 = s1 == s0;
    cout << hex << 11 << flg << endl;
    cout << flg2 << endl;
    cout << quoted(s2.substr(4)) << endl;

    // append
    s3.append(5, 'x');
    cout << "s3 is :" << s3 << endl;

    s3.append(s1);
    cout << "s3 is :" << s3 << endl;

    s3.push_back('t');
    cout << "s3 is :" << s3 << endl;

    cout << "s3[5] is :" << s3.at(5) << endl;

    // find
    string::size_type n;
    n = s1.find('o');
    bool found = n != string::npos;
    cout << "found: " << found << "following string: " << s1.substr(n + 1) << endl;

    // insert

    s1.insert(4, 1, 'p');
    cout << "after insert, get s1: " << s1 << endl;

    s1.insert(4, "demo String");
    cout << "after insert, get s1: " << s1 << endl;
    // size
    cout << "size of s1: " << s1.size() << endl;
    cout << "length of s1: " << s1.length() << endl;

    // delete data in specific index
    cout << "delete first 4 letter in s1: " << endl
         << '\t' << s1.erase(0, 4) << endl;

    // replace data in specific index
    cout << "replace first 4 letter in s1 with read: " << endl
         << '\t' << s1.replace(0, 4, "read") << endl;

    return 0;
}