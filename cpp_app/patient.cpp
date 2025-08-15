// Patient class implementation
#include "patient.h"
#include <iostream>
#include <algorithm>

using namespace std;

int Patient::nextId = 1;

void Patient::setNextId(int id) {
    nextId = id;
}

Patient::Patient() : id(nextId++), name(""), age(0), gender("") {}

Patient::Patient(const string& name, int age, const string& gender) 
    : id(nextId++), name(name), age(age), gender(gender) {}

int Patient::getId() const {
    return id;
}

void Patient::addSymptom(const string& symptom) {
    // Check if symptom already exists to avoid duplicates
    auto it = find(symptoms.begin(), symptoms.end(), symptom);
    if (it == symptoms.end()) {
        symptoms.push_back(symptom);
        cout << "Symptom '" << symptom << "' added successfully.\n";
    } else {
        cout << "Symptom '" << symptom << "' already exists for this patient.\n";
    }
}

// Clear all symptoms
void Patient::clearSymptoms() {
    symptoms.clear();
    cout << "All symptoms cleared for patient " << name << ".\n";
}

// Display all symptoms
void Patient::displaySymptoms() const {
    if (symptoms.empty()) {
        cout << "No symptoms recorded.\n";
    } else {
        cout << "Symptoms: ";
        for (size_t i = 0; i < symptoms.size(); ++i) {
            cout << symptoms[i];
            if (i < symptoms.size() - 1) cout << ", ";
        }
        cout << "\n";
    }
}

// Display detailed patient information
void Patient::displayInfo() const {
    cout << "\n--- Patient Information ---\n";
    cout << "ID: " << id << "\n";
    cout << "Name: " << name << "\n";
    cout << "Age: " << age << "\n";
    cout << "Gender: " << gender << "\n";
    displaySymptoms();
    cout << "---------------------------\n";
}

// Display summary (for patient list)
void Patient::displaySummary() const {
    cout << "ID: " << id << " | Name: " << name << " | Age: " << age 
              << " | Gender: " << gender << " | Symptoms: " << symptoms.size() << "\n";
}
