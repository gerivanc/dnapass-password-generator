/*
 * DNAPass Password Generator - Command-line interface
 * Copyright © 2025-2026 Gerivan Costa dos Santos
 * Author: gerivanc
 * GitHub: https://github.com/gerivanc/dnapass-password-generator
 * MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md
 * Version: 0.1.5
 *
 * Usage:
 *   dnapass_generator                      Interactive: asks for the length
 *   echo "45" | dnapass_generator          Automated: length read from stdin
 *   dnapass_generator -l 45 [options]      Length given as an argument
 *
 * The options mirror the toggles of the web version (docs/dnapass.html).
 * Run "dnapass_generator --help" for the full list.
 */

#include "dnapass_generator.hpp"

#include <exception>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

struct CliOptions {
    dnapass::GeneratorOptions generator;
    bool length_given = false;
    bool quiet = false;
    bool show_help = false;
    bool show_version = false;
};

void print_help(std::ostream& out) {
    out << "DNAPass Password Generator v" << dnapass::version << "\n"
        << "Generate secure passwords inspired by DNA sequences.\n\n"
        << "Usage:\n"
        << "  dnapass_generator [options] [LENGTH]\n"
        << "  echo \"45\" | dnapass_generator [options]\n\n"
        << "Options:\n"
        << "  -l, --length N     Password length (8 to 128). If omitted, it is read\n"
        << "                     from standard input (interactive prompt or pipe).\n"
        << "      --no-uppercase Exclude uppercase letters (INCLUDE UPPERCASE: NO)\n"
        << "      --no-lowercase Exclude lowercase letters (INCLUDE LOWERCASE: NO)\n"
        << "      --no-digits    Exclude digits            (INCLUDE DIGITS: NO)\n"
        << "      --no-special   Exclude special characters (INCLUDE SPECIAL CHARACTERS: NO)\n"
        << "  -q, --quiet        Print only the generated password\n"
        << "  -h, --help         Show this help and exit\n"
        << "  -v, --version      Show the version and exit\n\n"
        << "Rules (same as the web version):\n"
        << "  - Uppercase: at least 10% of the length (minimum 1), when enabled\n"
        << "  - Lowercase: at least 1, when enabled\n"
        << "  - Digits: at least 2 below 50 characters, 3 at 50 or more, when enabled\n"
        << "  - Special characters: at least 4, when enabled\n"
        << "  - Disabling uppercase and lowercase together falls back to lowercase letters\n"
        << "  - All randomness comes from the operating system CSPRNG\n";
}

// Strict integer parsing: the whole string must be a number.
int parse_length(const std::string& text) {
    std::size_t consumed = 0;
    int value = 0;
    try {
        value = std::stoi(text, &consumed);
    } catch (const std::exception&) {
        throw std::invalid_argument("Invalid length \"" + text + "\". Please enter a number between 8 and 128.");
    }
    if (consumed != text.size()) {
        throw std::invalid_argument("Invalid length \"" + text + "\". Please enter a number between 8 and 128.");
    }
    return value;
}

CliOptions parse_arguments(int argc, char* argv[]) {
    CliOptions cli;
    for (int i = 1; i < argc; ++i) {
        const std::string arg = argv[i];
        if (arg == "-h" || arg == "--help") {
            cli.show_help = true;
        } else if (arg == "-v" || arg == "--version") {
            cli.show_version = true;
        } else if (arg == "-q" || arg == "--quiet") {
            cli.quiet = true;
        } else if (arg == "--no-uppercase") {
            cli.generator.include_uppercase = false;
        } else if (arg == "--no-lowercase") {
            cli.generator.include_lowercase = false;
        } else if (arg == "--no-digits") {
            cli.generator.include_digits = false;
        } else if (arg == "--no-special") {
            cli.generator.include_special = false;
        } else if (arg == "-l" || arg == "--length") {
            if (i + 1 >= argc) {
                throw std::invalid_argument("Option " + arg + " requires a value (8 to 128).");
            }
            cli.generator.length = parse_length(argv[++i]);
            cli.length_given = true;
        } else if (arg.rfind("--length=", 0) == 0) {
            cli.generator.length = parse_length(arg.substr(9));
            cli.length_given = true;
        } else if (!arg.empty() && arg[0] != '-') {
            cli.generator.length = parse_length(arg); // positional LENGTH
            cli.length_given = true;
        } else {
            throw std::invalid_argument("Unknown option \"" + arg + "\". Use --help to see the available options.");
        }
    }
    return cli;
}

