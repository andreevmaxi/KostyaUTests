#include <cstdio>
#include "Stack_Dyn_Head.h"

int main()
{
    *stdout = *(fopen("rtrn1.txt", "w"));

    Stack_t stk1;
    Stack_Constructor (stk1);

    Stack_Push (&stk1, 27);

    int val = Stack_Pop (&stk1);

    printf ("value = %d\n", val);

    Stack_Destruct (&stk1);
    fclose(stdout);

    return 0;
}
