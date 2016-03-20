CC = g++
CFLAGS = -c -Wall
LDFALGS = 

BUILD_DIR = build
SOURCES = main.cpp hello.cpp factorial.cpp
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))
EXECUTABLE = hello

all: $(EXECUTABLE) 
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $+ -o $@

$(addprefix $(BUILD_DIR)/, %.o): %.cpp
	$(CC) $(CFLAGS) $< -o $@
    
$(OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)
    
.PHONY: clean
clean:
	rmdir -rf $(BUILD_DIR) $(EXECUTABLE)
