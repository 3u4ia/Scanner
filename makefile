CC = g++ -g3
CFLAGS = -g3 -Wall
TARGET = P1

OBJS2 = P1.o

all: $(TARGET)
main: $(OBJS2)

$(TARGET): $(OBJS2)
	$(CC) -o $(TARGET) $(OBJS2)

$(OBJS2): P1.cpp
	$(CC) $(CFLAGS) -c P1.cpp -o $(OBJS2)

clean:
	/bin/rm -f *.o $(TARGET)
