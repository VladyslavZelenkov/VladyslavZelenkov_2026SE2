#pragma once
#include <string>
#include <cstring>
#include <cctype>
#include <vector>
#include <stdexcept>

class StringCalculator {
public:
    int Calculate(const char* arg) {
        if (arg == nullptr || arg[0] == '\0') return 0;

        char buffer[1024];
        strncpy_s(buffer, arg, sizeof(buffer) - 1);
        buffer[sizeof(buffer) - 1] = '\0';

        std::string delimiter = ",";
        char* startPtr = buffer;
        char* context = nullptr;

        if (buffer[0] == '\\' && buffer[1] == '\\') {
            char* p = buffer + 2;
            while (*p && !std::isdigit(static_cast<unsigned char>(*p)) && *p != '-' && *p != '+') {
                p++;
            }
            size_t length = static_cast<size_t>(p - (buffer + 2));
            if (length > 0) {
                delimiter = std::string(buffer + 2, length);
                startPtr = p; 
            }
        }

        int sum = 0;
        std::vector<int> negativeNumbers;
        bool foundAnyNumber = false;

        char* ptr = strtok_s(startPtr, delimiter.c_str(), &context);

        while (ptr != nullptr) {
            if (strlen(ptr) > 0) {
                char* endPtr;
                int num = static_cast<int>(std::strtol(ptr, &endPtr, 10));

                if (*endPtr != '\0') {
                    throw std::invalid_argument("Invalid input");
                }

                foundAnyNumber = true;

                if (num < 0) {
                    negativeNumbers.push_back(num);
                }
                else if (num <= 1000) {
                    sum += num;
                }
            }

            ptr = strtok_s(nullptr, delimiter.c_str(), &context);
        }

        if (!foundAnyNumber) {
            throw std::invalid_argument("Invalid input");
        }

        if (!negativeNumbers.empty()) {
            throw std::runtime_error("Negatives not allowed");
        }

        return sum;
    }
};// Test direct push
