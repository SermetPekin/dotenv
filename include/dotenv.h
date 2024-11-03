
/*
 * dotenv - A simple header-only environment variable loader for C++ projects
 * Author: Sermet Pekin
 * 
 * MIT License
 * 
 * Copyright (c) 2024 Sermet Pekin
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */


#ifndef dotenv_H
#define dotenv_H

#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <algorithm>

class dotenv {
public:
    explicit dotenv(const std::string& filepath) {
        load(filepath);
    }

    std::string get(const std::string& key, const std::string& defaultValue = "") const {
        auto it = envVariables.find(key);
        if (it != envVariables.end()) {
            return it->second;  // Found in .env file
        }
        const char* envValue = std::getenv(key.c_str());
        return envValue ? envValue : defaultValue;  // Fallback to system environment or default
    }

    void set(const std::string& key, const std::string& value) {
        envVariables[key] = value;

        #ifdef _WIN32
            _putenv_s(key.c_str(), value.c_str());
        #else
            setenv(key.c_str(), value.c_str(), 1);
        #endif
    }

private:
    std::unordered_map<std::string, std::string> envVariables;

    static std::string trim(const std::string& str) {
        auto start = str.find_first_not_of(" \t");
        auto end = str.find_last_not_of(" \t");
        return (start == std::string::npos) ? "" : str.substr(start, end - start + 1);
    }

    // Load .env file
    void load(const std::string& filepath) {
        std::ifstream file(filepath);
        if (!file) {
            std::cerr << "Could not open "<< filepath << " file" <<  std::endl;
            return;
        }

        std::string line;
        while (std::getline(file, line)) {
            line = trim(line);
            if (line.empty() || line[0] == '#') continue;

            size_t delimiterPos = line.find('=');
            if (delimiterPos == std::string::npos) continue; // Skip if no '=' is found

            std::string key = trim(line.substr(0, delimiterPos));
            std::string value = trim(line.substr(delimiterPos + 1));

            if (!value.empty() && (value[0] == '"' || value[0] == '\'')) {
                value = value.substr(1, value.size() - 2);
            }

            envVariables[key] = value;

            #ifdef _WIN32
                _putenv_s(key.c_str(), value.c_str());
            #else
                setenv(key.c_str(), value.c_str(), 1);
            #endif
        }
    }
};

#endif // dotenv_H
