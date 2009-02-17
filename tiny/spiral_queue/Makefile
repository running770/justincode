SOURCES := $(shell echo *.c)
OBJECTS := $(SOURCES:%.c=%.o)
TARGET := jmain

CC:=gcc
CFLAGS += -Wall -I .
CXXFLAGS := -Wall -I.

.PHONY:all clean run

all:$(TARGET)

$(TARGET):$(OBJECTS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS)

run:
	./jmain.exe
