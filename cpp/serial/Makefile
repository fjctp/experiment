CC = g++-4.8
CCFLAGS = -Wall -std=c++0x -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -c
LDFLAGS = -lwiringPi

APP_NAME = main
BUILD_DIR = build
BIN_DIR = build/bin
SOURCES = $(APP_NAME).cpp 
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))
EXECUTABLE = $(BIN_DIR)/$(APP_NAME)

all: $(EXECUTABLE) 
    
$(EXECUTABLE): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $+ -o $@

$(addprefix $(BUILD_DIR)/, %.o): %.cpp | $(BUILD_DIR)
	$(CC) $(CCFLAGS) $< -o $@
    
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BIN_DIR):
	mkdir $(BIN_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
