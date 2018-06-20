#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

using namespace std;

class Line;
class Difference;

vector <Line> differentLines;

class Difference
{
public:
    int startPos;
    int endPos;
    string firstFileVersion;
    string secondFileVersion;

    Difference(int startPos, int endPos, const string & firstFileVersion, const string & secondFileVersion)
    {
        this->startPos = startPos;
        this->endPos = endPos;
        this->firstFileVersion = firstFileVersion;
        this->secondFileVersion = secondFileVersion;
    }

};

class Line
{

    string line1;
    string line2;
    vector <Difference> differences;
    bool different = 0;

public:

    Line(const string & _line1, const string & _line2)
    {
        line1 = _line1;
        line2 = _line2;
    }

    void findDifferences()
    {
        if(line1 == line2)
            return;
        else
        {
            Line *thisLine = new Line(line1, line2);
            string differenceString1 = "";
            string differenceString2 = "";

            if(line1.length() == line2.length()) // if lines are of the same size
            {
                int startPos = -1;
                int endPos = -1;


                for(int i = 0; i < line1.length(); i++)
                {
                    if(line1[i]!=line2[i] && startPos == -1) // if it's new difference
                    {
                        startPos = i;
                        differenceString1 += line1[i];
                        differenceString2 += line2[i];
                    }
                    else if(line1[i]!=line2[i] && startPos != -1) // still the same difference, so only updating difference strings
                    {
                        differenceString1 += line1[i];
                        differenceString2 += line2[i];
                    }
                    else if (line1[i] == line2[i] && startPos != -1) // end of the difference
                    {
                        endPos = i-1;
                        thisLine->differences.emplace_back(startPos, endPos, differenceString1, differenceString2);
                        startPos = -1;
                        endPos = -1;
                        differenceString1 = "";
                        differenceString2 = "";
                    }
                }
                if(endPos == -1 && startPos != -1) // if line ended and last difference is still not complete, then the end of the difference is the end of the line
                {
                    endPos = (int)line1.length()-1;
                    thisLine->differences.emplace_back(startPos, endPos, differenceString1, differenceString2);
                }
                differentLines.push_back(*thisLine);
            }
        }
        }

    void printDifferences()
    {
        for(auto const & value : differences)
        {
            cout << endl << "In positions " << value.startPos << " - " << value.endPos << endl << "Version 1: " << value.firstFileVersion << endl << "Version 2: " << value.secondFileVersion << endl;
        }
    }
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
    ifstream firstFile, secondFile;
    openFiles(argv, firstFile, secondFile);

    return 0;
}