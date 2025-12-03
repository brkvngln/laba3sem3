CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -I.
SOURCES = mfuncs.cpp ffuncs.cpp lfuncs.cpp qfuncs.cpp sfuncs.cpp tfuncs.cpp

.PHONY: all test clean

all: bin/main_app

bin/main_app: main.cpp $(SOURCES) | bin
	$(CXX) $(CXXFLAGS) -o bin/main_app main.cpp $(SOURCES)

bin/unit_tests: tests/unit_tests.cpp $(SOURCES) | bin
	$(CXX) $(CXXFLAGS) -o bin/unit_tests tests/unit_tests.cpp $(SOURCES)

test: bin/unit_tests
	@echo "=== ЗАПУСК ЮНИТ-ТЕСТОВ ==="
	./bin/unit_tests

run: bin/main_app
	./bin/main_app

clean:
	rm -rf bin

bin:
	mkdir -p bin

help:
	@echo "Команды:"
	@echo "  make test  - собрать и запустить юнит-тесты"
	@echo "  make run   - собрать и запустить основное приложение"
	@echo "  make clean - очистить сборочные файлы"