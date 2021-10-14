#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include <malloc.h>
#include "Functions.h"


int main()
{
    HTMLTag* obj[10];

    obj[0] = init(get_tag());
    printObj(obj[0]);
    deleteMemory(obj[0]);

    obj[1] = init(get_tag());
    printObj(obj[1]);
    deleteMemory(obj[1]);


}