/*
 * DNAPass Password Generator - Cryptographically secure random numbers
 * Copyright © 2025-2026 Gerivan Costa dos Santos
 * Author: gerivanc
 * GitHub: https://github.com/gerivanc/dnapass-password-generator
 * MIT License: https://github.com/gerivanc/dnapass-password-generator/blob/main/LICENSE.md
 * Version: 0.1.5
 */

#include "secure_random.hpp"

#include <stdexcept>

#if defined(_WIN32)
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #include <windows.h>
    #include <bcrypt.h>
    #if defined(_MSC_VER)
        #pragma comment(lib, "bcrypt.lib")
    #endif
#elif defined(__APPLE__)
    #include <sys/types.h>
    #include <sys/random.h>   // getentropy() on macOS 10.12+
    #define DNAPASS_HAVE_GETENTROPY 1
#elif defined(__linux__) || defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__NetBSD__)
    #include <unistd.h>       // getentropy() on glibc 2.25+, musl, BSDs
    #define DNAPASS_HAVE_GETENTROPY 1
#else
    #include <cstdio>         // /dev/urandom fallback for other POSIX systems
#endif

namespace dnapass {
namespace secure_random {

void fill_bytes(void* buffer, std::size_t size) {
    if (size == 0) return;
    unsigned char* out = static_cast<unsigned char*>(buffer);

#if defined(_WIN32)
    while (size > 0) {
        const ULONG chunk = size > 0xFFFFFFFFu ? 0xFFFFFFFFu : static_cast<ULONG>(size);
        const NTSTATUS status = BCryptGenRandom(nullptr, out, chunk, BCRYPT_USE_SYSTEM_PREFERRED_RNG);
        if (status < 0) {
            throw std::runtime_error("BCryptGenRandom failed: no secure random source available.");
        }
        out += chunk;
        size -= chunk;
    }
#elif defined(DNAPASS_HAVE_GETENTROPY)
    // getentropy() returns at most 256 bytes per call.
    while (size > 0) {
        const std::size_t chunk = size > 256 ? 256 : size;
        if (getentropy(out, chunk) != 0) {
            throw std::runtime_error("getentropy() failed: no secure random source available.");
        }
        out += chunk;
        size -= chunk;
    }
#else
    std::FILE* urandom = std::fopen("/dev/urandom", "rb");
    if (urandom == nullptr) {
        throw std::runtime_error("Cannot open /dev/urandom: no secure random source available.");
    }
    const std::size_t read = std::fread(out, 1, size, urandom);
    std::fclose(urandom);
    if (read != size) {
        throw std::runtime_error("Short read from /dev/urandom.");
    }
#endif
}

std::uint32_t next_uint32() {
    std::uint32_t value = 0;
    fill_bytes(&value, sizeof(value));
    return value;
}

std::uint32_t uniform_below(std::uint32_t bound) {
    if (bound == 0) {
        throw std::invalid_argument("uniform_below: bound must be greater than zero.");
    }
    // Accept only values below the largest multiple of `bound` that fits in
    // 2^32, so that every residue is equally likely (no modulo bias).
    const std::uint64_t space = 0x100000000ULL; // 2^32
    const std::uint64_t limit = space - (space % bound);
    std::uint32_t value;
    do {
        value = next_uint32();
    } while (static_cast<std::uint64_t>(value) >= limit);
    return value % bound;
}

int uniform_int(int min, int max) {
    if (max < min) {
        throw std::invalid_argument("uniform_int: max must be greater than or equal to min.");
    }
    const std::uint64_t range = static_cast<std::uint64_t>(static_cast<std::int64_t>(max) - min) + 1;
    if (range > 0xFFFFFFFFULL) {
        throw std::invalid_argument("uniform_int: range too large.");
    }
    return static_cast<int>(static_cast<std::int64_t>(min) +
                            uniform_below(static_cast<std::uint32_t>(range)));
}

double uniform_unit() {
    return static_cast<double>(next_uint32()) / 4294967296.0; // 2^32
}

} // namespace secure_random
} // namespace dnapass
