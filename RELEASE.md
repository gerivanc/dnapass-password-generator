# DNAPass Password Generator v0.1.2

**Release Date:** August 31th, 2025

Released on 	2025/07/13 	

Last updated 	2025/08/31 

Publisher 	[gerivanc](https://github.com/gerivanc/)

Changelog [Changelog](https://github.com/gerivanc/dnapass-password-generator/blob/main/CHANGELOG.md)

Release Notes [RELEASE.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/RELEASE.md)

Reporting Issues	[Report a](https://github.com/gerivanc/dnapass-password-generator/issues/new/choose)

---

## 📋 Overview
The ** 🧬 DNAPass Password Generator** v0.1.2 is now available! This initial release introduces a secure C++ tool for generating strong passwords inspired by DNA sequences. It provides a command-line interface (CLI) with customizable password lengths (8–128 characters) and ensures high entropy, exceeding NIST standards (80+ bits). The project includes a GitHub Actions badge in the documentation to reflect the status of CI/CD workflows.

---

## ✨ What's New
- Initial release of DNAPass Password Generator in C++.
- Implemented core password generation logic in `dnapass_generator.cpp`, using DNA-inspired sequences with ambiguity resolution.
- Added support for uppercase letters, lowercase letters, digits, and special characters, ensuring at least 4 special characters, 2–3 digits, 10% uppercase, and 1 lowercase.
- Introduced GitHub Actions badge in `README.md` to display CI/CD workflow status.
- Adjusted layout styling and emoji use in documentation for better readability and visual identity.
- Corrected anchor links in the Table of Contents for improved navigation.

---

# 📋 Requirements

Update and install the environments required for the installation. 

```bash
sudo apt update
sudo apt install git
sudo apt install cmake
sudo apt install g++
sudo apt install clang
```

After installing the environments, confirm and verify the installed versions. 

```bash
git --version
cmake --version
g++ --version
clang --version
```

---

# 💾 Installation

Cloning the repository to install packages.

```bash
git clone https://github.com/gerivanc/dnapass-password-generator.git
cd dnapass-password-generator
mkdir build
cd build
cmake ..
cmake --build .
```

---

# 🛠 Command Line Interface
## Usage

### Method 1. Call the function by question to generate the password by choosing between 8-128 characters. Entering password output length to 8 characters:

```bash
./dnapass_generator
```

Example of generated password with 8 characters: 
```bash
┌──(user㉿parrot)-[~/dnapass-password-generator/build]
└─$ ./dnapass_generator
Enter the password length (8 to 128): 8

Copyright © 2025 Gerivan Costa dos Santos
DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
Author: gerivanc
GitHub: https://github.com/gerivanc/dnapass-password-generator
MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md

Generated password: 4C)6%~a+
----------

Used words: GACAATGTG
Ambiguity resolution log:
  GACNNNNTG -> GACAATGTG

Password analysis:
  Length: 8
  Uppercase: 1
  Lowercase: 1
  Digits: 2
  Special characters: 4
```

### Method 2. - Automated Mode. Call to generate the password by choosing a 45-character password. In the function, enter the number of characters between 8 and 128. Entering password output length to 45 characters

```bash
echo "45" | ./dnapass_generator
```

Example of generated password with 45 characters: 
```
┌──(user㉿parrot)-[~/dnapass-password-generator/build]
└─$ echo "45" | ./dnapass_generator
Enter the password length (8 to 128): 
Copyright © 2025 Gerivan Costa dos Santos
DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
Author: gerivanc
GitHub: https://github.com/gerivanc/dnapass-password-generator
MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md

Generated password: gggacc4ga#ggGtgtgaaaGgcgcagAac$a,ac5*Cgattatt
----------

Used words: AATGAGAGC, GTCGAC, AGACGACGAG, GACGTC, gattaca, GCATTG, GCTGC
Ambiguity resolution log:
  NNNGAGAGC -> AATGAGAGC
  GTMKAC -> GTCGAC
  NNNNNNNGAG -> AGACGACGAG
  GACGTC -> GACGTC
  gattaca -> gattaca
  GCATTG -> GCATTG
  GCWGC -> GCTGC

Password analysis:
  Length: 45
  Uppercase: 4
  Lowercase: 35
  Digits: 2
  Special characters: 4
```

---

## 📬 Feedback
Help us improve by reporting issues using our [issue template](https://github.com/gerivanc/dnapass/blob/main/.github/ISSUE_TEMPLATE/issue_template.md).

Thank you for supporting **DNAPass Password Generator**! 🚀🔑
---

#### Copyright © 2025 Gerivan Costa dos Santos
