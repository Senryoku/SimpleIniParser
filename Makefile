C = g++
OPT = -Wall -pedantic -std=c++11
OBJ = obj/
SRC = src/
BIN = bin/
EXEC = IniTest
LIBS =

all : IniTest

$(OBJ)IniFile.o : $(SRC)IniFile.cpp
	$(C) $(OPT) $^ -c -o $@

$(OBJ)IniTest.o : $(SRC)IniTest.cpp
	$(C) $(OPT) $^ -c -o $@
	
$(EXEC) : $(OBJ)IniFile.o $(OBJ)IniTest.o
	$(C) $^ -o $(BIN)$@ $(LIBS)
	
debug : debug_option all

debug_option :
OPT = -Wall -pedantic -g -std=c++11

run : $(EXEC)
	./$(BIN)$(EXEC)

clean:
	/bin/rm -rf $(OBJ)*.o $(BIN)*	
.PHONY : clean

doc:
	doxygen
.PHONY : doc
