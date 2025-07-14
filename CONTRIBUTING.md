# Contributing to DNAPass Password Generator

Thank you for your interest in contributing to the **DNAPass Password Generator**! This project provides a secure and customizable password generation tool, compliant with NIST standards, and we welcome contributions to enhance its functionality, documentation, and accessibility. Whether you're fixing bugs, adding features, improving documentation, or contributing in other ways, your efforts are greatly appreciated.

---

## 🤝 Ways to Contribute

You can contribute to the DNAPass Password Generator in several ways:
- **Code**: Fix bugs, add new features, or optimize existing functionality in `dnapass_generator.cpp`.
- **Documentation**: Improve `README.md`, `SECURITY.md`, `RELEASE.md`, `DNAPASSCALCULATION.md`, or add inline comments.
- **Issues**: Report bugs, suggest features, or propose documentation enhancements via GitHub Issues.
- **Translations**: Translate documentation or CLI messages to other languages.
- **Media**: Create or update screenshots, logos, or other visual assets for the project.
- **Testing**: Validate functionality across different platforms or C++ compilers.

---

## 🚀 Getting Started

### ⚙️ 1. Setting Up Your Environment
To contribute, set up a local development environment:
1. **Install a C++ Compiler**: Ensure you have a C++17-compliant compiler installed, such as `g++` (GCC 7.0+) or `clang++` (Clang 5.0+).
2. **Clone the repository**:
   ```bash
   git clone https://github.com/gerivanc/dnapass.git
   cd dnapass
   ```
3. **Install development tools** (optional, but recommended):
   - **clang-format**: For automatic code formatting.
     ```bash
     sudo apt-get install clang-format  # On Debian/Ubuntu
     # Or use your package manager (e.g., brew on macOS, choco on Windows)
     ```
   - **clang-tidy**: For linting and static analysis (optional).
     ```bash
     sudo apt-get install clang-tidy
     ```
4. **Compile the project**:
   ```bash
   g++ -std=c++17 dnapass_generator.cpp -o dnapass_generator
   ```
   Alternatively, use `clang++`:
   ```bash
   clang++ -std=c++17 dnapass_generator.cpp -o dnapass_generator
   ```

