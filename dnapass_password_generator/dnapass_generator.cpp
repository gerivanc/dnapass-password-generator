// DNAPass Password Generator
// Copyright © 2025 Gerivan Costa dos Santos
// Generate secure passwords inspired by DNA sequences
// Author: gerivanc
// GitHub: https://github.com/gerivanc/dnapass-password-generator
// MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md

#include <algorithm>
#include <cctype>
#include <iostream>
#include <map>
#include <random>
#include <regex>
#include <stdexcept>
#include <string>
#include <vector>

std::vector<std::string> primary_sequences = {"TTATAA", "gattaca", "ACTGCT", "CGATTA", "GCTAGC"};
std::vector<std::string> secondary_sequences = {"ATCG", "CGTA", "TAGC", "GCTA"};
std::map<char, std::string> ambiguous_chars = {
    {'B', "CGT"}, {'D', "AGT"}, {'H', "ACT"}, {'K', "GT"},  {'M', "AC"},
    {'N', "ACGT"},{'R', "AG"}, {'S', "CG"}, {'V', "ACG"}, {'W', "AT"}, {'Y', "CT"}
};
std::vector<char> special_chars = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+'};

std::random_device rd;
std::mt19937 gen(rd());

std::string resolve_ambiguity(const std::string &sequence) {
    std::string resolved;
    for (char c : sequence) {
        if (ambiguous_chars.find(c) != ambiguous_chars.end()) {
            std::string options = ambiguous_chars[c];
            std::uniform_int_distribution<> dis(0, options.size() - 1);
            resolved += options[dis(gen)];
        } else {
            resolved += c;
        }
    }
    return resolved;
}

std::string generate_password(int length) {
    if (length < 8 || length > 128) {
        throw std::invalid_argument("Password length must be between 8 and 128 characters.");
    }

    std::string password;
    std::vector<std::string> used_words;
    int remaining_length = length;

    while (remaining_length > 0) {
        std::uniform_int_distribution<> dis(0, 99);
        bool use_primary = dis(gen) < 90;
        const auto &sequences = use_primary ? primary_sequences : secondary_sequences;
        std::uniform_int_distribution<> seq_dis(0, sequences.size() - 1);
        std::string sequence = sequences[seq_dis(gen)];
        std::string resolved = resolve_ambiguity(sequence);

        if (resolved.length() <= remaining_length) {
            password += resolved;
            used_words.push_back(sequence + " -> " + resolved);
            remaining_length -= resolved.length();
        } else {
            break;
        }
    }

    if (!password.empty()) {
        int uppercase_count = std::count_if(password.begin(), password.end(), [](char c) { return std::isupper(c); });
        int lowercase_count = std::count_if(password.begin(), password.end(), [](char c) { return std::islower(c); });
        int digit_count = std::count_if(password.begin(), password.end(), [](char c) { return std::isdigit(c); });
        int special_count = std::count_if(password.begin(), password.end(),
                                         [](char c) { return std::string("!@#$%^&*()-+").find(c) != std::string::npos; });

        int needed_special = std::max(0, 4 - special_count);
        int needed_digits = std::max(0, (gen() % 2 == 0 ? 2 : 3) - digit_count);
        int needed_uppercase = std::max(0, static_cast<int>(length * 0.1) - uppercase_count);
        int needed_lowercase = std::max(0, 1 - lowercase_count);

        std::string additional_chars;
        for (int i = 0; i < needed_special; ++i) {
            std::uniform_int_distribution<> dis(0, special_chars.size() - 1);
            additional_chars += special_chars[dis(gen)];
        }
        for (int i = 0; i < needed_digits; ++i) {
            std::uniform_int_distribution<> dis(0, 9);
            additional_chars += std::to_string(dis(gen));
        }
        for (int i = 0; i < needed_uppercase; ++i) {
            std::uniform_int_distribution<> dis(0, 25);
            additional_chars += static_cast<char>('A' + dis(gen));
        }
        for (int i = 0; i < needed_lowercase; ++i) {
            std::uniform_int_distribution<> dis(0, 25);
            additional_chars += static_cast<char>('a' + dis(gen));
        }

        password += additional_chars;

        std::shuffle(password.begin(), password.end(), gen);
    }

    if (password.length() > length) {
        password = password.substr(0, length);
    } else if (password.length() < length) {
        std::string filler;
        for (int i = password.length(); i < length; ++i) {
            std::uniform_int_distribution<> dis(0, 3);
            switch (dis(gen)) {
                case 0: filler += static_cast<char>('a' + (gen() % 26)); break;
                case 1: filler += static_cast<char>('A' + (gen() % 26)); break;
                case 2: filler += std::to_string(gen() % 10); break;
                case 3: filler += special_chars[gen() % special_chars.size()]; break;
            }
        }
        password += filler;
        std::shuffle(password.begin(), password.end(), gen);
    }

    return password;
}

void analyze_password(const std::string &password) {
    int uppercase_count = std::count_if(password.begin(), password.end(), [](char c) { return std::isupper(c); });
    int lowercase_count = std::count_if(password.begin(), password.end(), [](char c) { return std::islower(c); });
    int digit_count = std::count_if(password.begin(), password.end(), [](char c) { return std::isdigit(c); });
    int special_count = std::count_if(password.begin(), password.end(),
                                     [](char c) { return std::string("!@#$%^&*()-+").find(c) != std::string::npos; });

    std::cout << "Password analysis:" << std::endl;
    std::cout << "  Length: " << password.length() << std::endl;
    std::cout << "  Uppercase: " << uppercase_count << std::endl;
    std::cout << "  Lowercase: " << lowercase_count << std::endl;
    std::cout << "  Digits: " << digit_count << std::endl;
    std::cout << "  Special characters: " << special_count << std::endl;
}

int main() {
    std::cout << "Copyright © 2025 Gerivan Costa dos Santos" << std::endl;
    std::cout << "DNAPass Password Generator - Generate secure passwords inspired by DNA sequences" << std::endl;
    std::cout << "Author: gerivanc" << std::endl;
    std::cout << "GitHub: https://github.com/gerivanc/dnapass-password-generator" << std::endl;
    std::cout << "MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md" << std::endl;
    std::cout << std::endl;

    int length;
    std::cout << "Enter the password length (8 to 128): ";
    std::cin >> length;

    try {
        std::string password = generate_password(length);
        std::cout << "\nGenerated password: " << password << std::endl;
        std::cout << "----------" << std::endl;

        std::cout << "\nUsed words: ";
        for (const auto &word : primary_sequences) {
            std::cout << word << ", ";
        }
        for (const auto &word : secondary_sequences) {
            std::cout << word << ", ";
        }
        std::cout << "\b\b " << std::endl;

        std::cout << "\nAmbiguity resolution log:" << std::endl;
        for (const auto &word : primary_sequences) {
            std::cout << "  " << word << " -> " << resolve_ambiguity(word) << std::endl;
        }
        for (const auto &word : secondary_sequences) {
            std::cout << "  " << word << " -> " << resolve_ambiguity(word) << std::endl;
        }

        std::cout << std::endl;
        analyze_password(password);
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
