// Write a program in java to check whether  a Number is Positive or Negative using if else.

    
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter a number: ");
        int num = sc.nextInt();

        if (num > 0) {
            System.out.println("positive number");
        } else if (num < 0) {
            System.out.println("negative number");
        } else {
            System.out.println("zero");
        }

        sc.close();
    }
}
