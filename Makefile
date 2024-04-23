# archivitos .o
OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, main.o utils.o)

# ejecutable principal
BUILD_DIR = build
BIN = $(BUILD_DIR)/shell

$(BIN): $(OBJS)
	gcc $^ -o $@ -lreadline

$(OBJ_DIR)/main.o: src/main.c
	gcc -c $^ -o $@	

$(OBJ_DIR)/utils.o: src/utils.c
	gcc -c $^ -o $@

clean:
	rm $(BIN)
	rm $(OBJS)

test: $(BIN)
	# sacamos el valgrind
	valgrind --leak-check=full ./$(BIN)
