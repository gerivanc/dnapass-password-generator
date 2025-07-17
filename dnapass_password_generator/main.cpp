#include "dnapass_generator.hpp"
#include <iostream>
#include <random>
#include <algorithm>

int main() {
    try {
        std::random_device rd;
        std::mt19937 rng(rd());

        // Prompt for password length
        int length;
        std::cout << "Enter the password length (8 to 128): ";
        std::cin >> length;
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input. Please enter a number.");
        }

        // Generate the password
        dnapass::PasswordResult result = dnapass::generate_password(length, rng);

        // Display results with visual separation
        std::cout << "\n";
        std::cout << "Copyright © 2025 Gerivan Costa dos Santos\n";
        std::cout << "DNAPass Password Generator - Generate secure passwords inspired by DNA sequences\n";
        std::cout << "Author: gerivanc\n";
        std::cout << "GitHub: https://github.com/gerivanc/dnapass-password-generator\n";
        std::cout << "MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md\n";
        std::cout << "\n";
        std::cout << "Generated password: " << result.password << "\n";
        std::cout << "----------\n";
        std::cout << "\n";
        std::cout << "Used words: ";
        for (size_t i = 0; i < result.used_words.size(); ++i) {
            std::cout << (i > 0 ? ", " : "") << result.used_words[i];
        }
        std::cout << "\nAmbiguity resolution log:\n";
        for (const auto& log_entry : result.resolved_log) {
            std::cout << "  " << log_entry << "\n";
        }
        std::cout << "\nPassword analysis:\n";
        std::cout << "  Length: " << result.password.length() << "\n";
        std::cout << "  Uppercase: " << std::count_if(result.password.begin(), result.password.end(),
                                               [](char c) { return std::isupper(c); }) << "\n";
        std::cout << "  Lowercase: " << std::count_if(result.password.begin(), result.password.end(),
                                               [](char c) { return std::islower(c); }) << "\n";
        std::cout << "  Digits: " << std::count_if(result.password.begin(), result.password.end(),
                                        [](char c) { return std::isdigit(c); }) << "\n";
        std::cout << "  Special characters: " << std::count_if(result.password.begin(), result.password.end(),
                                         [](char c) { return dnapass::special_chars.find(c) != std::string::npos; }) << "\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        std::cout << "An unexpected error occurred: " << e.what() << "\n";
    } catch (...) {
        std::cout << "An unknown error occurred.\n";
    }
    return 0;
}