const char* yes_no(bool value) { return value ? "YES" : "NO"; }

} // namespace

int main(int argc, char* argv[]) {
    try {
        CliOptions cli = parse_arguments(argc, argv);

        if (cli.show_help) {
            print_help(std::cout);
            return 0;
        }
        if (cli.show_version) {
            std::cout << "DNAPass Password Generator v" << dnapass::version << "\n";
            return 0;
        }

        // Prompt for password length when it was not given as an argument.
        // This keeps both documented methods working:
        //   ./dnapass_generator            (interactive)
        //   echo "45" | ./dnapass_generator (automated)
        if (!cli.length_given) {
            if (!cli.quiet) {
                std::cout << "Enter the password length (8 to 128): ";
            }
            std::string input;
            if (!(std::cin >> input)) {
                throw std::invalid_argument("Invalid input. Please enter a number.");
            }
            cli.generator.length = parse_length(input);
        }

        // Generate the password
        const dnapass::PasswordResult result = dnapass::generate_password(cli.generator);

        if (cli.quiet) {
            std::cout << result.password << "\n";
            return 0;
        }

        const dnapass::CharacterCounts counts = dnapass::count_characters(result.password);

        // Display results with visual separation
        std::cout << "\n";
        std::cout << "Copyright © 2025-2026 Gerivan Costa dos Santos\n";
        std::cout << "DNAPass Password Generator v" << dnapass::version
                  << " - Generate secure passwords inspired by DNA sequences\n";
        std::cout << "Author: gerivanc\n";
        std::cout << "GitHub: https://github.com/gerivanc/dnapass-password-generator\n";
        std::cout << "MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md\n";
        std::cout << "\n";
        std::cout << "Generated password: " << result.password << "\n";
        std::cout << "----------\n";
        std::cout << "\n";
        std::cout << "Settings:\n";
        std::cout << "  Include uppercase: " << yes_no(cli.generator.include_uppercase) << "\n";
        std::cout << "  Include lowercase: " << yes_no(cli.generator.include_lowercase) << "\n";
        std::cout << "  Include digits: " << yes_no(cli.generator.include_digits) << "\n";
        std::cout << "  Include special characters: " << yes_no(cli.generator.include_special) << "\n";
        std::cout << "\n";
        std::cout << "Used words: ";
        for (std::size_t i = 0; i < result.used_words.size(); ++i) {
            std::cout << (i > 0 ? ", " : "") << result.used_words[i];
        }
        std::cout << "\nAmbiguity resolution log:\n";
        for (const auto& log_entry : result.resolved_log) {
            std::cout << "  " << log_entry << "\n";
        }
        std::cout << "\nPassword analysis:\n";
        std::cout << "  Length: " << counts.length << "\n";
        std::cout << "  Uppercase: " << counts.uppercase << "\n";
        std::cout << "  Lowercase: " << counts.lowercase << "\n";
        std::cout << "  Digits: " << counts.digits << "\n";
        std::cout << "  Special characters: " << counts.special << "\n";
        std::cout << "  Entropy (estimated): " << std::fixed << std::setprecision(2)
                  << dnapass::estimate_entropy_bits(result.password) << " bits\n";
        std::cout << "\nNote: the entropy shown is a charset-based upper bound. DNAPass builds\n"
                  << "passwords from a fixed, public set of sequences, so the real guessing\n"
                  << "entropy is lower. Use 16+ characters for high-security accounts.\n";
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "An unexpected error occurred: " << e.what() << "\n";
        return 2;
    } catch (...) {
        std::cerr << "An unknown error occurred.\n";
        return 2;
    }
    return 0;
}
