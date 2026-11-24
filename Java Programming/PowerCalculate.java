// Write a java program to calculate power of a number using a while loop

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter base: ");
        int base = sc.nextInt();

        System.out.print("Enter exponent: ");
        int exponent = sc.nextInt();

        long result = 1;
        int count = exponent;

        while (count != 0) {
            result *= base;
            count--;
        }

        System.out.println(base + " ^ " + exponent + " = " + result);
        sc.close();
    }
}

