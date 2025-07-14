# 🧬 DNAPass Password Generator

![C++](https://img.shields.io/badge/C++-17-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![GitHub Workflow Status](https://github.com/gerivanc/dnapass/actions/workflows/cpp-app.yml/badge.svg)

**DNAPass Password Generator is a secure C++ tool that generates strong passwords inspired by DNA sequences. It offers a command-line interface (CLI) with customizable length (8–128 characters) and ensures high entropy. The project uses DNA-inspired sequences, ambiguity resolution, and character diversity to create robust passwords for developers and security enthusiasts.**

---

## 🧪 Experimental Zone Ahead! 🚧 Calm down, project under construction! 🛠️ 
💡 Contributions and ideas are welcome — just don’t trip over the cables!

---

# ✨ Features
- Generates passwords with lengths between 8 and 128 characters.
- Supports uppercase letters, lowercase letters, digits, and special characters.
- Uses primary and secondary DNA sequence sets for unique password generation.
- Ensures at least 4 special characters, 2–3 digits, 10% uppercase, and 1 lowercase.
- Command-line interface for flexible usage.
- No external dependencies; uses C++ standard libraries.

---

# 💾 Installation
Clone the repository and compile the source code:
```bash
git clone https://github.com/gerivanc/dnapass.git
cd dnapass
g++ -std=c++17 dnapass_generator.cpp -o dnapass_generator
```

No additional dependencies are required, as DNAPass uses only C++ standard libraries (C++17 or higher).

## Usage
Run the generator from the command line:
```bash
./dnapass_generator
```
Follow the prompt to enter the desired password length (8–128). Example output:
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

# 📊 DNAPass Calculation Methodology
DNAPass generates passwords by:
1. Selecting random DNA sequences from primary (90%) or secondary (10%) sets.
2. Resolving ambiguous characters (e.g., 'N' to A/T/C/G).
3. Adjusting for length and enforcing character diversity (uppercase, lowercase, digits, special characters).
4. Shuffling the final password to ensure randomness.

See the [Contributing](https://github.com/gerivanc/dnapass-password-generator/blob/main/DNAPASSCALCULATION.md) for details.

---

## 🛠️ Development

To contribute to the **DNAPass Password Generator**, follow the guidelines in [CONTRIBUTING.md](https://github.com/gerivanc/dnapass/blob/main/CONTRIBUTING.md). Set up a development environment with:
```bash
git clone https://github.com/gerivanc/dnapass.git
cd dnapass
g++ -std=c++17 dnapass_generator.cpp -o dnapass_generator
```
Install `clang-format` for code formatting (optional, but recommended):
```bash
sudo apt-get install clang-format  # On Debian/Ubuntu
# Or use your package manager (e.g., brew on macOS, choco on Windows)
```

---

# 🤝 Contributing
See the [Contributing](https://github.com/gerivanc/dnapass-password-generator/blob/main/CONTRIBUTING.md) for details.

---

# 📝 Release Notes
See the [RELEASE.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/RELEASE.md) for detailed release notes for each version.

---

# 🛡️ Security
For security vulnerabilities, follow the process in Security instead of opening a public issue. We recommend using a password manager and enabling 2FA for enhanced security.
See the [Security](https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md) for details.

---

# 📅 Changelog
See the [Changelog](https://github.com/gerivanc/dnapass-password-generator/blob/main/CHANGELOG.md) for a detailed history of changes to this project.

---

# 📄 License
This project is licensed under the MIT License. See the [License](https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md) for details.

---

# ❤️ Support This Project
If you find DNAPass Password Generator useful, consider supporting its development with a donation:

[<img src="https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif" alt="Donate with PayPal">](https://www.paypal.com/ncp/payment/FYUGSCLQRSQDN)

---

# 📧 Contact
For questions or feedback, please contact: dean-grumbly-plop@duck.com.

#### Copyright © 2025 Gerivan Costa dos Santos
