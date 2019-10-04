#include <cstdio>
#include "Stack_Dyn_Head.h"

bool AnswCompare(int NumberOfTest); // return 1 if it's correct \\ 0 if not

int main()
    {

    }

bool AnswCompare(int NumberOfTest)
    {
    char FileRtrnName[10] = "rtrn0.txt";
    FileRtrnName[4] = NumberOfTest + '0';

    char FileAnswName[10] = "answ0.txt";
    FileAnswName[4] = NumberOfTest + '0';

    FILE* FileRtrn = fopen(FileRtrnName, "r");
    FILE* FileAnsw = fopen(FileAnswName, "r");

    bool IsRtrnIsGood = 1;
    int CharChange = 0;
    int StrProblem = 0;
    int CharOnProblemStr = 0;
    char tmp1 = {};
    char tmp2 = {};
    char Result[4] = {};
    Result[3] = '\0';

    while ( (tmp1 = getc (FileRtrn)) != EOF && (tmp2 = getc (FileAnsw)) != EOF && IsAnsIsGood )
    {
        ++CharChange;
        ++CharOnProblemStr;
        while(tmp2 == '\r')
        {
            (tmp2 = getc (NiceAns));
        }
        while(tmp1 == '\r')
        {
            (tmp1 = getc (FuncAns));
        }
        if(tmp1 == '\n')
        {
            CharOnProblemStr = 0;
            ++StrProblem;
        }
        if(tmp1 != tmp2)
        {
            IsAnsIsGood = 0;
        }
    }

    if (IsAnsIsGood)
    {
        Result[0] = 'O';
        Result[1] = 'K';
        Result[2] = ' ';
    } else
    {
        rewind(FuncAns);
        rewind(NiceAns);

        fprintf(Errors, "Error test%d:\nCharProblem = %d\nStrProblem = %d\nCharOnProblemStr = %d\ntext output:\n\n", i, CharChange, StrProblem, CharOnProblemStr);
        PrintError(FuncAns, Errors);

        fprintf(Errors, "\n\nTest Text:\n\n", i);
        FILE* TestS = fopen(NowTest, "rb");
        PrintError(TestS, Errors);

        fprintf(Errors, "\n\nTest Ans:\n\n", i);
        PrintError(NiceAns, Errors);
        fprintf(Errors, "\n\n");
        Result[0] = 'B';
        Result[1] = 'A';
        Result[2] = 'D';
    }
    printf("Test number %d , result is %s\n\n", NumberOfTest, Result);
    }

