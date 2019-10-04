#include <cstdio>
#include "Stack_Dyn_Head.h"

int main()
{
    Stack_t stk1;
    Stack_Constructor (stk1);

    *stdout = *(fopen("rtrn4.txt", "w"));

    Stack_Push(&stk1, -666);
    stk1.name = NULL;
    printf("value = %d", Stack_Pop(&stk1));
    Stack_Destruct (&stk1);
    fclose(stdout);
    return 0;
}
