/*
 * DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
 * Copyright © 2025 Gerivan Costa dos Santos
 * Author: gerivanc
 * GitHub: https://github.com/gerivanc/dnapass-password-generator
 * MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md
 * Version: 0.1.3
 */

#ifndef DNAPASS_GENERATOR_HPP
#define DNAPASS_GENERATOR_HPP

#include <string>
#include <vector>
#include <random>
#include <map>

namespace dnapass {

// REMOVE 'extern' and use 'inline' to avoid linking issues
inline const std::string special_chars = "!@#$%^&*()_+-=[]{}|;:,.<>?~\\";

extern const std::vector<std::string> primary_sequences;
extern const std::vector<std::string> secondary_words;
extern const std::map<char, std::vector<char>> ambiguous_chars;

struct PasswordResult {
    std::string password;
    std::vector<std::string> used_words;
    std::vector<std::string> resolved_log;
};

// Main function to generate passwords
PasswordResult generate_password(int length, std::mt19937& rng);

// Auxiliary function to resolve ambiguous sequences
std::pair<std::string, std::string> resolve_ambiguous_sequence(const std::string& sequence, std::mt19937& rng);

} // namespace dnapass

#endif // DNAPASS_GENERATOR_HPP
