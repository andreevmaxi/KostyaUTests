#include <cstdio>
#include "Stack_Dyn_Head.h"

int main()
{
    *stdout = *(fopen("rtrn3.txt", "w"));
    Stack_t stk1;
    Stack_Constructor (stk1);


    Stack_Push(&stk1, -666);
    for(int i = 0; i< 2; ++i)
        Stack_Push (&stk1, 1);

    int val;

    for(int i = 0; i< 2; ++i)
        val = Stack_Pop (&stk1);
    val = Stack_Pop (&stk1);
    printf ("value = %d\n", val);

    Stack_Destruct (&stk1);
    fclose(stdout);

    return 0;
}
