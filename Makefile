TARGET   := bin/Asteroids
CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra
INCLUDES := -Iinclude -ITebyaEngine/include
LDFLAGS  := -LTebyaEngine/lib -lTebya \
            -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_DIR  := obj
BIN_DIR  := bin

SRCS     := main.cpp $(wildcard src/*.cpp)
OBJS     := $(patsubst %.cpp, $(OBJ_DIR)/%.o, $(notdir $(SRCS)))

ifeq ($(MAKECMDGOALS), debug)
    CXXFLAGS += -g -O0 -DDEBUG -fsanitize=address,undefined
    LDFLAGS  += -fsanitize=address,undefined
    $(info [Asteroids] DEBUG)
else
    CXXFLAGS += -O2 -DNDEBUG
    $(info [Asteroids] RELEASE)
endif

all: engine dirs $(TARGET)
debug: engine dirs $(TARGET)

engine:
	@$(MAKE) -C TebyaEngine $(if $(filter debug,$(MAKECMDGOALS)),debug)

$(TARGET): $(OBJS)
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
