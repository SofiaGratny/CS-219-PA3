
# modify this makefile based on your requirement

OUTPUT = proj3
INCLIB= #write your header file if you have any
SOURCE = main.cpp #write your .cpp file name
all: $(OUTPUT)


$(OUTPUT): $(OUTPUT).o
	g++ -o $@ $@.o -std=c++11
	


$(OUTPUT).o: $(SOURCE) $(INCLIB)
	g++ -c $< -std=c++11 -o $@

