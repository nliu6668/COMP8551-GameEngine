#include "logger.h"
#include <iostream>

Logger::Logger() {
    file = ofstream(FILE_NAME, fstream::trunc | fstream::out);
    cout << "Logger initialized" << endl;
}

Logger::~Logger() {
    file.close();
}

Logger& Logger::operator<<(string text) {
    file << text;
    cout << "string" << endl;
    return *this;
}

Logger& Logger::operator<<(int num) {
    file << num;
    cout << "int" << endl;
    return *this;
}

Logger& Logger::operator<<(float num) {
    file << num;
    cout << "float" << endl;
    return *this;
}

Logger& Logger::operator<<(double num) {
    file << num;
    cout << "double" << endl;
    return *this;
}

Logger& Logger::operator<<(char c) {
    file << c;
    cout << "char" << endl;
    return *this;
}