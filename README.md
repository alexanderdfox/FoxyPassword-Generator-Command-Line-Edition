# FoxyPassword Generator - Command Line Edition

A secure, cross-platform password generator for command line use with enhanced security features and improved usability.

## 🚀 Features

- **Cryptographically Secure**: Uses hardware random number generation for maximum security
- **Cross-Platform**: Works on Windows, macOS, and Linux
- **Configurable Character Sets**: Choose from uppercase, lowercase, numbers, and special characters
- **Password Strength Validation**: Built-in strength checking
- **Modern C++**: Written in C++17 with best practices
- **Security Hardened**: Compiled with security flags and bounds checking

## 🔒 Security Improvements

- **Hardware Random Generation**: Uses `/dev/urandom` (Linux/macOS) or `CryptGenRandom` (Windows)
- **Thread-Safe**: Thread-local random number generators
- **Input Validation**: Comprehensive parameter checking
- **Memory Safety**: Proper bounds checking and memory management
- **Secure Compilation**: Built with security hardening flags

## 📦 Installation

### Prerequisites
- C++17 compatible compiler (GCC 7+, Clang 5+, or MSVC 2017+)
- Make (optional, for build automation)

### Building from Source

```bash
# Clone the repository
git clone https://github.com/yourusername/FoxyPassword-Generator-Command-Line-Edition.git
cd FoxyPassword-Generator-Command-Line-Edition/FoxyPassword

# Build the project
make

# Or build with optimizations
make release

# Run tests
make test
```

### Installation (Optional)

```bash
# Install system-wide (requires sudo on Linux/macOS)
sudo make install

# Uninstall
sudo make uninstall
```

## 🎯 Usage

### Basic Usage

```bash
# Generate a 12-character password with all character types
./passgen 12

# Generate a 16-character password with letters and numbers only
./passgen 16 -u -l -n

# Generate a 20-character password with letters and special characters
./passgen 20 -u -l -s
```

### Command Line Options

| Option | Description |
|--------|-------------|
| `-u` | Include uppercase letters (A-Z) |
| `-l` | Include lowercase letters (a-z) |
| `-n` | Include numbers (0-9) |
| `-s` | Include special characters (!@#$%^&*()_+-=[]{}|;:,.<>?) |
| `--help` or `-h` | Show help message |

### Examples

```bash
# Generate a strong password for a website
./passgen 16

# Generate a PIN-like password (numbers only)
./passgen 6 -n

# Generate a memorable password (letters only)
./passgen 12 -u -l

# Generate a complex password for system administration
./passgen 24
```

## 🔧 Build Options

```bash
# Standard build
make

# Debug build (with symbols and debug info)
make debug

# Release build (optimized for performance)
make release

# Clean build artifacts
make clean

# Run automated tests
make test
```

## 🛡️ Security Features

### Random Number Generation
- Uses `std::random_device` for hardware entropy
- Thread-local Mersenne Twister for performance
- Proper seeding from hardware random sources

### Password Strength
- Minimum length enforcement (8 characters)
- Maximum length limit (128 characters)
- Ensures at least one character from each selected type
- Built-in strength validation

### Input Validation
- Comprehensive parameter checking
- Bounds checking on all inputs
- Proper error handling and reporting

## 📋 Requirements

### Password Length
- **Minimum**: 8 characters (security best practice)
- **Maximum**: 128 characters (performance consideration)
- **Recommended**: 12-24 characters for most use cases

### Character Sets
- **Uppercase**: A-Z (26 characters)
- **Lowercase**: a-z (26 characters)
- **Numbers**: 0-9 (10 characters)
- **Special**: !@#$%^&*()_+-=[]{}|;:,.<>? (20 characters)

## 🔍 Password Strength Criteria

A password is considered "strong" if it meets these criteria:
- Length ≥ 8 characters
- Contains at least 3 different character types
- Uses cryptographically secure random generation

## 🐛 Troubleshooting

### Common Issues

**"Error: Password length must be between 8 and 128 characters"**
- Ensure your password length is within the valid range

**"Error: At least one character set must be selected"**
- Make sure you've specified at least one character type with the options

**"Unexpected error: stoi"**
- Check that your length parameter is a valid number

### Compilation Issues

If you encounter compilation errors:

```bash
# Ensure you have a C++17 compatible compiler
g++ --version

# Try building with debug flags for more information
make debug
```

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/amazing-feature`)
3. Commit your changes (`git commit -m 'Add amazing feature'`)
4. Push to the branch (`git push origin feature/amazing-feature`)
5. Open a Pull Request

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 🙏 Acknowledgments

- Inspired by the need for secure, command-line password generation
- Built with modern C++ best practices
- Security-focused development approach

## 📞 Support

If you encounter any issues or have questions:
- Open an issue on GitHub
- Check the troubleshooting section above
- Ensure you're using a supported platform and compiler

---

**⚠️ Security Notice**: This tool generates cryptographically secure passwords, but always use them in conjunction with other security best practices like two-factor authentication and secure storage.
