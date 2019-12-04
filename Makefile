####################################################################
# Makefile                                                         #
####################################################################

.SUFFIXES: all				
.PHONY: clean all dox splint

####################################################################
# Path Definitions                                                 #
####################################################################
OUT_DIR     = ./output
OBJ_DIR     = $(OUT_DIR)/build
EXE_DIR     = $(OUT_DIR)/exe
DOX_DIR     = $(OUT_DIR)/docu
SRC_DIR     = ./src
INCLUDE_DIR = ./include

####################################################################
# Flag Definitions                                                 #
####################################################################
FLAGS = -lm -fopenmp -Wall -g -Wl,--version-script,exportmap
# SPLINTFLAGS = +standard -skipposixheaders -mustfreeonly -likelybool -temptrans -usedef

SPLINTFLAGS = +posixlib +standard -mustfreeonly -likelybool \
			  -temptrans -nullstate -mustdefine -compdef -compdestroy \
			  -dependenttrans -noeffect
## -warnposix -preproc 
INCLUDEPATHS =-I$(INCLUDE_DIR)

####################################################################
# Create build and ouput directory								   #
####################################################################
$(OBJ_DIR):
	mkdir -p $(OUT_DIR)
	mkdir -p $(OBJ_DIR)
	@echo "Created build directory."

$(EXE_DIR):
	mkdir -p $(EXE_DIR)
	@echo "Created executable directory."

####################################################################
# Build instructions			 								   #
####################################################################
all: $(OBJ_DIR) $(EXE_DIR) $(EXE_DIR)/stencil_code_main 

$(EXE_DIR)/stencil_code_main: $(OBJ_DIR)/stencil_code_main.o
	g++ $(OBJ_DIR)/stencil_code_main.o -o $(EXE_DIR)/stencil_code_main

$(OBJ_DIR)/stencil_code_main.o: $(SRC_DIR)/stencil_code_main.cpp
	g++ $(FLAGS) $(INCLUDEPATHS) -o $(OBJ_DIR)/stencil_code_main.o $(SRC_DIR)/stencil_code_main.cpp

dox:
	mkdir -p $(DOX_DIR)
	@echo "Created doxygen directory."

	doxygen ./doc/client-server.dox

splint:
	splint $(SPLINTFLAGS) $(INCLUDEPATHS) $(SRC_DIR)/main.c
	splint $(SPLINTFLAGS) $(INCLUDEPATHS) $(SRC_DIR)/opt.c

clean:
	rm -rf $(OBJ_DIR) $(DOX_DIR) $(EXE_DIR) $(OUT_DIR)
