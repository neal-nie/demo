/*
 *
 * test for vector operation
 */

#include <vector>
#include <string>
#include <iostream>

using std::string;
using std::vector;

int main()
{
    vector<string> vec{"hello", "world", "c++"};
    for (const auto &s : vec)
    {
        std::cout << "sub string is: " << s << std::endl;
    }
    return 0;
}