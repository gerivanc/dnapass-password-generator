/*
 * DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
 * Copyright © 2025 Gerivan Costa dos Santos
 * Author: gerivanc
 * GitHub: https://github.com/gerivanc/dnapass-password-generator
 * MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md
 * Version: 0.1.0
 */

#ifndef DNAPASS_GENERATOR_HPP
#define DNAPASS_GENERATOR_HPP

#include <string>
#include <vector>
#include <random>

namespace dnapass {

extern const std::string special_chars; // External declaration of the constant

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
