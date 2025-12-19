CC ?= clang
CFLAGS ?= -Os
TARGET := bone
SRC := bone.c
HEADERS := bone.h

.PHONY: all run clean

all: $(TARGET)

run: all
	./bone

$(TARGET): bone.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.o $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) *.o
