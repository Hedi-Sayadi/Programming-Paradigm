// Patient Manager implementation
#include "patient_manager.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>
#include <sys/stat.h>
#include <sstream>
void PatientManager::loadDataFromCSV() {
    patients.clear();
    maxId = 0;
    // Load patients
    ifstream pfile("data/patients.csv");
    string line;
    getline(pfile, line); // skip header
    while (getline(pfile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string idStr, name, ageStr, gender;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, ageStr, ',');
        getline(ss, gender, ',');
        int id = stoi(idStr);
        int age = stoi(ageStr);
        Patient p(name, age, gender);
        // Set correct ID
        *(int*)&p = id;
        patients.push_back(p);
        if (id > maxId) maxId = id;
    }
    pfile.close();
    // Load symptoms
    ifstream sfile("data/symptoms.csv");
    getline(sfile, line); // skip header
    while (getline(sfile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string pidStr, symptomsStr;
        getline(ss, pidStr, ',');
        getline(ss, symptomsStr);
        int pid = stoi(pidStr);
        
        // Parse semicolon-separated symptoms
        if (!symptomsStr.empty()) {
            stringstream symptomStream(symptomsStr);
            string symptom;
            while (getline(symptomStream, symptom, ';')) {
                for (auto& p : patients) {
                    if (p.getId() == pid) {
                        p.addSymptom(symptom);
                        break;
                    }
                }
            }
        }
    }
    sfile.close();
    // Update nextId
    if (!patients.empty()) Patient::setNextId(maxId + 1);
}

void PatientManager::updatePatientSymptomsInCSV(int patientId, const vector<string>& symptoms) {
    // Read all existing data
    vector<string> lines;
    ifstream inFile("data/symptoms.csv");
    string line;
    bool hasHeader = false;
    
    // Check if file exists and read header
    if (inFile.is_open() && getline(inFile, line)) {
        if (line == "patient_id,symptoms") {
            hasHeader = true;
            lines.push_back(line);
        } else {
            // First line is data, not header - put it back
            inFile.seekg(0);
        }
    }
    inFile.close();
    
    // If no header exists, add it
    if (!hasHeader) {
        lines.push_back("patient_id,symptoms");
    }
    
    // Read existing data, skip lines for this patient
    ifstream inFile2("data/symptoms.csv");
    if (hasHeader) getline(inFile2, line); // skip header
    while (getline(inFile2, line)) {
        if (!line.empty()) {
            stringstream ss(line);
            string pidStr;
            getline(ss, pidStr, ',');
            if (stoi(pidStr) != patientId) {
                lines.push_back(line);
            }
        }
    }
    inFile2.close();
    
    // Add new entry for this patient with all symptoms
    if (!symptoms.empty()) {
        string symptomsStr = "";
        for (size_t i = 0; i < symptoms.size(); ++i) {
            symptomsStr += symptoms[i];
            if (i < symptoms.size() - 1) symptomsStr += ";";
        }
        lines.push_back(to_string(patientId) + "," + symptomsStr);
    }
    
    // Write everything back
    ofstream outFile("data/symptoms.csv");
    for (const string& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();
}
 #include <fstream>

using namespace std;

// Available symptoms in the system
vector<string> PatientManager::getAvailableSymptoms() const {
    return {
        "fever", "cough", "headache", "sore throat", "runny nose",
        "shortness of breath", "fatigue", "muscle aches", "nausea",
        "vomiting", "diarrhea", "loss of taste", "loss of smell",
        "chest pain", "dizziness", "rash", "joint pain", "chills"
    };
}

// Display available symptoms
void PatientManager::displayAvailableSymptoms() const {
    cout << "\nAvailable Symptoms:\n";
    auto symptoms = getAvailableSymptoms();
    for (size_t i = 0; i < symptoms.size(); ++i) {
        cout << (i + 1) << ". " << symptoms[i] << "\n";
    }
    cout << "\n";
}

// Add a new patient (interactive)
void PatientManager::addPatient() {
    string name, gender;
    int age;

    cout << "\n--- Add New Patient ---\n";
    cout << "Enter patient name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter age: ";
    cin >> age;
    cin.ignore();

    cout << "Enter gender (M/F/Other): ";
    getline(cin, gender);

    addPatient(name, age, gender);
}

// Add a new patient
void PatientManager::addPatient(const string& name, int age, const string& gender) {
    Patient newPatient(name, age, gender);
    patients.push_back(newPatient);
    cout << "Patient '" << name << "' added successfully with ID: " << newPatient.getId() << "\n";

    // Write to CSV only one header
    struct stat buffer;
    bool fileExists = (stat("data/patients.csv", &buffer) == 0);
    bool isEmpty = !fileExists || buffer.st_size == 0;
    std::ofstream file("data/patients.csv", std::ios::app);
    if (isEmpty) file << "id,name,age,gender\n";
    file << newPatient.getId() << "," << newPatient.name << "," << newPatient.age << "," << newPatient.gender << "\n";
    file.close();
}

// View all patients
void PatientManager::viewAllPatients() const {
    if (patients.empty()) {
        cout << "\nNo patients found.\n";
        return;
    }

    cout << "\n--- All Patients ---\n";
    for (const auto& patient : patients) {
        patient.displaySummary();
    }
    cout << "\nTotal patients: " << patients.size() << "\n";
}

// Find patient by ID
Patient* PatientManager::findPatientById(int id) {
    for (auto& patient : patients) {
        if (patient.getId() == id) {
            return &patient;
        }
    }
    return nullptr;
}

// Delete a patient
bool PatientManager::deletePatient(int id) {
    auto it = remove_if(patients.begin(), patients.end(),
        [id](const Patient& patient) { return patient.getId() == id; });
    
    if (it != patients.end()) {
        patients.erase(it, patients.end());
        cout << "Patient with ID " << id << " deleted successfully.\n";
        return true;
    }
    cout << "Patient with ID " << id << " not found.\n";
    return false;
}

// Edit patient information
void PatientManager::editPatient(int id) {
    Patient* patient = findPatientById(id);
    if (!patient) {
        cout << "Patient with ID " << id << " not found.\n";
        return;
    }

    cout << "\n--- Edit Patient (ID: " << id << ") ---\n";
    patient->displayInfo();

    int choice;
    cout << "\nWhat would you like to edit?\n";
    cout << "1. Name\n";
    cout << "2. Age\n";
    cout << "3. Gender\n";
    cout << "4. Cancel\n";
    cout << "Choice: ";
    cin >> choice;

    cin.ignore();
    switch (choice) {
        case 1: {
            string newName;
            cout << "Enter new name: ";
            getline(cin, newName);
            patient->name = newName;
            cout << "Name updated successfully.\n";
            break;
        }
        case 2: {
            int newAge;
            cout << "Enter new age: ";
            cin >> newAge;
            patient->age = newAge;
            cout << "Age updated successfully.\n";
            break;
        }
        case 3: {
            string newGender;
            cout << "Enter new gender: ";
            getline(cin, newGender);
            patient->gender = newGender;
            cout << "Gender updated successfully.\n";
            break;
        }
        case 4:
            cout << "Edit cancelled.\n";
            break;
        default:
            cout << "Invalid choice.\n";
    }
}

// Add symptom to a specific patient
void PatientManager::addSymptomToPatient(int patientId) {
    Patient* patient = findPatientById(patientId);
    if (!patient) {
        cout << "Patient with ID " << patientId << " not found.\n";
        return;
    }

    displayAvailableSymptoms();
    
    cout << "\nEnter symptom numbers separated by spaces (e.g., 1 3 5), or 0 to cancel: ";
    string input;
    cin.ignore();
    getline(cin, input);
    
    if (input == "0") {
        cout << "Operation cancelled.\n";
        return;
    }

    // Parse input to get symptom numbers
    stringstream ss(input);
    vector<int> choices;
    int choice;
    while (ss >> choice) {
        choices.push_back(choice);
    }

    if (choices.empty()) {
        cout << "No symptoms selected.\n";
        return;
    }

    auto symptoms = getAvailableSymptoms();
    vector<string> selectedSymptoms;
    
    for (int choice : choices) {
        if (choice >= 1 && choice <= static_cast<int>(symptoms.size())) {
            patient->addSymptom(symptoms[choice - 1]);
            selectedSymptoms.push_back(symptoms[choice - 1]);
        } else {
            cout << "Invalid symptom number: " << choice << "\n";
        }
    }

    if (!selectedSymptoms.empty()) {
        // Write all symptoms for this patient to CSV (replace existing)
        updatePatientSymptomsInCSV(patientId, patient->symptoms);
        cout << "Added " << selectedSymptoms.size() << " symptoms successfully.\n";
    }
}// View symptoms for a specific patient
void PatientManager::viewPatientSymptoms(int patientId) const {
    auto it = find_if(patients.begin(), patients.end(),
        [patientId](const Patient& patient) { return patient.getId() == patientId; });
    
    if (it != patients.end()) {
        cout << "\n--- Symptoms for " << it->name << " (ID: " << patientId << ") ---\n";
        it->displaySymptoms();
    } else {
        cout << "Patient with ID " << patientId << " not found.\n";
    }
}

// Clear symptoms for a specific patient
void PatientManager::clearPatientSymptoms(int patientId) {
    Patient* patient = findPatientById(patientId);
    if (!patient) {
        cout << "Patient with ID " << patientId << " not found.\n";
        return;
    }
    patient->clearSymptoms();
}

// Get total number of patients
int PatientManager::getPatientCount() const {
    return static_cast<int>(patients.size());
}

// Check if patient list is empty
bool PatientManager::isEmpty() const {
    return patients.empty();
}
