// FoxyPassword Generator - Secure Web Interface
// Uses cryptographically secure random generation (Web Crypto API)

class SecurePasswordGenerator {
    constructor() {
        this.uppercaseChars = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ';
        this.lowercaseChars = 'abcdefghijklmnopqrstuvwxyz';
        this.numberChars = '0123456789';
        this.specialChars = '!@#$%^&*()_+-=[]{}|;:,.<>?';
        
        this.init();
    }

    init() {
        this.bindEvents();
        this.updateLengthDisplay();
        this.validateCharacterSets();
    }

    bindEvents() {
        // Length slider
        const lengthSlider = document.getElementById('passwordLength');
        const lengthValue = document.getElementById('lengthValue');
        
        lengthSlider.addEventListener('input', () => {
            lengthValue.textContent = lengthSlider.value;
        });

        // Character set checkboxes
        const checkboxes = ['uppercase', 'lowercase', 'numbers', 'special'];
        checkboxes.forEach(id => {
            document.getElementById(id).addEventListener('change', () => {
                this.validateCharacterSets();
            });
        });

        // Generate buttons
        document.getElementById('generateBtn').addEventListener('click', () => {
            this.generatePassword();
        });

        document.getElementById('generateMultipleBtn').addEventListener('click', () => {
            this.generateMultiplePasswords();
        });

        // Copy button
        document.getElementById('copyButton').addEventListener('click', () => {
            this.copyToClipboard();
        });

        // Keyboard shortcuts
        document.addEventListener('keydown', (e) => {
            if (e.ctrlKey || e.metaKey) {
                switch(e.key) {
                    case 'Enter':
                        e.preventDefault();
                        this.generatePassword();
                        break;
                    case 'c':
                        if (document.getElementById('passwordOutput').value) {
                            e.preventDefault();
                            this.copyToClipboard();
                        }
                        break;
                }
            }
        });
    }

    updateLengthDisplay() {
        const lengthSlider = document.getElementById('passwordLength');
        const lengthValue = document.getElementById('lengthValue');
        lengthValue.textContent = lengthSlider.value;
    }

    validateCharacterSets() {
        const useUppercase = document.getElementById('uppercase').checked;
        const useLowercase = document.getElementById('lowercase').checked;
        const useNumbers = document.getElementById('numbers').checked;
        const useSpecial = document.getElementById('special').checked;

        const generateBtn = document.getElementById('generateBtn');
        const generateMultipleBtn = document.getElementById('generateMultipleBtn');

        if (!useUppercase && !useLowercase && !useNumbers && !useSpecial) {
            generateBtn.disabled = true;
            generateMultipleBtn.disabled = true;
            generateBtn.title = 'Please select at least one character set';
            generateMultipleBtn.title = 'Please select at least one character set';
        } else {
            generateBtn.disabled = false;
            generateMultipleBtn.disabled = false;
            generateBtn.title = '';
            generateMultipleBtn.title = '';
        }
    }

    // Cryptographically secure random number generation
    async getSecureRandomInt(min, max) {
        const range = max - min + 1;
        const bytesNeeded = Math.ceil(Math.log2(range) / 8);
        const maxNum = Math.pow(256, bytesNeeded);
        const maxValidNum = maxNum - (maxNum % range);

        let randomValue;
        do {
            const randomBytes = new Uint8Array(bytesNeeded);
            crypto.getRandomValues(randomBytes);
            randomValue = 0;
            for (let i = 0; i < bytesNeeded; i++) {
                randomValue = (randomValue << 8) + randomBytes[i];
            }
        } while (randomValue >= maxValidNum);

        return min + (randomValue % range);
    }

    // Get random character from specified character set
    async getRandomChar(charSet) {
        const index = await this.getSecureRandomInt(0, charSet.length - 1);
        return charSet[index];
    }

