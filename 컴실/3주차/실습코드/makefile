OBJECT = main.o array.o rangearray.o
SRC = main.cpp array.cpp rangearray.cpp

CC = g++
CXXFLAG = -c

TARGET = main

$(TARGET):$(OBJECT)
				$(CC) -o $(TARGET) $(OBJECT)

clean:
		rm $(OBJECT) $(TARGET)


main.o : Array.h RangeArray.h main.cpp
array.o : Array.h array.cpp
rangearray.o : RangeArray.h Array.h rangearray.cpp
