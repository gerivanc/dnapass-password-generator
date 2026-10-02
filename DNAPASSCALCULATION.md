# 🧬 DNAPass Calculation Methodology
This document explains how the DNAPass Password Generator creates secure passwords inspired by DNA sequences, including the logic behind sequence selection, ambiguity resolution, and entropy considerations.

---

# 🎲 Sequence Selection DNAPass uses two sets of DNA-inspired sequences to generate passwords:

Primary Sequences: A list of 253 DNA sequences, 244 of them unique (e.g., "GGGACN", "NCTCCAC", "CGCG", "GGRYG") derived from biological motifs, including ambiguous characters (e.g., 'N', 'R'). These sequences are selected with a 90% probability.
Secondary Sequences: A smaller set of 8 sequences (e.g., "gattaca", "cgcg") restricted to the nucleotides A, T, C, and G, selected with a 10% probability.

The generator concatenates randomly chosen sequences from these sets until the password length (8–128 characters) is reached, then trims to the exact length.

Every random choice in DNAPass (sequence selection, ambiguity resolution, case changes, character insertion and the final shuffle) uses a cryptographically secure random number generator: the operating system CSPRNG in the C++ CLI (`BCryptGenRandom` on Windows, `getentropy()` on Linux/macOS/BSD) and `crypto.getRandomValues()` in the web version. Random integers are drawn with rejection sampling, so there is no modulo bias.

---

# 🤹 Ambiguity Resolution
Primary sequences often contain ambiguous characters defined by the IUPAC nucleotide code (e.g., 'N' for any nucleotide, 'R' for A or G). These are resolved randomly using a predefined mapping:

'N': Random choice from ['A', 'T', 'C', 'G']
'R': Random choice from ['A', 'G']
'Y': Random choice from ['C', 'T']
And so on, as defined in the ambiguous_chars dictionary.

For example, "CACCTGCNNNN" might resolve to "CACCTGCTAGC". The resolution process logs both the original and resolved sequences for transparency.

---

# 🔣 Character Diversity
Each character type can be enabled or disabled (web toggles "INCLUDE UPPERCASE / LOWERCASE / DIGITS / SPECIAL CHARACTERS", CLI options `--no-uppercase`, `--no-lowercase`, `--no-digits`, `--no-special`). For every enabled type, DNAPass enforces the following rules:

Uppercase Letters: At least 10% of the password length (minimum 1) are uppercase, achieved by converting randomly chosen lowercase letters.
Lowercase Letters: At least one lowercase letter, ensured by converting a random uppercase letter if none exist.
Digits: At least 2 digits for passwords < 50 characters, or 3 for ≥ 50 characters.
Special Characters: At least 4 special characters from a predefined set of 28 symbols (`!@#$%^&*()_+-=[]{}|;:,.<>?~\`).
No Spaces: Any whitespace is removed.

Approximately 85% of alphabetic characters are first converted to lowercase to balance readability and complexity. If uppercase is disabled, the whole password is converted to lowercase (and vice versa), so a disabled case never appears in the output; if both are disabled, letters fall back to lowercase.

Digits and special characters are placed by reserving unique positions from one shared pool (sampling without replacement), so they can never overwrite each other and every minimum is guaranteed by construction. The final password is shuffled with a Fisher-Yates shuffle driven by the secure random source.

---

# 📈 Entropy Considerations
The entropy of a DNAPass-generated password is influenced by:

Sequence Selection: With 253 primary (244 unique) and 8 secondary sequences, the choice of sequences provides a combinatorial base. The 90%/10% probability split adds randomness.
Ambiguity Resolution: Each ambiguous character (e.g., 'N') has multiple possible outcomes (e.g., 4 for 'N'), increasing entropy. For a sequence with k ambiguous characters, each with m possible nucleotides, the entropy contribution is approximately log₂(mᵏ) bits.
Character Modifications: Adding digits (10 choices), special characters (28 choices), and case variations (2 choices per letter) further increases entropy.
Random Shuffling: The final shuffle ensures no predictable structure, maximizing entropy for the given character set.

The "Entropy (estimated)" value shown by both the CLI and the web version is a charset-based Shannon estimate: length × log₂(charset size), where the charset is the sum of the character classes present (26 uppercase + 26 lowercase + 10 digits + 28 special = 90). For a 12-character password this gives 12 × log₂(90) ≈ 77.9 bits; for 16 characters ≈ 103.9 bits; for 20 characters ≈ 129.8 bits.

This value is an **upper bound**, not the true guessing entropy: DNAPass builds passwords from a fixed, published set of sequences, letters come only from A/T/C/G before the case changes, and the minimum-count rules shape the composition, so an attacker who knows the algorithm faces fewer possibilities than a uniformly random password of the same length. For high-security accounts, use 16 characters or more (20+ recommended).

---

# 🧪 Example
For a 12-character password with all character types enabled:

Select a sequence: "GCAANNGTCTCN".
Resolve ambiguities: "GCAANNGTCTCN" → "GCAATTGTCTCA".
Trim to 12 characters: "GCAATTGTCTCA" (already 12).
Convert ~85% to lowercase: "gcaatTgtctca".
Ensure 2 digits: reserve 2 unique positions, e.g., "gc5atTgtc8ca".
Ensure 4 special characters: reserve 4 other unique positions, e.g., "g#5a@Tg!c8c%".
Ensure 10% uppercase (minimum 1): already satisfied by "T".
Ensure 1 lowercase: already satisfied.
Shuffle (Fisher-Yates): e.g., "c8%g!aT#g5@c".

The resulting password is strong, random, and meets all criteria, with entropy well above industry standards.

---

# 🛡️ Security Notes

All randomness comes from a cryptographically secure source: the operating system CSPRNG in the C++ CLI (since v0.1.5) and the Web Crypto API in the web version (since v0.1.4). No non-cryptographic generator (`std::mt19937`, `Math.random()`) is used for password generation; `Math.random()` remains only in the purely decorative DNA animation of the web page.
Users are encouraged to use password managers and enable two-factor authentication (2FA) for enhanced security.

For more details, see the [README.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/README.md) and [CONTRIBUTING.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/CONTRIBUTING.md) files.

#### Copyright © 2025-2026 Gerivan Costa dos Santos
