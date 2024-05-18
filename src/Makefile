CC=g++ -std=c++17
# CFLAGS_FOR_FUNC=-g
CFLAGS_FOR_FUNC=-g -Wall -Wextra -Werror 
ADD_CFLAGS=-g
# ADD_CFLAGS=-g -Wno-unused-parameter
# LIBS=-lgtest -lpthread -lrt -lm
LIBS=-lgtest -lpthread -lm
SOURCES= s21_smartcalc.cpp s21_credit.cpp s21_deposit.cpp
OBJECTS=$(SOURCES:.cpp=.o)
PATH-TO-QT=s21_Smart_CalcApp/s21_Smart_Calc/
GCOV_TEST = gcov_test
GCOV_DIR = report
TEST_TARGET = s21_smartcalc_test
# OS = $(uname)
OS=$(shell uname)

EXECUTABLE=test


all: $(EXECUTABLE)

install:
	rm -rf temp
	rm -rf ../../s21_SmartCalcApp
	mkdir temp
	cd temp; qmake ../s21_Smart_CalcApp/s21_Smart_Calc/s21_SmartCalc.pro
	cd temp; make
	cd temp; make clean
	mkdir ../../s21_SmartCalcApp
ifeq ($(OS), Darwin)
	cp temp/s21_SmartCalc.app/Contents/MacOS/s21_SmartCalc ../../s21_SmartCalcApp/s21_SmartCalc
else
	cp temp/s21_SmartCalc ../../s21_SmartCalcApp/s21_SmartCalc
endif
	rm -rf temp
	../../s21_SmartCalcApp/s21_SmartCalc

uninstall:
	rm -rf temp
	rm -rf ../../s21_SmartCalcApp

dist:
	rm -rf ../../s21_SmartCalcApp-tar
	mkdir ../../s21_SmartCalcApp-tar
	tar -cf ../../s21_SmartCalcApp-tar/s21_SmartCalc_v1.0.tar Makefile $(PATH-TO-QT)*.*

dvi:
	rm -rf ../../s21_SmartCalcPdf
	mkdir ../../s21_SmartCalcPdf
# texi2pdf s21_smartCalc.tex
	cp s21_smartCalc.pdf ../../s21_SmartCalcPdf/s21_smartCalc.pdf


doit_for_smartcalc:$(SOURCES) s21_smartcalc.h
	$(foreach var,$(SOURCES), $(CC) $(CFLAGS_FOR_FUNC) -c $(var);)


s21_smartcalc.a: doit_for_smartcalc
	ar rcs s21_smartcalc.a $(OBJECTS)
	cp s21_smartcalc.a libs21_smartcalc.a
	rm lib*.a *.o

test: s21_smartcalc_test
	rm *.o
	./s21_smartcalc_test

mem_test: s21_smartcalc_test
	rm *.o
ifeq ($(OS), Darwin)
	CK_FORK=no leaks -atExit -- ./$(TEST_TARGET)
else
	valgrind --tool=memcheck --undef-value-errors=no ./$(TEST_TARGET)
endif

s21_smartcalc_test: s21_smartcalc.a s21_smartcalc_test.o
	$(CC) -o s21_smartcalc_test  s21_smartcalc_test.o s21_smartcalc.a $(LIBS)

s21_smartcalc_test.o: s21_smartcalc_test.cpp s21_smartcalc.h
	$(CC) $(CFLAGS) -c s21_smartcalc_test.cpp  $(LIBS)

gcov_report: 
ifeq ($(OS), Darwin)
	$(CC) $(ADD_CFLAGS) --coverage s21_smartcalc_test.cpp $(SOURCES) -o s21_smartcalc_test $(LIBS)
	./s21_smartcalc_test
	lcov -t "s21_smartcalc_test" -o s21_smartcalc_test.info -c -d .
	lcov -r s21_smartcalc_test.info "/usr*" -o s21_smartcalc_test.info
	genhtml -o report s21_smartcalc_test.info
	open ./report/index.html
	rm -rf *.gcda *.gcno s21_smartcalc_test s21_smartcalc_test.info
else
	$(CC) $(ADD_CFLAGS) --coverage s21_smartcalc_test.cpp $(SOURCES) -o s21_smartcalc_test $(LIBS)
	./s21_smartcalc_test
	lcov -t "s21_smartcalc_test" -o s21_smartcalc_test.info -c -d .
	lcov -r s21_smartcalc_test.info "/usr*" -o s21_smartcalc_test.info 
	genhtml -o report s21_smartcalc_test.info
	xdg-open ./report/index.html
	open ./report/index.html
	rm -rf *.gcda *.gcno s21_smartcalc_test s21_smartcalc_test.info
endif

clean_all: clean clean_gcov

clean:
	rm *.o

clean_gcov:
	rm -rf ./*.gcda ./*.gcno ./*.info ./$(GCOV_TEST) ./$(GCOV_DIR)

check:
	clang-format -n ./*.cpp *.h
	cppcheck --enable=all --suppress=missingIncludeSystem\
	 --suppress=knownConditionTrueFalse --suppress=constParameter\
	 --suppress=constVariable --suppress=unusedStructMember\
	  --suppress=variableScope --language=c++ *.h *.cpp