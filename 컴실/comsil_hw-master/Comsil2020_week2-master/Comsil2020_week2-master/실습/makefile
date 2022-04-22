OBJECTS = main.o Output.o String_Manipulation.o
SRC = main.cpp Output.cpp String_Manipulation.cpp

CC = g++
CFLAGS = -g -c


TARGET= main
$(TARGET): $(OBJECTS) Header.h
			$(CC) -o $(TARGET) $(OBJECTS)

.PHONY: clean

clean: 
	rm $(OBJECTS) $(TARGET)
