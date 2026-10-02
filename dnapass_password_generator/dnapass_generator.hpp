/*
 * DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
 * Copyright © 2025-2026 Gerivan Costa dos Santos
 * Author: gerivanc
 * GitHub: https://github.com/gerivanc/dnapass-password-generator
 * MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md
 * Version: 0.1.5
 */

#ifndef DNAPASS_GENERATOR_HPP
#define DNAPASS_GENERATOR_HPP

#include <map>
#include <string>
#include <vector>

namespace dnapass {

// Project version (keep in sync with CMakeLists.txt and docs).
inline constexpr const char* version = "0.1.5";

// Allowed password length range.
inline constexpr int min_length = 8;
inline constexpr int max_length = 128;
inline constexpr int default_length = 32;

// Minimum number of special characters when special characters are enabled.
inline constexpr int min_special = 4;

// 'inline' (C++17) gives a single definition across translation units.
inline const std::string special_chars = "!@#$%^&*()_+-=[]{}|;:,.<>?~\\";
inline const std::string digit_chars = "0123456789";

extern const std::vector<std::string> primary_sequences;
extern const std::vector<std::string> secondary_words;
extern const std::map<char, std::vector<char>> ambiguous_chars;

// User-selectable options. These mirror the toggles of the web version
// (docs/dnapass.html): INCLUDE UPPERCASE / LOWERCASE / DIGITS / SPECIAL.
struct GeneratorOptions {
    int length = default_length;
    bool include_uppercase = true;
    bool include_lowercase = true;
    bool include_digits = true;
    bool include_special = true;
};

struct PasswordResult {
    std::string password;
    std::vector<std::string> used_words;
    std::vector<std::string> resolved_log;
};

struct CharacterCounts {
    int length = 0;
    int uppercase = 0;
    int lowercase = 0;
    int digits = 0;
    int special = 0;
};

// Minimum digits: 2 below 50 characters, 3 at 50 characters or more.
int min_digits_for(int length);

// Minimum uppercase letters: 10% of the length, at least 1.
int min_uppercase_for(int length);

// Main function to generate passwords. Uses the OS CSPRNG for every random
// decision. Throws std::invalid_argument for lengths outside 8..128.
PasswordResult generate_password(const GeneratorOptions& options);

// Convenience overload: all character types enabled.
PasswordResult generate_password(int length);

// Resolves IUPAC ambiguity codes (N, R, Y, ...) with the CSPRNG.
// Returns {resolved, original}.
std::pair<std::string, std::string> resolve_ambiguous_sequence(const std::string& sequence);

// Counts each character class in a password.
CharacterCounts count_characters(const std::string& password);

// Charset-based Shannon estimate: length * log2(charset size), where the
// charset size is the sum of the classes actually present in the password.
// This is an UPPER BOUND: DNAPass builds passwords from a fixed, public set of
// sequences, so the real guessing entropy is lower than this value.
double estimate_entropy_bits(const std::string& password);

// Returns true when `password` satisfies every rule implied by `options`.
bool meets_policy(const std::string& password, const GeneratorOptions& options);

} // namespace dnapass

#endif // DNAPASS_GENERATOR_HPP
