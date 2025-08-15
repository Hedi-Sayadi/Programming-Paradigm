// Patient class definition
#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Patient {
private:
    static int nextId;
    int id;

public:
    string name;
    int age;
    string gender;
    vector<string> symptoms;

    Patient();
    Patient(const string& name, int age, const string& gender);

    int getId() const;

    static void setNextId(int id);

    void addSymptom(const string& symptom);
    void clearSymptoms();
    void displaySymptoms() const;

    // Display patient information
    void displayInfo() const;
    void displaySummary() const;
};
