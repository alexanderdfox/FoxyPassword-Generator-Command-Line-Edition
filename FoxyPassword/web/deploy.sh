#!/bin/bash

# FoxyPassword Generator - Web Interface Deployment Script
# This script helps deploy the web interface to various platforms

set -e

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
PROJECT_NAME="FoxyPassword-Generator"
WEB_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$WEB_DIR/build"
DIST_DIR="$WEB_DIR/dist"

echo -e "${BLUE}🦊 FoxyPassword Generator - Web Interface Deployment${NC}"
echo "=================================================="

# Function to check if command exists
command_exists() {
    command -v "$1" >/dev/null 2>&1
}

# Function to create build directory
create_build_dir() {
    echo -e "${YELLOW}📁 Creating build directory...${NC}"
    mkdir -p "$BUILD_DIR"
    mkdir -p "$DIST_DIR"
}

# Function to copy web files
copy_web_files() {
    echo -e "${YELLOW}📋 Copying web files...${NC}"
    cp "$WEB_DIR/index.html" "$BUILD_DIR/"
    cp "$WEB_DIR/styles.css" "$BUILD_DIR/"
    cp "$WEB_DIR/script.js" "$BUILD_DIR/"
    cp "$WEB_DIR/README.md" "$BUILD_DIR/"
    
    echo -e "${GREEN}✓ Web files copied to build directory${NC}"
}

# Function to minify CSS (if available)
minify_css() {
    if command_exists "csso"; then
        echo -e "${YELLOW}🔧 Minifying CSS...${NC}"
        csso "$WEB_DIR/styles.css" -o "$BUILD_DIR/styles.min.css"
        echo -e "${GREEN}✓ CSS minified${NC}"
    elif command_exists "cleancss"; then
        echo -e "${YELLOW}🔧 Minifying CSS...${NC}"
        cleancss -o "$BUILD_DIR/styles.min.css" "$WEB_DIR/styles.css"
        echo -e "${GREEN}✓ CSS minified${NC}"
    else
        echo -e "${YELLOW}⚠ CSS minification tools not found, using original${NC}"
        cp "$WEB_DIR/styles.css" "$BUILD_DIR/styles.min.css"
    fi
}

# Function to minify JavaScript (if available)
minify_js() {
    if command_exists "terser"; then
        echo -e "${YELLOW}🔧 Minifying JavaScript...${NC}"
        terser "$WEB_DIR/script.js" -o "$BUILD_DIR/script.min.js" --compress --mangle
        echo -e "${GREEN}✓ JavaScript minified${NC}"
    elif command_exists "uglifyjs"; then
        echo -e "${YELLOW}🔧 Minifying JavaScript...${NC}"
        uglifyjs "$WEB_DIR/script.js" -o "$BUILD_DIR/script.min.js" --compress --mangle
        echo -e "${GREEN}✓ JavaScript minified${NC}"
    else
        echo -e "${YELLOW}⚠ JavaScript minification tools not found, using original${NC}"
        cp "$WEB_DIR/script.js" "$BUILD_DIR/script.min.js"
    fi
}

