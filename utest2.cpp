#include <cstdio>
#include "Stack_Dyn_Head.h"

int main()
{
    Stack_t stk1;
    Stack_Constructor (stk1);

    *stdout = *(fopen("rtrn2.txt", "w"));

    Stack_Push(&stk1, -666);
    for(int i = 0; i< 12; ++i)
        Stack_Push (&stk1, 1);

    int val;

    for(int i = 0; i< 12; ++i)
        val = Stack_Pop (&stk1);
    val = Stack_Pop (&stk1);
    printf ("value = %d\n", val);

    Stack_Destruct (&stk1);
    fclose(stdout);
    return 0;
}
