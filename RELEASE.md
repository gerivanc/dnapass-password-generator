# DNAPass Password Generator v0.1.0

**Release Date:** July 13th, 2025

Released on 	2025/07/13 	

Last updated 	2025/07/13 

Publisher 	[gerivanc](https://github.com/gerivanc/)

Changelog [Changelog](https://github.com/gerivanc/dnapass/blob/main/CHANGELOG.md)

Release Notes [RELEASE.md](https://github.com/gerivanc/dnapass/blob/main/RELEASE.md)

Reporting Issues	[Report a](https://github.com/gerivanc/dnapass/issues/new/choose)

---

## 📋 Overview
The **DNAPass Password Generator** v0.1.0 is now available! This initial release introduces a secure C++ tool for generating strong passwords inspired by DNA sequences. It provides a command-line interface (CLI) with customizable password lengths (8–128 characters) and ensures high entropy, exceeding NIST standards (80+ bits). The project includes a GitHub Actions badge in the documentation to reflect the status of CI/CD workflows.

---

## ✨ What's New
- Initial release of DNAPass Password Generator in C++.
- Implemented core password generation logic in `dnapass_generator.cpp`, using DNA-inspired sequences with ambiguity resolution.
- Added support for uppercase letters, lowercase letters, digits, and special characters, ensuring at least 4 special characters, 2–3 digits, 10% uppercase, and 1 lowercase.
- Introduced GitHub Actions badge in `README.md` to display CI/CD workflow status.
- Adjusted layout styling and emoji use in documentation for better readability and visual identity.
- Corrected anchor links in the Table of Contents for improved navigation.

---

## 🔧 Installation
Ensure you have a C++17-compliant compiler installed (e.g., `g++` 7.0+ or `clang++` 5.0+). No external dependencies are required, as DNAPass uses only C++ standard libraries.

### Cloning the Repository
To work with the source code or test the program locally, clone the repository and compile the code:

```bash
git clone https://github.com/gerivanc/dnapass.git
cd dnapass
g++ -std=c++17 dnapass_generator.cpp -o dnapass_generator
```

This command will compile the program into an executable named `dnapass_generator`. Alternatively, you can use `clang++`:
```bash
clang++ -std=c++17 dnapass_generator.cpp -o dnapass_generator
```

After compilation, you can run the generator using:
```bash
./dnapass_generator
```

Enter the desired password length (8–128) when prompted. Example:
```
Enter the password length (8 to 128): 12

Copyright © 2025 Gerivan Costa dos Santos
DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
Author: gerivanc
GitHub: https://github.com/gerivanc
MIT License: https://github.com/gerivanc/dnapass/blob/main/LICENSE.md

Generated password: 5t@A#t7!cga
----------

Used words: TTATAA, gattaca
Ambiguity resolution log:
  TTATAA -> TTATAA
  gattaca -> gattaca

Password analysis:
  Length: 12
  Uppercase: 1
  Lowercase: 5
  Digits: 2
  Special characters: 4
```

---

## 🖥️ Getting Started on Windows
For Windows users, you can compile and run the **DNAPass Password Generator** using a C++ compiler like MinGW (with `g++`) or MSVC (Microsoft Visual Studio). Follow these steps:
1. Install a compiler:
   - **MinGW**: Download from [MinGW-w64](https://www.mingw-w64.org/) or install via a package manager like `choco` (`choco install mingw`).
   - **MSVC**: Install Visual Studio with the C++ development workload.
2. Clone the repository:
   ```bash
   git clone https://github.com/gerivanc/dnapass.git
   cd dnapass
   ```
3. Compile the code:
   - With MinGW:
     ```bash
     g++ -std=c++17 dnapass_generator.cpp -o dnapass_generator
     ```
   - With MSVC (from Developer Command Prompt for Visual Studio):
     ```bash
     cl /std:c++17 dnapass_generator.cpp /o dnapass_generator
     ```
4. Run the program:
   ```bash
   dnapass_generator
   ```
For detailed guidance, check the [CONTRIBUTING.md](https://github.com/gerivanc/dnapass/blob/main/CONTRIBUTING.md) for setup and testing instructions.

---

## 📬 Feedback
Help us improve by reporting issues using our [issue template](https://github.com/gerivanc/dnapass/blob/main/.github/ISSUE_TEMPLATE/issue_template.md).

Thank you for supporting **DNAPass Password Generator**! 🚀🔑

---

#### Copyright © 2025 Gerivan Costa dos Santos
