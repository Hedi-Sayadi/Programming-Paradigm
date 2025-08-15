// Patient Manager class for handling multiple patients
#pragma once
#include "patient.h"
#include <vector>
#include <string>

using namespace std;

class PatientManager {
private:
    vector<Patient> patients;
    int maxId = 0;

public:
    // Patient CRUD operations
    void addPatient();
    void addPatient(const string& name, int age, const string& gender);
    void viewAllPatients() const;
    Patient* findPatientById(int id);
    bool deletePatient(int id);
    void editPatient(int id);

    // Symptom management for patients
    void addSymptomToPatient(int patientId);
    void viewPatientSymptoms(int patientId) const;
    void clearPatientSymptoms(int patientId);

    // Available symptoms list
    void displayAvailableSymptoms() const;
    vector<string> getAvailableSymptoms() const;
    void loadDataFromCSV();
    void updatePatientSymptomsInCSV(int patientId, const vector<string>& symptoms);

    // Utility methods
    int getPatientCount() const;
    bool isEmpty() const;
};
