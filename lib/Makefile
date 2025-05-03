CC = gcc
CFLAGS = -Wall -Wextra -I./src

SRCDIR = src
SRC = $(SRCDIR)/main.c $(SRCDIR)/linA.c
OBJ = $(SRC:.c=.o)

TARGET = main

all: $(TARGET)

# Link objs together
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# c -> o
$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(SRCDIR)/*.o $(TARGET)
