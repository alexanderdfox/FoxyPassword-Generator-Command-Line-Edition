# Quick Start Guide - FoxyPassword Generator

## 🚀 Get Started in 30 Seconds

### 1. Build the Tool
```bash
cd FoxyPassword
make
```

### 2. Generate Your First Password
```bash
# Generate a strong 16-character password
./passgen 16
```

### 3. That's It! 🎉

## 📋 Common Use Cases

### Website Passwords
```bash
# Strong password for websites (recommended)
./passgen 16
# Output: K9#mP$vN2@jL5qR8
```

### PIN Codes
```bash
# 6-digit PIN
./passgen 6 -n
# Output: 847392
```

### Memorable Passwords
```bash
# Letters only (easier to remember)
./passgen 12 -u -l
# Output: KjMpQrStUvWx
```

### System Administration
```bash
# Extra strong password for admin accounts
./passgen 24
# Output: P7#kL9$mN2@jQ5&vR8!sT3*wX6
```

## ⚡ Pro Tips

### 1. Use Default Settings
The default configuration generates the strongest passwords:
```bash
./passgen 16  # All character types included
```

### 2. Longer = Stronger
```bash
./passgen 12  # Good
./passgen 16  # Better
./passgen 20  # Best
```

### 3. Check Password Strength
The tool automatically validates password strength:
- ✅ "Strong password generated" = Excellent
- ⚠️ "Password may not meet security requirements" = Consider longer/more types

### 4. Batch Generation
```bash
# Generate multiple passwords
for i in {1..5}; do
    echo "Password $i: $(./passgen 16)"
done
```

## 🔧 Troubleshooting

### "Error: Password length must be between 8 and 128 characters"
- Use a length between 8 and 128
- Recommended: 12-24 characters

### "Error: At least one character set must be selected"
- Use at least one option: `-u`, `-l`, `-n`, or `-s`
- Or use no options for all character types

### Compilation Errors
```bash
# Check your compiler version
g++ --version  # Should be 7.0 or higher

# Try debug build
make debug
```

## 🎯 Best Practices

1. **Length**: Use 16+ characters for important accounts
2. **Variety**: Include multiple character types
3. **Uniqueness**: Generate a new password for each account
4. **Storage**: Use a password manager to store generated passwords
5. **2FA**: Combine with two-factor authentication

## 📞 Need Help?

```bash
# Show detailed help
./passgen --help
```

The tool is now secure, fast, and easy to use! 🦊
