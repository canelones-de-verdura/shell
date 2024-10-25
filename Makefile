# compilador
CC = gcc

# archivitos .o
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, main.o utils.o exec.o cd.o exit.o help.o pwd.o)

# ejecutable principal
BUILD_DIR = build
BIN = $(BUILD_DIR)/shell

$(BIN): $(OBJS)
	$(CC) $^ -o $@ -lreadline -O3

$(OBJ_DIR)/main.o: src/main.c
	gcc -c $^ -o $@	-O3

$(OBJ_DIR)/utils.o: src/utils.c
	gcc -c $^ -o $@ -O3

$(OBJ_DIR)/exec.o: src/exec.c
	gcc -c $^ -o $@ -O3


$(OBJ_DIR)/cd.o: src/cd.c
	gcc -c $^ -o $@ -O3

$(OBJ_DIR)/exit.o: src/exit.c
	gcc -c $^ -o $@ -O3

$(OBJ_DIR)/help.o: src/help.c
	gcc -c $^ -o $@ -O3

$(OBJ_DIR)/pwd.o: src/pwd.c
	gcc -c $^ -o $@ -O3

clean:
	rm $(BIN)
	rm $(OBJS)

test: $(BIN)
	# sacamos el valgrind
	valgrind --leak-check=full ./$(BIN)
