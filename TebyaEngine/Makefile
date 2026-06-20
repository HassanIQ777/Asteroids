# ============================================================
#  Tebya Engine — Static Library Build
#  Output: lib/libTebya.a
# ============================================================

CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -Iinclude
AR       := ar
ARFLAGS  := rcs

SRC_DIR  := src
LIB_DIR  := lib
BUILD_MODE := release

# ============================================================
#  Build modes
# ============================================================
ifeq ($(MAKECMDGOALS), debug)
    BUILD_MODE := debug
    CXXFLAGS += -g -O0 -DDEBUG -fsanitize=address,undefined
    $(info [Tebya] Building in DEBUG mode — buckle up)
else
    CXXFLAGS += -O2 -DNDEBUG
    $(info [Tebya] Building in RELEASE mode)
endif

OBJ_DIR  := obj/$(BUILD_MODE)
LIB      := $(LIB_DIR)/$(BUILD_MODE)/libTebya.a

SRCS     := $(wildcard $(SRC_DIR)/*.cpp)
OBJS     := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

# ============================================================
#  Rules
# ============================================================

all: dirs $(LIB)
debug: dirs $(LIB)

$(LIB): $(OBJS)
	@echo "[AR]  $@"
	@$(AR) $(ARFLAGS) $@ $^
	@echo "[OK]  libTebya.a sealed."

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "[CC]  $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

dirs:
	@mkdir -p $(OBJ_DIR) $(LIB_DIR)/$(BUILD_MODE)

clean:
	@rm -rf $(OBJ_DIR) $(LIB_DIR)
	@echo "[CLN] Library dust swept away."

rebuild: clean all

info:
	@echo "Sources : $(SRCS)"
	@echo "Objects : $(OBJS)"
	@echo "Library : $(LIB)"

.PHONY: all debug clean rebuild info dirs
