#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>

int main() {
    std::cout << "Welcome to the Index for Password Strength (IPS)!\n";

    std::cout << "\nEnter your password (8-15 characters): ";
    std::string passwd;
    std::cin >> passwd;

    if (passwd.length() < 8) {
        std::cout << "Invalid Password Length, tip: add more characters!\n";
        return 0;
    }
    if (passwd.length() > 15) {
        std::cout << "Invalid Password Length, tip: less characters please!\n";
        return 0;
    }

    double basicScore = 0, lengthScore = 0, repetitionScore = 0, complexityScore = 0;

    std::vector<std::string> basicProblems;
    std::vector<std::string> lengthProblems;
    std::vector<std::string> repetitionProblems;
    std::vector<std::string> complexityProblems;

    std::string lower = "abcdefghijklmnopqrstuvwxyz";
    std::string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string nums = "0123456789";
    std::string special = "!@#$%^&*()-_{}[]|;:.,?\\<>+~`=";

    bool hasLower = false, hasUpper = false, hasNum = false, hasSpecial = false;

    for (char c : passwd) {
        if (lower.find(c) != std::string::npos) hasLower = true;
        if (upper.find(c) != std::string::npos) hasUpper = true;
        if (nums.find(c) != std::string::npos) hasNum = true;
        if (special.find(c) != std::string::npos) hasSpecial = true;
    }

    if (!hasLower) basicProblems.push_back("The password doesn't contain any lowercase letters");
    if (!hasUpper) basicProblems.push_back("The password doesn't contain any uppercase letters");
    if (!hasNum) basicProblems.push_back("The password doesn't contain any numbers");
    if (!hasSpecial) basicProblems.push_back("The password doesn't contain any special characters");

    if (hasLower) basicScore += 25;
    if (hasUpper) basicScore += 25;
    if (hasNum) basicScore += 25;
    if (hasSpecial) basicScore += 25;

    if (passwd.length() >= 8) lengthScore += 25;
    if (passwd.length() >= 10) lengthScore += 25;
    if (passwd.length() >= 12) lengthScore += 25;
    if (passwd.length() >= 14) lengthScore += 25;

    if (passwd.length() < 15) {
        lengthProblems.push_back("Longer passwords are generally stronger");
    }

    std::vector<char> uniqueChars;
    std::vector<int> counts;

    for (char c : passwd) {
        auto it = std::find(uniqueChars.begin(), uniqueChars.end(), c);
        if (it == uniqueChars.end()) {
            uniqueChars.push_back(c);
            counts.push_back(1);
        } else {
            size_t idx = std::distance(uniqueChars.begin(), it);
            counts[idx]++;
        }
    }

    for (int count : counts) {
        if (count > 1) {
            repetitionProblems.push_back("The password contains repeated characters");
        } else {
            repetitionScore += 100.0 / (passwd.length() - 1);
        }
    }

    if (repetitionScore > 100) repetitionScore = 100;

    int sameChar = 0, sameClass = 0, sameLetter = 0;

    for (size_t i = 0; i < passwd.length() - 1; i++) {
        char currChar = passwd[i];
        char nextChar = passwd[i + 1];

        if (currChar != nextChar) {
            complexityScore += 12.5 / (passwd.length() - 1);
        } else {
            sameChar++;
        }

        bool currLower = lower.find(currChar) != std::string::npos;
        bool nextLower = lower.find(nextChar) != std::string::npos;
        bool currUpper = upper.find(currChar) != std::string::npos;
        bool nextUpper = upper.find(nextChar) != std::string::npos;

        if (currLower && nextUpper && std::tolower(static_cast<unsigned char>(nextChar)) != currChar) {
            complexityScore += 12.5 / (passwd.length() - 1);
        } else if (currUpper && nextLower && std::toupper(static_cast<unsigned char>(nextChar)) != currChar) {
            complexityScore += 12.5 / (passwd.length() - 1);
        } else {
            sameLetter++;
        }
    }

    if (sameChar > 0)
        complexityProblems.push_back("Repeated consecutive characters detected");
    if (sameClass > 0)
        complexityProblems.push_back("Repeated consecutive character classes detected");
    if (sameLetter > 0)
        complexityProblems.push_back("Repeated consecutive letters detected");

    double totalScore = (basicScore + lengthScore + repetitionScore + complexityScore) / 4.0;

    std::cout << "\nBasic Factor: " << basicScore << "/100\n";
    std::cout << "Length Factor: " << lengthScore << "/100\n";
    std::cout << "Repetition Factor: " << repetitionScore << "/100\n";
    std::cout << "Complexity Factor: " << complexityScore << "/100\n";
    std::cout << "\nTotal Password Strength: " << (std::round(totalScore * 100.0) / 100.0) << "/100\n\n";

    std::cout << "Issues Identified:\n";
    for (const auto& p : basicProblems) std::cout << " - " << p << "\n";
    for (const auto& p : lengthProblems) std::cout << " - " << p << "\n";
    for (const auto& p : repetitionProblems) std::cout << " - " << p << "\n";
    for (const auto& p : complexityProblems) std::cout << " - " << p << "\n";

    return 0;
}
