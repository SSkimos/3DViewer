CC = gcc

WARNING    =  #-Wall -Werror -Wextra -Wuninitialized -g
CFLAGS     = -std=c11 -pedantic  $(WARNING) # -fsanitize=address
LFLAGS    ?= $(shell pkg-config --cflags --libs check)
INC_CHECK ?= $(shell pkg-config --cflags check)

SRC_DIR  = .
SRC     := $(shell find $(SRC_DIR) -name "s21*.c" | sed -e 's/\.\///')

TEST_DIR    = tests
TEST       := $(shell find $(TEST_DIR) -name "*.c" | sed -e 's/\.\///')
TEST_FLAGS := --coverage -c -g

INC_DIRS   := $(shell find $(SRC_DIR) -type d)
INC_FLAGS  := $(addprefix -I, $(INC_DIRS))

BUILD_DIR       = .o_files
BUILD_TEST_DIR  = .o_test
GCOV_OBJ_DIR   := gcov_res

OBJS      := $(SRC:%.c=$(BUILD_DIR)/%.o)
TEST_OBJS := $(TEST:%.c=$(BUILD_TEST_DIR)/%.o)
GCOV_OBJS := $(SRC:%.c=$(GCOV_OBJ_DIR)/%.o)

DEC_TEST := model_test.c
LIB      := libmodel.a

all: launch

test: test.out
	./test.out

tests: test.out
	./test.out

test.out: $(LIB) $(TEST_OBJS) $(BUILD_TEST_DIR)/main.o
	$(CC) $(CFLAGS) $(LFLAGS) $(TEST_OBJS) $(BUILD_TEST_DIR)/main.o $(LIB) -o test.out

gcov_report: $(TEST_OBJS) $(GCOV_OBJS) $(BUILD_TEST_DIR)/main.o $(SRC) test.out
	@mkdir -p $(GCOV_OBJ_DIR)
	ar rc $(LIB) $(GCOV_OBJS)
	ranlib $(LIB)
	$(CC) $(LFLAGS) --coverage $(TEST_OBJS) $(BUILD_TEST_DIR)/main.o $(LIB) -o test.out
	./test.out
	./../materials/lcov/bin/lcov -f -c --directory . -o ./gcov_res/coverage.info 
	./../materials/lcov/bin/genhtml gcov_res/coverage.info --output-directory=gcov_res
	open gcov_res/index.html


install: libmodel.a
	cmake -S . -B build
	make -C build/

launch: install
	./build/3DViewer.app/Contents/MacOS/3DViewer

uninstall:
	rm -rf build-app-Desktop_x86_darwin_generic_mach_o_64bit-Debug
	rm -rf view/CMakeLists.txt.user
	rm -rf CMakeFiles
	rm -rf build/*

clean: 
	rm -f *.gcda *.gcov *.o *.gcno
	rm -f $(LIB)
	rm -rf $(BUILD_DIR)
	rm -rf $(BUILD_TEST_DIR)
	rm -rf $(GCOV_OBJ_DIR)
	rm -f test.out

dvi:
	open ../README_RUS.md

dist: install
	tar -czf s21_3DViewer.tar.gz --directory=build/ .

leaks: test.out
	leaks -atExit -- ./test.out

rebuild: clean all

$(LIB): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	ar rc $(LIB) $(OBJS)
	ranlib $(LIB)

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_TEST_DIR)/main.o: $(DEC_TEST) 
	@mkdir -p $(BUILD_TEST_DIR)
	$(CC) $(CFLAGS) $(INC_CHECK) -c -o $(BUILD_TEST_DIR)/main.o $(DEC_TEST)

$(BUILD_TEST_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC)  $(INC_CHECK) -c $^ -o $@

$(GCOV_OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(TEST_FLAGS) -c $< -o $@

lint:
	-cp ../materials/linters/.clang-format .
	-find . -type f -name "*.c" | xargs clang-format --style=Google -n
	-find . -type f -name "*.h" | xargs clang-format --style=Google -n
	-find . -type f -name "*.c" | xargs cppcheck --enable=all --suppress=missingIncludeSystem

flint: lint
	-find . -type f -name "*.c" | xargs clang-format --style=Google -i
	-find . -type f -name "*.h" | xargs clang-format --style=Google -i

