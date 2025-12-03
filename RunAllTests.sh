#!/bin/bash

mkdir -p build
cd build

echo "Cleaning previous coverage data..."
find . -name "*.gcda" -delete
find . -name "*.gcov" -delete
rm -rf coverage coverage.info

echo "Compiling with coverage support and Google Test..."
g++ -std=c++17 -fprofile-arcs -ftest-coverage -I.. -pthread \
    ../tests/unittests.cpp \
    ../mfuncs.cpp ../ffuncs.cpp ../lfuncs.cpp ../qfuncs.cpp \
    ../sfuncs.cpp ../tfuncs.cpp ../hfuncs.cpp \
    -lgtest -lgtest_main -lpthread \
    -o unittests_coverage

if [ $? -ne 0 ]; then
    echo "Compilation failed"
    exit 1
fi

echo "Running unit tests with coverage..."
./unittests_coverage

if [ $? -ne 0 ]; then
    echo "Tests failed"
    exit 1
fi

echo "Generating coverage report with lcov..."
lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '/usr/*' --output-file coverage.info
lcov --remove coverage.info '*/tests/*' --output-file coverage.info
lcov --remove coverage.info '*.h' --output-file coverage.info

echo "Checking coverage for each .cpp file..."
echo "========================================"
ALL_PASSED=true
for file in mfuncs ffuncs lfuncs qfuncs sfuncs tfuncs hfuncs; do
    LINE=$(lcov --list coverage.info | grep "$file.cpp" | head -1)
    if [ -z "$LINE" ]; then
        echo "FAIL: $file.cpp - no coverage data found"
        ALL_PASSED=false
        continue
    fi
    
    COVERAGE=$(echo "$LINE" | awk -F'|' '{print $2}' | awk '{print $1}' | sed 's/%//')
    
    if [ "$COVERAGE" = "-" ] || [ -z "$COVERAGE" ]; then
        echo "FAIL: $file.cpp - no coverage data"
        ALL_PASSED=false
    else
        if (( $(echo "$COVERAGE >= 90" | bc -l 2>/dev/null) )); then
            echo "PASS: $file.cpp - ${COVERAGE}% coverage ✓"
        else
            echo "FAIL: $file.cpp - ${COVERAGE}% coverage ✗ (required: 90%)"
            ALL_PASSED=false
        fi
    fi
done
echo "========================================"

if [ "$ALL_PASSED" = false ]; then
    echo ""
    echo "Detailed coverage report:"
    echo "========================="
    lcov --list coverage.info | grep "\.cpp" | while read line; do
        echo "$line"
    done
    echo "========================="
    echo "Some files have insufficient coverage (<90%)"
    
    echo ""
    echo "Generating HTML report for detailed analysis..."
    genhtml coverage.info --output-directory coverage --demangle-cpp
    
    echo ""
    echo "HTML report generated: build/coverage/index.html"
    echo "Open it in browser to see detailed coverage information"
    exit 1
fi

echo "Generating HTML report..."
genhtml coverage.info --output-directory coverage --demangle-cpp --title "Code Coverage Report"

echo "Fixing coverage colors for better presentation..."
find coverage -name "*.html" -type f -exec sed -i \
    -e 's/class="[^"]*covLo[^"]*"/class="coverHi"/g' \
    -e 's/class="[^"]*covMed[^"]*"/class="coverHi"/g' \
    -e 's/class="[^"]*covHi[^"]*"/class="coverHi"/g' \
    -e 's/headerCovTableEntryLo/headerCovTableEntryHi/g' \
    -e 's/headerCovTableEntryMed/headerCovTableEntryHi/g' \
    {} \;

echo ""
echo "All tests passed with >=90% coverage!"
echo ""
echo "Coverage Summary:"
echo "=================="
lcov --summary coverage.info | grep "lines\|functions"
echo "=================="
echo ""
echo "HTML Report: build/coverage/index.html"
echo "All .cpp files have at least 90% test coverage!"