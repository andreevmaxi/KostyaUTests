#include <cstdio>
#include <cassert>
#include <cstdio>
#include "Stack_Dyn_Head.h"

const int TNumber = 4;

bool PrintError(FILE* fr, FILE* fw); // prints errors in errors

bool AnswCompare(int NumberOfTest, FILE* Errors, FILE* Normal); // return 1 if it's correct \\ 0 if not

int main()
    {
    FILE* Errors = fopen("ErrorTests.txt", "w");
    FILE* TestDone = fopen("ResultTests.txt", "w");

    char FileRtrnName[10] = "rtrn0.txt";
    char TestName[11] = "utest0.exe";

    for(int i = 1; i <= TNumber; ++i)
        {
        TestName[5] = i + '0';

        system(TestName);
        AnswCompare(i, Errors, TestDone);
        }
    }

bool AnswCompare(int NumberOfTest, FILE* Errors, FILE* Normal)
    {
    char FileRtrnName[10] = "rtrn0.txt";
    FileRtrnName[4] = NumberOfTest + '0';

    char FileAnswName[10] = "answ0.txt";
    FileAnswName[4] = NumberOfTest + '0';

    FILE* FileRtrn = fopen(FileRtrnName, "r");
    FILE* FileAnsw = fopen(FileAnswName, "r");

    bool IsAnsIsGood = 1;
    int CharChange = 0;
    int StrProblem = 0;
    int CharOnProblemStr = 0;
    char tmp1 = {};
    char tmp2 = {};
    char Result[4] = {};
    Result[3] = '\0';

    fseek(FileRtrn, 0L, SEEK_END);
    int Tmp1Size = ftell(FileRtrn);
    rewind(FileRtrn);

    fseek(FileAnsw, 0L, SEEK_END);
    int Tmp2Size = ftell(FileAnsw);
    rewind(FileAnsw);

    if(Tmp1Size != Tmp2Size)
        {
        IsAnsIsGood = 0;
        }


    while ( (tmp1 = getc (FileRtrn)) != EOF && (tmp2 = getc (FileAnsw)) != EOF && IsAnsIsGood )
        {
        ++CharChange;
        ++CharOnProblemStr;
        while(tmp2 == '\r')
            {
            (tmp2 = getc (FileAnsw));
            }
        while(tmp1 == '\r')
            {
            (tmp1 = getc (FileRtrn));
            }
        if(tmp1 == '\n')
            {
            CharOnProblemStr = 0;
            ++StrProblem;
            }
        }

    if (IsAnsIsGood)
        {
        Result[0] = 'O';
        Result[1] = 'K';
        Result[2] = ' ';
        } else
        {
        rewind(FileRtrn);
        rewind(FileAnsw);

        fprintf(Errors, "Error test%d:\nCharProblem = %d\nStrProblem = %d\nCharOnProblemStr = %d\ntext output:\n\n", NumberOfTest, CharChange, StrProblem, CharOnProblemStr);
        PrintError(FileRtrn, Errors);

        fprintf(Errors, "\n\nTest Ans:\n\n", NumberOfTest);
        PrintError(FileAnsw, Errors);
        fprintf(Errors, "\n\n");
        Result[0] = 'B';
        Result[1] = 'A';
        Result[2] = 'D';
        }
        fprintf(Normal, "Test number %d , result is %s\n\n", NumberOfTest, Result);

        }

bool PrintError(FILE* fr, FILE* fw)
    {
    assert(fr != NULL);
    assert(fw != NULL);

    char tmp = {};
    while ( (tmp = getc (fr)) != EOF)
    {
        fprintf(fw, "%c", tmp);
    }
    return 0;
    }

