// MediCheck Application Test Suite
#include "patient_manager.h"
#include "diagnosis.h"
#include <iostream>
#include <cassert>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class MediCheckTester {
private:
    PatientManager manager;
    int testsPassed = 0;
    int testsFailed = 0;

public:
    void runAllTests() {
        cout << "========================================\n";
        cout << "     MediCheck Test Suite Starting     \n";
        cout << "========================================\n\n";

        // Clean up test files before starting
        cleanupTestFiles();

        testPatientManagement();
        testSymptomManagement();
        testDiagnosisEngine();
        testCSVPersistence();
        testDataLoading();

        printTestResults();
    }

private:
    void cleanupTestFiles() {
        remove("data/patients.csv");
        remove("data/symptoms.csv");
        cout << "Test files cleaned up.\n\n";
    }

    void assertTrue(bool condition, const string& testName) {
        if (condition) {
            cout << " PASS: " << testName << "\n";
            testsPassed++;
        } else {
            cout << " FAIL: " << testName << "\n";
            testsFailed++;
        }
    }

    void testPatientManagement() {
        cout << "--- Testing Patient Management ---\n";

        // Test 1: Add patients
        manager.addPatient("John Doe", 30, "M");
        manager.addPatient("Jane Smith", 25, "F");
        manager.addPatient("Bob Johnson", 45, "M");
        
        assertTrue(manager.getPatientCount() == 3, "Add 3 patients");

        // Test 2: Find patient by ID
        Patient* patient = manager.findPatientById(1);
        assertTrue(patient != nullptr, "Find patient by ID 1");
        assertTrue(patient->name == "John Doe", "Patient 1 has correct name");
        assertTrue(patient->age == 30, "Patient 1 has correct age");
        assertTrue(patient->gender == "M", "Patient 1 has correct gender");

        // Test 3: Find non-existent patient
        Patient* nonExistent = manager.findPatientById(999);
        assertTrue(nonExistent == nullptr, "Non-existent patient returns nullptr");

        // Test 4: Delete patient
        bool deleted = manager.deletePatient(2);
        assertTrue(deleted == true, "Delete existing patient");
        assertTrue(manager.getPatientCount() == 2, "Patient count after deletion");

        // Test 5: Delete non-existent patient
        bool notDeleted = manager.deletePatient(999);
        assertTrue(notDeleted == false, "Delete non-existent patient fails");

        cout << "\n";
    }

    void testSymptomManagement() {
        cout << "--- Testing Symptom Management ---\n";

        Patient* patient = manager.findPatientById(1);
        if (patient) {
            // Test 1: Add symptoms
            patient->addSymptom("fever");
            patient->addSymptom("cough");
            patient->addSymptom("headache");
            
            assertTrue(patient->symptoms.size() == 3, "Add 3 symptoms to patient");

            // Test 2: Add duplicate symptom
            size_t beforeSize = patient->symptoms.size();
            patient->addSymptom("fever"); // Should not add duplicate
            assertTrue(patient->symptoms.size() == beforeSize, "Duplicate symptom not added");

            // Test 3: Clear symptoms
            patient->clearSymptoms();
            assertTrue(patient->symptoms.empty(), "Clear all symptoms");

            // Test 4: Re-add symptoms for further testing
            patient->addSymptom("fever");
            patient->addSymptom("cough");
            patient->addSymptom("shortness of breath");
        }

        // Test 5: Available symptoms list
        vector<string> availableSymptoms = manager.getAvailableSymptoms();
        assertTrue(availableSymptoms.size() == 18, "Available symptoms list has 18 items");
        assertTrue(availableSymptoms[0] == "fever", "First symptom is fever");
        assertTrue(availableSymptoms[1] == "cough", "Second symptom is cough");

        cout << "\n";
    }

    void testDiagnosisEngine() {
        cout << "--- Testing Diagnosis Engine ---\n";

        // Test 1: Common Cold diagnosis
        vector<string> coldSymptoms = {"runny nose", "sore throat"};
        vector<string> coldDiseases = predictDiseases(coldSymptoms);
        bool hasCommonCold = false;
        for (const auto& disease : coldDiseases) {
            if (disease == "Common Cold") {
                hasCommonCold = true;
                break;
            }
        }
        assertTrue(hasCommonCold, "Common Cold diagnosed with runny nose + sore throat");

        // Test 2: Flu diagnosis
        vector<string> fluSymptoms = {"fever", "cough"};
        vector<string> fluDiseases = predictDiseases(fluSymptoms);
        bool hasFlu = false;
        for (const auto& disease : fluDiseases) {
            if (disease == "Flu") {
                hasFlu = true;
                break;
            }
        }
        assertTrue(hasFlu, "Flu diagnosed with fever + cough");

        // Test 3: COVID-19 diagnosis
        vector<string> covidSymptoms = {"fever", "cough", "loss of taste"};
        vector<string> covidDiseases = predictDiseases(covidSymptoms);
        bool hasCovid = false;
        for (const auto& disease : covidDiseases) {
            if (disease == "COVID-19") {
                hasCovid = true;
                break;
            }
        }
        assertTrue(hasCovid, "COVID-19 diagnosed with fever + cough + loss of taste");

        // Test 4: No symptoms = no diseases
        vector<string> noSymptoms = {};
        vector<string> noDiseases = predictDiseases(noSymptoms);
        assertTrue(noDiseases.empty(), "No symptoms results in no diseases");

        // Test 5: Pneumonia diagnosis
        vector<string> pneumoniaSymptoms = {"fever", "cough", "shortness of breath"};
        vector<string> pneumoniaDiseases = predictDiseases(pneumoniaSymptoms);
        bool hasPneumonia = false;
        for (const auto& disease : pneumoniaDiseases) {
            if (disease == "Pneumonia") {
                hasPneumonia = true;
                break;
            }
        }
        assertTrue(hasPneumonia, "Pneumonia diagnosed with fever + cough + shortness of breath");

        cout << "\n";
    }

    void testCSVPersistence() {
        cout << "--- Testing CSV Persistence ---\n";

        // Test 1: Check if patients.csv is created
        ifstream patientsFile("data/patients.csv");
        assertTrue(patientsFile.is_open(), "Patients CSV file created");
        
        // Test 2: Check patients.csv content
        string line;
        getline(patientsFile, line); // header
        assertTrue(line == "id,name,age,gender", "Patients CSV has correct header");
        
        bool foundJohnDoe = false;
        while (getline(patientsFile, line)) {
            if (line.find("John Doe") != string::npos) {
                foundJohnDoe = true;
                break;
            }
        }
        patientsFile.close();
        assertTrue(foundJohnDoe, "John Doe found in patients CSV");

        // Test 3: Update symptoms CSV
        Patient* patient = manager.findPatientById(1);
        if (patient) {
            patient->symptoms = {"fever", "cough", "headache"};
            manager.updatePatientSymptomsInCSV(1, patient->symptoms);
        }

        // Test 4: Check symptoms.csv
        ifstream symptomsFile("data/symptoms.csv");
        assertTrue(symptomsFile.is_open(), "Symptoms CSV file created");
        
        getline(symptomsFile, line); // header
        assertTrue(line == "patient_id,symptoms", "Symptoms CSV has correct header");
        
        bool foundPatientSymptoms = false;
        while (getline(symptomsFile, line)) {
            if (line.find("1,fever;cough;headache") != string::npos) {
                foundPatientSymptoms = true;
                break;
            }
        }
        symptomsFile.close();
        assertTrue(foundPatientSymptoms, "Patient symptoms found in symptoms CSV");

        cout << "\n";
    }

    void testDataLoading() {
        cout << "--- Testing Data Loading ---\n";

        // Create a new PatientManager to test loading
        PatientManager newManager;
        
        // Test 1: Load data from CSV
        newManager.loadDataFromCSV();
        assertTrue(newManager.getPatientCount() > 0, "Data loaded from CSV");

        // Test 2: Check loaded patient data
        Patient* loadedPatient = newManager.findPatientById(1);
        assertTrue(loadedPatient != nullptr, "Patient 1 loaded successfully");
        
        if (loadedPatient) {
            assertTrue(loadedPatient->name == "John Doe", "Loaded patient has correct name");
            assertTrue(loadedPatient->age == 30, "Loaded patient has correct age");
            assertTrue(loadedPatient->gender == "M", "Loaded patient has correct gender");
            assertTrue(!loadedPatient->symptoms.empty(), "Loaded patient has symptoms");
        }

        // Test 3: Check if symptoms are loaded correctly
        if (loadedPatient) {
            bool hasRequiredSymptoms = false;
            for (const auto& symptom : loadedPatient->symptoms) {
                if (symptom == "fever" || symptom == "cough" || symptom == "headache") {
                    hasRequiredSymptoms = true;
                    break;
                }
            }
            assertTrue(hasRequiredSymptoms, "Loaded patient has expected symptoms");
        }

        cout << "\n";
    }

    void printTestResults() {
        cout << "========================================\n";
        cout << "           Test Results Summary         \n";
        cout << "========================================\n";
        cout << "Tests Passed: " << testsPassed << "\n";
        cout << "Tests Failed: " << testsFailed << "\n";
        cout << "Total Tests:  " << (testsPassed + testsFailed) << "\n";
        cout << "Success Rate: " << (testsPassed * 100.0 / (testsPassed + testsFailed)) << "%\n";
        
        if (testsFailed == 0) {
            cout << "\n All tests passed! The application is working correctly.\n";
        } else {
            cout << "\n  Some tests failed. Please check the implementation.\n";
        }
        cout << "========================================\n";
    }
};

int main() {
    MediCheckTester tester;
    tester.runAllTests();
    return 0;
}
