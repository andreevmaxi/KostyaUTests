#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#define empty -666

#define Stack_Constructor( this )         \
    this.name = #this;                    \
    Stack_Construct ( &this );

#define Dump( this )                      \
    Dump_Def ( &this , __LINE__, __FILE__, __PRETTY_FUNCTION__);


//! These are codes of possible errors.
enum Error_codes {OK, Stack_OverFlow, Stack_Empty, Canary_Stack_Dead, Canary_Arr_Dead, Wrong_Hash};

const double multy = 1.7;

const int MAX_SIZE = 5;

const long int can_size = 27272727;

typedef int elem_t;

struct Stack_t
{
    long int canary_front;
    elem_t* data;
    int size;
    int max_size;
    char* name;
    int error;
    long int* canary_arr_front;
    long int* canary_arr_back;
    long int canary_back;
    long int hash;
};

int Dump_Def (Stack_t* stk, const int line, const char* file, const char* function);

long Hash (Stack_t* stk);

int Size_Change (Stack_t* stk, int new_size);

int Stack_Construct (Stack_t* stk);

int Stack_Destruct (Stack_t* stk);

int Stack_OK (Stack_t* stk);

elem_t Stack_Pop (Stack_t* stk);

int Stack_Push (Stack_t* stk, elem_t value);

int Unitest (void);


/*!
@detailed This function is claimed from #define Dump(...).
It gives to a user all information about Stack condition. For instance:
Name; line, file, function from which it was used; pointer to the Stack;
the Stack error code; current amount of elements, maximal amount of
elements which is allocated; all current elements of the Stack.
@param[in] stk The pointer to the element of the Stack.
@param[in] line The line in which the element is used.
@param[in] file The file in which the element is used.
@param[in] function The function in which the element is used.

@param[out] The error code of the element of the Stack.
*/
int Dump_Def (Stack_t* stk, const int line, const char* file, const char* function)
{
    Stack_OK (stk);

    printf ("\n\n\nFrom file %s, line %d, function \"%s\"\n", file, line, function);
    printf ("Stack_t \"%s\" [0x%x]", stk->name, stk);
    if (stk->error == 0)
        printf (" (OK)\n");
    else printf (" (Error)\n");
    printf ("{\n    current size = %d\n", stk->size);
    printf ("    maximal allocated size = %d\n", stk->max_size);
    if (stk->error == Canary_Stack_Dead) printf ("    Expected left stack canary %ld, received left stack canary is %ld, Expected right stack canary %ld, received right stack canary is %ld\n", can_size, stk->canary_front, can_size, stk->canary_back);
    if (stk->error == Canary_Arr_Dead)   printf ("    Expected left data canary %ld, received left data canary is %ld, Expected right data canary %ld, received right data canary is %ld\n", can_size, *(stk->canary_arr_front), can_size, *(stk->canary_arr_back));
    printf ("    hash = %ld, expected %ld\n", stk->hash, Hash (stk));
    printf ("    data[%d] = [0x%x]\n", stk->max_size, stk->data);
    printf ("     {\n");

    int i = 0;
    for (i = 0; i < stk->max_size; i++)
    {
        if (i < stk->size)
            printf ("          *");
        else printf ("           ");

        printf ("[%d] = %d", i, stk->data[i]);
        if (*(stk->data + i) == empty)
            printf (" [It might be empty]");
        printf ("\n");
    }

    printf ("     }\n");
    printf ("Error = %d\n", stk->error);
    printf ("}\n\n\n");

    return stk->error;
}

/*!
@brief It finds hash of the stack.
@param[in] A pointer to the element of the structure.
*/

long int Hash (Stack_t* stk)
{
    assert (stk);

    int i = 0;
    int j = 0;
    long sum = 0;

    char* pointer = (char*)stk;

    long int hash_const = 0xA1B3C4F9;

    for (j = 0; j < sizeof (Stack_t) - sizeof (stk->hash); j++)
    {
        sum += *(pointer + j) * (j + 1);
        sum ^= hash_const;
        sum << 2;
    }

    for (i = 0; i < stk->size; i++)
        sum += *(stk->data + i) * (i + 1);

    return sum;
}


/*!
@brief This function creates an element of the Stack.
@param[in] stk The pointer to the Stack.
*/

int Stack_Construct (Stack_t* stk)
{
    assert (stk);

    int i = 0;
    stk->data = (elem_t*)((long*)calloc (1, sizeof (elem_t) * MAX_SIZE + 2 * sizeof(long)) + 1);

    for (i = 0; i < MAX_SIZE; i++)
        *((elem_t*)stk->data + i) = empty;

    stk->size = 0;
    stk->max_size = MAX_SIZE;
    stk->error = 0;

    stk->canary_arr_front = (long int*)stk->data - 1;
    stk->canary_arr_back = (long int*) ((elem_t*)stk->data + MAX_SIZE);

    stk->canary_front = can_size;
    *(stk->canary_arr_front) = can_size;
    *(stk->canary_arr_back) = can_size;
    stk->canary_back = can_size;
    stk->hash = Hash (stk);

    if (Stack_OK (stk))
        {
            Dump (*stk);
            return Stack_OK (stk);
        }
    return 0;
}

