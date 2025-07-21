# 🧬 DNAPass Calculation Methodology
This document explains how the DNAPass Password Generator creates secure passwords inspired by DNA sequences, including the logic behind sequence selection, ambiguity resolution, and entropy considerations.

---

# 🎲 Sequence Selection DNAPass uses two sets of DNA-inspired sequences to generate passwords:

Primary Sequences: A list of 141 DNA sequences (e.g., "TTATAA", "CACCTGCNNNN") derived from biological motifs, including ambiguous characters (e.g., 'N', 'R'). These sequences are selected with a 90% probability.
Secondary Sequences: A smaller set of 8 sequences (e.g., "gattaca", "cgcg") restricted to the nucleotides A, T, C, and G, selected with a 10% probability.

The generator concatenates randomly chosen sequences from these sets until the password length (8–128 characters) is reached, then trims to the exact length.

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
To ensure password strength, DNAPass enforces the following rules:

Uppercase Letters: At least 10% of the password length (minimum 1) are uppercase, achieved by randomly converting alphabetic characters.
Lowercase Letters: At least one lowercase letter, ensured by converting a random alphabetic character if none exist.
Digits: At least 2 digits for passwords < 50 characters, or 3 for ≥ 50 characters, inserted randomly.
Special Characters: At least 4 special characters from a predefined set (e.g., "!@#$%^&*"), inserted randomly.
No Spaces: Any spaces are removed using regex.

Approximately 85% of alphabetic characters are converted to lowercase to balance readability and complexity. The final password is shuffled randomly to avoid predictable patterns.

---

# 📈 Entropy Considerations
The entropy of a DNAPass-generated password is influenced by:

Sequence Selection: With 141 primary and 8 secondary sequences, the choice of sequences provides a combinatorial base. The 90%/10% probability split adds randomness.
Ambiguity Resolution: Each ambiguous character (e.g., 'N') has multiple possible outcomes (e.g., 4 for 'N'), increasing entropy. For a sequence with k ambiguous characters, each with m possible nucleotides, the entropy contribution is approximately log₂(mᵏ) bits.
Character Modifications: Adding digits (10 choices), special characters (32 choices), and case variations (2 choices per letter) further increases entropy.
Random Shuffling: The final shuffle ensures no predictable structure, maximizing entropy for the given character set.

For a 12-character password, assuming a mix of 62 alphanumeric characters (26 lowercase, 26 uppercase, 10 digits) plus 32 special characters, the theoretical entropy is approximately log₂(94¹²) ≈ 78.7 bits. DNAPass exceeds this by enforcing diverse character types, typically achieving entropy above NIST's 80-bit recommendation for high-security passwords.

---

# 🧪 Example
For a 12-character password:

Select sequences (e.g., "TTATAA" + "gattaca") → "TTATAAGATTACA".
Trim to 12 characters: "TTATAAGATTAC".
Resolve ambiguities (if any): Already resolved in this case.
Convert ~85% to lowercase: "ttataagattac".
Ensure 2 digits: Replace random positions, e.g., "ttat5agat7ac".
Ensure 4 special characters: Replace random positions, e.g., "t#at5@gat7!c".
Ensure 10% uppercase (minimum 1): Convert one letter, e.g., "t#At5@gat7!c".
Ensure 1 lowercase: Already satisfied.
Shuffle: "5t@A#t7!cga".

The resulting password is strong, random, and meets all criteria, with entropy well above industry standards.

---

# 🛡️ Security Notes

The random module is used for simplicity in this initial version. For cryptographic purposes, future versions may switch to the secrets module.
Users are encouraged to use password managers and enable two-factor authentication (2FA) for enhanced security.

For more details, see the [README.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/README.md) and [CONTRIBUTING.md](https://github.com/gerivanc/dnapass-password-generator/blob/main/CONTRIBUTING.md) files.

#### Copyright © 2025 Gerivan Costa dos Santos
