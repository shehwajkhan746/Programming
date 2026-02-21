//Write a C program to find the factorial of a given integer number using both recursive and non-recursive functions.

//Non-Recursive Function
#include<stdio.h>
int main()
{
int n,i,f;
printf("Enter the number:\n ");
scanf("%d",&n);
f=1;
for(i=1;i<=n;i++)
f=f*i;
printf("Factorial of %d = %d",n,f);
return 0;
}

