#pragma once

#include <string>
#include <fstream>

#include "../core/Curve.h"
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
        
        //should probbaly have error checking
        void parse(Curve* curve) {
            ifstream ifs(this->filePath, ifstream::in);

            string line;
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

                curve->x.push_back(configElement::toNumber(xs));
                curve->y.push_back(configElement::toNumber(ys));
            }
        };

};