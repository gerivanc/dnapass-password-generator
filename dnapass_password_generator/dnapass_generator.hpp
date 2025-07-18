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

struct PasswordResult {
    std::string password;
    std::vector<std::string> used_words;
    std::vector<std::string> resolved_log;
};

// Função principal para gerar senhas
PasswordResult generate_password(int length, std::mt19937& rng);

// Função auxiliar para resolver sequências ambíguas
std::pair<std::string, std::string> resolve_ambiguous_sequence(const std::string& sequence, std::mt19937& rng);

} // namespace dnapass

#endif // DNAPASS_GENERATOR_HPP
