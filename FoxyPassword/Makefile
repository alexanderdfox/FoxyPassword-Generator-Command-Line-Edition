# Cross-platform compiler detection
ifeq ($(OS),Windows_NT)
    # Windows
    CC=g++
    TARGET=passgen.exe
    RM=del /Q
    CP=copy
    MKDIR=mkdir
    PYTHON=python
    PYTHON_SERVER=python -m http.server
else
    # Unix-like systems (macOS, Linux)
    CC=g++
    TARGET=passgen
    RM=rm -f
    CP=cp
    MKDIR=mkdir -p
    PYTHON=python3
    PYTHON_SERVER=python3 -m http.server
endif

# Common compiler flags
CXXFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -O2 -DNDEBUG

# Platform-specific security flags
ifeq ($(OS),Windows_NT)
    # Windows-specific flags
    SECURITY_FLAGS=-D_FORTIFY_SOURCE=2
    WARNING_FLAGS=-Werror=format-security
else
    # Unix-like systems (macOS, Linux)
    SECURITY_FLAGS=-fstack-protector-strong -D_FORTIFY_SOURCE=2
    WARNING_FLAGS=-Werror=format-security -Werror=implicit-function-declaration
    
    # Add platform-specific flags
    UNAME_S := $(shell uname -s)
    ifeq ($(UNAME_S),Darwin)
        # macOS-specific flags
        SECURITY_FLAGS += -fPIE
    else
        # Linux-specific flags
        SECURITY_FLAGS += -fPIE -pie
    endif
endif

SOURCE=passgen.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CXXFLAGS) $(SECURITY_FLAGS) $(WARNING_FLAGS) $(SOURCE) -o $(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

release: CXXFLAGS += -O3 -march=native
release: $(TARGET)

clean:
	$(RM) $(TARGET)

install: $(TARGET)
ifeq ($(OS),Windows_NT)
	@echo "Windows installation: Copy $(TARGET) to a directory in your PATH"
	@echo "Example: copy $(TARGET) C:\Windows\System32\"
else
	$(CP) $(TARGET) /usr/local/bin/
endif

uninstall:
ifeq ($(OS),Windows_NT)
	@echo "Windows uninstallation: Remove $(TARGET) from your PATH directory"
else
	$(RM) /usr/local/bin/$(TARGET)
endif

test: $(TARGET)
	@echo "Testing password generation..."
	@echo "Generating 10-character password:"
ifeq ($(OS),Windows_NT)
	@$(TARGET) 10
	@echo "Generating 16-character password with letters and numbers:"
	@$(TARGET) 16 -u -l -n
	@echo "Generating 20-character password with letters and special chars:"
	@$(TARGET) 20 -u -l -s
	@echo "Testing help:"
	@$(TARGET) --help
else
	@./$(TARGET) 10
	@echo "Generating 16-character password with letters and numbers:"
	@./$(TARGET) 16 -u -l -n
	@echo "Generating 20-character password with letters and special chars:"
	@./$(TARGET) 20 -u -l -s
	@echo "Testing help:"
	@./$(TARGET) --help
endif

web: $(TARGET)
	@echo "Starting web interface..."
	@cd web && $(PYTHON) server.py

web-serve: $(TARGET)
	@echo "Starting simple HTTP server for web interface..."
	@cd web && $(PYTHON_SERVER) 8080

web-files:
	@echo "Checking web interface files..."
ifeq ($(OS),Windows_NT)
	@if exist web\index.html if exist web\styles.css if exist web\script.js ( \
		echo ✓ All web files present \
	) else ( \
		echo ✗ Missing web files & \
		exit /b 1 \
	)
else
	@if [ -f web/index.html ] && [ -f web/styles.css ] && [ -f web/script.js ]; then \
		echo "✓ All web files present"; \
	else \
		echo "✗ Missing web files"; \
		exit 1; \
	fi
endif

# Additional cross-platform targets
help:
	@echo "Available targets:"
	@echo "  all        - Build the password generator"
	@echo "  debug      - Build with debug symbols"
	@echo "  release    - Build with optimizations"
	@echo "  clean      - Remove build artifacts"
	@echo "  install    - Install system-wide (Unix) or show instructions (Windows)"
	@echo "  uninstall  - Remove from system (Unix) or show instructions (Windows)"
	@echo "  test       - Run automated tests"
	@echo "  web        - Start web interface server"
	@echo "  web-serve  - Start simple HTTP server for web interface"
	@echo "  web-files  - Check web interface files"
	@echo "  help       - Show this help message"
ifeq ($(OS),Windows_NT)
	@echo ""
	@echo "Windows Notes:"
	@echo "  - Requires MinGW-w64 or Visual Studio Build Tools"
	@echo "  - Python 3.x required for web interface"
	@echo "  - Use 'make install' to see installation instructions"
else
	@echo ""
	@echo "Unix Notes:"
	@echo "  - Requires GCC 7+ or Clang 5+"
	@echo "  - Python 3.x required for web interface"
	@echo "  - Use 'sudo make install' for system-wide installation"
endif

# Platform detection info
info:
	@echo "Platform Information:"
ifeq ($(OS),Windows_NT)
	@echo "  OS: Windows"
	@echo "  Compiler: $(CC)"
	@echo "  Target: $(TARGET)"
	@echo "  Python: $(PYTHON)"
else
	@echo "  OS: $(shell uname -s)"
	@echo "  Architecture: $(shell uname -m)"
	@echo "  Compiler: $(CC)"
	@echo "  Target: $(TARGET)"
	@echo "  Python: $(PYTHON)"
endif
	@echo "  CXXFLAGS: $(CXXFLAGS)"
	@echo "  SECURITY_FLAGS: $(SECURITY_FLAGS)"
	@echo "  WARNING_FLAGS: $(WARNING_FLAGS)"

.PHONY: all debug release clean install uninstall test web web-serve web-files help info
