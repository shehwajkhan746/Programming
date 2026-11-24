// Write a Java program to insert an element of an array at the end

import java.util.Scanner;

public class array {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter number of elements: ");
        int n = sc.nextInt();

        int[] arr = new int[n];
        System.out.println("Enter " + n + " elements:");
        for (int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        System.out.print("Enter element to insert at the end: ");
        int element = sc.nextInt();

        int[] newArr = new int[n + 1];

        for (int i = 0; i < n; i++) {
            newArr[i] = arr[i];
        }

        newArr[n] = element;

        System.out.print("Array after insertion: ");
        for (int i = 0; i < newArr.length; i++) {
            System.out.print(newArr[i] + " ");
        }

        sc.close();
    }
}