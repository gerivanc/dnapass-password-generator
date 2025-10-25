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
 * Version: 0.1.3
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
	"TTATAA", "CACCTGCN", "NGAGGTC", "GACNNGTC", "AGGCCT", "GACGTC", "GCTCGAGG", "GTMKAC", 
	"CGCGG", "TGCGGA", "TGCGCA", "ACCTGCN", "GGTACC", "GGWACC", "CCANNNNTGG", "CCGTCTC", 
	"GAGCGG", "CAGCTCN", "NGAGCTG", "CCGC", "NGAANNTGG", "CACNNNGTG", "GCANNTGCAN", 
	"NGCANNTGC", "GACNNNTCCN", "NGGCAANNTG", "GCAANNGTCTCN", "NGAGACNNTGC", "AGCT", "GGWCC", 
	"CCTAGG", "CCTNAGG", "ACNNNGTAYCN", "NGTACNNGT", "N", "GCNGC", "GCTAGG", "GCTNAGC", "AGTACT", 
	"CCNGG", "CYCCRG", "GAGGTG", "GGNCC", "GGNNCC", "ACTGGGN", "NCCCAGT", "GCATCN", "NGATGC", 
	"GCTAGC", "GACNNNGTC", "GAGCACNN", "NGTCTC", "NGAGNCTC", "CTGGAGN", "NCTGGAG", "GCTNAGG", 
	"TTCGAA", "GAGACNN", "CTTGAGN", "NCTCAAG", "CCSGG", "CGATCG", "GCTCTCN", "NAGAGACC", "ATCGAT", 
	"YACGTR", "GATNNATC", "GRCGYC", "GAATGCN", "GCATTC", "WCCGGW", "ACNNNCTCCN", "NGGAGNNTGT", 
	"GGAGNNTGTN", "CAACACN", "NTGTTGTG", "CCNNNNNNGG", "CTCAGT", "RCCGGY", "TCCGGY", "CCWGG", 
	"NNGG", "CGGCGC", "CCGGC", "GGCGC", "GGGGGG", "GGGACN", "NCTCCAC", "CGCG", "GGRYG", "ACCGGT", 
	"CGRYG", "GATC", "GACNNNTGAN", "NTCANNGTC", "TCAKNGTCN", "GCCGGCC", "CATG", "CATCACN", "NGTGATG", 
	"GCCGAGN", "NNGC", "AAGCTT", "GANTC", "GTTAAC", "CCGG", "GGTGAN", "NNTCC", "GCCGCC", "AATT", 
	"NAGAGAGC", "CCCGN", "NNGGG", "CTCGAG", "WGTACW", "GCSGC", "GAWTC", "CASTGNN", "GCWGC", "TARCCAN", 
	"NTGGTA", "GTSAC", "ATGAAN", "NTTCAT", "ACGGAN", "NTCCGT", "CCCGGG", "CACNNNTCEN", "NGGANNNNGTG", 
	"NNNC", "NNCNCNNTC", "GACNNTCC", "NTGTTTC", "CTTGAC", "GGGC", "ATTAAT", "CCTNNNNAGG", "RAATTY", 
	"TCTAGA", "RCATGY", "RGATCY", "GAAANNTTC", "CTTAG", "ATGCN", "CGTAYR", "GCTNNA", "TCCAGN", "GACNTG", 
	"NNATGC", "CGWATG", "AGCNTT", "TGANNC", "CCRTAG", "GATCYR", "NNTGCA", "ACGWTC", "TCCNNG", "GAGNNT", 
	"CATGNC", "NNCCTA", "GTCAGR", "AGNNTC", "CTAYGN", "GGCNNA", "TTCAGN", "NATGGC", "CCRYGT", "GANNCT", 
	"TGCCNN", "ACTCYR", "NNGTAC", "CGATNN", "GCTCYR", "TGANNT", "NNCCGA", "AGCYGT", "GTCNNA", "CCTAYR", 
	"NNAGCT", "TGACNN", "CCGNNT", "GATNCC", "ACTGNN", "NNTGCC", "CGCYGT", "TTCNNA", "GAGNCC", "NNTCGA", 
	"AGNTGC", "CCTCYR", "GTCNNG", "NNAGGC", "TGANCC", "CGNNTA", "ACTCYG", "NNGTGC", "CCRYGA", "GATNNG", 
	"TGCCYR", "NNTGAC", "CGANNT", "AGCYGN", "TTCNNG", "GGCNNT", "GATATC", "CTGCAG", "GGATCC", "AAGCTN", 
	"NGAGCTC", "TCTAGA", "GAGCTC", "CTCGAG", "GCGGCCGC", "ACCGGT", "CATATG", "GAATTC", "CCCGGG", 
	"GGTCTC", "CACGTG", "GCGCGC", "ATGCAT", "AGGCCT", "GTCGAC", "ACTAGT", "TCTAGA", "CATGCA", "GTACAC", 
	"TCGCGA", "AGATCT", "GCCGGC", "CTTAAG", "AACGTT", "GTATAC", "CACACA", "TGTACA", "ACATGT", "TAGCAT", 
	"GCTAGC", "CATCAT", "GTAGTC", "ACACAC", "TGTGTG", "AGAGAG", "CTCTCT", "GAGAGA", "CTCCTC", "GAGGAG", 
	"ATATAT", "TATATA", "GCGCAT", "ATGCGC", "CGATCG", "GCTAGC"
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
