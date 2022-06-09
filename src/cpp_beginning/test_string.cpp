/*
 *
 * test for string object
 * reference: https://riptutorial.com/cplusplus/topic/488/std--string
 */

#include <string>
#include <iostream>
#include <algorithm>

using std::string;

int main()
{
    string s0;
    string s1("hello");
    string s2{"world"};

    string s3(3, '!');

    std::cout << "s1: " << s1 << std::endl;
    std::cout << "s2: " << s2 << std::endl;

    // add
    s1 += " " + s2;
    s1.append("!");
    s1.append("ww");
    s1.insert(0, "test ");
    s1.insert(s1.begin() + 1, 2, 'm');
    std::cout << "s1(add): " << s1 << std::endl;

    // delete
    s1.erase(s1.begin());
    s1.erase(s1.begin() + 2, s1.begin() + 4);
    s1.pop_back();
    std::cout << "s1(delete): " << s1 << std::endl;
    // remove turn sequence of interator
    s1.erase(std::remove(s1.begin(), s1.end(), 'l'), s1.end());
    std::cout << "s1(delete): " << s1 << std::endl;

    // change
    s1.replace(s1.begin(), s1.begin() + 3, "sss");
    std::cout << "s1(change): " << s1 << std::endl;
    std::replace(s1.begin(), s1.end(), 'w', 't');
    std::cout << "s1(change): " << s1 << std::endl;
    s1.replace(std::find(s1.begin(), s1.end(), 'o'), s1.end(), "x");
    std::cout << "s1(change): " << s1 << std::endl;

    // search
    std::cout << "length of s1: " << s1.size() << std::endl;
    std::cout << "find pos of h: " << s1.find('h') << std::endl;
    std::cout << "find pos of ex: " << s1.find("ex") << std::endl;
    std::cout << "find pos of tx: " << s1.find("tx") << std::endl;
    std::cout << "num of s: " << std::count(s1.begin(), s1.end(), 's') << std::endl;
}