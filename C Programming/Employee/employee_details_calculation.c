/*
Write a C program – using structures for reading the employee details
like employee name, date of joining and salary and also to compute
Total salary outgo for a month  
*/

#include<stdio.h>
#include<string.h>

    struct Employee
    {
    char name[20];
    int day;
    char month[10];
    int year;
    float salary;
    };
int main()
{
    struct Employee e[10];
    int total_salary=0;
    int n,i,t;
    char month[10];
    printf ("Enter Number Of Employees: \n");
    scanf ("%d",&n);
    for (i=1; i<=n; i++)
    {
        printf("Enter Employee Name: \n");
        scanf("%s", e[i].name);
        printf("Enter Employee Date of Joining: \n");
        scanf("%d %s %d", &e[i].day, e[i].month, &e[i].year);
        printf("Enter Employee Salary: \n");
        scanf("%f", &e[i].salary);
        
        printf("%s %d %s %d %f\n", e[i].name, e[i].day, e[i].month, e[i].year, e[i].salary);
    }
        printf("Enter the month for total salary: \n");
        scanf("%s",month);
    for(i=1; i<=n; i++)
    {
        t=strcmp(e[i].month, month);
        if(t==0)
        total_salary = total_salary + e[i].salary;
    }
printf ("The total salary for giving month = %f\n", total_salary);
return 0;
}