COMPILER = g++
COMPILER_FLAGS = -c -g -O0 -std=c++0x 
LINKER = g++
LINKER_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system 
WORKING_DIR = ../

demo1 : demo1.o
	$(LINKER) demo1.o engine.o $(LINKER_FLAGS)
	rm -rf demo1
	mkdir demo1
	mv a.out demo1/demo1
	cp -ra ../rc/demo1/img demo1/img
	cp -ra ../rc/demo1/fnt demo1/fnt
	rm -f *.o
demo1.o : engine.o 
	$(COMPILER) $(COMPILER_FLAGS) $(WORKING_DIR)demo1.cpp
engine.o :
	$(COMPILER) $(COMPILER_FLAGS) $(WORKING_DIR)engine.cpp
clean:
	rm -f *.o
	rm -rf demo1
