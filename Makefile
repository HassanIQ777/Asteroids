CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra
INCLUDES := -Iinclude -ITebyaEngine/include

BIN_DIR  := bin
BUILD_MODE := release
SANITIZER_FLAGS :=

ifeq ($(MAKECMDGOALS), debug)
    BUILD_MODE := debug
    SANITIZER_FLAGS := -fsanitize=address,undefined
    CXXFLAGS += -g -O0 -DDEBUG $(SANITIZER_FLAGS)
    $(info [Asteroids] DEBUG)
else
    CXXFLAGS += -O2 -DNDEBUG
    $(info [Asteroids] RELEASE)
endif

OBJ_DIR  := obj/$(BUILD_MODE)
BIN_DIR  := bin/$(BUILD_MODE)
TARGET   := $(BIN_DIR)/Asteroids
ENGINE_LIB := TebyaEngine/lib/$(BUILD_MODE)/libTebya.a
LDFLAGS  := -LTebyaEngine/lib/$(BUILD_MODE) -lTebya \
            -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer \
            $(SANITIZER_FLAGS)

SRCS     := main.cpp $(wildcard src/*.cpp)
OBJS     := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

all: engine dirs $(TARGET)
debug: engine dirs $(TARGET)

engine:
	@$(MAKE) -C TebyaEngine $(if $(filter debug,$(MAKECMDGOALS)),debug)

$(TARGET): $(OBJS) $(ENGINE_LIB)
	@echo "[LD]  $@"
	@$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "[OK]  $(TARGET) ready."

$(OBJ_DIR)/main.o: main.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

dirs:
	@mkdir -p $(OBJ_DIR) $(BIN_DIR)

run: all
	@./$(TARGET)

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

cleanall: clean
	@$(MAKE) -C TebyaEngine clean

rebuild: cleanall all

.PHONY: all debug engine run clean cleanall rebuild dirs
