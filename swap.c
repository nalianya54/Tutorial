#include <stdio.h>
void swapfunc(int* num1, int* num2)
{
    int swap = *num1;
    *num1 = *num2;
    *num2 = swap;
}

int main()
{
    int a = 5;
    int b = 7;
    printf("before swapping a = %d, b = %d\n", a, b);
    swapfunc(&a, &b);
    printf("after swaping a = %d, b = %d\n", a, b);
    return 0;
}
