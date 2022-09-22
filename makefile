CXX			= g++.exe
CXX_FLAGS	= -Wall -Werror -O2 -std=c++11 -static -static-libgcc
EX_NAME		:= cpp

SRC			:= src
INCLUDE		:= include

OUTS	= task.exe

ifeq ($(OS),Windows_NT)
# PLATFORM = "Windows"
RM			:= del /s /q /f 
FIND_FILE	= $(shell dir /b /s /a-d "$(1)\*.$(2)")
else
#  PLATFORM = "Unix-Like"
RM			:= rm -f
FIND_FILE	= $(shell find $(1) -type f | grep ".$(2)$$" --color=never)
endif

GET_OBJS	= $(patsubst %.$(EX_NAME), %.o,$(call FIND_FILE,$(1),$(EX_NAME)))
ALL_OBJ		= $(call GET_OBJS,$(SRC))

.PHONY: all clean
all: $(OUTS)
	@echo Done

$(OUTS): $(ALL_OBJ)
	@echo Linking $@
	@$(CXX) $^ -o $@

%.o: %.$(EX_NAME)
	@echo Compiling $@
	@$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -c $< -o $@

clean:
	@echo remove $(ALL_OBJ)
	@$(RM) $(ALL_OBJ)
	@echo remove $(OUTS)
	@$(RM) $(OUTS)
