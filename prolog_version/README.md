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
