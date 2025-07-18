/*
 * DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
 * written in C++.
 *
 * This program provides the core functionality for generating strong, random
 * passwords with customizable character sets, inspired by DNA sequences.
 *
 * =========================
 * Features:
 * - Generates passwords with lengths between 8 and 128 characters.
 * - Supports uppercase letters, lowercase letters, digits, and special characters.
 * - Uses DNA-inspired sequences for password generation.
 * ----------------------------------------
 *
 * Copyright © 2025 Gerivan Costa dos Santos
 * DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
 * Author: gerivanc
 * GitHub: https://github.com/gerivanc/dnapass-password-generator
 * MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md
 * Changelog: https://github.com/gerivanc/dnapass-password-generator/blob/main/CHANGELOG.md
 * Issue Report: https://github.com/gerivanc/dnapass-password-generator/blob/main/.github/ISSUE_TEMPLATE/issue_template.md
 * Version: 0.1.0
 */

#include "dnapass_generator.hpp"
#include <string>
#include <vector>
#include <map>
#include <random>
#include <regex>
#include <algorithm>
#include <cctype>
#include <stdexcept>

namespace dnapass {

const std::vector<std::string> primary_sequences = {
    "TTATAA", "CACCTGCNNNN", "NNNNNNNNGCAGGTG", "GACNNNNNGTC", "AGGCCT", "GACGTC", "GCTCGAGG",
    "GTMKAC", "CGCG", "TCCGGA", "TGCGCA", "ACCTGCNNNN", "NNNNNNCAGGT", "GGTACC", "GGWACC",
    "CCANNNNNTGG", "CCGTCTC", "GAGCGG", "CAGCTCNNNNNNN", "NNNNNNNNGAGCTG", "CCGC", "GASTCT",
    "GACTCNNNN", "NNNNNGATCC", "WGGCCR", "RAATTY", "ATGAGNNNNNNNNNNNNNNN", "GACGTG", "GTAC",
    "GCTNAGT", "GCNTGTT", "ACRYGT", "CACNNNNTG", "GCANNNNNNTGCANNNNNNNNNNNN",
    "NNNNNNNNNNGCANNNNNNTGC", "GACNNNNNNTCCNNNNNNNNNNNNNN", "NNNNNNNGGCANNNNNNTG",
    "GCANNNNNNGTCTCNNNNNNNNNNNN", "NNNNNNNNNGACNNNNNTGC", "AGCT", "GTCTCN", "NNNNGAGAC",
    "GTGCAC", "GAGTNNTCTG", "GGTGG", "TCCGGA", "AGGCCT", "GGAGTC", "GTGCAC", "GCWGC", "GCTAGG",
    "GCTNAGC", "AGTACT", "GWGCWC", "CCNGG", "GACTNNNNNGTC", "CYCCRG", "GACNNNNNGTC",
    "GAGGNNNNNNNNNNNNN", "NNNNNNNNNNNCTCTC", "GACNNNNTG", "ATGCAAT", "CATTTG", "GCTCTCN",
    "NNNNGAGACC", "ATCGAT", "YACGTR", "GATNNNNATC", "GRCGYC", "CCNNGG", "GAATGTC", "GCATTG",
    "WCCGGW", "ACNNNNNCTCC", "NNNNNNGGAGNNNNGT", "GGAGNNNNNTGT", "CAACACNNNNNNNNNNNNNNNNNNNNNN",
    "NNNNNNNNNNNNNNNTGTTGTG", "CCNNNNNNNGG", "GCATCNNN", "NNNNNGATG", "ACTGGN", "CTCAGN",
    "GATNNNNATC", "CCTYAGG", "RCCGGA", "CCWGG", "GCAATGNN", "CATTTG", "GCATGNN", "CATCC",
    "GATNNNNATC", "CCNNNNNNNGG", "GCAATGNN", "CATTTG", "CTCAGNNNNNNNNNN", "NNNNNNNGAG",
    "ACTGGN", "CTCAGN", "GCGCGC", "GAGGAGNNNNNNNNN", "NNNNNNNCTCTC", "GAGGCTC", "GCAGCNNN",
    "NNNNNNCTG", "NNNNNNNNNNNNNCTGCAC", "CGCGC", "CGGGC", "CGGG", "GGAGNNNNNNNNNNNN",
    "NNNNNNNNNNNNNCTGCAC", "CGCGC", "GGNCCG", "GGRYCG", "GGCC", "GCYRCC", "ACCGGT", "ATCGAT",
    "GWGCWC", "CGGG", "CGRYCG", "GWGCWC", "CCGG", "CGRYCG", "CCNNNNNNGG", "GGGACNNNNNNNNNN",
    "NNNNNNNNNNGTCCC", "GAATGTC", "GCATTG", "GTCTCN", "NNNNGAGAC", "GATC", "GACNNNNNTGANNNNNNNNNNNNN",
    "NNNNNNNNNNNNNTC", "TCAKNNNNGTC", "NNNNNNNNNNNNNN", "GCCGGC", "GCTAGC", "CATG", "GGNCC",
    "CGGWCCG", "GAGCTC", "CCGGGG", "GTCGAC", "GCTCTTCN", "NNNGAGAGC", "TTAA", "GCWGC", "GCGCC",
    "GGTGNNNNNNNNNNNN", "NNNNNNNNNNNNCTCC", "AGGCCT", "CCWWGG", "ATTTAAAT", "GCWGC", "GCG",
    "CGAAGACNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNCTTCTG", "CCCGNNNN", "NNNNNNNCCGG",
    "CCNGG", "CTCGAG", "GGTGNNNNNNNNNNNN", "NNNNNNNNNNNNCTCC", "AGGCCT", "CCTNNNNNNAGG",
    "RAATTY", "TCTAGA", "RCATGY", "CCANNNNNNNNTGG", "CTCGAG", "CCCGGG", "CTTAG", "GTMKAC",
    "GAAANNNNTTC", "GACGTC", "AGTACT", "ATGCT"
};

const std::vector<std::string> secondary_words = {
    "gattaca", "cgcg", "atcg", "tagc", "actg", "ccgg", "ttaa", "ggcc"
};

const std::map<char, std::vector<char>> ambiguous_chars = {
    {'N', {'A', 'T', 'C', 'G'}},
    {'R', {'A', 'G'}},
    {'Y', {'C', 'T'}},
    {'M', {'A', 'C'}},
    {'K', {'G', 'T'}},
    {'S', {'C', 'G'}},
    {'W', {'A', 'T'}},
    {'B', {'C', 'G', 'T'}},
    {'D', {'A', 'G', 'T'}},
    {'H', {'A', 'C', 'T'}},
    {'V', {'A', 'C', 'G'}}
};

std::pair<std::string, std::string> resolve_ambiguous_sequence(const std::string& sequence, std::mt19937& rng) {
    std::string resolved;
    for (char c : sequence) {
        auto it = ambiguous_chars.find(c);
        if (it != ambiguous_chars.end()) {
            std::uniform_int_distribution<> dist(0, it->second.size() - 1);
            resolved += it->second[dist(rng)];
        } else {
            resolved += c;
        }
    }
    return {resolved, sequence};
}

PasswordResult generate_password(int length, std::mt19937& rng) {
    if (length < 8 || length > 128) {
        throw std::invalid_argument("Password length must be between 8 and 128 characters.");
    }

    std::string password;
    std::vector<std::string> used_words;
    std::vector<std::string> resolved_log;
    std::uniform_real_distribution<> dist(0.0, 1.0);

    // Choose words randomly (90% from primary set, 10% from secondary)
    while (password.length() < static_cast<size_t>(length)) {
        std::string word, original;
        if (dist(rng) < 0.9) { // 90% chance to use primary set
            std::uniform_int_distribution<> word_dist(0, primary_sequences.size() - 1);
            word = primary_sequences[word_dist(rng)];
            auto [resolved_word, orig] = resolve_ambiguous_sequence(word, rng);
            word = resolved_word;
            original = orig;
        } else { // 10% chance to use secondary set
            std::uniform_int_distribution<> word_dist(0, secondary_words.size() - 1);
            word = secondary_words[word_dist(rng)];
            original = word;
        }
        used_words.push_back(word);
        resolved_log.push_back(original + " -> " + word);
        password += word;
    }

    // Adjust password length
    password = password.substr(0, length);

    // Remove spaces and invalid characters
    password = std::regex_replace(password, std::regex("\\s+"), "");

    // Convert ~85% of alphabetic characters to lowercase
    for (size_t i = 0; i < password.length(); ++i) {
        if (std::isalpha(password[i]) && dist(rng) < 0.85) {
            password[i] = std::tolower(password[i]);
        }
    }

    // Ensure character diversity
    // Add at least two (or three for long passwords) digits
    std::string digits = "0123456789";
    int digit_count = std::count_if(password.begin(), password.end(), [](char c) { return std::isdigit(c); });
    int min_digits = (length >= 50) ? 3 : 2;
    std::uniform_int_distribution<> idx_dist(0, password.length() - 1);
    std::uniform_int_distribution<> digit_dist(0, digits.length() - 1);
    while (digit_count < min_digits) {
        password[idx_dist(rng)] = digits[digit_dist(rng)];
        ++digit_count;
    }

    // Add at least four special characters
    int special_count = std::count_if(password.begin(), password.end(),
                                      [](char c) { return dnapass::special_chars.find(c) != std::string::npos; });
    std::uniform_int_distribution<> special_dist(0, dnapass::special_chars.length() - 1);
    while (special_count < 4) {
        password[idx_dist(rng)] = dnapass::special_chars[special_dist(rng)];
        ++special_count;
    }

    // Ensure at least 10% uppercase (minimum 1)
    int upper_count = std::count_if(password.begin(), password.end(), [](char c) { return std::isupper(c); });
    int min_upper = std::max(1, length / 10);
    while (upper_count < min_upper) {
        int idx = idx_dist(rng);
        if (std::isalpha(password[idx])) {
            password[idx] = std::toupper(password[idx]);
            ++upper_count;
        }
    }

    // Ensure at least one lowercase
    bool has_lower = std::any_of(password.begin(), password.end(), [](char c) { return std::islower(c); });
    if (!has_lower) {
        int idx = idx_dist(rng);
        while (!std::isalpha(password[idx])) {
            idx = idx_dist(rng);
        }
        password[idx] = std::tolower(password[idx]);
    }

    // Shuffle randomly to avoid patterns
    std::shuffle(password.begin(), password.end(), rng);

    // Verify if the password meets all criteria
    upper_count = std::count_if(password.begin(), password.end(), [](char c) { return std::isupper(c); });
    has_lower = std::any_of(password.begin(), password.end(), [](char c) { return std::islower(c); });
    digit_count = std::count_if(password.begin(), password.end(), [](char c) { return std::isdigit(c); });
    special_count = std::count_if(password.begin(), password.end(),
                                  [](char c) { return dnapass::special_chars.find(c) != std::string::npos; });
    bool no_spaces = password.find(' ') == std::string::npos;

    if (password.length() >= 8 && password.length() <= 128 &&
        upper_count >= min_upper && has_lower && digit_count >= min_digits &&
        special_count >= 4 && no_spaces) {
        return {password, used_words, resolved_log};
    } else {
        return generate_password(length, rng); // Retry if criteria not met
    }
}

} // namespace dnapass