    // Generate a single secure password
    async generatePassword() {
        try {
            const length = parseInt(document.getElementById('passwordLength').value);
            const useUppercase = document.getElementById('uppercase').checked;
            const useLowercase = document.getElementById('lowercase').checked;
            const useNumbers = document.getElementById('numbers').checked;
            const useSpecial = document.getElementById('special').checked;

            // Validate inputs
            if (length < 8 || length > 128) {
                this.showNotification('Password length must be between 8 and 128 characters', 'error');
                return;
            }

            if (!useUppercase && !useLowercase && !useNumbers && !useSpecial) {
                this.showNotification('Please select at least one character set', 'error');
                return;
            }

            // Build character set
            let charSet = '';
            if (useUppercase) charSet += this.uppercaseChars;
            if (useLowercase) charSet += this.lowercaseChars;
            if (useNumbers) charSet += this.numberChars;
            if (useSpecial) charSet += this.specialChars;

            // Generate required characters (one from each selected set)
            let requiredChars = '';
            if (useUppercase) requiredChars += await this.getRandomChar(this.uppercaseChars);
            if (useLowercase) requiredChars += await this.getRandomChar(this.lowercaseChars);
            if (useNumbers) requiredChars += await this.getRandomChar(this.numberChars);
            if (useSpecial) requiredChars += await this.getRandomChar(this.specialChars);

            // Generate remaining characters
            let password = '';
            const remainingLength = length - requiredChars.length;
            
            for (let i = 0; i < remainingLength; i++) {
                password += await this.getRandomChar(charSet);
            }

            // Insert required characters at random positions
            for (let char of requiredChars) {
                const insertPos = await this.getSecureRandomInt(0, password.length);
                password = password.slice(0, insertPos) + char + password.slice(insertPos);
            }

            // Display password
            document.getElementById('passwordOutput').value = password;
            
            // Update strength indicator
            this.updateStrengthIndicator(password);
            
            // Hide multiple passwords section
            document.getElementById('multiplePasswords').style.display = 'none';

        } catch (error) {
            console.error('Error generating password:', error);
            this.showNotification('Error generating password. Please try again.', 'error');
        }
    }

    // Generate multiple passwords
    async generateMultiplePasswords() {
        try {
            const passwords = [];
            const count = 5; // Generate 5 passwords

            for (let i = 0; i < count; i++) {
                const length = parseInt(document.getElementById('passwordLength').value);
                const useUppercase = document.getElementById('uppercase').checked;
                const useLowercase = document.getElementById('lowercase').checked;
                const useNumbers = document.getElementById('numbers').checked;
                const useSpecial = document.getElementById('special').checked;

                // Build character set
                let charSet = '';
                if (useUppercase) charSet += this.uppercaseChars;
                if (useLowercase) charSet += this.lowercaseChars;
                if (useNumbers) charSet += this.numberChars;
                if (useSpecial) charSet += this.specialChars;

                // Generate required characters
                let requiredChars = '';
                if (useUppercase) requiredChars += await this.getRandomChar(this.uppercaseChars);
                if (useLowercase) requiredChars += await this.getRandomChar(this.lowercaseChars);
                if (useNumbers) requiredChars += await this.getRandomChar(this.numberChars);
                if (useSpecial) requiredChars += await this.getRandomChar(this.specialChars);

                // Generate password
                let password = '';
                const remainingLength = length - requiredChars.length;
                
                for (let j = 0; j < remainingLength; j++) {
                    password += await this.getRandomChar(charSet);
                }

                // Insert required characters
                for (let char of requiredChars) {
                    const insertPos = await this.getSecureRandomInt(0, password.length);
                    password = password.slice(0, insertPos) + char + password.slice(insertPos);
                }

                passwords.push(password);
            }

            this.displayMultiplePasswords(passwords);

        } catch (error) {
            console.error('Error generating multiple passwords:', error);
            this.showNotification('Error generating passwords. Please try again.', 'error');
        }
    }

    // Display multiple passwords
    displayMultiplePasswords(passwords) {
        const container = document.getElementById('multiplePasswords');
        const list = document.getElementById('passwordList');
        
        list.innerHTML = '';
        
        passwords.forEach((password, index) => {
            const item = document.createElement('div');
            item.className = 'password-item';
            item.innerHTML = `
                <span class="password">${password}</span>
                <button class="copy-btn" onclick="passwordGenerator.copySpecificPassword('${password}')" title="Copy password">
                    <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                        <rect x="9" y="9" width="13" height="13" rx="2" ry="2"></rect>
                        <path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"></path>
                    </svg>
                </button>
            `;
            list.appendChild(item);
        });
        
        container.style.display = 'block';
    }

    // Copy specific password to clipboard
    copySpecificPassword(password) {
        navigator.clipboard.writeText(password).then(() => {
            this.showNotification('Password copied to clipboard!', 'success');
        }).catch(() => {
            this.showNotification('Failed to copy password', 'error');
        });
    }

