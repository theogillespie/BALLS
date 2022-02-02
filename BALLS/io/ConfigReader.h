#pragma once

#include <string>
#include <vector>
#include <fstream>

using namespace std;

// configuration format:
// name (key) = value (string or double)
// # means comment and is ignored


#define _COMMENT "#"
#define _ASSIGN "="

struct configElement {
    string name;
    string value;
    
    string getString() {
        ostringstream os;
        os << this->name << " : " << this->value;
        return os.str();
    }
};

class ConfigParseError : public exception
{
public:
    const string descriptionBase = "Error encountered when parsing config";
    string description;
public:

    ConfigParseError(string file, unsigned int lineNumber) {
        this->description = descriptionBase + "(" + file + ", line: " + to_string(lineNumber) + ")";

    };

    const char* what()
    {
        return this->description.c_str();
    };
};


class ConfigReader {
    string filePath;
public:

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
                line = lines[i];
                if (line.find(_COMMENT) != string::npos) {
                    continue;
                }
                if (line.find(_ASSIGN) == string::npos) {
                    throw new ConfigParseError(this->filePath, i);
                }
                
                configElement element;
                element.name = line.substr(0, line.find("="));
                element.value = line.substr(line.find("=")+1, line.length());
                this->elements.push_back(element);

            } catch (const std::exception& e) {
                throw new ConfigParseError(this->filePath, i);
            };
        }
        
        return &this->elements;
    };
};