# Contributing to DNAPass Password Generator

Thank you for your interest in contributing to the **DNAPass Password Generator**! This guide outlines the process for contributing to the project. Whether you're fixing bugs, adding features, or improving documentation, your contributions are welcome!

---

## 📌 Getting Started

1. **Read the Documentation**:
   - Review the [README.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/README.md) for an overview of the project.
   - Check the [DNAPASSCALCULATION.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/DNAPASSCALCULATION.md) for details on the password generation methodology.
   - See the [RELEASE.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/RELEASE.md) for version-specific details.

2. **Set Up Your Environment**:
   - Clone the repository:
     ```bash
     git clone https://github.com/gerivanc/dnapass-password-generator.git
     cd dnapass-password-generator
     ```
   - Ensure you have a C++17-compliant compiler (e.g., `g++` 7.0+ or `clang++` 5.0+).
   - Install CMake for building the project:
     ```bash
     sudo apt-get install cmake  # On Debian/Ubuntu
     # Or use your package manager (e.g., brew on macOS, choco on Windows)
     ```
   - (Optional) Install `clang-format` for code formatting:
     ```bash
     sudo apt-get install clang-format  # On Debian/Ubuntu
     ```
   - Build the project:
     ```bash
     mkdir build && cd build
     cmake ..
     cmake --build .
     ```

3. **Check Coding Standards**:
   - Use `clang-format` to ensure consistent code style:
     ```bash
     clang-format -i dnapass_password_generator/*.cpp dnapass_password_generator/*.hpp tests/*.cpp
     ```
   - Follow C++17 standards and avoid external dependencies beyond standard libraries.
   - Never use a non-cryptographic generator (e.g. `std::mt19937`, `rand()`, `Math.random()`) for anything that affects the generated password; use `dnapass::secure_random` in C++ and `crypto.getRandomValues()` in the web version.
   - Keep the C++ CLI (`dnapass_password_generator/`) and the web version (`docs/dnapass.html`) in sync: the same rules and the same options.
   - Write all code comments in English.

---

## 🤝 How to Contribute

1. **Fork the Repository**:
   - Fork the project on GitHub: [DNAPass](https://github.com/gerivanc/dnapass-password-generator/).
   - Clone your fork:
     ```bash
     git clone https://github.com/<your-username>/dnapass-password-generator.git
     ```

2. **Create a Branch**:
   - Create a branch for your changes:
     ```bash
     git checkout -b feature/your-feature-name
     ```

3. **Make Changes**:
   - Implement your feature or bug fix in `dnapass_password_generator/` (C++ CLI), `docs/` (web version and PWA), or documentation files.
   - Ensure your code compiles and runs without errors:
     ```bash
     ./build/dnapass_generator
     ```

4. **Test Your Changes**:
   - Run the automated tests from the `build` folder:
     ```bash
     ctest --output-on-failure
     ```
   - Test the program with various password lengths (8–128) and options (e.g. `./dnapass_generator -l 8 --no-special`).
   - Verify that the output meets the requirements (e.g., 4 special characters, 2–3 digits, 10% uppercase, 1 lowercase for each enabled type).
   - Add new checks to `tests/test_generator.cpp` when you change the generation rules.

5. **Commit and Push**:
   - Write clear commit messages:
     ```bash
     git commit -m "Add feature: describe your change"
     ```
   - Push to your fork:
     ```bash
     git push origin feature/your-feature-name
     ```

6. **Open a Pull Request**:
   - Go to [DNAPass](https://github.com/gerivanc/dnapass-password-generator/). and create a pull request from your branch.
   - Reference any related issues (e.g., "Fixes #123").
   - Provide a clear description of your changes.

---

## 🐛 Reporting Bugs

- Use the [Bug Report template](https://github.com/gerivanc/dnapass-password-generator/blob/main/.github/ISSUE_TEMPLATE/bug_report.md) to report issues.
- Include steps to reproduce, expected behavior, and environment details (OS, compiler version, project version).

---

## 💡 Suggesting Features

- Use the [Issue Report template](https://github.com/gerivanc/dnapass-password-generator/blob/main/.github/ISSUE_TEMPLATE/issue_template.md) for feature requests or improvements.
- Provide a clear description and use case for the suggested feature.

---

## 🔒 Security Vulnerabilities

- For security issues, follow the instructions in [SECURITY.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/SECURITY.md) to report privately.
- Do not disclose security vulnerabilities publicly until they are resolved.

---

## 📬 Contact

For questions or support, reach out to the maintainer at [dean-grumbly-plop@duck.com](mailto:dean-grumbly-plop@duck.com).

Thank you for helping improve the **DNAPass Password Generator**! 🚀🔑

---

#### Copyright © 2025-2026 Gerivan Costa dos Santos
