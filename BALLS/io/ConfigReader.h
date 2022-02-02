#pragma once

#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct configElement {
    string name;
    string value;
};

class ConfigReader {
    string filePath;
    vector<configElement> elements = vector<configElement>();

    ConfigReader(string location) {
        this->filePath = location;
    };

    vector<configElement>* parse() {
        ifstream ifs(this->filePath, ifstream::in);
        vector<string> lines;

        string line;
        while (getline(ifs, line)) {
            if (line.empty()) {
                continue;
            }
            lines.push_back(line);
        }

        for(int i = 0; i < lines.size(); i++) {
            try {
                configElement element;
                line = lines[i];
                element.name = line.substr(0, line.find("="));
                element.value = line.substr(line.find("=", line.length()));
                this->elements.push_back(element);

            } catch (const std::exception& e) {
                printf(e.what());
            };
        }
        
        return &this->elements;
    };
};