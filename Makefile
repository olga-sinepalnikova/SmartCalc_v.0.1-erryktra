CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
TARGET = s21_smartcalc.a

# подбирает флаги для check в зависимости от системы (мак или линукс)
OS = $(shell uname -s)
ifeq ($(OS), Darwin)
CHECK_FLAGS = -lcheck
OPEN_COMMAND = open
APP = build/frontend.app 
else ifeq ($(OS), Linux)
CHECK_FLAGS = -lcheck -lsubunit -lpthread -lrt -lm
OPEN_COMMAND = less
APP = build/frontend
endif

$(TARGET):
	$(CC) $(FLAGS) -c -g backend/*.c
	ar rcs $(TARGET) *.o
# ranlib $(TARGET)

all: dvi rebuild test gcov_report install run clang_format_check

install: build
	@mkdir $(HOME)/Desktop/SmartCalc_v1.0/
	@cp -rf $(APP) $(HOME)/Desktop/SmartCalc_v1.0/
	make clean

uninstall: clean
	@rm -rf $(HOME)/Desktop/SmartCalc_v1.0/

clean:
	rm -rf build/
	rm -rf *.o *.a *.gch *.gcno *.gcda report/ s21_test.info *.dSYM/ *.out *.log

build:
	mkdir build
	cd ./build/ && qmake ../frontend/ && make

rebuild: clean build

dist:
	mkdir SmartCalc_v1.0/
	mkdir SmartCalc_v1.0/src
	cp Makefile *.c *.h *.pro *.cpp *.ui *.user SmartCalc_v1.0/src/
	tar cvzf SmartCalc_v1.0.tgz SmartCalc_v1.0/
	mv SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf SmartCalc_v1.0/

test: clean $(TARGET)
	$(CC) -g --coverage tests/main.c $(TARGET) $(FLAGS) -o run_tests.out $(CHECK_FLAGS)
	./run_tests.out

gcov_report:
	gcc tests/main.c backend/*.c -o gcov_test --coverage $(CHECK_FLAGS) -lm
	./gcov_test
	lcov -t "stest" -o s21_test.info -c -d .
	genhtml -o report/ s21_test.info
	open ./report/index.html
	rm -rf gcov_test

dvi:
	$(OPEN_COMMAND) README.md

style:
	cp ../materials/linters/.clang-format .
	clang-format -style=Google -i *.c backend/*.c
	clang-format -style=Google -i *.h
	rm -rf .clang-format

check:
	gcc -g s21*.c test.c -o test

valgrind: test
	valgrind --show-reachable=no --trace-children=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --log-file=valgrind.log  ./run_tests.out

leaks: test
	leaks -atExit -- ./run_tests.o > leak_report.txt
