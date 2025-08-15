#include "patient.h"
#include "patient_manager.h"
#include "diagnosis.h"
#include <iostream>
#include <limits>
using namespace std;

void clearInputStream() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void displayMainMenu() {
    cout << "\n========== MediCheck - Main Menu ==========\n";
    cout << "1. Patient Management\n";
    cout << "2. Symptom Management\n";
    cout << "3. Disease Diagnosis\n";
    cout << "4. Exit\n";
    cout << "==========================================\n";
    cout << "Select an option: ";
}

void displayPatientMenu() {
    cout << "\n--- Patient Management ---\n";
    cout << "1. Add New Patient\n";
    cout << "2. View All Patients\n";
    cout << "3. Edit Patient\n";
    cout << "4. Delete Patient\n";
    cout << "5. Back to Main Menu\n";
    cout << "Choice: ";
}

void displaySymptomMenu() {
    cout << "\n--- Symptom Management ---\n";
    cout << "1. Add Symptoms to Patient\n";
    cout << "2. View Patient Symptoms\n";
    cout << "3. Clear Patient Symptoms\n";
    cout << "4. View Available Symptoms\n";
    cout << "5. Back to Main Menu\n";
    cout << "Choice: ";
}

void handlePatientManagement(PatientManager& manager) {
    int choice;
    do {
        displayPatientMenu();
        cin >> choice;

        if (cin.fail()) {
            clearInputStream();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                manager.addPatient();
                break;
            case 2:
                manager.viewAllPatients();
                break;
            case 3: {
                if (manager.isEmpty()) {
                    cout << "No patients available for editing.\n";
                    break;
                }
                int id;
                cout << "Enter patient ID to edit: ";
                cin >> id;
                manager.editPatient(id);
                break;
            }
            case 4: {
                if (manager.isEmpty()) {
                    cout << "No patients available for deletion.\n";
                    break;
                }
                int id;
                cout << "Enter patient ID to delete: ";
                cin >> id;
                manager.deletePatient(id);
                break;
            }
            case 5:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void handleSymptomManagement(PatientManager& manager) {
    int choice;
    do {
        displaySymptomMenu();
        cin >> choice;

        if (cin.fail()) {
            clearInputStream();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                if (manager.isEmpty()) {
                    cout << "No patients available. Please add a patient first.\n";
                    break;
                }
                manager.viewAllPatients();
                int id;
                cout << "Enter patient ID to add symptoms: ";
                cin >> id;
                manager.addSymptomToPatient(id);
                break;
            }
            case 2: {
                if (manager.isEmpty()) {
                    cout << "No patients available.\n";
                    break;
                }
                manager.viewAllPatients();
                int id;
                cout << "Enter patient ID to view symptoms: ";
                cin >> id;
                manager.viewPatientSymptoms(id);
                break;
            }
            case 3: {
                if (manager.isEmpty()) {
                    cout << "No patients available.\n";
                    break;
                }
                manager.viewAllPatients();
                int id;
                cout << "Enter patient ID to clear symptoms: ";
                cin >> id;
                manager.clearPatientSymptoms(id);
                break;
            }
            case 4:
                manager.displayAvailableSymptoms();
                break;
            case 5:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void handleDiagnosis(PatientManager& manager) {
    if (manager.isEmpty()) {
        cout << "No patients available. Please add a patient first.\n";
        return;
    }

    manager.viewAllPatients();
    int id;
    cout << "Enter patient ID for diagnosis: ";
    cin >> id;

    Patient* patient = manager.findPatientById(id);
    if (!patient) {
        cout << "Patient with ID " << id << " not found.\n";
        return;
    }

    if (patient->symptoms.empty()) {
        cout << "No symptoms recorded for this patient. Please add symptoms first.\n";
        return;
    }

    cout << "\n--- Diagnosis for " << patient->name << " ---\n";
    patient->displaySymptoms();

    auto possibleDiseases = predictDiseases(patient->symptoms);
    
    if (possibleDiseases.empty()) {
        cout << "No matching conditions found based on current symptoms.\n";
    } else {
        cout << "\nPossible conditions:\n";
        for (const auto& disease : possibleDiseases) {
            cout << "- " << disease << "\n";
        }
        cout << "\nNote: This is for informational purposes only. Please consult a healthcare professional.\n";
    }
}

int main() {
    PatientManager manager;
    int choice;

    // Load existing data from CSV files
    manager.loadDataFromCSV();

    cout << "========================================\n";
    cout << "   Welcome to MediCheck Application    \n";
    cout << "   Simple Medical Diagnosis System     \n";
    cout << "========================================\n";

    do {
        displayMainMenu();
        cin >> choice;

        if (cin.fail()) {
            clearInputStream();
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                handlePatientManagement(manager);
                break;
            case 2:
                handleSymptomManagement(manager);
                break;
            case 3:
                handleDiagnosis(manager);
                break;
            case 4:
                cout << "\nThank you for using MediCheck!\n";
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please select 1-4.\n";
        }
    } while (choice != 4);

    return 0;
}
