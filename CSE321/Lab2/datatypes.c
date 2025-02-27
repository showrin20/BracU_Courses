#include <stdio.h>
int main ()
{
    int a, b;
    int c;
    float f;
    double d;
    char k;
    
    a = 10;
    b = 20;
    c = a + b;
    printf("value of c : %d \n", c);

    f = (float)5/2;
    printf("value of f : %f \n", f);
    
    printf("int %d \n", sizeof(a));
    printf("float %d \n", sizeof(f));
    printf("double %d \n", sizeof(d));
    printf("char %d \n", sizeof(k));
    return 0;
}

