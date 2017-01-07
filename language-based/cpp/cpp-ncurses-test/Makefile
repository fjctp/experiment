CC = g++-4.8
CCFLAGS = -Wall -std=c++0x -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -c
LDFLAGS = -lncurses

BUILD_DIR = build
SOURCES = console.cpp 
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))
EXECUTABLE = console

all: $(EXECUTABLE) 
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $+ -o $@

$(addprefix $(BUILD_DIR)/, %.o): %.cpp
	$(CC) $(CCFLAGS) $< -o $@
    
$(OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)
    
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
