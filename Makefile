C = g++
OPT = -Wall -pedantic
OBJ = obj/
SRC = src/
BIN = bin/
LIBS = -lsfml-window -lsfml-system

all : IniTest

$(OBJ)IniFile.o : $(SRC)IniFile.cpp
	$(C) $(OPT) $^ -c -o $@

$(OBJ)IniTest.o : $(SRC)IniTest.cpp
	$(C) $(OPT) $^ -c -o $@
	
IniTest : $(OBJ)IniFile.o $(OBJ)IniTest.o
	$(C) $^ -o $(BIN)$@ $(LIBS)
	
debug : debug_option all

debug_option :
OPT = -Wall -pedantic -g 

run :
	./$(EXEC)

clean:
	/bin/rm -rf $(OBJ)*.o $(BIN)*
