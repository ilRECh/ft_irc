TARGET		:= ircserv
CXX			:= clang++
CXXFLAGS	:= -pedantic-errors -Wall -Wextra -Werror -std=c++98 -pedantic -g -fno-limit-debug-info
LDFLAGS		:= -L/usr/lib -lstdc++ -lm
BUILD		:= ./build
OBJ_DIR		:= $(BUILD)/objects
APP_DIR		:= $(BUILD)/apps
INC_DIRS	:= $(shell find ./include -type d)
INCLUDE		:= $(addprefix -I,$(INC_DIRS))
SRC			:=                      \
	$(wildcard srcs/*.cpp) \
	$(wildcard srcs/cmds/*.cpp)

OBJECTS		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)
DEPENDENCIES \
			:= $(OBJECTS:.o=.d)

.PHONY: all build clean fclean info re

$(OBJECTS) : build

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@
	@echo $(CXX) $(CXXFLAGS) $@

$(APP_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)
	@echo $(CXX) $(CXXFLAGS) $@

-include $(DEPENDENCIES)

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(OBJ_DIR)/*

fclean: clean
	-@rm -rvf $(APP_DIR)/*

info:
	@echo "[*] Application dir: ${APP_DIR}     \n"
	@echo "[*] Object dir:      ${OBJ_DIR}     \n"
	@echo "[*] Sources:         ${SRC}         \n"
	@echo "[*] Objects:         ${OBJECTS}     \n"
	@echo "[*] Dependencies:    ${DEPENDENCIES}\n"

re			: fclean all
