#!/bin/bash

echo "=== Сборка проекта структур данных ==="

# Создаем папку для сборки
mkdir -p build
cd build

# Проверяем наличие CMake
if command -v cmake &> /dev/null; then
    echo "Используется CMake для сборки..."
    cmake ..
    make -j4
    
    if [ $? -eq 0 ]; then
        echo ""
        echo "=== Сборка успешно завершена ==="
        echo "Исполняемые файлы находятся в папке build/bin/"
        echo ""
        echo "Для запуска основного приложения: ./bin/main_app"
        echo "Для запуска тестов: ./bin/unit_tests"
        echo "Для запуска бенчмарков: ./bin/benchmarks"
    else
        echo "Ошибка сборки с CMake"
        exit 1
    fi
else
    echo "CMake не найден, используется прямой компилятор..."
    
    # Компиляция основной программы
    g++ -std=c++17 -I.. ../main.cpp ../mfuncs.cpp ../ffuncs.cpp ../lfuncs.cpp ../qfuncs.cpp ../sfuncs.cpp ../tfuncs.cpp ../hfuncs.cpp -o bin/main_app
    
    # Компиляция тестов
    g++ -std=c++17 -I.. ../tests/unit_tests.cpp ../mfuncs.cpp ../ffuncs.cpp ../lfuncs.cpp ../qfuncs.cpp ../sfuncs.cpp ../tfuncs.cpp ../hfuncs.cpp -o bin/unit_tests
    
    # Компиляция бенчмарков
    g++ -std=c++17 -I.. ../tests/benchmarks.cpp ../mfuncs.cpp ../ffuncs.cpp ../lfuncs.cpp ../qfuncs.cpp ../sfuncs.cpp ../tfuncs.cpp ../hfuncs.cpp -o bin/benchmarks
    
    if [ $? -eq 0 ]; then
        echo ""
        echo "=== Сборка успешно завершена ==="
        echo "Исполняемые файлы находятся в папке bin/"
        echo ""
        echo "Для запуска основного приложения: ./bin/main_app"
        echo "Для запуска тестов: ./bin/unit_tests"
        echo "Для запуска бенчмарков: ./bin/benchmarks"
    else
        echo "Ошибка сборки"
        exit 1
    fi
fi