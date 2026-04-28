/*Write a C program to input base and height of a triangle and find area of the given triangle. 
How to find area of a triangle in C programming. 
Logic to find area of a triangle in C program.*/

#include <stdio.h>

int main() {
    float base, height, area;

    printf("Enter base of the triangle: ");
    scanf("%f", &base);

    printf("Enter height of the triangle: ");
    scanf("%f", &height);

    area =  base * height;
    area = area / 2;

    printf("Area of the triangle: %.2f\n", area);

    return 0;
}