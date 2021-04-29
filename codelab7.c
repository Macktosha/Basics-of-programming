#include <stdio.h>
#include <math.h>
int bitcounter(long int x);
void main()
{
        int Number;// исходное число
        unsigned long value;// версия без знака
        int i,range;//вспомогательные счетчики и ячейки для циклов и сравнения
            i=range=0
            printf ("Enter the value of number to find searchable range: \n");
            scanf ("%ld",&Number);
            value = (unsigned int) Number;
                range=bitcounter(value);
    if ((i=range%2)==1)
    {
        range=range/2+1;
        printf ("Number of your range = %d\n",range);
    }
    else
        printf ("There is no correct range in your number\n");
}
int bitcounter(long int x)
{
    int counter;
    counter=0;
        while (x!=0)
        {
            counter++;
            x=x>>1;
        }
    return counter;
}