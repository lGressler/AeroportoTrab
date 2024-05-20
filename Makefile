CC = gcc
CFLAGS = -Wall -Iinclude -g
SRC = src
OBJ = obj
BIN = bin

OBJS = $(OBJ)/aeroporto.o $(OBJ)/aviao.o $(OBJ)/fila.o $(OBJ)/lista_avioes.o $(OBJ)/operacao.o $(OBJ)/main.o
TARGET = $(BIN)/EDAero

all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

$(OBJ)/%.o: $(SRC)/%.c
	@mkdir -p $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ) $(BIN)

.PHONY: all clean