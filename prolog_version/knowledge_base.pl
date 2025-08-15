% Prolog knowledge base for symptoms and diseases
% This file contains facts about symptoms and disease relationships

% Symptom definitions - all possible symptoms in the system
symptom(fever).
symptom(cough).
symptom(headache).
symptom(sore_throat).
symptom(runny_nose).
symptom(shortness_of_breath).
symptom(fatigue).
symptom(muscle_aches).
symptom(nausea).
symptom(vomiting).
symptom(diarrhea).
symptom(loss_of_taste).
symptom(loss_of_smell).
symptom(chest_pain).
symptom(dizziness).
symptom(rash).
symptom(joint_pain).
symptom(chills).

% Disease definitions
disease(common_cold).
disease(flu).
disease(covid19).
disease(pneumonia).
disease(gastroenteritis).
disease(migraine).
disease(allergic_reaction).
disease(strep_throat).
disease(bronchitis).
disease(food_poisoning).
disease(sinusitis).
disease(asthma).
disease(anxiety_panic_attack).
disease(dehydration).
disease(arthritis).
disease(inflammatory_arthritis).
disease(tension_headache).
disease(skin_condition).
disease(fever_unknown_cause).

% Primary symptom-disease relationships
% Format: has_symptom(Disease, Symptom)

% Common Cold symptoms
has_symptom(common_cold, runny_nose).
has_symptom(common_cold, sore_throat).
has_symptom(common_cold, cough).
has_symptom(common_cold, headache).

% Flu symptoms
has_symptom(flu, fever).
has_symptom(flu, cough).
has_symptom(flu, muscle_aches).
has_symptom(flu, fatigue).
has_symptom(flu, headache).
has_symptom(flu, chills).

% COVID-19 symptoms
has_symptom(covid19, fever).
has_symptom(covid19, cough).
has_symptom(covid19, loss_of_taste).
has_symptom(covid19, loss_of_smell).
has_symptom(covid19, shortness_of_breath).
has_symptom(covid19, fatigue).
has_symptom(covid19, muscle_aches).
has_symptom(covid19, headache).
has_symptom(covid19, sore_throat).

% Pneumonia symptoms
has_symptom(pneumonia, fever).
has_symptom(pneumonia, cough).
has_symptom(pneumonia, shortness_of_breath).
has_symptom(pneumonia, chest_pain).
has_symptom(pneumonia, chills).

% Gastroenteritis symptoms
has_symptom(gastroenteritis, nausea).
has_symptom(gastroenteritis, vomiting).
has_symptom(gastroenteritis, diarrhea).
has_symptom(gastroenteritis, fever).

% Migraine symptoms
has_symptom(migraine, headache).
has_symptom(migraine, nausea).
has_symptom(migraine, dizziness).
has_symptom(migraine, vomiting).

% Allergic Reaction symptoms
has_symptom(allergic_reaction, rash).
has_symptom(allergic_reaction, runny_nose).
has_symptom(allergic_reaction, sore_throat).
has_symptom(allergic_reaction, shortness_of_breath).

% Strep Throat symptoms
has_symptom(strep_throat, sore_throat).
has_symptom(strep_throat, fever).

% Bronchitis symptoms
has_symptom(bronchitis, cough).
has_symptom(bronchitis, chest_pain).
has_symptom(bronchitis, fatigue).
has_symptom(bronchitis, shortness_of_breath).

% Food Poisoning symptoms
has_symptom(food_poisoning, nausea).
has_symptom(food_poisoning, vomiting).
has_symptom(food_poisoning, diarrhea).
has_symptom(food_poisoning, fever).

% Sinusitis symptoms
has_symptom(sinusitis, headache).
has_symptom(sinusitis, runny_nose).
has_symptom(sinusitis, sore_throat).
has_symptom(sinusitis, fever).

% Asthma symptoms
has_symptom(asthma, shortness_of_breath).
has_symptom(asthma, cough).
has_symptom(asthma, chest_pain).

% Anxiety/Panic Attack symptoms
has_symptom(anxiety_panic_attack, shortness_of_breath).
has_symptom(anxiety_panic_attack, dizziness).
has_symptom(anxiety_panic_attack, chest_pain).
has_symptom(anxiety_panic_attack, nausea).

% Dehydration symptoms
has_symptom(dehydration, dizziness).
has_symptom(dehydration, fatigue).
has_symptom(dehydration, headache).

% Arthritis symptoms
has_symptom(arthritis, joint_pain).
has_symptom(inflammatory_arthritis, joint_pain).
has_symptom(inflammatory_arthritis, fever).

% Single symptom conditions
has_symptom(tension_headache, headache).
has_symptom(skin_condition, rash).
has_symptom(fever_unknown_cause, fever).
