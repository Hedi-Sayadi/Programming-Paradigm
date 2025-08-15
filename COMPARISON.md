# Programming Paradigms Comparison: Imperative vs Declarative
## MediCheck Disease Diagnosis System

This document compares the implementation of the same disease diagnosis functionality using two different programming paradigms.

---

## Overview

**Problem**: Given a list of patient symptoms, predict possible medical conditions.

**Solution Approaches**:
- **Imperative (C++)**: Step-by-step procedures with explicit control flow
- **Declarative (Prolog)**: Logical facts and rules with implicit inference

---

## Code Comparison

### Disease Rule: "Flu Detection"

#### Imperative Approach (C++)
```cpp
// Explicit step-by-step algorithm
if (hasSymptoms(symptoms, {"fever", "cough"}) ||
    hasSymptoms(symptoms, {"fever", "muscle_aches"}) ||
    hasSymptoms(symptoms, {"fever", "fatigue", "headache"}) ||
    hasSymptoms(symptoms, {"fever", "chills"}) ||
    hasSymptoms(symptoms, {"muscle_aches", "fatigue", "headache"})) {
    diseases.insert("Flu");
}
```

#### Declarative Approach (Prolog)
```prolog
% Logical relationship definition
possible_disease(PatientSymptoms, flu) :-
    (has_all_symptoms(PatientSymptoms, [fever, cough]);
     has_all_symptoms(PatientSymptoms, [fever, muscle_aches]);
     has_all_symptoms(PatientSymptoms, [fever, fatigue, headache]);
     has_all_symptoms(PatientSymptoms, [fever, chills]);
     has_all_symptoms(PatientSymptoms, [muscle_aches, fatigue, headache])).
```

### Complex Rule: "Strep Throat" (with exclusions)

#### Imperative Approach (C++)
```cpp
// Explicit conditional logic with negations
if (hasSymptoms(symptoms, {"sore_throat", "fever"}) &&
    !hasSymptom(symptoms, "runny_nose") &&
    !hasSymptom(symptoms, "cough")) {
    diseases.insert("Strep Throat");
}
```

#### Declarative Approach (Prolog)
```prolog
% Logic with natural language-like conditions
possible_disease(PatientSymptoms, strep_throat) :-
    has_all_symptoms(PatientSymptoms, [sore_throat, fever]),
    not_has_symptom(PatientSymptoms, runny_nose),
    not_has_symptom(PatientSymptoms, cough).
```

---

## Detailed Comparison

| Aspect | Imperative (C++) | Declarative (Prolog) |
|--------|------------------|---------------------|
| **Paradigm** | Procedural | Logic Programming |
| **Focus** | *How* to compute | *What* to compute |
| **Control Flow** | Explicit (loops, conditions) | Implicit (inference engine) |
| **Data Structures** | Arrays, vectors, sets | Lists, facts, predicates |
| **Rule Representation** | if-then-else statements | Logical clauses |
| **Pattern Matching** | Manual comparison | Built-in unification |
| **Queries** | Function calls | Logical queries |
| **Extensibility** | Add more if-statements | Add more facts/rules |

---

## Execution Flow Comparison

### Imperative Flow (C++)
```
1. Call predictDiseases(symptoms)
2. Create empty diseases set
3. For each disease rule:
   a. Check if symptom conditions match
   b. If true, add disease to set
4. Return disease set
```

### Declarative Flow (Prolog)
```
1. Query: diagnose([fever, cough], Diseases)
2. Prolog inference engine:
   a. Try to match patient symptoms with all rules
   b. Unify variables automatically
   c. Backtrack through alternative solutions
3. Return all matching diseases
```

---

## Practical Examples

### Example 1: Simple Diagnosis

**Input**: `[fever, cough]`

#### C++ Output Process:
```cpp
std::vector<std::string> symptoms = {"fever", "cough"};
auto diseases = predictDiseases(symptoms);
// diseases contains: ["Flu", "COVID-19"]
```

#### Prolog Query Process:
```prolog
?- diagnose([fever, cough], Diseases).
Diseases = [flu, covid19].
```

### Example 2: Complex Query

**Input**: `[fever, cough, headache, fatigue]`

