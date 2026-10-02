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
 * - Supports uppercase letters, lowercase letters, digits, and special
 *   characters, each of which can be enabled or disabled.
 * - Uses DNA-inspired sequences for password generation.
 * - Every random decision uses the operating system CSPRNG (see
 *   secure_random.hpp); std::mt19937 is no longer used.
 * - Same generation rules as the web version (docs/dnapass.html).
 * ----------------------------------------
 *
 * Copyright © 2025-2026 Gerivan Costa dos Santos
 * DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
 * Author: gerivanc
 * GitHub: https://github.com/gerivanc/dnapass-password-generator
 * MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md
 * Changelog: https://github.com/gerivanc/dnapass-password-generator/blob/main/CHANGELOG.md
 * Issue Report: https://github.com/gerivanc/dnapass-password-generator/blob/main/.github/ISSUE_TEMPLATE/issue_template.md
 * Version: 0.1.5
 */

#include "dnapass_generator.hpp"
#include "secure_random.hpp"

#include <algorithm>
#include <cmath>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

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

namespace {

// ASCII-only character classification. Passwords contain only ASCII, and
// these helpers avoid the undefined behavior of <cctype> with negative chars.
bool is_upper(char c) { return c >= 'A' && c <= 'Z'; }
bool is_lower(char c) { return c >= 'a' && c <= 'z'; }
bool is_alpha(char c) { return is_upper(c) || is_lower(c); }
bool is_digit(char c) { return c >= '0' && c <= '9'; }
bool is_special(char c) { return special_chars.find(c) != std::string::npos; }
bool is_space(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v'; }
char to_upper(char c) { return is_lower(c) ? static_cast<char>(c - 'a' + 'A') : c; }
char to_lower(char c) { return is_upper(c) ? static_cast<char>(c - 'A' + 'a') : c; }

std::size_t random_index(std::size_t size) {
    return static_cast<std::size_t>(secure_random::uniform_below(static_cast<std::uint32_t>(size)));
}

// Picks up to `count` unique indices from `pool` (without replacement) using
// the CSPRNG, removing them from the pool. Mirrors reserveIndices() in the
// web version. Reserving positions up front (instead of poking random
// positions in a loop) guarantees that:
//   1. each placed digit/special/uppercase letter really increases its count;
//   2. digits and special characters never overwrite each other, because
//      both are drawn from the same shared pool.
std::vector<std::size_t> reserve_indices(std::vector<std::size_t>& pool, int count) {
    std::vector<std::size_t> picked;
    for (int k = 0; k < count && !pool.empty(); ++k) {
        const std::size_t r = random_index(pool.size());
        picked.push_back(pool[r]);
        pool.erase(pool.begin() + static_cast<std::ptrdiff_t>(r));
    }
    return picked;
}

} // namespace

int min_digits_for(int length) {
    return (length >= 50) ? 3 : 2;
}

int min_uppercase_for(int length) {
    return std::max(1, length / 10);
}

std::pair<std::string, std::string> resolve_ambiguous_sequence(const std::string& sequence) {
    std::string resolved;
    resolved.reserve(sequence.size());
    for (char c : sequence) {
        auto it = ambiguous_chars.find(c);
        if (it != ambiguous_chars.end()) {
            resolved += it->second[random_index(it->second.size())];
        } else {
            resolved += c;
        }
    }
    return {resolved, sequence};
}

PasswordResult generate_password(const GeneratorOptions& options) {
    const int length = options.length;
    if (length < min_length || length > max_length) {
        throw std::invalid_argument("Password length must be between 8 and 128 characters.");
    }

    std::string password;
    std::vector<std::string> used_words;
    std::vector<std::string> resolved_log;

    // Choose sequences randomly (90% from primary set, 10% from secondary)
    while (password.length() < static_cast<std::size_t>(length)) {
        std::string word;
        std::string original;
        if (secure_random::uniform_unit() < 0.9) { // 90% chance to use primary set
            const std::string& chosen = primary_sequences[random_index(primary_sequences.size())];
            auto resolved = resolve_ambiguous_sequence(chosen);
            word = resolved.first;
            original = resolved.second;
        } else { // 10% chance to use secondary set
            word = secondary_words[random_index(secondary_words.size())];
            original = word;
        }
        used_words.push_back(word);
        resolved_log.push_back(original + " -> " + word);
        password += word;
    }

    // Adjust password length
    password = password.substr(0, static_cast<std::size_t>(length));

    // Remove whitespace (sequences contain none; kept as a safety net)
    password.erase(std::remove_if(password.begin(), password.end(), is_space), password.end());

    // Convert ~85% of alphabetic characters to lowercase
    for (char& c : password) {
        if (is_alpha(c) && secure_random::uniform_unit() < 0.85) {
            c = to_lower(c);
        }
    }

    // Enforce the case options requested by the user. Disabling uppercase
    // (or lowercase) must really exclude that case from the output, not only
    // skip the minimum-count enforcement below.
    if (!options.include_uppercase && options.include_lowercase) {
        std::transform(password.begin(), password.end(), password.begin(), to_lower);
    } else if (options.include_uppercase && !options.include_lowercase) {
        std::transform(password.begin(), password.end(), password.begin(), to_upper);
    } else if (!options.include_uppercase && !options.include_lowercase) {
        // Both disabled: fall back to lowercase so the sequence-derived
        // letters stay valid characters instead of being stripped.
        std::transform(password.begin(), password.end(), password.begin(), to_lower);
    }

    // Shared pool of positions available for digit/special insertion.
    std::vector<std::size_t> available(password.size());
    for (std::size_t i = 0; i < available.size(); ++i) available[i] = i;

    // Digits: at least 2 below 50 characters, 3 at 50+.
    if (options.include_digits) {
        const int existing = static_cast<int>(std::count_if(password.begin(), password.end(), is_digit));
        const int needed = std::max(0, min_digits_for(length) - existing);
        for (std::size_t idx : reserve_indices(available, needed)) {
            password[idx] = digit_chars[random_index(digit_chars.size())];
        }
    }

    // Special characters: at least 4. Reserved from the same pool, so they
    // can never overwrite a digit placed above.
    if (options.include_special) {
        const int existing = static_cast<int>(std::count_if(password.begin(), password.end(), is_special));
        const int needed = std::max(0, min_special - existing);
        for (std::size_t idx : reserve_indices(available, needed)) {
            password[idx] = special_chars[random_index(special_chars.size())];
        }
    }

    // Uppercase: at least 10% of the length (minimum 1). Only lowercase
    // letters are converted, so digits/specials placed above are untouched.
    if (options.include_uppercase) {
        const int existing = static_cast<int>(std::count_if(password.begin(), password.end(), is_upper));
        const int needed = std::max(0, min_uppercase_for(length) - existing);
        std::vector<std::size_t> lower_positions;
        for (std::size_t i = 0; i < password.size(); ++i) {
            if (is_lower(password[i])) lower_positions.push_back(i);
        }
        for (std::size_t idx : reserve_indices(lower_positions, needed)) {
            password[idx] = to_upper(password[idx]);
        }
    }

    // Lowercase: at least one.
    if (options.include_lowercase && std::none_of(password.begin(), password.end(), is_lower)) {
        std::vector<std::size_t> upper_positions;
        for (std::size_t i = 0; i < password.size(); ++i) {
            if (is_upper(password[i])) upper_positions.push_back(i);
        }
        for (std::size_t idx : reserve_indices(upper_positions, 1)) {
            password[idx] = to_lower(password[idx]);
        }
    }

    // Shuffle randomly to avoid patterns (CSPRNG-driven Fisher-Yates)
    for (std::size_t i = password.size(); i > 1; --i) {
        const std::size_t j = random_index(i);
        std::swap(password[i - 1], password[j]);
    }

    // Defensive check: the steps above are designed to always satisfy the
    // policy, so a failure here indicates a programming error.
    if (!meets_policy(password, options)) {
        throw std::logic_error("Generated password does not satisfy the requested policy.");
    }

    return {password, used_words, resolved_log};
}

PasswordResult generate_password(int length) {
    GeneratorOptions options;
    options.length = length;
    return generate_password(options);
}

CharacterCounts count_characters(const std::string& password) {
    CharacterCounts counts;
    counts.length = static_cast<int>(password.size());
    for (char c : password) {
        if (is_upper(c)) ++counts.uppercase;
        else if (is_lower(c)) ++counts.lowercase;
        else if (is_digit(c)) ++counts.digits;
        else if (is_special(c)) ++counts.special;
    }
    return counts;
}

double estimate_entropy_bits(const std::string& password) {
    const CharacterCounts counts = count_characters(password);
    int charset = 0;
    if (counts.uppercase > 0) charset += 26;
    if (counts.lowercase > 0) charset += 26;
    if (counts.digits > 0) charset += 10;
    if (counts.special > 0) charset += static_cast<int>(special_chars.size());
    return charset > 0 ? counts.length * std::log2(static_cast<double>(charset)) : 0.0;
}

bool meets_policy(const std::string& password, const GeneratorOptions& options) {
    if (static_cast<int>(password.size()) != options.length) return false;

    for (char c : password) {
        if (!(is_alpha(c) || is_digit(c) || is_special(c))) return false; // also rejects spaces
    }

    const CharacterCounts counts = count_characters(password);
    const int length = options.length;

    if (options.include_digits ? counts.digits < min_digits_for(length) : counts.digits != 0) return false;
    if (options.include_special ? counts.special < min_special : counts.special != 0) return false;

    if (options.include_uppercase) {
        if (counts.uppercase < min_uppercase_for(length)) return false;
    } else if (counts.uppercase != 0) {
        return false;
    }

    if (options.include_lowercase) {
        if (counts.lowercase < 1) return false;
    } else if (options.include_uppercase && counts.lowercase != 0) {
        return false;
    }

    return true;
}

} // namespace dnapass
