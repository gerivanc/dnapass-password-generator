# Getting Started with DNAPass Password Generator on Windows

Welcome to the **DNAPass Password Generator**, a secure and customizable tool for generating robust passwords inspired by DNA sequences! This guide provides step-by-step instructions for installing and using the **DNAPass Password Generator** on Windows using a command-line interface (CLI). Whether you're securing personal accounts or generating cryptographic keys, this guide will help you get started quickly and efficiently.

---

## 📋 Prerequisites

Before diving in, ensure your Windows environment is ready:

- **Operating System**: Windows 10 or later.
- **C++ Compiler**: A C++17-compliant compiler, such as MinGW (with `g++`) or Microsoft Visual Studio (with `cl`). Download options:
  - **MinGW**: Available from [MinGW-w64](https://www.mingw-w64.org/) or via a package manager like `choco` (`choco install mingw`).
  - **MSVC**: Included in Visual Studio with the C++ development workload, downloadable from [visualstudio.microsoft.com](https://visualstudio.microsoft.com).
- **Git**: Required for cloning the repository. Download from [git-scm.com](https://git-scm.com/download/win).
- **Internet Connection**: Required for cloning the repository from GitHub.

---

## 🛠️ Installation

The **DNAPass Password Generator** is built in C++ and requires compilation from source code. Below are the steps to install and compile the project on Windows.

1. **Install Git**:
   - **Download Git**: Visit [git-scm.com](https://git-scm.com/download/win) and download the latest version of Git for Windows.
   - **Run the Installer**:
     - Follow the installation wizard, accepting the default settings unless you have specific preferences.
     - Ensure the option “Add Git to PATH” is selected (usually enabled by default) to make Git accessible in Command Prompt or PowerShell.
   - **Verify Git Installation**:
     Open Command Prompt (`cmd`) or PowerShell and run:
     ```powershell
     git --version
     ```
     If installed correctly, you’ll see output like `git version 2.x.x`. If you get an error (e.g., `'git' is not recognized`), ensure Git was added to your system PATH. You can fix this by reinstalling Git and selecting the “Add Git to PATH” option, or manually adding the Git executable path (e.g., `C:\Program Files\Git\bin`) to your system’s environment variables:
     - Press `Win + R`, type `sysdm.cpl`, and go to **Advanced > Environment Variables**.
     - Under **System Variables**, find `Path`, edit it, and add the Git bin directory (e.g., `C:\Program Files\Git\bin`).

2. **Install a C++ Compiler**:
   - **Option 1: MinGW**:
     - Download and install MinGW-w64 from [MinGW-w64](https://www.mingw-w64.org/) or via a package manager like Chocolatey:
       ```powershell
       choco install mingw
       ```
     - Verify installation:
       ```powershell
       g++ --version
       ```
       Ensure the output shows a version supporting C++17 (e.g., GCC 7.0+).
   - **Option 2: MSVC (Visual Studio)**:
     - Download and install Visual Studio from [visualstudio.microsoft.com](https://visualstudio.microsoft.com).
     - During installation, select the “Desktop development with C++” workload.
     - Verify installation by opening the **Developer Command Prompt for Visual Studio** and running:
       ```powershell
       cl
       ```

3. **Clone the Repository**:
   In Command Prompt or PowerShell, navigate to a directory where you want to store the project (e.g., `C:\Projects`):
   ```powershell
   git clone https://github.com/gerivanc/dnapass.git
   cd dnapass
   ```

4. **Compile the Program**:
   - **With MinGW**:
     ```powershell
     g++ -std=c++17 dnapass_generator.cpp -o dnapass_generator
     ```
   - **With MSVC**:
     Open the **Developer Command Prompt for Visual Studio** and run:
     ```powershell
     cl /std:c++17 dnapass_generator.cpp /o dnapass_generator
     ```
   This generates an executable named `dnapass_generator.exe`.

5. **Verify Compilation**:
   Run the executable to ensure it works:
   ```powershell
   .\dnapass_generator
   ```
   You should see a prompt asking for the password length.

---

## 🔑 Generating Passwords

Once compiled, you can generate passwords using the CLI. The program prompts for a password length (8–128 characters) and generates a secure password with DNA-inspired sequences, ensuring at least 4 special characters, 2–3 digits, 10% uppercase, and 1 lowercase.

### Example Usage

- **Generate a 12-Character Password**:
  ```powershell
  .\dnapass_generator
  ```
  **Prompt**:
  ```
  Enter the password length (8 to 128): 12
  ```
  **Example Output**:
  ```
  Copyright © 2025 Gerivan Costa dos Santos
  DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
  Author: gerivanc
  GitHub: https://github.com/gerivanc
  MIT License: https://github.com/gerivanc/dnapass/blob/main/LICENSE.md

  Generated password: 5t@A#t7!cga
  ----------

  Used words: TTATAA, gattaca
  Ambiguity resolution log:
    TTATAA -> TTATAA
    gattaca -> gattaca

  Password analysis:
    Length: 12
    Uppercase: 1
    Lowercase: 5
    Digits: 2
    Special characters: 4
  ```

- **Generate a 128-Character Password**:
  ```powershell
  .\dnapass_generator
  ```
  **Prompt**:
  ```
  Enter the password length (8 to 128): 128
  ```
  **Example Output**:
  ```
  Copyright © 2025 Gerivan Costa dos Santos
  DNAPass Password Generator - Generate secure passwords inspired by DNA sequences
  Author: gerivanc
  GitHub: https://github.com/gerivanc
  MIT License: https://github.com/gerivanc/dnapass/blob/main/LICENSE.md

  Generated password: k9#JTR^S<pY<D7jvB268<!4~NPrSe~$NqWZL~lO-7p\g;=Dq91|SP3!@Onj$E3d]!MZ,7Tz)^CwjKwYd1#^1W)_odEjmKFrY=K+9c5$Q0UaKH5MH;I4fFj:YJMlXkQkhkiL]T+M.1*[O&s~Lfw\^UPBVf=(t
  ----------

  Used words: [list of sequences]
  Ambiguity resolution log: [log entries]

  Password analysis:
    Length: 128
    Uppercase: 13
    Lowercase: 80
    Digits: 10
    Special characters: 25
  ```

---

## 🖥️ Windows Tips for Smooth Usage

- **Check Compiler Version**:
  - For MinGW:
    ```powershell
    g++ --version
    ```
  - For MSVC, in the Developer Command Prompt:
    ```powershell
    cl
    ```
  Ensure the compiler supports C++17.

- **Add Compiler to PATH**:
  If `g++` or `cl` is not recognized, ensure the compiler is added to your system PATH:
  - Press `Win + R`, type `sysdm.cpl`, go to **Advanced > Environment Variables**.
  - Add the compiler’s bin directory (e.g., `C:\MinGW\bin` for MinGW or the MSVC `bin` directory).

- **Run Commands from Repository**:
  After compilation, always run the executable from the project directory:
  ```powershell
  .\dnapass_generator
  ```

---

## ⚠️ Troubleshooting

- **Command Not Found**:
  - Ensure you’re in the correct directory (`dnapass`) and the executable (`dnapass_generator.exe`) was generated.
  - Verify the compiler is correctly installed and added to PATH.

- **Compilation Fails**:
  - Ensure you’re using a C++17-compliant compiler (e.g., `g++` 7.0+ or MSVC 2017+).
  - Check for syntax errors in `dnapass_generator.cpp`. If errors persist, open an issue on GitHub.

- **Git Not Recognized**:
  - If `git --version` fails, ensure Git is installed and added to PATH. Reinstall Git, selecting “Add Git to PATH,” or manually add the Git bin directory (e.g., `C:\Program Files\Git\bin`).

- **Low Entropy Warning**:
  - If the generated password’s entropy is low, increase the length (e.g., enter `24` or higher at the prompt) to meet NIST standards (80+ bits).

For additional help, visit the [Issues tab](https://github.com/gerivanc/dnapass/issues) on GitHub.

---

## 🔒 Security Best Practices

- **Use a Password Manager**: Store generated passwords in a secure password manager like [Bitwarden](https://bitwarden.com/).
- **Enable 2FA**: Add two-factor authentication for critical accounts.
- **Avoid Reusing Passwords**: Generate unique passwords for each service.
- **Regular Updates**: Update your master passwords periodically using high-length passwords (e.g., 128 characters).

---

## 🌟 Next Steps

Explore the project details in the [README.md](https://github.com/gerivanc/dnapass/blob/main/README.md). For detailed entropy calculations, check [DNAPASSCALCULATION.md](https://github.com/gerivanc/dnapass/blob/main/DNAPASSCALCULATION.md).

Want to contribute? See our [Contributing Guidelines](https://github.com/gerivanc/dnapass/blob/main/CONTRIBUTING.md) to join the project!

---

## 📬 Contact

For questions or feedback, reach out at: [dean-grumbly-plop@duck.com](mailto:dean-grumbly-plop@duck.com).

---

#### Copyright © 2025 Gerivan Costa dos Santos
