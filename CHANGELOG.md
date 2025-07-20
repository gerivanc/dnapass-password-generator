# Changelog

[![Keep a Changelog](https://img.shields.io/badge/Keep%20a%20Changelog-1.0.0-orange)](https://keepachangelog.com/en/1.0.0/)
[![Semantic Versioning](https://img.shields.io/badge/Semantic%20Versioning-2.0.0-blue)](https://semver.org/spec/v2.0.0.html)

All notable changes to the 🧬 DNAPass Password Generator project are documented in this file. This project adheres to the [Keep a Changelog](https://keepachangelog.com/en/1.0.0/) standard, which ensures a structured and human-readable format for tracking changes. By following this approach, we provide clear visibility into the project's evolution, making it easier for users and contributors to understand what has been added, changed, or fixed in each release. Additionally, the project follows [Semantic Versioning](https://semver.org/spec/v2.0.0.html) (SemVer), which uses a versioning scheme of MAJOR.MINOR.PATCH. This practice enhances predictability and compatibility by clearly indicating the impact of updates: major versions for breaking changes, minor versions for new features, and patch versions for bug fixes. Together, these standards improve the project's maintainability, transparency, and usability for developers and security enthusiasts.

---

## [0.1.1] - 2025-07-19

### Added
- Initial password generation functions implemented
- Command-line interface (CLI) support
- Basic documentation for usage and setup
- Initial C++ implementation of DNAPass password generator
- Logic based on DNA nucleotides (A, T, G, C) for password creation
- CLI support for generating passwords with adjustable length
- Random seed initialization based on system time
- Documentation draft with usage examples
- Initial integration of user authentication via biometric data
- Support for secure password generation based on DNA patterns
- API endpoints for DNA-based login and user profile creation
- Initial implementation of the DNAPass CLI tool in C++
- DNA-inspired password generation algorithm with customizable length (8–128 characters)
- Character diversity and ambiguity resolution strategies
- Basic documentation and usage instructions

### Changed
- Improved folder structure for easier navigation
- Refactored core logic for better performance
- Improved nucleotide mapping to enhance character distribution
- Refactored core algorithm for better readability and performance
- Refactored encryption module to enhance DNA matching performance
- Updated UI for onboarding to reflect biometric steps
- Adjusted database schema to support genetic data fields
- Optimized the entropy calculation for improved randomness
- Refactored password generation logic for better readability and performance

### Fixed
- Resolved minor bugs related to password length validation
- Fixed CLI input parsing issues
- Corrected memory leak during password generation loop
- Resolved edge case with repeated nucleotide sequences
- Resolved login failure issue on older devices
- Corrected bug causing session timeout after successful authentication
- Fixed display glitch in genetic profile preview
- Corrected character pool mixing to prevent unintentional bias in output
- Fixed CLI input validation for edge-case lengths

## [0.1.0] - 2025-07-18

### Added
- Initial implementation of the password generator with DNA-inspired sequences.
- Support for generating passwords with lengths between 8 and 128 characters.
- Inclusion of uppercase letters, lowercase letters, digits, and special characters in password generation.
- Ambiguity resolution for DNA sequences using a predefined map of ambiguous characters.
- Password analysis feature displaying counts of uppercase, lowercase, digits, and special characters.
- Detailed step-by-step installation instructions in `README.md`, including prerequisites (`git`, `cmake`, `g++`) and troubleshooting for common errors.
- Support for automated password generation via input redirection (e.g., `echo "75" | ./dnapass_generator`) in `README.md`.
- Project structure section in `README.md` to clarify the organization of source files and workflows.
- GitHub Actions workflow badge for `cpp-release.yml` in `README.md` to show release status.
- Detailed installation guide in `README.md` with step-by-step instructions for Linux (e.g., Parrot Linux, Ubuntu), including prerequisites (`git`, `cmake`, `g++`) and troubleshooting for common errors.
- Support for automated password generation via input redirection (e.g., `echo "75" | ./dnapass_generator`) documented in `README.md`.
- Project structure section in `README.md` to clarify the organization of source files, headers, and GitHub Actions workflows.
- GitHub Actions workflow badge for `cpp-release.yml` in `README.md` to display release status alongside the build status.
- Adição de verificações de depuração no workflow `cpp-build.yml` para exibir o diretório atual e o conteúdo do `CMakeLists.txt` no Windows.

### Changed
- Moved the definition of the `special_chars` constant to `dnapass_generator.hpp` as an inline variable to resolve linkage issues.
- Adjusted the structure of lambdas in `dnapass_generator.cpp` to correctly reference `special_chars` from the namespace.
- Updated the `CMakeLists.txt` files in the root directory and `dnapass_password_generator` subfolder to support modular compilation across multiple operating systems and compilers.
- Improved the GitHub Actions workflow `cpp-release.yml` by adding Homebrew installation verification for `macos-latest` to prevent `brew: command not found` errors.
- Consolidated `CMakeLists.txt` files into a single file at the project root, updating source file paths and include directories for clarity and maintainability.
- Moved `special_chars` constant from `dnapass_generator.cpp` to `dnapass_generator.hpp` with `inline` declaration to improve code organization and resolve linkage issues.
- Updated GitHub Actions workflows (`cpp-build.yml` and `cpp-release.yml`) to use `apt-get` instead of `brew` on Ubuntu and to point CMake to the project root.
- Enhanced `README.md` with clearer instructions for Linux users, including commands for installing dependencies and a detailed build process.
- Consolidated `CMakeLists.txt` files into a single file at the project root, updating source file paths (`dnapass_password_generator/dnapass_generator.cpp`, `dnapass_password_generator/main.cpp`) and include directories for improved maintainability.
- Moved `special_chars` constant from `dnapass_generator.cpp` to `dnapass_generator.hpp` with `inline` declaration to enhance code organization and resolve linkage issues.
- Updated GitHub Actions workflows (`cpp-build.yml` and `cpp-release.yml`) to use `apt-get` for dependency installation on Ubuntu and to point CMake to the project root directory.
- Enhanced `README.md` with detailed build and usage instructions, including example outputs and support for both interactive and automated execution modes.
- Atualização das URLs no arquivo `dnapass_generator.cpp` para refletir o repositório correto: `https://github.com/gerivanc/dnapass-password-generator` e `https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md`.
- Ajuste no workflow `cpp-build.yml` para usar `%GITHUB_WORKSPACE%\dnapass-password-generator` como caminho fonte no CMake, garantindo a detecção do `CMakeLists.txt`.

### Fixed
- Resolved compilation error due to missing `<map>` header in `dnapass_generator.hpp`, enabling the use of `std::map` for `ambiguous_chars`.
- Fixed redefinition error of `struct PasswordResult` by removing duplicate declaration in `dnapass_generator.cpp`, ensuring it is defined only in the header.
- Corrected linkage errors on Parrot Linux by ensuring proper inclusion of `dnapass_generator.hpp` in `dnapass_generator.cpp`.
- Added the `<algorithm>` header to `main.cpp` to resolve compilation errors related to `std::count_if` not being recognized.
- Corrected the definition of `dnapass::special_chars` in `dnapass_generator.cpp` to fix linker errors (e.g., `Undefined symbols for architecture arm64`) on `macos-latest` with `clang`.
- Resolved linker error (`undefined reference to dnapass::special_chars`) by defining `special_chars` as `inline` in `dnapass_generator.hpp`.
- Fixed GitHub Actions workflow errors by correcting CMake paths and compiler setup for Ubuntu, macOS, and Windows environments.
- Addressed `cmake: command not found` and `./dnapass_generator: No such file or directory` errors by adding prerequisite installation steps in `README.md`.
- Resolved linker error (`undefined reference to dnapass::special_chars`) by defining `special_chars` as `inline` in `dnapass_generator.hpp`.
- Fixed GitHub Actions workflow errors by correcting CMake paths and compiler setup for Ubuntu, macOS, and Windows environments.
- Addressed common user errors (`cmake: command not found`, `./dnapass_generator: No such file or directory`) by adding prerequisite installation steps and troubleshooting guidance in `README.md`.
- Correção de erros de sintaxe no workflow `cpp-build.yml` ao processar comandos no ambiente Windows, incluindo a substituição de `&&` por etapas separadas e ajuste de caminhos relativos.
- Resolução de falhas na configuração do CMake no Windows, corrigindo o diretório de trabalho para apontar corretamente para a raiz do repositório.

---

#### Copyright © 2025 Gerivan Costa dos Santos
