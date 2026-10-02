/*
 * DNAPass Password Generator - Cryptographically secure random numbers
 * Copyright © 2025-2026 Gerivan Costa dos Santos
 * Author: gerivanc
 * GitHub: https://github.com/gerivanc/dnapass-password-generator
 * MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md
 * Version: 0.1.5
 *
 * Every random decision that feeds into a generated password goes through
 * this module. It reads directly from the operating system's CSPRNG:
 *   - Windows:            BCryptGenRandom (system-preferred RNG)
 *   - Linux/macOS/BSD:    getentropy()
 *   - Other POSIX:        /dev/urandom
 * It never falls back to a non-cryptographic generator (such as
 * std::mt19937): if the OS source fails, an exception is thrown instead
 * (fail closed). This mirrors crypto.getRandomValues() in docs/dnapass.html.
 */

#ifndef DNAPASS_SECURE_RANDOM_HPP
#define DNAPASS_SECURE_RANDOM_HPP

#include <cstddef>
#include <cstdint>

namespace dnapass {
namespace secure_random {

// Fills `buffer` with `size` bytes from the operating system CSPRNG.
// Throws std::runtime_error if the OS source is unavailable.
void fill_bytes(void* buffer, std::size_t size);

// Uniform 32-bit unsigned integer.
std::uint32_t next_uint32();

// Uniform integer in [0, bound) using rejection sampling (no modulo bias).
// `bound` must be greater than zero.
std::uint32_t uniform_below(std::uint32_t bound);

// Uniform integer in [min, max] (inclusive), no modulo bias.
int uniform_int(int min, int max);

// Uniform double in [0, 1), built from 32 random bits (same resolution as
// secureRandomFloat() in the web version).
double uniform_unit();

} // namespace secure_random
} // namespace dnapass

#endif // DNAPASS_SECURE_RANDOM_HPP
