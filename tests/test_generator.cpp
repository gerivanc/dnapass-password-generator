/*
 * DNAPass Password Generator - Automated tests
 * Copyright © 2025-2026 Gerivan Costa dos Santos
 * GitHub: https://github.com/gerivanc/dnapass-password-generator
 * MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md
 * Version: 0.1.5
 *
 * Generates passwords for every combination of the four character toggles
 * and every length from 8 to 128, and checks each one against the policy.
 * Also checks the CSPRNG helpers for range correctness and gross bias.
 * No external test framework is required; run with "ctest" or directly.
 */

#include "dnapass_generator.hpp"
#include "secure_random.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {

int failures = 0;

void check(bool condition, const std::string& message) {
    if (!condition) {
        ++failures;
        if (failures <= 20) std::cerr << "FAIL: " << message << "\n";
    }
}

std::string describe(const dnapass::GeneratorOptions& o) {
    return "length=" + std::to_string(o.length) +
           " upper=" + (o.include_uppercase ? "yes" : "no") +
           " lower=" + (o.include_lowercase ? "yes" : "no") +
           " digits=" + (o.include_digits ? "yes" : "no") +
           " special=" + (o.include_special ? "yes" : "no");
}

void test_all_combinations(int repetitions) {
    long generated = 0;
    for (int mask = 0; mask < 16; ++mask) {
        for (int length = dnapass::min_length; length <= dnapass::max_length; ++length) {
            dnapass::GeneratorOptions options;
            options.length = length;
            options.include_uppercase = (mask & 1) != 0;
            options.include_lowercase = (mask & 2) != 0;
            options.include_digits = (mask & 4) != 0;
            options.include_special = (mask & 8) != 0;
            for (int r = 0; r < repetitions; ++r) {
                const auto result = dnapass::generate_password(options);
                ++generated;
                check(dnapass::meets_policy(result.password, options),
                      "policy violated: " + describe(options) + " -> " + result.password);
                check(result.password.find(' ') == std::string::npos, "space found");
                if (!options.include_uppercase && !options.include_lowercase) {
                    const auto c = dnapass::count_characters(result.password);
                    check(c.uppercase == 0, "both cases off must fall back to lowercase");
                }
            }
        }
    }
    std::cout << "Generated and validated " << generated << " passwords.\n";
}

void test_invalid_lengths() {
    for (int bad : {-1, 0, 7, 129, 1000}) {
        bool threw = false;
        try {
            dnapass::generate_password(bad);
        } catch (const std::invalid_argument&) {
            threw = true;
        }
        check(threw, "length " + std::to_string(bad) + " must be rejected");
    }
}

void test_minimum_rules() {
    check(dnapass::min_digits_for(8) == 2, "min digits at 8");
    check(dnapass::min_digits_for(49) == 2, "min digits at 49");
    check(dnapass::min_digits_for(50) == 3, "min digits at 50");
    check(dnapass::min_uppercase_for(8) == 1, "min uppercase at 8");
    check(dnapass::min_uppercase_for(128) == 12, "min uppercase at 128");
}

void test_random_helpers() {
    // Range and rough uniformity of uniform_int over a small range.
    const int buckets = 7;
    const int draws = 70000;
    std::vector<int> counts(buckets, 0);
    for (int i = 0; i < draws; ++i) {
        const int v = dnapass::secure_random::uniform_int(0, buckets - 1);
        check(v >= 0 && v < buckets, "uniform_int out of range");
        if (v >= 0 && v < buckets) ++counts[static_cast<std::size_t>(v)];
    }
    // Chi-square with 6 degrees of freedom; 22.46 is the p = 0.001 critical value.
    const double expected = static_cast<double>(draws) / buckets;
    double chi2 = 0.0;
    for (int c : counts) chi2 += (c - expected) * (c - expected) / expected;
    check(chi2 < 22.46, "uniform_int distribution looks biased (chi2=" + std::to_string(chi2) + ")");

    for (int i = 0; i < 10000; ++i) {
        const double u = dnapass::secure_random::uniform_unit();
        check(u >= 0.0 && u < 1.0, "uniform_unit out of [0, 1)");
    }
    check(dnapass::secure_random::uniform_int(5, 5) == 5, "degenerate range");
}

void test_entropy_estimate() {
    // 12 characters from the full set: 12 * log2(26 + 26 + 10 + 28)
    const double bits = dnapass::estimate_entropy_bits("aA1!aA1!aA1!");
    const double expected = 12 * std::log2(26.0 + 26.0 + 10.0 + static_cast<double>(dnapass::special_chars.size()));
    check(std::fabs(bits - expected) < 1e-9, "entropy estimate formula");
}

} // namespace

int main() {
    try {
        test_minimum_rules();
        test_invalid_lengths();
        test_random_helpers();
        test_entropy_estimate();
        test_all_combinations(10);
    } catch (const std::exception& e) {
        std::cerr << "Unexpected exception: " << e.what() << "\n";
        return 1;
    }
    if (failures > 0) {
        std::cerr << failures << " check(s) failed.\n";
        return 1;
    }
    std::cout << "All tests passed.\n";
    return 0;
}
