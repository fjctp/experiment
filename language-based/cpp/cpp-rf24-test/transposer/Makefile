CC = g++-4.8
CCFLAGS = -IRF24/ -std=c++0x -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -c
LDFLAGS = -lrf24-bcm -lbcm2835

BUILD_DIR = build
SOURCES = Comm.cpp radio.cpp RadioComm.cpp
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))
OBJS_RF24 = $(addprefix RF24/, librf24-bcm.so.1.0 )
EXECUTABLE = radio

all: $(EXECUTABLE) 
    
$(EXECUTABLE): $(OBJECTS) $(OBJS_RF24)
	$(CC) $(LDFLAGS) $+ -o $@

$(addprefix $(BUILD_DIR)/, %.o): %.cpp
	$(CC) $(CCFLAGS) $< -o $@
    
$(OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)
    
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(EXECUTABLE)
