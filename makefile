CC = g++ -g3
CFLAGS = -g3 -Wall
TARGET = P1

OBJS1 = P1.o
OBJS2 = Scanner.o

CLSFLDR = ScannerClass


all: $(TARGET)
main: $(OBJS1)

$(TARGET): $(OBJS1) $(CLSFLDR)/$(OBJS2)
	$(CC) -o $(TARGET) $(OBJS1) ScannerClass/$(OBJS2)

$(OBJS1): P1.cpp $(CLSFLDR)/Scanner.h
	$(CC) $(CFLAGS) -c P1.cpp -o $(OBJS1)

$(OBJS2): $(CLSFLDR)/Scanner.cpp $(CLSFLDR)/Scanner.h
	$(CC) $(CFLAGS) -c $(CLSFLDR)/Scanner.cpp -o $(CLSFLDR)/$(OBJS2)

clean:
	/bin/rm -f *.o ./ScannerClass/*.o $(TARGET)
