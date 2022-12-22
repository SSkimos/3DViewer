CC=gcc 
SRC=#back/stack.c back/polish.c back/parser.c back/credit.c
OBJ=#back/stack.o back/polish.o back/parser.o back/credit.o
SRC_T=#back/tests/s21_calc_tests.c
OBJ_T=#back/tests/s21_calc_tests.o
CFLAGS=--coverage $(shell pkg-config --cflags --libs check)

all: tests install

gcov_report: tests
	lcov -t "otchet" -o otchet.info -c -d ./back
	genhtml -o report otchet.info

tests: lib.a $(OBJ_T) $(OBJ)
	$(CC) $(CFLAGS) lib.a $(OBJ_T) $(OBJ) $(TESTFLAGS) -o test
	./test

lib.a: $(OBJ)
	ar rcs lib.a $(OBJ)

install:
	mkdir -p build
	cd ./build; cmake ../view/CMakeLists.txt; make
	./build/test_calc.app/Contents/MacOS/test_calc

uninstall:
	rm -rf build-app-Desktop_x86_darwin_generic_mach_o_64bit-Debug
	rm -rf view/CMakeLists.txt.user
	rm -rf CMakeFiles
	rm -rf build/*

clean:
	rm -rf back/*.o
	rm -rf back/tests/*.o
	rm -rf back/tests/*.gc*
	rm -rf back/*.gc*
	rm -rf back/*.a
	rm -f test
	rm -rf a.out *.a
	rm -rf report/*
	rm -rf otchet.info
	rm -rf build/.*
dvi:
	open ../README_RUS.md
dist:
	tar -cvf archive.tar ../src
