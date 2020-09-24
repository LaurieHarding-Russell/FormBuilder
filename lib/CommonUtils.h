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
}