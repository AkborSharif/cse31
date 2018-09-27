#include <stdio.h>
int main()
{
char name[50];
printf("Please enter your name: ");
scanf("%49[0-9a-zA-Z ]", name);
printf("Welcome to CSE031, %s!\n", name);
return 0;
}
