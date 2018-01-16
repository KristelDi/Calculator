PROGRAM_NAME = runCalculator

CXX = g++
CXX_FLAGS = -std=c++11

DIRS	=	./ ./src 

SOURCES = main.cpp ./src/calculator.cpp 

OBJ=$(SOURCES:.cpp=.o)


all: $(SOURCES) $(PROGRAM_NAME)

$(PROGRAM_NAME) : $(OBJ) 
	$(CXX) $(CXX_FLAGS) $(OBJ) -o $@

.cpp.o:
	$(CXX) $(CXX_FLAGS) -c $< -o $@


clean: 
	@for dir in $(DIRS) ;\
		do \
		echo cleaning $$dir ;\
		(cd $$dir;  rm -rf *.a *.o *.mod *.ex* *core* out* ./extras/core* \#*  *~) ;\
		done
