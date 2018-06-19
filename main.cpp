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

inline int openFiles(char ** argv, ifstream & File1, ifstream & File2)
{
    File1.open(argv[1]);
    File2.open(argv[2]);
    if(File1 && File2) // file have been sucessfully opened
        return 1; // 1 - opened
    return 0; // failed to open
}

int main(int argc, char ** argv)
{
    cout << parameterChecker(argc, argv);
    ifstream firstFile, secondFile;
    openFiles(argv, firstFile, secondFile);

    return 0;
}