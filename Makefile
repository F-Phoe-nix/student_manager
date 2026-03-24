CC = gcc
CFLAGS = -Wall -g

TARGET = student_manager

SRCS = main.c student.c interface.c file_ops.c utils.c

OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(TARGET)

#Linking object files into executables
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

#Compiling source into object files
%.o: %.c student.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean