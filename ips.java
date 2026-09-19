import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class PasswordStrengthIndex {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Welcome to the Index for Password Strength (IPS)!");

        System.out.print("\nEnter your password (8-15 characters): ");
        String passwd = scanner.next();

        if (passwd.length() < 8) {
            System.out.println("Invalid Password Length, tip: add more characters!");
            return;
        }
        if (passwd.length() > 15) {
            System.out.println("Invalid Password Length, tip: less characters please!");
            return;
        }

        double basicScore = 0, lengthScore = 0, repetitionScore = 0, complexityScore = 0;

        List<String> basicProblems = new ArrayList<>();
        List<String> lengthProblems = new ArrayList<>();
        List<String> repetitionProblems = new ArrayList<>();
        List<String> complexityProblems = new ArrayList<>();

        String lower = "abcdefghijklmnopqrstuvwxyz";
        String upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        String nums = "0123456789";
        String special = "!@#$%^&*()-_{}[]|;:.,?\\<>+~`=";

        boolean hasLower = false, hasUpper = false, hasNum = false, hasSpecial = false;

        for (char c : passwd.toCharArray()) {
            if (lower.indexOf(c) != -1) hasLower = true;
            if (upper.indexOf(c) != -1) hasUpper = true;
            if (nums.indexOf(c) != -1) hasNum = true;
            if (special.indexOf(c) != -1) hasSpecial = true;
        }

        if (!hasLower) basicProblems.add("The password doesn't contain any lowercase letters");
        if (!hasUpper) basicProblems.add("The password doesn't contain any uppercase letters");
        if (!hasNum) basicProblems.add("The password doesn't contain any numbers");
        if (!hasSpecial) basicProblems.add("The password doesn't contain any special characters");

        if (hasLower) basicScore += 25;
        if (hasUpper) basicScore += 25;
        if (hasNum) basicScore += 25;
        if (hasSpecial) basicScore += 25;

        if (passwd.length() >= 8) lengthScore += 25;
        if (passwd.length() >= 10) lengthScore += 25;
        if (passwd.length() >= 12) lengthScore += 25;
        if (passwd.length() >= 14) lengthScore += 25;

        if (passwd.length() < 15) {
            lengthProblems.add("Longer passwords are generally stronger");
        }

        List<Character> uniqueChars = new ArrayList<>();
        List<Integer> counts = new ArrayList<>();

        for (char c : passwd.toCharArray()) {
            int idx = uniqueChars.indexOf(c);
            if (idx == -1) {
                uniqueChars.add(c);
                counts.add(1);
            } else {
                counts.set(idx, counts.get(idx) + 1);
            }
        }

        for (int count : counts) {
            if (count > 1) {
                repetitionProblems.add("The password contains repeated characters");
            } else {
                repetitionScore += 100.0 / (passwd.length() - 1);
            }
        }

        if (repetitionScore > 100) repetitionScore = 100;

        int sameChar = 0, sameClass = 0, sameLetter = 0;

        for (int i = 0; i < passwd.length() - 1; i++) {
            char currChar = passwd.charAt(i);
            char nextChar = passwd.charAt(i + 1);

            if (currChar != nextChar) {
                complexityScore += 12.5 / (passwd.length() - 1);
            } else {
                sameChar++;
            }

            boolean currLower = lower.indexOf(currChar) != -1;
            boolean nextLower = lower.indexOf(nextChar) != -1;
            boolean currUpper = upper.indexOf(currChar) != -1;
            boolean nextUpper = upper.indexOf(nextChar) != -1;

            if (currLower && nextUpper && Character.toLowerCase(nextChar) != currChar) {
                complexityScore += 12.5 / (passwd.length() - 1);
            } else if (currUpper && nextLower && Character.toUpperCase(nextChar) != currChar) {
                complexityScore += 12.5 / (passwd.length() - 1);
            } else {
                sameLetter++;
            }
        }

        if (sameChar > 0)
            complexityProblems.add("Repeated consecutive characters detected");
        if (sameClass > 0)
            complexityProblems.add("Repeated consecutive character classes detected");
        if (sameLetter > 0)
            complexityProblems.add("Repeated consecutive letters detected");

        double totalScore = (basicScore + lengthScore + repetitionScore + complexityScore) / 4.0;

        System.out.println("\nBasic Factor: " + basicScore + "/100");
        System.out.println("Length Factor: " + lengthScore + "/100");
        System.out.println("Repetition Factor: " + repetitionScore + "/100");
        System.out.println("Complexity Factor: " + complexityScore + "/100");
        System.out.println("\nTotal Password Strength: " + (Math.round(totalScore * 100.0) / 100.0) + "/100\n");

        System.out.println("Issues Identified:");
        for (String p : basicProblems) System.out.println(" - " + p);
        for (String p : lengthProblems) System.out.println(" - " + p);
        for (String p : repetitionProblems) System.out.println(" - " + p);
        for (String p : complexityProblems) System.out.println(" - " + p);

        scanner.close();
    }
}
