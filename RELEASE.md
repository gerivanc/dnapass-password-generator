# DNAPass Password Generator v0.1.5

**Release Date:** October 2st, 2026

Released on 	2025/07/13 	

Last updated 	2026/10/02 

Web Generator 	[DNAPassword](https://dnapass.gerivan.me/dnapass.html)

Interactive Viewer 	[DNAPass](https://dnapass.gerivan.me/dnapass.html)

Publisher 	[gerivanc](https://github.com/gerivanc/)

Changelog [Changelog](https://github.com/gerivanc/dnapass-password-generator/blob/main/CHANGELOG.md)

Release Notes [RELEASE.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/RELEASE.md)

Reporting Issues	[Report a](https://github.com/gerivanc/dnapass-password-generator/issues/new/choose)

---

## 📋 Overview
The **🧬 DNAPass Password Generator** v0.1.5 is now available! This release makes the web generator installable as a Progressive Web App (PWA) and brings the C++ command-line interface (CLI) in line with the web version: the same generation rules, the same character options, and a cryptographically secure random source on every platform.

---

## ✨ What's New
- **Installable web app (PWA)**: [dnapass.html](https://dnapass.gerivan.me/dnapass.html) can be installed from the browser and works offline. A bilingual banner (English / Portuguese) asks whether you want to install it, using the native prompt on Chromium browsers and step-by-step instructions on iOS, Safari for macOS and other browsers.
- **CSPRNG in the CLI**: `std::mt19937` was replaced by the operating system's secure random source (`BCryptGenRandom` on Windows, `getentropy()` on Linux/macOS/BSD), with bias-free rejection sampling.
- **Same options as the web version**: `--length`, `--no-uppercase`, `--no-lowercase`, `--no-digits`, `--no-special`, plus `--quiet`, `--help` and `--version`.
- **Same rules as the web version**: case options really exclude the disabled case; 2 digits below 50 characters and 3 at 50+; at least 4 special characters; at least 10% uppercase and 1 lowercase — guaranteed by reserving unique positions, never overwritten.
- **Entropy estimate in the CLI**, with an honest note that it is an upper bound.
- **Automated tests** (`ctest`): 19,360 passwords validated per run across every toggle combination and every length from 8 to 128; both GitHub Actions workflows run them.
- **Web fixes**: residual bias in `getRandomInt()` removed, empty length field no longer produces an empty password, pinch-to-zoom re-enabled, tighter Content-Security-Policy.

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
Enter the password length (8 to 128): 
Copyright © 2025-2026 Gerivan Costa dos Santos
DNAPass Password Generator v0.1.5 - Generate secure passwords inspired by DNA sequences
Author: gerivanc
GitHub: https://github.com/gerivanc/dnapass-password-generator
MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md

Generated password: =attcgaAcg3c%gcggc?cgC&5
----------

Settings:
  Include uppercase: YES
  Include lowercase: YES
  Include digits: YES
  Include special characters: YES

Used words: GCAACTGCAA, GAGC, ggcc, CATCAT
Ambiguity resolution log:
  GCANNTGCAN -> GCAACTGCAA
  NNGC -> GAGC
  ggcc -> ggcc
  CATCAT -> CATCAT

Password analysis:
  Length: 24
  Uppercase: 2
  Lowercase: 16
  Digits: 2
  Special characters: 4
  Entropy (estimated): 155.80 bits

Note: the entropy shown is a charset-based upper bound. DNAPass builds
passwords from a fixed, public set of sequences, so the real guessing
entropy is lower. Use 16+ characters for high-security accounts.
```

### Method 2. - Automated Mode. Call to generate the password by choosing a 32-character password. In the function, enter the number of characters between 8 and 128.

```bash
echo "32" | ./dnapass_generator
```

### Method 3. - Command-line options. Generate a 16-character password without special characters:

```bash
./dnapass_generator --length 16 --no-special
```

Example output:
```
┌──(user㉿parrot)-[~/dnapass-password-generator/build]
└─$ ./dnapass_generator --length 16 --no-special

Copyright © 2025-2026 Gerivan Costa dos Santos
DNAPass Password Generator v0.1.5 - Generate secure passwords inspired by DNA sequences
Author: gerivanc
GitHub: https://github.com/gerivanc/dnapass-password-generator
MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md

Generated password: Ct3caCcaGtta9cgt
----------

Settings:
  Include uppercase: YES
  Include lowercase: YES
  Include digits: YES
  Include special characters: NO

Used words: TCTAGA, GGTACC, CCGTAG
Ambiguity resolution log:
  TCTAGA -> TCTAGA
  GGTACC -> GGTACC
  CCRTAG -> CCGTAG

Password analysis:
  Length: 16
  Uppercase: 3
  Lowercase: 11
  Digits: 2
  Special characters: 0
  Entropy (estimated): 95.27 bits

Note: the entropy shown is a charset-based upper bound. DNAPass builds
passwords from a fixed, public set of sequences, so the real guessing
entropy is lower. Use 16+ characters for high-security accounts.
```

Other examples:
```bash
./dnapass_generator -l 64 --quiet                  # print only the password
./dnapass_generator 20 --no-uppercase --no-digits  # positional length
./dnapass_generator --help                         # list all options
```

> 🔐 **Tip**: `--quiet` prints only the password, without the sequence log, which is useful for scripts and avoids leaving the password's building blocks in your terminal history.

---

## 📬 Feedback
Help us improve by reporting issues using our [issue template](https://github.com/gerivanc/dnapass-password-generator/blob/main/.github/ISSUE_TEMPLATE/issue_template.md).

Thank you for supporting **DNAPass Password Generator**! 🚀🔑

---

#### Copyright © 2025-2026 Gerivan Costa dos Santos
