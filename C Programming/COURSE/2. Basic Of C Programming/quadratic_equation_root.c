#include<stdio.h>
main()
{
  float a, b, c, discriminant, root1, root2;
  printf("Input the values of a, b and c\n");
  scanf("%f %f %f", &a, &b, &c);

  discriminant = b * b - 4 * a * c;
  if (discriminant < 0){
      printf("Roots are imaginary");
  }
  else {
      root1 = (-b + sqrt(discriminant))/(2 * a);
      root1 = (-b - sqrt(discriminant))/(2 * a);
      printf("Root1 = %5.2f\n Root2 = %5.2f\n", root1, root2);
  }
return 0;
)
