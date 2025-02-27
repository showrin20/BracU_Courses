#include <stdio.h>

int main() 
{
    char s1[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
    char s2[6] = {'W', 'o', 'r', 'l', 'd', '\0'};
    
    //strcpy(s2,s1);
    strcat(s1,s2);
    printf("s1 message: %s\n", s1);
    printf("s2 message: %s\n", s2);
    return 0;
}

