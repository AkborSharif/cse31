#include <stdio.h>
int main()
{
int num,typo;
printf("Enter the number of lines for the punishment: ");
scanf("%d",& num);
if (num<=0)
{
printf("You entered an incorrect value for the number of lines! ");  
return 0;
}


printf("Enter the line for which we want to makea typo: ");
scanf("%d",& typo);
if (typo<=0||typo>num)
{
printf("You entered an incorrect value for the line typo!");
return 0;  
}

for(int i = 1; i<=num; i++)
{
if (i==typo)
{
   printf("C programming language is the bet!\n" );
}
else {
printf("C programming language is the best!\n");
}
}
}
