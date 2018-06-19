#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

struct Difference
{
    int startPos;
    int endPos;
    string firstFileVersion;
    string secondFileVersion;
};

int parameterChecker(int argc, char ** argv) // check if parameters were passed correctly
{
    if(argc != 3)
        return 0;
    string str1(argv[1]);
    string str2(argv[2]);
    if(str1.length()>=5 && str1.length()>=5)
    {
        str1 = str1.substr(str1.length() - 4, 4);
        str2 = str2.substr(str2.length() - 4, 4);

        if(str1 == ".txt" && str2 == ".txt")
            return 1;
        return 0;
    }
}

int main(int argc, char ** argv)
{
    cout << parameterChecker(argc, argv);
    return 0;
}