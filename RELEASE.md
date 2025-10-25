# DNAPass Password Generator v0.1.3

**Release Date:** October 24th, 2025

Released on 	2025/07/13 	

Last updated 	2025/08/31 

Publisher 	[gerivanc](https://github.com/gerivanc/)

Changelog [Changelog](https://github.com/gerivanc/dnapass-password-generator/blob/main/CHANGELOG.md)

Release Notes [RELEASE.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/RELEASE.md)

Reporting Issues	[Report a](https://github.com/gerivanc/dnapass-password-generator/issues/new/choose)

---

## 📋 Overview
The ** 🧬 DNAPass Password Generator** v0.1.3 is now available! This initial release introduces a secure C++ tool for generating strong passwords inspired by DNA sequences. It provides a command-line interface (CLI) with customizable password lengths (8–128 characters) and ensures high entropy, exceeding NIST standards (80+ bits). The project includes a GitHub Actions badge in the documentation to reflect the status of CI/CD workflows.

---

## ✨ What's New
- Completed total of 200 sequences for nucleotides in code 'dnapass_generator.cpp' function 'const std::vector<std::string> primary_sequences = { '
- GitHub Actions CI/CD workflow for automated testing and building across multiple platforms
- Multi-platform support (Ubuntu, macOS, Windows) with GCC and Clang compilers
- Automated release process triggered by version tags
- Comprehensive error handling and input validation in password generation
- Initial public release of DNAPass Password Generator
- Completed total of 200 sequences for nucleotides in code 'dnapass_generator.cpp'
- Resolved CMake configuration issues preventing successful builds on macOS and Windows
- Fixed `special_chars` variable declaration and linking errors across multiple compilation units
- Corrected recursive password generation to include maximum attempt limits

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

### Method 1. Call the function by question to generate the password by choosing between 8-128 characters. Entering password output length to 24 characters:

```bash
./dnapass_generator
```

Example of generated password with 24 characters: 
```bash
┌──(user㉿parrot)-[~/dnapass-password-generator/build]
└─$ ./dnapass_generator
Enter the password length (8 to 128): 24

Copyright © 2025 Gerivan Costa dos Santos
DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
Author: gerivanc
GitHub: https://github.com/gerivanc/dnapass-password-generator
MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md

Generated password: gccgact1c;tgcaG6C[c<@gGc
----------

Used words: ACTCCG, CGCCGT, CACTGGC, ACCGGT
Ambiguity resolution log:
	ACTCYR -> ACTCCG
	CGCYGT -> CGCCGT
	CASTGNN -> CACTGGC
	WCCGGW -> ACCGGT

Password analysis:
	Length: 24
	Uppercase: 3
	Lowercase: 15
	Digits: 2
	Special characters: 4
```

### Method 2. - Automated Mode. Call to generate the password by choosing a 32-character password. In the function, enter the number of characters between 8 and 128. Entering password output length to 32 characters

```bash
echo "32" | ./dnapass_generator
```

Example of generated password with 32 characters: 
```
┌──(user㉿parrot)-[~/dnapass-password-generator/build]
└─$ echo "32" | ./dnapass_generator
Enter the password length (8 to 128): 
Copyright © 2025 Gerivan Costa dos Santos
DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
Author: gerivanc
GitHub: https://github.com/gerivanc/dnapass-password-generator
MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md

Generated password: CTaaatAtcg)g(caccacT&gt=4a7Gtgat
----------

Used words: TCTAGA, GTCCTA, cgcg, ACTGAT, ATATAT, CGAATG
Ambiguity resolution log:
	TCTAGA -> TCTAGA
	GTCNNA -> GTCCTA
	cgcg -> cgcg
	ACTGNN -> ACTGAT
	ATATAT -> ATATAT
	CGWATG -> CGAATG

Password analysis:
	Length: 32
	Uppercase: 5
	Lowercase: 21
	Digits: 2
	Special characters: 4
```

---

## 📬 Feedback
Help us improve by reporting issues using our [issue template](https://github.com/gerivanc/dnapass/blob/main/.github/ISSUE_TEMPLATE/issue_template.md).

Thank you for supporting **DNAPass Password Generator**! 🚀🔑
---

#### Copyright © 2025 Gerivan Costa dos Santos
