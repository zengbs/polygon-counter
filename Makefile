MACRO := -DCGAL_NO_GMP=1 -DCGAL_DISABLE_ROUNDING_MATH_CHECK=ON


CC   := g++

CC_FLAGS      = -pthread -g -Wall -lm --std=c++1z   -O3 #-frounding-math
CC_DEBUG_FLAG = -g -Wall


INC := -I/home/rocky/softwares/cgal/default/include
LIB :=


EXECUTABLE := a.out


## source files
CC_FILE =  main.cpp rotation.cpp insertion.cpp validate.cpp deletion.cpp utilities.cpp \
          sweep_line_algorithm.cpp rectangles_generation.cpp naive.cpp  \
          segregate.cpp timer.cpp pixelization.cpp generate_simple_polygons.cpp \
          test_polygons.cpp naivePolygons.cpp

SRC_PATH = src

CC_SRC = $(patsubst %,$(SRC_PATH)/%,$(CC_FILE))

## object files
CC_OBJ_FILE = $(CC_FILE:.cpp=.o)
OBJ_PATH    = objective
CC_OBJ      = $(patsubst %,$(OBJ_PATH)/%,$(CC_OBJ_FILE))


# header files
HEADER_FILE = macro.h prototypes.h typedef.h intervaltree.h global.h
INC_PATH    = includes
HEADER      = $(patsubst %,$(INC_PATH)/%,$(HEADER_FILE))

CC_ALL_FLAG   = $(CC_DEBUG_FLAG)  $(INC) $(CC_FLAGS) $(MACRO)
CUDA_ALL_FLAG = $(INC) $(CUDA_FLAGS) $(MACRO)

# Compiling
$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp $(HEADER)
	$(CC) $(CC_ALL_FLAG) -o $@ -c $<


# Linking
$(EXECUTABLE): $(CC_OBJ) $(CUDA_OBJ)
	g++ -o $@ $^  $(LIB)  -lm -pthread -frounding-math
	mv $(EXECUTABLE) bin/

.PHONY:
clean:
	@rm -rf ${OBJ_PATH}/*.o rm ${EXECUTABLE}

