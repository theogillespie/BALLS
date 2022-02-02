#pragma once

#include <exception>
#include <string>
#include <fstream>
#include <vector>

#include "ConfigReader.h"

using namespace std;

#define _DELIMITER ","

//effectively works as naive csv reader
class CurveReader {
    public: 
        string filePath;

        CurveReader(string filepath) {
            this->filePath = filepath;
        };

        CurveReader() {};
        
        //should probbaly have error checking
        void parse(vector<double> *x, vector<double> *y) {
            ifstream ifs(this->filePath, ifstream::in);
            string line;
            try {
                while (getline(ifs, line)) {
                if (line.empty()) {
                    continue;
                }

                string xs = line.substr(0, line.find(_DELIMITER));
                string ys = line.substr(line.find(_DELIMITER)+1, line.length());

                if(!configElement::isNumber(xs)) {
                    continue;
                }

                ConfigReader::removeStringWhitespace(&xs);
                ConfigReader::removeStringWhitespace(&ys);

                x->push_back(configElement::toNumber(xs));
                y->push_back(configElement::toNumber(ys));
            }
            } catch(exception* e) {
                cout << e->what();
            }
            
        };

};