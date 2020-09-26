#ifndef COMMON_UTIL_H
#define COMMON_UTIL_H
#include <string>
#include <fstream>

namespace util {
    static std::string loadFile(std::string name) {
        std::string data = "";
        std::ifstream file (name);

        if (file.is_open()) {
            std::string line;
            while ( getline(file, line) ) {
                data += line + '\n';
            }
            file.close();
        }
        return data;
    }

    static unsigned char* loadFileToUnsignedChar(std::string name) { // FIXME, C++17 byte type?
        std::ifstream file(name, std::ios::binary);
        if (!file.is_open()) {
            exit(1);
        }
        file.seekg(0, std::ios::end);
        unsigned long int fontBufferSize = (unsigned long int)file.tellg();
        file.close();
        unsigned char* fontBuffer = new unsigned char[fontBufferSize];
        fread(fontBuffer, 1, 1<<25, fopen(name.c_str(), "rb"));
        return fontBuffer;
    }
}
#endif