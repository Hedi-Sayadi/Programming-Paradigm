# MediCheck Prolog Version - Declarative Disease Diagnosis

## Overview
This is the declarative implementation of the MediCheck disease prediction system using Prolog. It demonstrates rule-based inference and pattern matching for medical diagnosis, contrasting with the imperative C++ approach.

## Features
- **Declarative Rules**: Disease diagnosis using logical facts and rules
- **Pattern Matching**: Sophisticated symptom combination matching
- **Confidence Scoring**: Disease predictions with symptom match counts
- **Interactive Queries**: Flexible querying system
- **Comprehensive Test Suite**: Pre-built test cases for validation

## Files Structure
- `knowledge_base.pl` - Facts about symptoms, diseases, and their relationships
- `diagnosis.pl` - Main diagnostic rules and inference engine
- `test_diagnosis.pl` - Test cases and interactive examples

## Requirements
- SWI-Prolog (recommended) or any compatible Prolog interpreter
- Download from: https://www.swi-prolog.org/

## Running the Prolog System

### Method 1: Interactive SWI-Prolog Session
1. Start SWI-Prolog
2. Load the main file:
   ```prolog
   ?- [diagnosis].
   ```
3. Run queries (see examples below)

### Method 2: Load Test Suite
```prolog
?- [test_diagnosis].
?- run_all_tests.
```

## Basic Usage Examples

### Simple Diagnosis Queries
```prolog
% Basic diagnosis - returns list of possible diseases
?- diagnose([fever, cough], Diseases).
Diseases = [flu, covid19].

% Check for specific symptoms
?- diagnose([loss_of_taste, loss_of_smell], Diseases).
Diseases = [covid19].

% Single symptom
?- diagnose([headache], Diseases).
Diseases = [tension_headache].
```

### Advanced Queries
```prolog
% Diagnosis with confidence scores
?- diagnose_detailed([fever, cough, headache], Results).
Results = [flu-3, covid19-3].

% Check if a specific disease is possible
?- possible_disease([fever, cough], flu).
true.

% Explain diagnosis interactively
?- explain_diagnosis([nausea, vomiting, diarrhea]).
Patient symptoms: [nausea,vomiting,diarrhea]
Possible conditions:
  - gastroenteritis
  - food_poisoning
```

### System Information Queries
```prolog
% Show all available symptoms
?- show_symptoms.

% Show all diseases in knowledge base
?- show_diseases.

% Get help and examples
?- help.
```

## Available Symptoms
The system recognizes these 18 symptoms (use underscores instead of spaces):
- `fever`, `cough`, `headache`, `sore_throat`, `runny_nose`
- `shortness_of_breath`, `fatigue`, `muscle_aches`, `nausea`
- `vomiting`, `diarrhea`, `loss_of_taste`, `loss_of_smell`
- `chest_pain`, `dizziness`, `rash`, `joint_pain`, `chills`

## Disease Conditions
The system can diagnose these conditions:
- `common_cold`, `flu`, `covid19`, `pneumonia`
- `gastroenteritis`, `migraine`, `allergic_reaction`, `strep_throat`
- `bronchitis`, `food_poisoning`, `sinusitis`, `asthma`
- `anxiety_panic_attack`, `dehydration`, `arthritis`
- `inflammatory_arthritis`, `tension_headache`, `skin_condition`
- `fever_unknown_cause`

## Key Prolog Features Demonstrated

### 1. Declarative Rules
Instead of imperative if-then logic, Prolog uses declarative rules:
```prolog
possible_disease(PatientSymptoms, flu) :-
    (has_all_symptoms(PatientSymptoms, [fever, cough]);
     has_all_symptoms(PatientSymptoms, [fever, muscle_aches])).
```

### 2. Pattern Matching
Sophisticated pattern matching with multiple conditions:
```prolog
possible_disease(PatientSymptoms, strep_throat) :-
    has_all_symptoms(PatientSymptoms, [sore_throat, fever]),
    not_has_symptom(PatientSymptoms, runny_nose),
    not_has_symptom(PatientSymptoms, cough).
```

### 3. List Processing
Native list operations for symptom checking:
```prolog
has_all_symptoms(PatientSymptoms, []).
has_all_symptoms(PatientSymptoms, [Symptom|Rest]) :-
    has_patient_symptom(PatientSymptoms, Symptom),
    has_all_symptoms(PatientSymptoms, Rest).
```

### 4. Meta-predicates
Using `findall/3` for collecting all solutions:
```prolog
predict_diseases(PatientSymptoms, Diseases) :-
    findall(Disease, possible_disease(PatientSymptoms, Disease), DiseaseList),
    sort(DiseaseList, Diseases).
```

## Testing the System

### Run All Tests
```prolog
?- run_all_tests.
```

### Individual Test Cases
```prolog
?- test_common_cold.
?- test_flu.
?- test_covid19.
```

## Comparison with C++ Version

| Aspect | C++ (Imperative) | Prolog (Declarative) |
|--------|------------------|---------------------|
| **Style** | Procedural steps | Logical relationships |
| **Rules** | if-then statements | Logical facts and rules |
| **Data** | Arrays/vectors | Lists and facts |
| **Logic** | Explicit algorithms | Implicit inference |
| **Queries** | Function calls | Logical queries |

## Example Session
```prolog
?- [diagnosis].
true.

?- diagnose([fever, cough], D).
D = [flu, covid19].

?- possible_disease([fever, cough, loss_of_taste], covid19).
true.

?- explain_diagnosis([headache, nausea]).
Patient symptoms: [headache,nausea]
Possible conditions:
  - migraine
true.
```

## Extending the System

### Adding New Symptoms
1. Add symptom fact to `knowledge_base.pl`:
   ```prolog
   symptom(new_symptom).
   ```

2. Associate with diseases:
   ```prolog
   has_symptom(some_disease, new_symptom).
   ```

### Adding New Diseases
1. Add disease fact:
   ```prolog
   disease(new_disease).
   ```

2. Define symptoms:
   ```prolog
   has_symptom(new_disease, symptom1).
   has_symptom(new_disease, symptom2).
   ```

3. Add diagnostic rule in `diagnosis.pl`:
   ```prolog
   possible_disease(PatientSymptoms, new_disease) :-
       has_all_symptoms(PatientSymptoms, [symptom1, symptom2]).
   ```

This Prolog implementation showcases the power of declarative programming for rule-based expert systems and provides an excellent contrast to the imperative C++ approach.
