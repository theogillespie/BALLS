#pragma once

#include "ConfigReader.h"

#include <string>
#include <vector>

using namespace std;

class FieldMissingError: public exception
{
public:
    const string base = "Missing Field in Projectile Configuration: ";
    string var;
    FieldMissingError(string field) {
       this->var = field;
    };

    const char* what()
    {
        return (this->base + this->var).c_str();
    };
};

struct ProjectileConfigField {
    string name;
    string valueS;
    double valueD;

    ProjectileConfigField(string label) {
        this->name = label;
    }
};

class ProjectileLoader {
public: 

    ConfigReader cr;

    vector<ProjectileConfigField*> fields;

    ProjectileLoader(string filepath, vector<ProjectileConfigField*> configFields) {
        cr = ConfigReader(filepath);
        this->fields = configFields;
    };
    
    void load() {
        try {
            cr.parse();
        } catch(const std::exception& e) {
            cout << "Error while loading projectile configuration: " + *e.what();
        }

        for(int i = 0; i < cr.elements.size(); i++) {
           configElement element = cr.elements[i];
           bool found;
           for(int j = 0; j < this->fields.size(); j++) {
               ProjectileConfigField* field = this->fields[j];
               if(element.name == field->name) {
                   if(configElement::isNumber(element.value)) {
                       field->valueD = configElement::toNumber(element.value);
                   }
                   found = true;
                   break;
               }
           }
           if(!found) {
               cout << FieldMissingError(element.name).what();
           }
        }

        
    }
};