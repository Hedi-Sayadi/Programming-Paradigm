# Project Title  
**MediCheck: A Simple Medical Diagnosis Application**

---

## 2 Project Overview  
The Medical Diagnosis App is a simple C++ application that allows healthcare staff (or patients) to store basic patient data, record their symptoms, and receive possible disease predictions based on those symptoms.  

The main app is developed entirely in **C++ (imperative style)**. One of its core functionalities disease prediction based on symptoms will be reimplemented separately in a **declarative language Prolog** for comparison purposes.

---

## 3 Goals  
- Provide a patient record management system.  
- Allow symptom input for each patient.  
- Predict possible diseases based on a predefined symptom-disease mapping.  
- Demonstrate the difference between **imperative programming (C++)** and **declarative programming Prolog** for the same functionality.

---

## 4 Features  

### Part 1: C++ Implementation (Main Project)  
**Patient Management:**  
- Add new patient (name, age, gender).  
- View patient list.  
- Edit/delete patient records.  

**Symptom Recording:**  
- Enter symptoms for a patient from a predefined list (e.g., fever, cough, headache).  
- Store symptoms in memory or optionally in a text file.  

**Disease Prediction (Imperative):**  
- Use simple `if/else` rules in C++ to match entered symptoms with known diseases.  
- Return a list of possible conditions.  
  
---

### Part 2: Declarative Reimplementation (Standalone Program)  
- Take the disease prediction functionality and reimplement it in:  
  - **Prolog** (rule-based inference using facts and rules)  
- This module is independent, it does not connect to the C++ app.  
- It reads a given set of symptoms and outputs the predicted diseases.  

---

## Example Workflow  

**C++ App (Main Project):**  
1. User launches app.  
2. Adds patient 'Alice', age 25.  
3. Enters symptoms: fever, cough.  
4. App checks its rules:  
   - Fever + cough → possible Flu.  
   - Fever + cough + loss of taste → possible COVID-19.  
5. App displays:  


Possible conditions for Alice: Flu, COVID-19

**Prolog Reimplementation:**  
prolog
?- predict([fever, cough], Diseases).
Diseases = [flu, covid19].

---

## 6 Technology Stack & Status

###  COMPLETED - Imperative Part:
- **C++17** with comprehensive console application
- **Patient Management**: Add, edit, delete, view patients
- **Symptom Recording**: 18 predefined symptoms with interactive selection
- **Disease Prediction**: 15+ conditions with sophisticated rule-based diagnosis
- **Build System**: Windows batch files and cross-platform Makefile
- **Interactive Menu**: User-friendly console interface

###  COMPLETED - Declarative Part:
- **Prolog** (SWI-Prolog compatible) knowledge-based system
- **Facts Database**: Complete symptom-disease relationship mapping
- **Inference Rules**: Declarative disease prediction logic
- **Query System**: Flexible diagnostic queries with confidence scoring
- **Test Suite**: Comprehensive test cases and examples
- **Interactive Help**: Built-in help and example system

###  Current Project Structure:
```
Programming_Paradigms/
│
├── readme.md                 # Project overview (this file)
│
├── cpp_app/                  #  COMPLETE - Imperative implementation
│   ├── main.cpp              # Console application entry point
│   ├── patient.cpp/h         # Patient management classes
│   ├── patient_manager.cpp/h # Patient collection operations
│   ├── diagnosis.cpp/h       # Disease prediction rules (C++)
│   ├── build.bat            # Windows build script
│   ├── run.bat              # Windows run script  
│   ├── Makefile             # Cross-platform build
│   ├── README.md            # C++ specific documentation
│   ├── bin/                 # Compiled executables
│   └── data/                # Optional data storage
│
├── prolog_version/           #  COMPLETE - Declarative implementation
│   ├── diagnosis.pl          # Main inference engine
│   ├── knowledge_base.pl     # Symptom-disease facts database
│   ├── test_diagnosis.pl     # Test cases and examples
│   └── README.md             # Prolog specific documentation
```

###  Ready to Use:
- **C++ Application**: `.\build.bat` then `.\run.bat` in cpp_app directory
- **Prolog System**: Load `[diagnosis]` in SWI-Prolog, then query with `diagnose([fever, cough], Diseases)`

###  Implemented Features:
- **Complete Patient CRUD**: Create, Read, Update, Delete operations
- **Advanced Symptom Management**: Interactive symptom selection and management
- **Sophisticated Diagnosis**: 15+ disease conditions with complex rule combinations
- **Dual Implementation**: Same logic in both imperative and declarative styles
- **Comprehensive Testing**: Built-in test suites for both implementations

- **Full Documentation**: README files and code comparison guide