# Function to create optimized HTML
create_optimized_html() {
    echo -e "${YELLOW}🔧 Creating optimized HTML...${NC}"
    
    # Create optimized version with minified assets
    cat > "$BUILD_DIR/index.min.html" << 'EOF'
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>FoxyPassword Generator - Secure Password Creation</title>
    <meta name="description" content="Generate cryptographically secure passwords with FoxyPassword Generator">
    <meta name="keywords" content="password generator, secure passwords, cryptography">
    <link rel="stylesheet" href="styles.min.css">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Inter:wght@300;400;500;600;700&display=swap" rel="stylesheet">
    <link rel="icon" type="image/svg+xml" href="data:image/svg+xml,<svg xmlns='http://www.w3.org/2000/svg' viewBox='0 0 100 100'><text y='.9em' font-size='90'>🦊</text></svg>">
</head>
<body>
    <div class="container">
        <header class="header">
            <div class="logo">
                <span class="logo-icon">🦊</span>
                <h1>FoxyPassword</h1>
            </div>
            <p class="tagline">Cryptographically Secure Password Generator</p>
        </header>

        <main class="main">
            <div class="password-card">
                <div class="password-display">
                    <div class="password-field">
                        <input type="text" id="passwordOutput" readonly placeholder="Your secure password will appear here">
                        <button id="copyButton" class="copy-btn" title="Copy to clipboard">
                            <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <rect x="9" y="9" width="13" height="13" rx="2" ry="2"></rect>
                                <path d="M5 15H4a2 2 0 0 1-2-2V4a2 2 0 0 1 2-2h9a2 2 0 0 1 2 2v1"></path>
                            </svg>
                        </button>
                    </div>
                    <div class="password-strength">
                        <div class="strength-bar">
                            <div id="strengthIndicator" class="strength-indicator"></div>
                        </div>
                        <span id="strengthText" class="strength-text">Generate a password to see strength</span>
                    </div>
                </div>

                <div class="controls">
                    <div class="control-group">
                        <label for="passwordLength" class="control-label">Password Length</label>
                        <div class="length-control">
                            <input type="range" id="passwordLength" min="8" max="128" value="16" class="length-slider">
                            <span id="lengthValue" class="length-value">16</span>
                        </div>
                    </div>

                    <div class="character-options">
                        <h3>Character Sets</h3>
                        <div class="option-grid">
                            <label class="option-item">
                                <input type="checkbox" id="uppercase" checked>
                                <span class="checkbox-custom"></span>
                                <span class="option-text">Uppercase Letters (A-Z)</span>
                                <span class="option-count">26</span>
                            </label>
                            <label class="option-item">
                                <input type="checkbox" id="lowercase" checked>
                                <span class="checkbox-custom"></span>
                                <span class="option-text">Lowercase Letters (a-z)</span>
                                <span class="option-count">26</span>
                            </label>
                            <label class="option-item">
                                <input type="checkbox" id="numbers" checked>
                                <span class="checkbox-custom"></span>
                                <span class="option-text">Numbers (0-9)</span>
                                <span class="option-count">10</span>
                            </label>
                            <label class="option-item">
                                <input type="checkbox" id="special" checked>
                                <span class="checkbox-custom"></span>
                                <span class="option-text">Special Characters (!@#$%^&*)</span>
                                <span class="option-count">20</span>
                            </label>
                        </div>
                    </div>

                    <div class="action-buttons">
                        <button id="generateBtn" class="btn btn-primary">
                            <svg width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2">
                                <path d="M21 2v6h-6"></path>
                                <path d="M3 12a9 9 0 0 1 15-6.7L21 8"></path>
                                <path d="M3 22v-6h6"></path>
                                <path d="M21 12a9 9 0 0 1-15 6.7L3 16"></path>
                            </svg>
                            Generate Password
                        </button>
                        <button id="generateMultipleBtn" class="btn btn-secondary">
                            Generate Multiple
                        </button>
                    </div>
                </div>
            </div>

            <div class="info-cards">
                <div class="info-card">
                    <h3>🔒 Security Features</h3>
                    <ul>
                        <li>Cryptographically secure random generation</li>
                        <li>Hardware entropy sources</li>
                        <li>Client-side processing (no server storage)</li>
                        <li>Automatic strength validation</li>
                    </ul>
                </div>
                <div class="info-card">
                    <h3>💡 Best Practices</h3>
                    <ul>
                        <li>Use 16+ characters for important accounts</li>
                        <li>Include multiple character types</li>
                        <li>Generate unique passwords for each account</li>
                        <li>Store securely in a password manager</li>
                    </ul>
                </div>
            </div>

            <div id="multiplePasswords" class="multiple-passwords" style="display: none;">
                <h3>Generated Passwords</h3>
                <div id="passwordList" class="password-list"></div>
            </div>
        </main>

        <footer class="footer">
            <p>&copy; 2024 FoxyPassword Generator. Built with security in mind.</p>
            <p class="disclaimer">This tool generates passwords locally in your browser. No passwords are transmitted or stored on any server.</p>
        </footer>
    </div>

    <div id="notification" class="notification"></div>

    <script src="script.min.js"></script>
</body>
</html>
EOF

    echo -e "${GREEN}✓ Optimized HTML created${NC}"
}

# Function to create deployment package
create_deployment_package() {
    echo -e "${YELLOW}📦 Creating deployment package...${NC}"
    
    # Create distribution package
    tar -czf "$DIST_DIR/foxypassword-web.tar.gz" -C "$BUILD_DIR" .
    zip -r "$DIST_DIR/foxypassword-web.zip" "$BUILD_DIR"/*
    
    echo -e "${GREEN}✓ Deployment packages created:${NC}"
    echo "  - $DIST_DIR/foxypassword-web.tar.gz"
    echo "  - $DIST_DIR/foxypassword-web.zip"
}

# Function to validate deployment
validate_deployment() {
    echo -e "${YELLOW}🔍 Validating deployment...${NC}"
    
    local required_files=("index.html" "styles.css" "script.js" "index.min.html" "styles.min.css" "script.min.js")
    local missing_files=()
    
    for file in "${required_files[@]}"; do
        if [[ ! -f "$BUILD_DIR/$file" ]]; then
            missing_files+=("$file")
        fi
    done
    
    if [[ ${#missing_files[@]} -eq 0 ]]; then
        echo -e "${GREEN}✓ All files present and valid${NC}"
    else
        echo -e "${RED}✗ Missing files: ${missing_files[*]}${NC}"
        exit 1
    fi
}

# Function to show deployment info
show_deployment_info() {
    echo -e "${BLUE}📊 Deployment Summary${NC}"
    echo "=================="
    echo "Build Directory: $BUILD_DIR"
    echo "Distribution: $DIST_DIR"
    echo "Original Size: $(du -sh "$WEB_DIR" | cut -f1)"
    echo "Build Size: $(du -sh "$BUILD_DIR" | cut -f1)"
    
    if [[ -f "$DIST_DIR/foxypassword-web.tar.gz" ]]; then
        echo "Package Size: $(du -sh "$DIST_DIR/foxypassword-web.tar.gz" | cut -f1)"
    fi
}

# Main deployment function
deploy() {
    echo -e "${BLUE}🚀 Starting deployment...${NC}"
    
    create_build_dir
    copy_web_files
    minify_css
    minify_js
    create_optimized_html
    validate_deployment
    create_deployment_package
    show_deployment_info
    
    echo -e "${GREEN}🎉 Deployment completed successfully!${NC}"
    echo ""
    echo -e "${YELLOW}Next steps:${NC}"
    echo "1. Upload files from $BUILD_DIR to your web server"
    echo "2. Or use the packages in $DIST_DIR for distribution"
    echo "3. Test the deployment thoroughly"
}

# Function to clean build artifacts
clean() {
    echo -e "${YELLOW}🧹 Cleaning build artifacts...${NC}"
    rm -rf "$BUILD_DIR"
    rm -rf "$DIST_DIR"
    echo -e "${GREEN}✓ Build artifacts cleaned${NC}"
}

# Function to show help
show_help() {
    echo -e "${BLUE}FoxyPassword Generator - Web Interface Deployment${NC}"
    echo ""
    echo "Usage: $0 [COMMAND]"
    echo ""
    echo "Commands:"
    echo "  deploy    Build and package the web interface for deployment"
    echo "  clean     Remove build artifacts"
    echo "  help      Show this help message"
    echo ""
    echo "Examples:"
    echo "  $0 deploy    # Build and package for deployment"
    echo "  $0 clean     # Clean build artifacts"
}

# Main script logic
case "${1:-deploy}" in
    "deploy")
        deploy
        ;;
    "clean")
        clean
        ;;
    "help"|"-h"|"--help")
        show_help
        ;;
    *)
        echo -e "${RED}Unknown command: $1${NC}"
        show_help
        exit 1
        ;;
esac
