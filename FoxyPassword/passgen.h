#ifndef PASSGEN_H
#define PASSGEN_H
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <string>
#include <cctype>
#include <random>
#include <algorithm>
#include <stdexcept>

namespace passgen {
    /**
     * @brief Secure password generator class
     * 
     * This class provides cryptographically secure password generation
     * with configurable character sets and length requirements.
     */
    class Passgen {
    public:
        /**
         * @brief Generate a secure password
         * @param length Password length (minimum 8, maximum 128)
         * @param useUppercase Include uppercase letters (A-Z)
         * @param useLowercase Include lowercase letters (a-z)
         * @param useNumbers Include numbers (0-9)
         * @param useSpecial Include special characters (!@#$%^&*()_+-=[]{}|;:,.<>?)
         * @return Generated password string
         * @throws std::invalid_argument if parameters are invalid
         */
        static std::string generatePassword(int length, 
                                          bool useUppercase = true, 
                                          bool useLowercase = true, 
                                          bool useNumbers = true, 
                                          bool useSpecial = true);
        
        /**
         * @brief Display usage information
         * @param argv Command line arguments array
         */
        static void showUsage(char* argv[]);
        
        /**
         * @brief Validate password strength
         * @param password Password to validate
         * @return true if password meets security requirements
         */
        static bool isPasswordStrong(const std::string& password);
        
    private:
        /**
         * @brief Get a random character from the specified character sets
         * @param useUppercase Include uppercase letters
         * @param useLowercase Include lowercase letters
         * @param useNumbers Include numbers
         * @param useSpecial Include special characters
         * @return Random character from the combined character set
         */
        static char getRandomChar(bool useUppercase, 
                                 bool useLowercase, 
                                 bool useNumbers, 
                                 bool useSpecial);
        
        /**
         * @brief Get cryptographically secure random number generator
         * @return Reference to the random number generator
         */
        static std::mt19937& getRandomGenerator();
        
        // Character sets
        static const std::string UPPERCASE_CHARS;
        static const std::string LOWERCASE_CHARS;
        static const std::string NUMBER_CHARS;
        static const std::string SPECIAL_CHARS;
    };
}
#endif