#### C++ Execution:
```cpp
// Multiple if-statements checked sequentially
// Results in: ["Flu", "COVID-19", "Dehydration"]
```

#### Prolog Execution:
```prolog
?- diagnose([fever, cough, headache, fatigue], Diseases).
Diseases = [flu, covid19, dehydration].

% Alternative: Get confidence scores
?- diagnose_detailed([fever, cough, headache, fatigue], Results).
Results = [flu-4, covid19-4, dehydration-3].
```

---

## Strengths & Weaknesses

### Imperative (C++) Strengths:
-  **Performance**: Direct execution, no inference overhead
-  **Control**: Explicit control over execution order
-  **Debugging**: Step-through debugging possible
-  **Memory Management**: Explicit control over resources
-  **Integration**: Easy to integrate with other C++ systems

### Imperative (C++) Weaknesses:
-  **Verbosity**: More code for complex logic
-  **Maintenance**: Adding rules requires code changes
-  **Readability**: Business logic mixed with implementation

### Declarative (Prolog) Strengths:
-  **Conciseness**: Natural expression of logical relationships
-  **Readability**: Rules read like natural language
-  **Flexibility**: Easy to add new facts and rules
-  **Querying**: Rich querying capabilities built-in
-  **Inference**: Automatic reasoning and backtracking

### Declarative (Prolog) Weaknesses:
-  **Performance**: Inference overhead
-  **Learning Curve**: Different thinking paradigm required
-  **Debugging**: Logic bugs can be harder to trace
-  **Integration**: May require bridging with other languages

---

## Extensibility Comparison

### Adding a New Disease: "Sinusitis"

#### In C++ (Imperative):
```cpp
// Add to diagnosis.cpp
if (hasSymptoms(symptoms, {"headache", "runny_nose"}) ||
    hasSymptoms(symptoms, {"headache", "sore_throat", "runny_nose"}) ||
    (hasSymptom(symptoms, "headache") && 
     hasSymptom(symptoms, "fever") && 
     hasSymptom(symptoms, "runny_nose"))) {
    diseases.insert("Sinusitis");
}
```

#### In Prolog (Declarative):
```prolog
% Add to knowledge_base.pl
disease(sinusitis).
has_symptom(sinusitis, headache).
has_symptom(sinusitis, runny_nose).
has_symptom(sinusitis, sore_throat).
has_symptom(sinusitis, fever).

% Add to diagnosis.pl
possible_disease(PatientSymptoms, sinusitis) :-
    (has_all_symptoms(PatientSymptoms, [headache, runny_nose]);
     has_all_symptoms(PatientSymptoms, [headache, sore_throat, runny_nose]);
     (has_patient_symptom(PatientSymptoms, headache), 
      has_patient_symptom(PatientSymptoms, fever), 
      has_patient_symptom(PatientSymptoms, runny_nose))).
```

---

## Key Learning Points

### When to Use Imperative:
- Performance is critical
- Integration with existing C++ systems
- Complex data processing and algorithms
- Need explicit control over execution

### When to Use Declarative:
- Rule-based systems and expert systems
- Complex logical relationships
- Frequent rule changes and updates
- Natural language-like rule expression
- Rapid prototyping of knowledge systems

### Hybrid Approach:
In real-world applications, you might:
1. Use **Prolog for rule definition and prototyping**
2. **Convert to C++ for production** performance
3. Use **Prolog as a configuration language** for C++ systems
4. **Embed Prolog in C++** for dynamic rule evaluation

---

## Performance Considerations

### C++ Performance:
- Direct memory access
- Compiled to native machine code
- O(1) rule evaluation for most cases
- Suitable for real-time applications

### Prolog Performance:
- Interpreted execution with inference overhead
- Backtracking can be expensive
- Better for complex logical reasoning
- Suitable for expert systems and AI applications

---

## Conclusion

Both paradigms have their place in software development:

- **Imperative programming** excels in system programming, performance-critical applications, and when you need explicit control over execution.

- **Declarative programming** shines in domain-specific applications, rule-based systems, and scenarios where the logic is complex but the execution details are less important.

The MediCheck project demonstrates that the same problem can be elegantly solved using different approaches, each with its own trade-offs and advantages.
