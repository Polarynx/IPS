# Index for Password Strength (IPS)

![Java](https://img.shields.io/badge/Java-JDK_8%2B-orange.svg)
![License](https://img.shields.io/badge/License-MIT-blue.svg)

Index for Password Strength (IPS) is a command-line program built in Java that evaluates the strength of a user-provided password using a custom scoring system. The program analyzes multiple security factors and produces both a numerical score and specific feedback on weaknesses.

---

## Features

- Enforces password length constraints (8–15 characters)
- Evaluates 4 independent security factors:
  - **Character Diversity:** Checks for lowercase, uppercase, numeric, and special characters
  - **Length:** Evaluates total password length against security benchmarks
  - **Repetition:** Detects and penalizes repeated characters
  - **Sequential & Structural Complexity:** Identifies predictable patterns and consecutive characters
- **Detailed Output:**
  - Individual Factor Scores (out of 100)
  - Final Composite IPS Score (out of 100)
  - Clear explanations of detected security issues

---

## How It Works

The IPS score is computed by averaging four factors:

$$\text{Total Score} = \frac{\text{Basic Score} + \text{Length Score} + \text{Repetition Score} + \text{Complexity Score}}{4}$$

| Factor | Description | Max Score |
| :--- | :--- | :--- |
| **Basic Factor** | Grants +25 points for each character category (lowercase, uppercase, numbers, special characters) | 100 |
| **Length Factor** | Grants +25 points for reaching length thresholds (8, 10, 12, and 14 characters) | 100 |
| **Repetition Factor** | Rewards unique character distributions and penalizes frequency of duplicate characters | 100 |
| **Complexity Factor** | Rewards non-consecutive character variation and flags predictable transitions | 100 |

---

## Technologies Used

- **Language:** Java (JDK 8+)
- **Standard Libraries:** `java.util.Scanner`, `java.util.ArrayList`, `java.util.List`
- **Concepts:** Java Collections Framework, input validation, string processing, scoring algorithms, security logic

---

## How to Run

### Option 1: Run Locally (Command Line)

1. Clone or download this repository.
2. Compile the Java source file:
   ```bash
   javac PasswordStrengthIndex.java
   ```
3. Run the compiled program:
   ```bash
   java PasswordStrengthIndex
   ```
4. Enter a password when prompted to view your strength rating and security feedback.

### Option 2: Online Compiler

1. Go to the [Programiz Online Java Compiler](https://www.programiz.com/java-programming/online-compiler/).
2. Copy and paste the contents of `PasswordStrengthIndex.java` into the editor.
3. Click **Run**, then enter a password in the interactive console.

---

## Example Output

```text
Welcome to the Index for Password Strength (IPS)!

Enter your password (8-15 characters): P@ssw0rd123

Basic Factor: 100.0/100
Length Factor: 50.0/100
Repetition Factor: 75.0/100
Complexity Factor: 87.5/100

Total Password Strength: 78.13/100

Issues Identified:
 - Longer passwords are generally stronger
 - The password contains repeated characters
```
