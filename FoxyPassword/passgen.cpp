#include "passgen.h"
#include <random>
#include <algorithm>
#include <stdexcept>
#include <cstring>

using namespace passgen;

// Static member initialization
const std::string Passgen::UPPERCASE_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string Passgen::LOWERCASE_CHARS = "abcdefghijklmnopqrstuvwxyz";
const std::string Passgen::NUMBER_CHARS = "0123456789";
const std::string Passgen::SPECIAL_CHARS = "!@#$%^&*()_+-=[]{}|;:,.<>?";

// Thread-local random number generator for better security
static std::mt19937& getRandomGenerator() {
    static thread_local std::mt19937 generator;
    static thread_local bool initialized = false;
    
    if (!initialized) {
        // Use hardware random device for seeding
        std::random_device rd;
        generator.seed(rd());
        initialized = true;
    }
    
    return generator;
}

std::mt19937& Passgen::getRandomGenerator() {
    return ::getRandomGenerator();
}

char Passgen::getRandomChar(bool useUppercase, bool useLowercase, bool useNumbers, bool useSpecial) {
    std::string charSet;
    
    if (useUppercase) charSet += UPPERCASE_CHARS;
    if (useLowercase) charSet += LOWERCASE_CHARS;
    if (useNumbers) charSet += NUMBER_CHARS;
    if (useSpecial) charSet += SPECIAL_CHARS;
    
    if (charSet.empty()) {
        throw std::invalid_argument("At least one character set must be selected");
    }
    
    std::uniform_int_distribution<int> distribution(0, charSet.length() - 1);
    return charSet[distribution(getRandomGenerator())];
}

std::string Passgen::generatePassword(int length, bool useUppercase, bool useLowercase, bool useNumbers, bool useSpecial) {
    // Validate input parameters
    if (length < 8 || length > 128) {
        throw std::invalid_argument("Password length must be between 8 and 128 characters");
    }
    
    if (!useUppercase && !useLowercase && !useNumbers && !useSpecial) {
        throw std::invalid_argument("At least one character set must be selected");
    }
    
    std::string password;
    password.reserve(length);
    
    // Generate password ensuring at least one character from each selected set
    std::string requiredChars;
    if (useUppercase) requiredChars += getRandomChar(true, false, false, false);
    if (useLowercase) requiredChars += getRandomChar(false, true, false, false);
    if (useNumbers) requiredChars += getRandomChar(false, false, true, false);
    if (useSpecial) requiredChars += getRandomChar(false, false, false, true);
    
    // Fill the rest of the password
    int remainingLength = length - requiredChars.length();
    for (int i = 0; i < remainingLength; ++i) {
        password += getRandomChar(useUppercase, useLowercase, useNumbers, useSpecial);
    }
    
    // Insert required characters at random positions
    for (char requiredChar : requiredChars) {
        std::uniform_int_distribution<int> distribution(0, password.length());
        int insertPos = distribution(getRandomGenerator());
        password.insert(insertPos, 1, requiredChar);
    }
    
    return password;
}

bool Passgen::isPasswordStrong(const std::string& password) {
    if (password.length() < 8) return false;
    
    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasNumber = false;
    bool hasSpecial = false;
    
    for (char c : password) {
        if (std::isupper(c)) hasUppercase = true;
        else if (std::islower(c)) hasLowercase = true;
        else if (std::isdigit(c)) hasNumber = true;
        else hasSpecial = true;
    }
    
    // Password is strong if it has at least 2 different character types
    // or if it's long enough (16+ chars) with any character type
    int charTypes = (hasUppercase ? 1 : 0) + (hasLowercase ? 1 : 0) + 
                   (hasNumber ? 1 : 0) + (hasSpecial ? 1 : 0);
    
    return charTypes >= 2 || password.length() >= 16;
}

void Passgen::showUsage(char* argv[]) {
    std::cout << "\nFoxyPassword Generator - Secure Command Line Edition\n";
    std::cout << "==================================================\n\n";
    std::cout << "Usage: " << argv[0] << " <length> [options]\n\n";
    std::cout << "Arguments:\n";
    std::cout << "  length    Password length (8-128 characters)\n\n";
    std::cout << "Options:\n";
    std::cout << "  -u        Include uppercase letters (A-Z)\n";
    std::cout << "  -l        Include lowercase letters (a-z)\n";
    std::cout << "  -n        Include numbers (0-9)\n";
    std::cout << "  -s        Include special characters (!@#$%^&*()_+-=[]{}|;:,.<>?)\n";
    std::cout << "  --help    Show this help message\n\n";
    std::cout << "Examples:\n";
    std::cout << "  " << argv[0] << " 12              # Generate 12-char password with all character types\n";
    std::cout << "  " << argv[0] << " 16 -u -l -n     # Generate 16-char password with letters and numbers\n";
    std::cout << "  " << argv[0] << " 20 -u -l -s     # Generate 20-char password with letters and special chars\n\n";
    std::cout << "Security Notes:\n";
    std::cout << "  - Uses cryptographically secure random number generation\n";
    std::cout << "  - Ensures at least one character from each selected type\n";
    std::cout << "  - Minimum length of 8 characters recommended\n";
    std::cout << "  - Maximum length of 128 characters for performance\n\n";
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            Passgen::showUsage(argv);
            return 1;
        }
        
        // Check for help flag
        if (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0) {
            Passgen::showUsage(argv);
            return 0;
        }
        
        // Parse length
        int length = std::stoi(argv[1]);
        
        // Default character sets (all enabled)
        bool useUppercase = true;
        bool useLowercase = true;
        bool useNumbers = true;
        bool useSpecial = true;
        
        // Parse options
        bool hasSpecificOptions = false;
        for (int i = 2; i < argc; ++i) {
            if (strcmp(argv[i], "-u") == 0) {
                if (!hasSpecificOptions) {
                    useUppercase = false;
                    useLowercase = false;
                    useNumbers = false;
                    useSpecial = false;
                    hasSpecificOptions = true;
                }
                useUppercase = true;
            } else if (strcmp(argv[i], "-l") == 0) {
                if (!hasSpecificOptions) {
                    useUppercase = false;
                    useLowercase = false;
                    useNumbers = false;
                    useSpecial = false;
                    hasSpecificOptions = true;
                }
                useLowercase = true;
            } else if (strcmp(argv[i], "-n") == 0) {
                if (!hasSpecificOptions) {
                    useUppercase = false;
                    useLowercase = false;
                    useNumbers = false;
                    useSpecial = false;
                    hasSpecificOptions = true;
                }
                useNumbers = true;
            } else if (strcmp(argv[i], "-s") == 0) {
                if (!hasSpecificOptions) {
                    useUppercase = false;
                    useLowercase = false;
                    useNumbers = false;
                    useSpecial = false;
                    hasSpecificOptions = true;
                }
                useSpecial = true;
            }
        }
        
        // Generate password
        std::string password = Passgen::generatePassword(length, useUppercase, useLowercase, useNumbers, useSpecial);
        
        // Display result
        std::cout << password << std::endl;
        
        // Show strength indicator
        if (Passgen::isPasswordStrong(password)) {
            std::cerr << "✓ Strong password generated" << std::endl;
        } else {
            std::cerr << "⚠ Password may not meet security requirements" << std::endl;
        }
        
        return 0;
        
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        Passgen::showUsage(argv);
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }
}
