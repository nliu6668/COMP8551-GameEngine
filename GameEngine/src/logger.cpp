#include "logger.h"
#include <iostream>

Logger::Logger() {
    file = ofstream(FILE_NAME, fstream::trunc | fstream::out);
}

Logger::~Logger() {
    file.close();
}

Logger& Logger::operator<<(string text) {
    file << text;
    return *this;
}

Logger& Logger::operator<<(int num) {
    file << num;
    return *this;
}

Logger& Logger::operator<<(float num) {
    file << num;
    return *this;
}

Logger& Logger::operator<<(double num) {
    file << num;
    return *this;
}

Logger& Logger::operator<<(char c) {
    file << c;
    return *this;
}