/*!
@brief This function cleans the existing element of Stack.
@param[in] stk The pointer to an element of the Stack.
*/

int Stack_Destruct (Stack_t* stk)
{
    assert (stk);

    int i = 0;
    free (stk->data);

    stk->size = 0;
    stk->max_size = MAX_SIZE;
    stk->error = 0;
    stk->hash = 0;

    return 0;
}

/*!
@brief This function checks whether everything is O'kay with the element of the Stack.
@param[in] stk The pointer to an element of the Stack.
\return The code of the error in the element of string.
*/

int Stack_OK (Stack_t* stk)
{
    if (stk->size < 0)
    {
        stk->error = Stack_Empty;
        return Stack_Empty;
    }

    if (stk->size > stk->max_size)
    {
        stk->error = Stack_OverFlow;
        return Stack_OverFlow;
    }

    if (stk->canary_front != can_size || stk->canary_back != can_size)
    {
        stk->error = Canary_Stack_Dead;
        return Canary_Stack_Dead;
    }

    if (*((long int*)stk->data - 1) != can_size || *((long int*)((elem_t*)stk->data + stk->max_size)) != can_size)
    {
        stk->error = Canary_Arr_Dead;
        return Canary_Arr_Dead;
    }

    if ((stk->hash) != Hash (stk))
    {
        stk->error = Wrong_Hash;
        return Wrong_Hash;
    }

    return stk->error;

}

/*!
@brief This function receives an element of the Stack.
@param[in] stk The pointer to an element of the Stack.
\return The last element of the Stack.
*/

elem_t Stack_Pop (Stack_t* stk)
{
    assert (stk);

    if (Stack_OK (stk))
    {
        Dump (*stk);
        return Stack_OK (stk);
    }

    if (stk->size <= 0)
    {
        stk->error = Stack_Empty;
        stk->hash = Hash (stk);
        Dump (*stk);
        return empty;
    }

    stk->size--;

    if (stk->size <= (stk->max_size / multy - 2) && stk->size > MAX_SIZE)
        Size_Change (stk, (int)(stk->max_size / multy - 2));


    elem_t answer = *(stk->data + stk->size);
    *(stk->data + stk->size) = empty;

    if (stk->error == Stack_OverFlow)
        stk->error = OK;

    stk->hash = Hash (stk);

    if (Stack_OK (stk)) Dump (*stk);

    return answer;
}

/*!
@brief This function puts an element to the Stack.
@param[in] stk The pointer to an element of the Stack.
@param[in] value The value of a variable to put into the Stack.
\return The code of an error.
*/
int Stack_Push (Stack_t* stk, elem_t value)
{
    assert (stk);

    if (Stack_OK (stk))
    {
        Dump (*stk);
        return Stack_OK (stk);
    }

    if (stk->size >= stk->max_size)
    {
        stk->error = Stack_OverFlow;
        Dump (*stk);
        return Stack_OverFlow;
    }

    *(stk->data + stk->size++) = value;
    stk->hash = Hash (stk);

    if (stk->size >= stk->max_size)
        Size_Change (stk, (int)(stk->max_size * multy));


    if (stk->error == Stack_Empty)
        stk->error = OK;

    stk->hash = Hash (stk);

    if (Stack_OK (stk)) Dump (*stk);

    return OK;
}

/*!
@brief This function reallocates the Stack.
@param[in] stk The pointer to an element of the Stack.
@param[in] new_size The new amount of the elements in the Stack.
\return Error code.
*/

int Size_Change (Stack_t* stk, int new_size)
{
    assert (stk);

    if (Stack_OK (stk))
    {
        Dump (*stk);
        return Stack_OK (stk);
    }

    if (new_size <= 0)
        return 1;



    stk->data = (elem_t*)((long*)(realloc ((long*)stk->data - 1, sizeof(elem_t) * new_size + 2 * sizeof(long))) + 1);

    int i = 0;
    for (i = stk->max_size; i < new_size; i++)
        *(stk->data + i) = empty;

    stk->max_size = new_size;

    stk->canary_arr_front = (long int*)stk->data - 1;
    stk->canary_arr_back = (long int*) ((elem_t*)stk->data + stk->max_size);

    *(stk->canary_arr_front) = can_size;
    *(stk->canary_arr_back) = can_size;

    stk->hash = Hash (stk);

    if (Stack_OK (stk)) Dump (*stk);

    return 0;
}
