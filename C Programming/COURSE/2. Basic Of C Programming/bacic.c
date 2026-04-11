#include <stdio.h>
#define N 10  //symbolic constant

main()
{ 
    int count;  //declaration of variable count
    float sum, average, number;  //declaration of variables sum, average and number
    sum = 0;    //initialization of variable sum
    count = 0;  //initialization of variable count
    
    while (count < N)
    {
        printf("Enter a number: ");
        scanf("%f", &number);
        sum = sum + number;
        count = count + 1;
    }
    average = sum / N;
    printf("N = %d   Sum = %f", N, sum);
    printf("The average is: %f\n", average);

    return 0;
}
