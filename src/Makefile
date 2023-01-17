CC=gcc 
SRC=#back/stack.c back/polish.c back/parser.c back/credit.c
OBJ= s21_affin_p.o s21_parse_obj.o
SRC_T=#back/tests/s21_calc_tests.c
OBJ_T=#back/tests/s21_calc_tests.o
CFLAGS=

all: install


.PHONY:matrix_t
matrix_t:
	$(MAKE) -C model/matrix_t

matrix_t_clean:
	$(MAKE) -C model/matrix_t clean

# tests: lib.a $(OBJ_T) $(OBJ)
# 	$(CC) $(CFLAGS) lib.a $(OBJ_T) $(OBJ) $(TESTFLAGS) -o test
# 	./test

libmodel.a: model/s21_parse_obj.c model/s21_affin_p.c matrix_t
	cc -c model/s21_parse_obj.c model/s21_affin_p.c
	ar rcs libmodel.a s21_parse_obj.o s21_affin_p.o
	ranlib libmodel.a

install: libmodel.a
	cmake -S . -B build
	make -C build/
	./build/3DViewer.app/Contents/MacOS/3DViewer

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

