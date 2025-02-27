#include <stdio.h>

int main()
{
    int num;
    float fnum;
    char str[100];


    printf("Enter an integer: ");
    scanf("%d", &num);
    printf("You entered: %d\n", num);

    printf("Enter a floating-point number: ");
    scanf("%f", &fnum);
    printf("You entered: %.2f\n", fnum);

    
    printf("Enter a string: ");
    scanf("%s", str); 
    printf("You entered: %s\n", str);

    return 0;
}

