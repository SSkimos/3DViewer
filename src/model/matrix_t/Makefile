CC = gcc

WARNING    = -Wall -Werror -Wextra
CFLAGS     = -std=c11 -pedantic $(WARNING)
LFLAGS    ?= $(shell pkg-config --cflags --libs check)
INC_CHECK ?= $(shell pkg-config --cflags check)

SRC_DIR  = .
SRC     := $(shell find $(SRC_DIR) -name "s21*.c" | sed -e 's/\.\///')

TEST_DIR    = tests
TEST_FLAGS := --coverage -c -g
INC_DIRS   := $(shell find $(SRC_DIR) -type d)
INC_FLAGS  := $(addprefix -I, $(INC_DIRS))

BUILD_DIR       = obj
BUILD_TEST_DIR  = obj_test
GCOV_OBJ_DIR   := gcov_res

OBJS      := $(SRC:%.c=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST:%.c=$(BUILD_TEST_DIR)/%.o)
GCOV_OBJS := $(SRC:%.c=$(GCOV_OBJ_DIR)/%.o)

DEC_TEST := matrix_test.c
LIB      := s21_matrix.a


all: $(LIB)

$(LIB): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rc $(LIB) $(OBJS)
	ranlib $(LIB)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean rebuild lint test
clean: 
	rm -f *.gcda *.gcov *.o *.gcno
	rm -f $(LIB)
	rm -rf $(BUILD_DIR)
	rm -rf $(BUILD_TEST_DIR)
	rm -rf $(GCOV_OBJ_DIR)
	rm -f test.out

