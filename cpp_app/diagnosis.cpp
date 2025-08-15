// Imperative disease prediction rules
#include "diagnosis.h"
#include <algorithm>
#include <set>

using namespace std;

// check if a symptom exists in the list
bool hasSymptom(const vector<string>& symptoms, const string& symptom) {
    return find(symptoms.begin(), symptoms.end(), symptom) != symptoms.end();
}

// check if multiple symptoms exist
bool hasSymptoms(const vector<string>& symptoms, const vector<string>& requiredSymptoms) {
    for (const auto& symptom : requiredSymptoms) {
        if (!hasSymptom(symptoms, symptom)) {
            return false;
        }
    }
    return true;
}

vector<string> predictDiseases(const vector<string>& symptoms) {
    set<string> diseases; // Using set to avoid duplicates

    // Rule 1: Common Cold
    if (hasSymptoms(symptoms, {"runny nose", "sore throat"}) ||
        hasSymptoms(symptoms, {"runny nose", "cough"}) ||
        hasSymptoms(symptoms, {"sore throat", "cough"}) ||
        (hasSymptom(symptoms, "runny nose") && hasSymptom(symptoms, "headache"))) {
        diseases.insert("Common Cold");
    }

    // Rule 2: Flu (Influenza)
    if (hasSymptoms(symptoms, {"fever", "cough"}) ||
        hasSymptoms(symptoms, {"fever", "muscle aches"}) ||
        hasSymptoms(symptoms, {"fever", "fatigue", "headache"}) ||
        hasSymptoms(symptoms, {"fever", "chills"}) ||
        hasSymptoms(symptoms, {"muscle aches", "fatigue", "headache"})) {
        diseases.insert("Flu");
    }

    // Rule 3: COVID-19
    if (hasSymptoms(symptoms, {"fever", "cough", "loss of taste"}) ||
        hasSymptoms(symptoms, {"fever", "shortness of breath"}) ||
        hasSymptoms(symptoms, {"loss of taste", "loss of smell"}) ||
        hasSymptoms(symptoms, {"fever", "fatigue", "muscle aches"}) ||
        hasSymptoms(symptoms, {"cough", "loss of taste"}) ||
        hasSymptoms(symptoms, {"cough", "loss of smell"}) ||
        hasSymptoms(symptoms, {"fever", "headache", "sore throat"})) {
        diseases.insert("COVID-19");
    }

    // Rule 4: Pneumonia
    if (hasSymptoms(symptoms, {"fever", "cough", "shortness of breath"}) ||
        hasSymptoms(symptoms, {"chest pain", "cough", "fever"}) ||
        hasSymptoms(symptoms, {"shortness of breath", "chest pain"}) ||
        hasSymptoms(symptoms, {"fever", "chills", "shortness of breath"})) {
        diseases.insert("Pneumonia");
    }

    // Rule 5: Gastroenteritis (Stomach Flu)
    if (hasSymptoms(symptoms, {"nausea", "vomiting", "diarrhea"}) ||
        hasSymptoms(symptoms, {"nausea", "diarrhea"}) ||
        hasSymptoms(symptoms, {"vomiting", "diarrhea"}) ||
        hasSymptoms(symptoms, {"nausea", "vomiting"}) ||
        (hasSymptom(symptoms, "diarrhea") && hasSymptom(symptoms, "fever"))) {
        diseases.insert("Gastroenteritis");
    }

    // Rule 6: Migraine
    if (hasSymptoms(symptoms, {"headache", "nausea"}) ||
        hasSymptoms(symptoms, {"headache", "dizziness"}) ||
        (hasSymptom(symptoms, "headache") && hasSymptom(symptoms, "vomiting"))) {
        diseases.insert("Migraine");
    }

    // Rule 7: Allergic Reaction
    if (hasSymptoms(symptoms, {"rash", "runny nose"}) ||
        hasSymptoms(symptoms, {"rash", "sore throat"}) ||
        (hasSymptom(symptoms, "rash") && hasSymptom(symptoms, "shortness of breath"))) {
        diseases.insert("Allergic Reaction");
    }

    // Rule 8: Strep Throat
    if (hasSymptoms(symptoms, {"sore throat", "fever"}) &&
        !hasSymptom(symptoms, "runny nose") &&
        !hasSymptom(symptoms, "cough")) {
        diseases.insert("Strep Throat");
    }

    // Rule 9: Bronchitis
    if (hasSymptoms(symptoms, {"cough", "chest pain"}) ||
        hasSymptoms(symptoms, {"cough", "fatigue"}) ||
        (hasSymptom(symptoms, "cough") && hasSymptom(symptoms, "shortness of breath"))) {
        diseases.insert("Bronchitis");
    }

    // Rule 10: Food Poisoning
    if (hasSymptoms(symptoms, {"nausea", "vomiting"}) ||
        hasSymptoms(symptoms, {"diarrhea", "nausea"}) ||
        hasSymptoms(symptoms, {"vomiting", "diarrhea", "fever"})) {
        diseases.insert("Food Poisoning");
    }

    // Rule 11: Sinusitis
    if (hasSymptoms(symptoms, {"headache", "runny nose"}) ||
        hasSymptoms(symptoms, {"headache", "sore throat", "runny nose"}) ||
        (hasSymptom(symptoms, "headache") && hasSymptom(symptoms, "fever") && hasSymptom(symptoms, "runny nose"))) {
        diseases.insert("Sinusitis");
    }

    // Rule 12: Asthma Attack
    if (hasSymptoms(symptoms, {"shortness of breath", "cough"}) ||
        (hasSymptom(symptoms, "shortness of breath") && hasSymptom(symptoms, "chest pain"))) {
        diseases.insert("Asthma");
    }

    // Rule 13: Anxiety/Panic Attack
    if (hasSymptoms(symptoms, {"shortness of breath", "dizziness"}) ||
        hasSymptoms(symptoms, {"chest pain", "dizziness"}) ||
        hasSymptoms(symptoms, {"nausea", "dizziness", "shortness of breath"})) {
        diseases.insert("Anxiety/Panic Attack");
    }

    // Rule 14: Dehydration
    if (hasSymptoms(symptoms, {"dizziness", "fatigue"}) ||
        hasSymptoms(symptoms, {"headache", "dizziness", "fatigue"})) {
        diseases.insert("Dehydration");
    }

    // Rule 15: Arthritis/Joint Issues
    if (hasSymptom(symptoms, "joint pain")) {
        if (hasSymptom(symptoms, "fever")) {
            diseases.insert("Inflammatory Arthritis");
        } else {
            diseases.insert("Arthritis");
        }
    }

    // Single symptom conditions
    if (hasSymptom(symptoms, "fever") && symptoms.size() == 1) {
        diseases.insert("Fever (Unknown Cause)");
    }

    if (hasSymptom(symptoms, "headache") && symptoms.size() == 1) {
        diseases.insert("Tension Headache");
    }

    if (hasSymptom(symptoms, "rash") && symptoms.size() == 1) {
        diseases.insert("Skin Condition");
    }

    // Convert set to vector
    return vector<string>(diseases.begin(), diseases.end());
}
