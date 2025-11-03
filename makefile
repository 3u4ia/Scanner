CC = g++ -g3
CFLAGS = -g3 -Wall
TARGET = P1

OBJS1 = P1.o
OBJS2 = Scanner.o
OBJS3 = TokensAndStates.o

CLSFLDR = ScannerClass


all: $(TARGET)
main: $(OBJS1)

$(TARGET): $(OBJS1) $(CLSFLDR)/$(OBJS2) $(OBJS3)
	$(CC) -o $(TARGET) $(OBJS1) ScannerClass/$(OBJS2) $(OBJS3)

$(OBJS1): P1.cpp $(CLSFLDR)/Scanner.h TokensAndStates.h
	$(CC) $(CFLAGS) -c P1.cpp -o $(OBJS1)

$(OBJS2): $(CLSFLDR)/Scanner.cpp $(CLSFLDR)/Scanner.h TokensAndStates.h
	$(CC) $(CFLAGS) -c $(CLSFLDR)/Scanner.cpp -o $(CLSFLDR)/$(OBJS2)

$(OBJS3): TokensAndStates.cpp TokensAndStates.h
	$(CC) $(CFLAGS) -c TokensAndStates.cpp -o $(OBJS3)

clean:
	/bin/rm -f *.o ./ScannerClass/*.o $(TARGET)
