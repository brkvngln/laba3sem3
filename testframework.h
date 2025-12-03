#ifndef TESTFRAMEWORK_H
#define TESTFRAMEWORK_H

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

class TestCase {
private:
    std::string name;
    bool passed;
    std::string error_message;

public:
    TestCase(const std::string& test_name) : name(test_name), passed(true) {}
    virtual ~TestCase() = default;
    
    virtual void run() = 0;
    
    void assertTrue(bool condition, const std::string& message = "Ошибка проверки") {
        if (!condition) {
            passed = false;
            error_message = message;
            throw std::runtime_error(message);
        }
    }
    
    void assertEquals(int expected, int actual, const std::string& message = "") {
        if (expected != actual) {
            passed = false;
            error_message = message + " (ожидалось: " + std::to_string(expected) + 
                          ", получено: " + std::to_string(actual) + ")";
            throw std::runtime_error(error_message);
        }
    }
    
    void assertEquals(const std::string& expected, const std::string& actual, const std::string& message = "") {
        if (expected != actual) {
            passed = false;
            error_message = message + " (ожидалось: " + expected + ", получено: " + actual + ")";
            throw std::runtime_error(error_message);
        }
    }
    
    void assertNull(const void* ptr, const std::string& message = "Указатель не нулевой") {
        if (ptr != nullptr) {
            passed = false;
            error_message = message;
            throw std::runtime_error(message);
        }
    }
    
    void assertNotNull(const void* ptr, const std::string& message = "Указатель нулевой") {
        if (ptr == nullptr) {
            passed = false;
            error_message = message;
            throw std::runtime_error(message);
        }
    }
    
    bool hasPassed() const { return passed; }
    std::string getName() const { return name; }
    std::string getErrorMessage() const { return error_message; }
};

class TestRunner {
private:
    std::vector<TestCase*> test_cases;
    int passed_count;
    int failed_count;

public:
    TestRunner() : passed_count(0), failed_count(0) {}
    
    void addTest(TestCase* test_case) {
        test_cases.push_back(test_case);
    }
    
    void runAllTests() {
        std::cout << "Запуск " << test_cases.size() << " тестов...\n" << std::endl;
        
        for (auto test_case : test_cases) {
            std::cout << "ТЕСТ: " << test_case->getName() << " ... ";
            try {
                test_case->run();
                std::cout << "УСПЕХ" << std::endl;
                passed_count++;
            } catch (const std::exception& e) {
                std::cout << "ПРОВАЛ" << std::endl;
                std::cout << "  Ошибка: " << e.what() << std::endl;
                failed_count++;
            }
        }
        
        std::cout << "\n=== РЕЗУЛЬТАТЫ ТЕСТИРОВАНИЯ ===" << std::endl;
        std::cout << "Всего:  " << test_cases.size() << std::endl;
        std::cout << "Успешно: " << passed_count << std::endl;
        std::cout << "Провалено: " << failed_count << std::endl;
        if (test_cases.size() > 0) {
            std::cout << "Успешность: " << (passed_count * 100 / test_cases.size()) << "%" << std::endl;
        }
    }
    
    ~TestRunner() {
        for (auto test_case : test_cases) {
            delete test_case;
        }
    }
};

#endif