# Changelog

[![Keep a Changelog](https://img.shields.io/badge/Keep%20a%20Changelog-1.0.0-orange)](https://keepachangelog.com/en/1.0.0/)
[![Semantic Versioning](https://img.shields.io/badge/Semantic%20Versioning-2.0.0-blue)](https://semver.org/spec/v2.0.0.html)

All notable changes to the 🧬 DNAPass Password Generator project are documented in this file. This project adheres to the [Keep a Changelog](https://keepachangelog.com/en/1.0.0/) standard, which ensures a structured and human-readable format for tracking changes. By following this approach, we provide clear visibility into the project's evolution, making it easier for users and contributors to understand what has been added, changed, or fixed in each release. Additionally, the project follows [Semantic Versioning](https://semver.org/spec/v2.0.0.html) (SemVer), which uses a versioning scheme of MAJOR.MINOR.PATCH. This practice enhances predictability and compatibility by clearly indicating the impact of updates: major versions for breaking changes, minor versions for new features, and patch versions for bug fixes. Together, these standards improve the project's maintainability, transparency, and usability for developers and security enthusiasts.

---

## [0.1.5] - 2026-10-02

### Added
- Progressive Web App (PWA) support for `docs/dnapass.html`: the web generator can now be installed from any browser that supports installation and keeps working offline after the first visit.
- New service worker `docs/sw.js` (network-first for pages, stale-while-revalidate for same-origin assets, versioned cache `dnapass-v0.1.5`, old caches removed on activation). Cross-origin requests are never intercepted, and generated passwords are never sent over the network or cached.
- Bilingual (English / Brazilian Portuguese) install banner in `docs/dnapass.html` asking whether the visitor wants to install the app: uses the native install prompt on Chromium browsers (`beforeinstallprompt`), shows "Share → Add to Home Screen" instructions on iOS/iPadOS, "File → Add to Dock" on Safari for macOS, and browser-menu instructions on other browsers without an install API. "Not now" is remembered for 7 days, the banner never appears when the app is already running installed, and it can be closed with the Escape key.
- PWA meta tags in `docs/dnapass.html` (`mobile-web-app-capable`, `apple-mobile-web-app-capable`, `apple-mobile-web-app-title`, `application-name`) and `worker-src 'self'` / `manifest-src 'self'` CSP directives.
- C++ CLI: cryptographically secure random number module (`secure_random.hpp` / `secure_random.cpp`) that reads directly from the operating system CSPRNG (`BCryptGenRandom` on Windows, `getentropy()` on Linux/macOS/BSD, `/dev/urandom` elsewhere) and fails closed instead of falling back to a non-cryptographic generator. Includes a bias-free `uniform_below()`/`uniform_int()` based on rejection sampling.
- C++ CLI: command-line options that mirror the web toggles: `-l/--length N` (or a positional `LENGTH`), `--no-uppercase`, `--no-lowercase`, `--no-digits`, `--no-special`, `-q/--quiet`, `-h/--help`, `-v/--version`. The interactive prompt (`./dnapass_generator`) and automated mode (`echo "45" | ./dnapass_generator`) keep working unchanged.
- C++ CLI: "Settings" block and "Entropy (estimated)" line in the output, with the same upper-bound note shown on the web page.
- C++ API: `GeneratorOptions`, `CharacterCounts`, `count_characters()`, `estimate_entropy_bits()`, `meets_policy()`, `min_digits_for()`, `min_uppercase_for()` and the `dnapass::version` constant.
- Automated test suite `tests/test_generator.cpp` (CTest): validates 19,360 passwords per run (all 16 toggle combinations × every length from 8 to 128 × 10 repetitions) against the policy, plus range/chi-square checks for the CSPRNG helpers and CLI smoke tests. Both GitHub Actions workflows now run `ctest`.

### Changed
- C++ CLI: password generation now follows exactly the same rules as `docs/dnapass.html`: case normalization when uppercase or lowercase is disabled, digit minimum of 2 below 50 characters and 3 at 50 or more, at least 4 special characters, at least 10% uppercase (minimum 1) and at least 1 lowercase, all placed by reserving unique positions from a shared pool, followed by a CSPRNG-driven Fisher-Yates shuffle.
- C++ CLI: `std::mt19937` (not cryptographically secure) was removed from password generation; `generate_password()` now takes `GeneratorOptions` (a `generate_password(int length)` overload is kept for convenience).
- C++ CLI: errors are written to standard error and the program exits with a non-zero status (1 for invalid input, 2 for unexpected errors) so scripts can detect failures. Length input is now parsed strictly (e.g. `12abc` is rejected).
- `docs/site.webmanifest`: added `id`, `scope`, `lang`, `display_override`, `orientation` and `categories`; `start_url` now opens the generator (`/dnapass.html`); `theme_color`/`background_color` aligned with the page (`#000000`); icons now declare `purpose` explicitly and include an `any` entry for the 960×960 icon. The `web-app-manifest-960x958.png` icon is declared with its real size (`960x960`) in the manifest and in `docs/index.html`; the previous `960x958` value did not match the image.
- `docs/dnapass.html`: manifest is now linked with a relative URL (`site.webmanifest`) so it is always same-origin; `img-src` CSP tightened to `'self' data:` (no external images are used on the page); `<meta name="description">` now describes the generator instead of a generic developer bio.
- `docs/dnapass.html`: entropy is computed as `length × log2(charset)` instead of `log2(charset^length)` (same value, no huge intermediate number).
- `docs/dnapass.html`, `docs/index.html`, `DNAPASSCALCULATION.md`: replaced the inaccurate claim that a 12-character password exceeds 80 bits (the charset-based estimate is about 78 bits at 12 characters with the 90-symbol set, and it is an upper bound); 16+ characters are now recommended for high-security accounts.
- Documentation updated to the real size of the primary sequence list (253 entries, 244 unique) instead of "200".
- `SECURITY.md`: supported-versions table updated; versions before 0.1.4 are no longer supported because they generate passwords with a non-cryptographic PRNG.
- Issue templates: added the YAML front matter GitHub needs to list them in the issue chooser, fixed mislabeled contact links, and updated build instructions and version examples.

### Fixed
- `docs/dnapass.html`: rejection sampling in `getRandomInt()` accepted the boundary value (`value > limit` instead of `value >= limit`), leaving a residual 1-in-2^32 bias toward the low end of the range.
- `docs/dnapass.html`: an empty or non-numeric length field passed validation (`parseInt('')` is `NaN`, and `NaN < 8` is `false`) and produced an empty password; the length is now validated with `Number.isInteger()`.
- `docs/dnapass.html`: removed `maximum-scale=1.0` and `user-scalable=no` from the viewport (blocked pinch-to-zoom, a WCAG accessibility issue), matching `docs/index.html`.
- C++ CLI: "at least N" guarantees could silently fail (positions overwritten by later steps, counters incremented without a real change), and the result was only rescued by unbounded recursive retries; generation is now correct by construction and verified by `meets_policy()`.
- `README.md`: bug-report section linked to the CONTRIBUTING guide of a different repository.
- `RELEASE.md`: feedback link pointed to a non-existent repository path.
- `DNAPASSCALCULATION.md`: removed references to Python's `random`/`secrets` modules (the project is written in C++ and JavaScript) and fixed the worked example.

### Removed
- C++ CLI: `std::mt19937` (non-cryptographic PRNG) from password generation, together with the `std::mt19937& rng` parameter of `generate_password()` and `resolve_ambiguous_sequence()`, the `#include <random>` in `dnapass_generator.hpp`, and the `std::random_device` seeding in `main.cpp`.
- C++ CLI: the unbounded recursive retry (`return generate_password(length, rng);`) that regenerated the password whenever the diversity rules were not met; generation is now correct by construction.
- C++ CLI: `std::regex_replace` and `#include <regex>` used to strip whitespace in `dnapass_generator.cpp` (replaced by a simple character filter), and the `<cctype>` calls (`std::isalpha`, `std::isupper`, `std::tolower`, ...) that are undefined for negative `char` values (replaced by ASCII-only helpers).
- C++ CLI: the old minimum-count loops (`while (digit_count < min_digits)`, `while (special_count < 4)`, `while (upper_count < min_upper)`) that wrote to random positions and could overwrite characters placed by earlier steps.
- C++ CLI: error messages printed to standard output with exit status `0`; errors now go to standard error with a non-zero exit status.
- Leftover maintenance comments in the C++ sources: "REMOVE 'extern' and use 'inline' to avoid linking issues" (`dnapass_generator.hpp`) and the Portuguese comment "CORREÇÃO: Usar a variável special_chars diretamente" (`main.cpp`).
- `docs/dnapass.html`: `maximum-scale=1.0` and `user-scalable=no` from the `<meta name="viewport">` tag (blocked pinch-to-zoom).
- `docs/dnapass.html`: unused `Content-Security-Policy img-src` allowances (`*.githubusercontent.com`, `img.shields.io`, `komarev.com`, `github-readme-activity-graph.vercel.app`, `nirzak-streak-stats.vercel.app`, `github-readme-stats.vercel.app`, `github-profile-summary-cards.vercel.app`, `vercel.app`, `vercel.live`); the page loads no external images.
- `docs/dnapass.html`: the absolute manifest URL (`https://dnapass.gerivan.me/site.webmanifest`), the generic developer-bio `<meta name="description">`, the Portuguese comment "Meta tags para PWA", and the `parseInt()`-based length validation that let an empty field through.
- `docs/dnapass.html` and `docs/index.html`: the inaccurate claims "For a 12-character password, DNAPass typically achieves entropy above NIST's 80-bit recommendation" and "exceeding NIST's 80-bit recommendation for high-security passwords".
- `docs/site.webmanifest`: the white `theme_color`/`background_color` (`#ffffff`), which conflicted with the page's `#000000`, and the incorrect `960x958` size declaration (the image is 960×960); the same wrong `sizes="960x958"` was removed from `docs/index.html`.
- Documentation: the outdated "200 primary sequences" and "141 primary sequences" counts (`docs/dnapass.html`, `docs/index.html`, `DNAPASSCALCULATION.md`).
- `DNAPASSCALCULATION.md`: the references to Python's `random` and `secrets` modules, the "32 special characters / 94-symbol" figures (the set has 28 symbols, 90 in total), and the inconsistent worked example.
- `SECURITY.md`: the support rows for versions 0.1.3 and 0.1.2 and the contradictory "< 0.5 not supported" row.
- `README.md`: the "written in Python" text in the header image alt text and the link to another repository's CONTRIBUTING guide (`entropy-password-generator`).
- `RELEASE.md`: the broken feedback link (`gerivanc/dnapass`) and the v0.1.3 release notes, replaced by v0.1.5.
- `.github/ISSUE_TEMPLATE/config.yml`: the unsupported `issue_templates:` key and the mislabeled "Issue Report" and "Bug Report" contact links (described as security channels); replaced by a link to `SECURITY.md`.
- `.github/ISSUE_TEMPLATE/bug_report.md` and `issue_template.md`: the single-file build command (`g++ -std=c++17 dnapass_generator.cpp -o dnapass_generator`), which no longer builds the project, and the "80+ bits of entropy" expected-behavior examples.
- `.github/workflows/cpp-build.yml`: the Portuguese comment "Definir compilador baseado no OS" and the wildcard artifact path `build/dnapass_generator*`.

## [0.1.4] - 2026-09-06

### Added
- Cryptographically secure random number generation for password creation in `docs/dnapass.html`, using the Web Crypto API (`crypto.getRandomValues()`): `secureRandomUint32()`, `secureRandomFloat()`, and a bias-free `getRandomInt()` built on rejection sampling, replacing `Math.random()` everywhere it fed into the generated password (sequence selection, case-flattening pass, character-diversity insertion, and the Fisher-Yates shuffle)
- `reserveIndices()` helper in `docs/dnapass.html` that draws unique array positions from a shared pool without replacement, so digits, special characters, and forced-uppercase letters can never land on the same index
- ARIA live-region attributes (`role="status"`, `aria-live="polite"`, `aria-atomic="true"`) on the password display, and `aria-live="polite"` on the analysis panel in `docs/dnapass.html`, so screen readers announce newly generated passwords and updated analysis values
- Hardened Content-Security-Policy directives in `docs/dnapass.html`: `object-src 'none'`, `base-uri 'self'`, `form-action 'self'`
- Clarifying note in the "ENTROPY CONSIDERATIONS" section of `docs/dnapass.html` explaining that the displayed entropy is a charset-based Shannon estimate (an upper bound), since DNAPASS builds passwords from a fixed, published set of sequences rather than choosing every character independently and uniformly at random
- `rel="noopener noreferrer"` on all 14 external `target="_blank"` links in `docs/index.html` to prevent reverse tabnabbing.
- Open Graph meta tags (`og:type`, `og:title`, `og:description`, `og:url`, `og:image`) in `docs/index.html` for social sharing previews.
- Twitter Card meta tags (`twitter:card`, `twitter:title`, `twitter:description`, `twitter:image`) in `docs/index.html`.
- `@media (prefers-reduced-motion: reduce)` rule in `docs/index.html` to disable the pulse, DNA-rain, Matrix-rain, helix-rotation, and security-alert animations for users who request reduced motion.
- `aria-hidden="true"` on purely decorative background elements in `docs/index.html` (`dna-rain`, `matrix-bg`, `dna-animation`/`dna-helix`) so screen readers skip them.
- `role="alert"` on the security overlay in `docs/index.html`, with its `aria-hidden` state now toggled by `showSecurityAlert()` when shown and reset when hidden, so assistive technology announces it correctly.

### Changed
- `docs/dnapass.html`: "INCLUDE UPPERCASE" and "INCLUDE LOWERCASE" now normalize the generated password to the requested case before the diversity checks run, so disabling one of them actually excludes that case from the output instead of only skipping the minimum-count enforcement
- `docs/dnapass.html`: digit-count enforcement now scales with password length (at least 2 digits below 50 characters, 3 at 50 characters or more), matching the rule already documented in the "CHARACTER DIVERSITY" section instead of only guaranteeing a single digit
- `docs/dnapass.html`: digit, special-character, and forced-uppercase minimums are now satisfied by reserving unique positions up front instead of looping with counters that could be incremented without a real change taking place
- Corrected the "How It Works" entropy section in `docs/index.html` from "141 primary and 8 secondary sequences" to "200 primary and 8 secondary sequences" to match the Overview section and the current `primary_sequences` count in `dnapass_generator.cpp`.
- Tightened the `Content-Security-Policy img-src` directive in `docs/index.html` to only the domains actually referenced on the page.
- Updated the `<meta name="description">` in `docs/index.html` to describe DNAPass specifically instead of a generic developer bio.
- Updated the `<meta name="viewport">` in `docs/index.html` to keep pinch-to-zoom enabled for accessibility.
- Rebuilt the inner `<ul>`/`<li>` markup of the Usage → Command Line and Troubleshooting code blocks in `docs/index.html` so the lists render correctly.
- Replaced backtick-wrapped inline code and stray leftover `**` Markdown artifacts in the Troubleshooting list (`docs/index.html`) with consistent `<span class="highlight">` styling.
- Translated remaining Portuguese code comments (CSS and JavaScript) in `docs/index.html` to English.

### Fixed
- `docs/dnapass.html`: fixed a bug where the special-character insertion step could overwrite a position that had just been filled to satisfy the digit minimum (or vice versa), since both steps picked random positions independently; most noticeable at the minimum allowed length of 8 characters, where it could silently produce passwords with fewer digits or special characters than guaranteed
- `docs/dnapass.html`: fixed minimum-count enforcement loops (digits, special characters, forced uppercase) that incremented their internal counters even when a randomly chosen position had already been counted, letting the loop exit before the documented minimum was actually reached
- `docs/dnapass.html`: added an iteration guard to the "ensure at least one lowercase letter" step, removing a theoretical unbounded loop
- Unclosed `<li>` tags in the Usage → Command Line and Troubleshooting code blocks in `docs/index.html`.
- Duplicate/conflicting `h2` CSS rule in `docs/index.html` that overrode the heading `font-size` (2.2rem vs. 1.8em) set earlier in the stylesheet.
- Missing `aria-hidden` reset on the security alert overlay in `docs/index.html` when it is hidden again after its timeout.

### Removed
- Duplicate `<meta name="theme-color">` tag in `docs/dnapass.html` (two conflicting declarations, `#00ffff` and `#000000`, existed in `<head>`; kept the one used for the PWA status bar)
- Duplicate `<meta name="theme-color">` tag (`#00ffff`) in `docs/index.html`, keeping only the PWA-consistent `#000000` value.
- Redundant `h2` CSS rule (previously commented "Centraliza os títulos") in `docs/index.html` that duplicated and conflicted with the primary `h2` style.
- `maximum-scale=1.0` and `user-scalable=no` from the `<meta name="viewport">` tag in `docs/index.html` (blocked pinch-to-zoom, a WCAG accessibility violation).
- Unused `Content-Security-Policy img-src` allowances in `docs/index.html` (`img.shields.io`, `komarev.com`, `github-readme-activity-graph.vercel.app`, `nirzak-streak-stats.vercel.app`, `github-readme-stats.vercel.app`, `github-profile-summary-cards.vercel.app`, `vercel.app`, `vercel.live`) not referenced anywhere on the page.

## [0.1.3] - 2025-10-24

### Added
- Completed total of 200 sequences for nucleotides in code 'dnapass_generator.cpp' function 'const std::vector<std::string> primary_sequences = { '
- GitHub Actions CI/CD workflow for automated testing and building across multiple platforms
- Multi-platform support (Ubuntu, macOS, Windows) with GCC and Clang compilers
- Automated release process triggered by version tags
- Comprehensive error handling and input validation in password generation
- Initial public release of DNAPass Password Generator
- Core password generation functionality inspired by DNA sequences
- Support for customizable password lengths (8-128 characters)
- Character diversity enforcement (uppercase, lowercase, digits, special characters)
- Ambiguous DNA sequence resolution system
- Initial project setup and structure
- Basic CMake build system configuration
- Core DNA sequence libraries and character mapping

### Changed
- Refactored CMake configuration to support cross-platform compilation
- Improved project structure with separated source files in `dnapass_password_generator/` directory
- Enhanced character diversity enforcement in password generation algorithm
- Updated compiler-specific flags for better code quality and warnings

### Fixed
- Completed total of 200 sequences for nucleotides in code 'dnapass_generator.cpp'
- Resolved CMake configuration issues preventing successful builds on macOS and Windows
- Fixed `special_chars` variable declaration and linking errors across multiple compilation units
- Corrected recursive password generation to include maximum attempt limits
- Addressed file path inconsistencies in build system configuration
- Fixed character counting logic in password analysis output

## [0.1.2] - 2025-08-31

### Added
- Expanded the `primary_sequences` list in `dnapass_generator.cpp` to include 200 unique DNA-inspired sequences, adding 62 new sequences to the existing 138 unique sequences to enhance password generation variety. **GPG Key ID: B5690EEEBB952194, Verified on Jul 26, 2025, 09:49 AM. Commit: ab808319d020ea7bbc0f0772483a3fc66cb8e5a9

### Changed
- Extracted and processed the `Sequence` column from the `PASSWORD TEMPLATE FOR WEBSITES.pdf` file, removing the pipe '|' symbol from all sequences and reducing repetitions of 5 or more 'N' characters to a single 'N'.
- Integrated the processed sequences into `dnapass_generator.cpp`, ensuring proper formatting with quotes and commas for compatibility with the existing `std::vector<std::string>` structure.
- Removed duplicate sequences from `primary_sequences` in `dnapass_generator.cpp`, reducing the list from 190 to 138 unique sequences before expanding to 200 unique sequences.
- Reviewed and confirmed that `dnapass_generator.hpp` remains consistent with the updated `dnapass_generator.cpp` and requires no mandatory changes.
- Analyzed `main.cpp` and confirmed its compatibility with the updated `primary_sequences` list, with no mandatory changes needed.

### Fixed
- None

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