    // Copy to clipboard
    copyToClipboard() {
        const passwordOutput = document.getElementById('passwordOutput');
        
        if (!passwordOutput.value) {
            this.showNotification('No password to copy', 'error');
            return;
        }

        navigator.clipboard.writeText(passwordOutput.value).then(() => {
            this.showNotification('Password copied to clipboard!', 'success');
        }).catch(() => {
            // Fallback for older browsers
            passwordOutput.select();
            passwordOutput.setSelectionRange(0, 99999);
            document.execCommand('copy');
            this.showNotification('Password copied to clipboard!', 'success');
        });
    }

    // Update password strength indicator
    updateStrengthIndicator(password) {
        const indicator = document.getElementById('strengthIndicator');
        const text = document.getElementById('strengthText');
        
        if (!password) {
            indicator.style.width = '0%';
            text.textContent = 'Generate a password to see strength';
            return;
        }

        // Calculate strength
        let score = 0;
        let feedback = [];

        // Length score
        if (password.length >= 8) score += 1;
        if (password.length >= 12) score += 1;
        if (password.length >= 16) score += 1;
        if (password.length >= 20) score += 1;

        // Character variety score
        let hasUppercase = /[A-Z]/.test(password);
        let hasLowercase = /[a-z]/.test(password);
        let hasNumbers = /[0-9]/.test(password);
        let hasSpecial = /[!@#$%^&*()_+\-=\[\]{}|;:,.<>?]/.test(password);

        let charTypes = (hasUppercase ? 1 : 0) + (hasLowercase ? 1 : 0) + 
                       (hasNumbers ? 1 : 0) + (hasSpecial ? 1 : 0);

        if (charTypes >= 2) score += 1;
        if (charTypes >= 3) score += 1;
        if (charTypes >= 4) score += 1;

        // Entropy score (approximate)
        let entropy = 0;
        if (hasUppercase) entropy += 26;
        if (hasLowercase) entropy += 26;
        if (hasNumbers) entropy += 10;
        if (hasSpecial) entropy += 20;

        let entropyScore = Math.log2(Math.pow(entropy, password.length));
        if (entropyScore > 50) score += 1;
        if (entropyScore > 80) score += 1;

        // Determine strength level
        let strengthLevel, strengthText, strengthColor;
        
        if (score >= 8) {
            strengthLevel = 100;
            strengthText = 'Excellent - Very Strong';
            strengthColor = '#10b981';
        } else if (score >= 6) {
            strengthLevel = 75;
            strengthText = 'Good - Strong';
            strengthColor = '#10b981';
        } else if (score >= 4) {
            strengthLevel = 50;
            strengthText = 'Fair - Moderate';
            strengthColor = '#f59e0b';
        } else if (score >= 2) {
            strengthLevel = 25;
            strengthText = 'Weak - Needs improvement';
            strengthColor = '#ef4444';
        } else {
            strengthLevel = 0;
            strengthText = 'Very Weak - Not recommended';
            strengthColor = '#ef4444';
        }

        // Update UI
        indicator.style.width = strengthLevel + '%';
        indicator.style.background = strengthColor;
        text.textContent = strengthText;
        text.style.color = strengthColor;
    }

    // Show notification
    showNotification(message, type = 'success') {
        const notification = document.getElementById('notification');
        notification.textContent = message;
        notification.className = `notification ${type} show`;
        
        setTimeout(() => {
            notification.classList.remove('show');
        }, 3000);
    }
}

// Initialize the password generator when DOM is loaded
let passwordGenerator;
document.addEventListener('DOMContentLoaded', () => {
    passwordGenerator = new SecurePasswordGenerator();
    
    // Check for Web Crypto API support
    if (!window.crypto || !window.crypto.getRandomValues) {
        passwordGenerator.showNotification(
            'Warning: Your browser does not support secure random generation. Consider using a modern browser.',
            'error'
        );
    }
});

// Security: Prevent password field from being saved by password managers
document.addEventListener('DOMContentLoaded', () => {
    const passwordField = document.getElementById('passwordOutput');
    passwordField.setAttribute('autocomplete', 'off');
    passwordField.setAttribute('data-form-type', 'other');
});

// Security: Clear clipboard after a delay (optional)
function clearClipboardAfterDelay() {
    setTimeout(() => {
        navigator.clipboard.writeText('').catch(() => {
            // Ignore errors
        });
    }, 30000); // Clear after 30 seconds
}

// Export for global access (for copy buttons)
window.passwordGenerator = passwordGenerator;
