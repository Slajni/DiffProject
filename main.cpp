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

public:

    int lineNumber;
    vector <Difference> differences;

    Line(const string & _line1, const string & _line2, int lineNumber)
    {
        line1 = _line1;
        line2 = _line2;
        this->lineNumber = lineNumber;
    }

    void findDifferences()
    {
        if(line1 == line2)
            return;
        else
        {
            string differenceString1 = "";
            string differenceString2 = "";
            int startPos = -1;
            int endPos = -1;

            if(line1.length() == line2.length()) // if lines are of the same size
            {

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
                        this->differences.emplace_back(startPos, endPos, differenceString1, differenceString2);
                        startPos = -1;
                        endPos = -1;
                        differenceString1 = "";
                        differenceString2 = "";
                    }
                }
                if(endPos == -1 && startPos != -1) // if line ended and last difference is still not complete, then the end of the difference is the end of the line
                {
                    endPos = (int)line1.length()-1;
                    this->differences.emplace_back(startPos, endPos, differenceString1, differenceString2);
                }
                differentLines.push_back(*this);
            }
            else if(line1.length()!=line2.length()) // if lines are not the same size
            {
                string longerLine;
                string shorterLine;
                bool firstLonger = 0;
                if(line1.length() > line2.length()) // looking for longer line
                {
                    longerLine = line1;
                    shorterLine = line2;
                    firstLonger = 1;
                }
                else
                {
                    longerLine = line2;
                    shorterLine = line1;
                }

                if(shorterLine == longerLine.substr(0,shorterLine.length())) // if the lines are the same only one of them has something added at the end
                {
                    differenceString1 = longerLine.substr(shorterLine.length(),longerLine.length()-shorterLine.length()); // catch the added value to the longer line
                    startPos = shorterLine.length();
                    endPos = longerLine.length();
                    if(firstLonger == 1)
                        this->differences.emplace_back(startPos, endPos, differenceString1, "");
                    else
                        this->differences.emplace_back(startPos, endPos, "", differenceString1);
                }
                else
                {
                    for(int i = 0; i < shorterLine.length(); i++)
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
                            this->differences.emplace_back(startPos, endPos, differenceString1, differenceString2);
                            startPos = -1;
                            endPos = -1;
                            differenceString1 = "";
                            differenceString2 = "";
                        }
                    }
                    if(endPos == -1 && startPos != -1) // if line ended and last difference is still not complete, then the end of the longer word is the end of the line
                    {
                        endPos = (int)longerLine.length()-1;
                        this->differences.emplace_back(startPos, endPos, differenceString1, differenceString2);
                    }
                    else
                    {
                        differenceString1 = longerLine.substr(shorterLine.length(),longerLine.length()-shorterLine.length()); // catch the added value to the longer line
                        startPos = shorterLine.length()-1;
                        endPos = longerLine.length()-1;
                        if(firstLonger == 1)
                            this->differences.emplace_back(startPos, endPos, differenceString1, "");
                        else
                            this->differences.emplace_back(startPos, endPos, "", differenceString1);
                    }
                }

                differentLines.push_back(*this);
            }
        }
    }

    void printDifferences() const
    {
        for(auto const & value : differences)
        {
            cout << endl << "In line: " << this->lineNumber <<  "  In positions " << value.startPos << " - " << value.endPos << endl << "Version 1: " << value.firstFileVersion << endl << "Version 2: " << value.secondFileVersion << endl;
        }
    }
    void printCurDifference(const Difference & value) const
    {
        cout << endl << "In line: " << this->lineNumber <<  "  In positions " << value.startPos << " - " << value.endPos << endl << "Version 1: " << value.firstFileVersion << endl << "Version 2: " << value.secondFileVersion << endl;
    }
    string chooseVersion() const
    {
        string result = "";
        int choice = 0;
        int base = 0;
        int nextDifStartPos;

        for (auto const &value: differences)
        {
            nextDifStartPos = value.startPos;
            for (base; base < nextDifStartPos; base++)
            {
                result += this->line1[base];
            }
            printCurDifference(value);
            cout << endl << "Choose 1 if you want to keep version from first file or any other value if you want to keep verion from 2nd one: " << endl;
            cin >> choice;
            if(choice == 1)
            {
                result += value.firstFileVersion;
            }
            else
            {
                result += value.secondFileVersion;
            }
            base = value.endPos + 1;
        }
        if(base < this->line1.length())
            for(base; base < line1.length(); base++)
                result += this->line1[base];

        return result;
    }
};


bool parameterChecker(int argc, char ** argv) // check if parameters were passed correctly
{
    if(argc != 3)
        return false;
    string str1(argv[1]);
    string str2(argv[2]);
    if(str1.length()>=5 && str1.length()>=5)
    {
        str1 = str1.substr(str1.length() - 4, 4);
        str2 = str2.substr(str2.length() - 4, 4);

        if(str1 == ".txt" && str2 == ".txt")
            return true;
        return false;
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
    if(parameterChecker(argc,argv))
    {
        ifstream firstFile, secondFile;
        openFiles(argv, firstFile, secondFile);

        string firstFileLine;
        string secondFileLine;
        int curline = 0;
        Line * lineToCheck;

        while (true)
        {
            getline(firstFile, firstFileLine);
            getline(secondFile, secondFileLine);

            if (firstFile.eof() && secondFile.eof())
                break;

            curline++;
            if(firstFile.eof())
            {
                Line *lastLines = new Line("", secondFileLine, curline);
                lastLines->findDifferences();
                while(getline(secondFile,secondFileLine))
                {
                    delete lastLines;
                    curline++;
                    lastLines = new Line("", secondFileLine, curline);
                    lastLines->findDifferences();
                }
                delete lastLines;
            }
            else if(secondFile.eof())
            {
                Line *lastLines = new Line(firstFileLine,"", curline);
                lastLines->findDifferences();
                while(getline(firstFile,firstFileLine))
                {
                    delete lastLines;
                    curline++;
                    lastLines = new Line(firstFileLine,"", curline);
                    lastLines->findDifferences();
                }
                delete lastLines;
            }
            lineToCheck = new Line(firstFileLine, secondFileLine, curline);
            lineToCheck->findDifferences();

            delete lineToCheck;

        }

        firstFile.close();
        secondFile.close();
        firstFile.open(argv[1]);
        ofstream resultFile;
        resultFile.open("result.txt");

        int nextline = -1; // used for loop as condition to iterate through non different lines
        int base = 1; // --- || ---
        string lineToPrint;
        for (auto const &value: differentLines)
        {
            nextline = value.lineNumber;
            for (base; base < nextline; base++)
            {
                getline(firstFile, lineToPrint);
                resultFile << lineToPrint << endl;
            }
            base++;
            getline(firstFile, lineToPrint);
            lineToPrint = value.chooseVersion();
            resultFile << lineToPrint << endl;
        }

        resultFile.close();
        firstFile.close();
    }
    else
    {
        cout << endl << "Wrong parameters";
        //help();
    }





    return 0;
}