### 📢 2. Reporting Issues
If you find a bug, have a feature request, or notice documentation that needs improvement:
- **Search existing issues**: Check the [GitHub Issues page](https://github.com/gerivanc/dnapass/issues) to avoid duplicates.
- **Use templates**: Follow the issue templates in `.github/ISSUE_TEMPLATE/` for bug reports or feature requests.
- **Provide details**: Include a clear title, description, steps to reproduce (if applicable), expected behavior, and screenshots or logs.
- **Security issues**: For vulnerabilities, follow the process in [SECURITY.md](https://github.com/gerivanc/dnapass/blob/main/SECURITY.md) instead of opening a public issue.

### 🔄 3. Submitting Pull Requests
To contribute code, documentation, or other changes, submit a pull request (PR):
1. **Fork the repository**:
   - Click the "Fork" button on the [repository page](https://github.com/gerivanc/dnapass).
   - Clone your fork:
     ```bash
     git clone https://github.com/<your-username>/dnapass.git
     cd dnapass
     ```
2. **Create a branch**:
   - Use a descriptive name (e.g., `feature/add-new-mode`, `fix/bug-entropy-calc`):
     ```bash
     git checkout -b feature/your-feature-name
     ```
3. **Make changes**:
   - Follow the coding standards below.
   - Test changes locally (see "Testing" section).
   - Update documentation (e.g., `README.md`, inline comments) if necessary.
   - Run formatting tools:
     ```bash
     clang-format -i dnapass_generator.cpp
     ```
     Optionally, run `clang-tidy` for linting:
     ```bash
     clang-tidy dnapass_generator.cpp -- -std=c++17
     ```
4. **Commit changes**:
   - Use clear, concise commit messages following the [Conventional Commits](https://www.conventionalcommits.org/) format (e.g., `feat: add new password mode`, `fix: correct entropy calculation`):
     ```bash
     git commit -m "feat: describe your change"
     ```
5. **Push to your fork**:
   ```bash
   git push origin feature/your-feature-name
   ```
6. **Open a pull request**:
   - Go to the [repository](https://github.com/gerivanc/dnapass) and click "New pull request".
   - Select your branch and provide a detailed description of your changes.
   - Reference related issues (e.g., "Fixes #123").
   - Ensure your PR passes the GitHub Actions CI checks (if configured).

### 📜 4. Coding Standards
To maintain consistency and security, adhere to these guidelines:
- **C++ Version**: Use C++17 or higher, as specified in the compilation instructions.
- **Style**: Follow the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html) or [LLVM Coding Standards](https://llvm.org/docs/CodingStandards.html). Use `clang-format` for consistent formatting.
- **Comments**: Write clear, English comments for all functions and complex logic. Use Doxygen-style comments for functions if adding documentation.
- **Security**: Use `std::random_device` and `std::mt19937` for random number generation. Avoid insecure functions like `rand()`. If introducing new dependencies, justify their necessity and security.
- **File Structure**: Keep changes within the existing structure (e.g., core logic in `dnapass_generator.cpp`).
- **Licensing**: By contributing, you agree that your contributions are licensed under the [MIT License](https://github.com/gerivanc/dnapass/blob/main/LICENSE.md).

### 🧪 5. Testing
Ensure your changes do not break existing functionality:
- **Manual Testing**:
  - Run the compiled binary with different configurations:
    ```bash
    ./dnapass_generator
    ```
    Enter different password lengths (e.g., 8, 12, 128) to verify output.
- **Cross-Platform Testing**:
  - Test on Linux, macOS, and Windows to ensure compatibility.
  - Use different compilers (e.g., `g++`, `clang++`, MSVC) to verify portability.
- **Automated Tests**:
  - Currently, the project does not include automated tests. If adding tests, consider using a framework like [Catch2](https://github.com/catchorg/Catch2) or [Google Test](https://github.com/google/googletest). Place tests in a `tests/` directory. Example compilation with Catch2:
    ```bash
    g++ -std=c++17 tests/test_dnapass.cpp -o test_dnapass
    ./test_dnapass
    ```
  - Contributions that add test coverage are highly encouraged.
- **Validation**:
  - Verify that password generation meets NIST standards (80+ bits of entropy).
  - Check that passwords include required character types (uppercase, lowercase, digits, special characters).

### ✅ 6. Pull Request Review Process
After submitting a PR:
- **Review Time**: The maintainer will review your PR within 7 business days. Complex changes may take longer.
- **Criteria**: PRs are evaluated based on code quality, adherence to standards, security, and alignment with project goals.
- **Feedback**: You may be asked to make revisions. Address feedback promptly to expedite merging.
- **Approval**: PRs require approval from the maintainer (Gerivan Costa dos Santos) before merging.
- **CI Checks**: Ensure all GitHub Actions checks (if configured) pass. Fix any failures reported in the workflow.

### 🤗 7. Code of Conduct
We are committed to fostering an inclusive and respectful community. Please:
- Be kind, respectful, and professional in all interactions.
- Avoid offensive language, harassment, or discriminatory behavior.
- Report inappropriate behavior to the maintainer at [dean-grumbly-plop@duck.com](mailto:dean-grumbly-plop@duck.com).
Violations may result in exclusion from the project.

### ❓ 8. Getting Help
For questions or assistance:
- Read the [README.md](https://github.com/gerivanc/dnapass/blob/main/README.md) for project details.
- Check the [SECURITY.md](https://github.com/gerivanc/dnapass/blob/main/SECURITY.md) for vulnerability reporting.
- Open an issue on the [GitHub Issues page](https://github.com/gerivanc/dnapass/issues).
- Contact the maintainer at [dean-grumbly-plop@duck.com](mailto:dean-grumbly-plop@duck.com).

### 🙌 9. Acknowledgments
Thank you for contributing to the **DNAPass Password Generator**! Your efforts help make this tool more secure, accessible, and valuable for users worldwide. Significant contributors may be acknowledged in the project’s documentation or release notes (with your consent).

---

#### Copyright © 2025 Gerivan Costa dos Santos
