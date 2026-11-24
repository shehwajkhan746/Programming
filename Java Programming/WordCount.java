// Write a program to count the words in a sentence

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter a sentence: ");
        String sentence = sc.nextLine().trim();

        int count = 0;
        if (!sentence.isEmpty()) {
            String[] words = sentence.split("\\s+");
            count = words.length;
        }

        System.out.println("Number of words: " + count);
        sc.close();
    }
}