//!@file

#include <stdio.h>
#include "Stack_Dyn_Head.h"



int main()
{
    elem_t x = 6;

    Stack_t stk1 = {};
    Stack_Constructor (stk1);
    /*
    stk1.max_size = 100;
    stk1.data[78] = (elem_t) stk1.canary_arr_back;
    stk1.size = 90;*/

    Stack_Push (&stk1, 27);

    int val = Stack_Pop (&stk1);

    printf ("value = %d\n", val);

    Stack_Destruct (&stk1);

    Unitest ();

    return 0;
}
