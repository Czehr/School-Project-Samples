#include <stdio.h>
#include <stdlib.h>

/* Convert Decimal to base n */
void decimalBaseConvert(int decimal, int base)
{
    /* Base Case */
    if (decimal == 0)
        return;

    /* Get remainder */
    int remainder = decimal % base;

    /* Get decimal for next call */
    decimal = decimal / base;

    if(remainder < 0)
        decimal += 1;

    /* Recursive call for rest of output string */
    decimalBaseConvert(decimal, base);

    /* Print current digit */
    if (remainder < 0)
        printf("%d, ", remainder - base);
    else
        printf("%d, ", remainder);
}


int main(int argc, char **argv[])
{
    int decimal, base;

    /* Convert inputs to integers */
    decimal = atoi(argv[1]);
    base    = atoi(argv[2]);

   if(decimal !=0)
   {
        decimalBaseConvert(decimal, base);
        printf("\n");
   }
   else
        printf("0\n");

    return 0;
};
