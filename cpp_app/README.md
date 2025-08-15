# MediCheck C++ Application

## Overview
This is a simple, console-based medical diagnosis application implemented in C++. It demonstrates imperative programming paradigm with basic patient management and symptom-based disease prediction.

## Features
- **Patient Management**: Add, view, edit, and delete patient records
- **Symptom Recording**: Add symptoms from a predefined list to patients
- **Disease Prediction**: Rule-based diagnosis using imperative programming
- **Simple Console Interface**: Easy-to-use menu-driven system

## Building the Application

### Requirements
- C++ compiler with C++17 support (g++ recommended)
- Windows environment (for .bat scripts)

### Build Instructions

#### Option 1: Using the Build Script (Windows)
```cmd
.\build.bat
```

#### Option 2: Manual Compilation
```cmd
g++ -std=c++17 -Wall -Wextra -O2 main.cpp patient.cpp patient_manager.cpp diagnosis.cpp -o bin\medicheck.exe
```

#### Option 3: Using Makefile (if you have make installed)
```cmd
make
```

## Running the Application

### Option 1: Using Run Script
```cmd
.\run.bat
```

### Option 2: Direct Execution
```cmd
bin\medicheck.exe
```

## Application Structure

### Core Files
- `main.cpp` - Main application entry point with console menu system
- `patient.h/.cpp` - Patient class definition and implementation  
- `patient_manager.h/.cpp` - Patient management operations
- `diagnosis.h/.cpp` - Disease prediction rules (imperative style)
- `build.bat` - Windows build script
- `run.bat` - Windows run script

### Available Symptoms
The system recognizes 18 different symptoms:
- fever, cough, headache, sore throat, runny nose
- shortness of breath, fatigue, muscle aches, nausea
- vomiting, diarrhea, loss of taste, loss of smell
- chest pain, dizziness, rash, joint pain, chills

### Disease Rules
The application includes rules for predicting these conditions:
- Common Cold, Flu, COVID-19, Pneumonia
- Gastroenteritis, Migraine, Allergic Reaction
- Strep Throat, Bronchitis, Food Poisoning
- And several single-symptom conditions

## Usage Example

1. **Start the application**
2. **Add a new patient** (Patient Management → Add New Patient)
   - Enter name: Alice
   - Enter age: 25
   - Enter gender: F
3. **Add symptoms** (Symptom Management → Add Symptoms to Patient)
   - Select patient ID
   - Choose symptoms like "fever" and "cough"
4. **Get diagnosis** (Disease Diagnosis)
   - Select patient ID
   - View predicted conditions

## Extending the Application
To add new symptoms or diseases:
1. Add new symptoms to `getAvailableSymptoms()` in `patient_manager.cpp`
2. Add new disease rules in `predictDiseases()` in `diagnosis.cpp`
