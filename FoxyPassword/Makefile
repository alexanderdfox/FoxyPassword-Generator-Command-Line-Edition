CC=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Wpedantic -O2 -DNDEBUG
SECURITY_FLAGS=-fstack-protector-strong -D_FORTIFY_SOURCE=2
# Add platform-specific flags
ifeq ($(shell uname),Darwin)
    SECURITY_FLAGS += -fPIE
else
    SECURITY_FLAGS += -fPIE -pie
endif
WARNING_FLAGS=-Werror=format-security -Werror=implicit-function-declaration

TARGET=passgen
SOURCE=passgen.cpp

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CXXFLAGS) $(SECURITY_FLAGS) $(WARNING_FLAGS) $(SOURCE) -o $(TARGET)

debug: CXXFLAGS += -g -DDEBUG
debug: $(TARGET)

release: CXXFLAGS += -O3 -march=native
release: $(TARGET)

clean:
	rm -f $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/$(TARGET)

test: $(TARGET)
	@echo "Testing password generation..."
	@echo "Generating 10-character password:"
	@./$(TARGET) 10
	@echo "Generating 16-character password with letters and numbers:"
	@./$(TARGET) 16 -u -l -n
	@echo "Generating 20-character password with letters and special chars:"
	@./$(TARGET) 20 -u -l -s
	@echo "Testing help:"
	@./$(TARGET) --help

.PHONY: all debug release clean install uninstall test
