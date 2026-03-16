CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lsqlite3

TARGET = student_manager

SRCS = main.c student.c interface.c db.c utils.c

OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(TARGET)

#Linking object files into executables
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LDFLAGS)

#Compiling source into object files
%.o: %.c student.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean