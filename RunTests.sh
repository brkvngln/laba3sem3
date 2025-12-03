#!/bin/bash

echo "=== Running Go Tests with Coverage ==="

# Запускаем тесты для всех пакетов
go test -coverprofile=coverage.out -covermode=atomic ./structures/...

go tool cover -html=coverage.out -o coverage.html

echo ""
echo "=== Coverage Summary ==="
go tool cover -func=coverage.out

echo ""
echo "=== Checking Coverage Threshold ==="
COVERAGE_LINE=$(go tool cover -func=coverage.out | grep total)
COVERAGE=$(echo "$COVERAGE_LINE" | awk '{print $3}' | sed 's/%//')
echo "Total Coverage: $COVERAGE%"

if (( ${COVERAGE%.*} >= 90 )); then
    echo "✓ Coverage meets requirement (90%)"
else
    echo "✗ Coverage below requirement (90%)"
    exit 1
fi

echo ""
echo "HTML report generated: coverage.html"
echo "To view: open coverage.html"