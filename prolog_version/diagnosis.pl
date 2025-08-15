% Prolog disease prediction rules
% Main diagnosis system using declarative programming

% Include the knowledge base
:- consult(knowledge_base).

% Helper predicates

% Check if a symptom is in the patient's symptom list
has_patient_symptom(PatientSymptoms, Symptom) :-
    member(Symptom, PatientSymptoms).

% Check if patient has all symptoms in a list
has_all_symptoms(_, []).
has_all_symptoms(PatientSymptoms, [Symptom|Rest]) :-
    has_patient_symptom(PatientSymptoms, Symptom),
    has_all_symptoms(PatientSymptoms, Rest).

% Check if patient has any of the symptoms in a list
has_any_symptom(PatientSymptoms, [Symptom|_]) :-
    has_patient_symptom(PatientSymptoms, Symptom).
has_any_symptom(PatientSymptoms, [_|Rest]) :-
    has_any_symptom(PatientSymptoms, Rest).

% Check if patient does NOT have a symptom
not_has_symptom(PatientSymptoms, Symptom) :-
    \+ has_patient_symptom(PatientSymptoms, Symptom).

% Count symptoms for a disease that patient has
count_matching_symptoms(PatientSymptoms, Disease, Count) :-
    findall(Symptom, (has_symptom(Disease, Symptom), has_patient_symptom(PatientSymptoms, Symptom)), MatchingSymptoms),
    length(MatchingSymptoms, Count).

% Disease prediction rules using pattern matching and logical conditions

% Rule 1: Common Cold
possible_disease(PatientSymptoms, common_cold) :-
    (has_all_symptoms(PatientSymptoms, [runny_nose, sore_throat]);
     has_all_symptoms(PatientSymptoms, [runny_nose, cough]);
     has_all_symptoms(PatientSymptoms, [sore_throat, cough]);
     has_all_symptoms(PatientSymptoms, [runny_nose, headache])).

% Rule 2: Flu
possible_disease(PatientSymptoms, flu) :-
    (has_all_symptoms(PatientSymptoms, [fever, cough]);
     has_all_symptoms(PatientSymptoms, [fever, muscle_aches]);
     has_all_symptoms(PatientSymptoms, [fever, fatigue, headache]);
     has_all_symptoms(PatientSymptoms, [fever, chills]);
     has_all_symptoms(PatientSymptoms, [muscle_aches, fatigue, headache])).

% Rule 3: COVID-19
possible_disease(PatientSymptoms, covid19) :-
    (has_all_symptoms(PatientSymptoms, [fever, cough, loss_of_taste]);
     has_all_symptoms(PatientSymptoms, [fever, shortness_of_breath]);
     has_all_symptoms(PatientSymptoms, [loss_of_taste, loss_of_smell]);
     has_all_symptoms(PatientSymptoms, [fever, fatigue, muscle_aches]);
     has_all_symptoms(PatientSymptoms, [cough, loss_of_taste]);
     has_all_symptoms(PatientSymptoms, [cough, loss_of_smell]);
     has_all_symptoms(PatientSymptoms, [fever, headache, sore_throat])).

% Rule 4: Pneumonia
possible_disease(PatientSymptoms, pneumonia) :-
    (has_all_symptoms(PatientSymptoms, [fever, cough, shortness_of_breath]);
     has_all_symptoms(PatientSymptoms, [chest_pain, cough, fever]);
     has_all_symptoms(PatientSymptoms, [shortness_of_breath, chest_pain]);
     has_all_symptoms(PatientSymptoms, [fever, chills, shortness_of_breath])).

% Rule 5: Gastroenteritis
possible_disease(PatientSymptoms, gastroenteritis) :-
    (has_all_symptoms(PatientSymptoms, [nausea, vomiting, diarrhea]);
     has_all_symptoms(PatientSymptoms, [nausea, diarrhea]);
     has_all_symptoms(PatientSymptoms, [vomiting, diarrhea]);
     has_all_symptoms(PatientSymptoms, [nausea, vomiting]);
     (has_patient_symptom(PatientSymptoms, diarrhea), has_patient_symptom(PatientSymptoms, fever))).

% Rule 6: Migraine
possible_disease(PatientSymptoms, migraine) :-
    (has_all_symptoms(PatientSymptoms, [headache, nausea]);
     has_all_symptoms(PatientSymptoms, [headache, dizziness]);
     (has_patient_symptom(PatientSymptoms, headache), has_patient_symptom(PatientSymptoms, vomiting))).

% Rule 7: Allergic Reaction
possible_disease(PatientSymptoms, allergic_reaction) :-
    (has_all_symptoms(PatientSymptoms, [rash, runny_nose]);
     has_all_symptoms(PatientSymptoms, [rash, sore_throat]);
     (has_patient_symptom(PatientSymptoms, rash), has_patient_symptom(PatientSymptoms, shortness_of_breath))).

% Rule 8: Strep Throat (specific exclusion rule)
possible_disease(PatientSymptoms, strep_throat) :-
    has_all_symptoms(PatientSymptoms, [sore_throat, fever]),
    not_has_symptom(PatientSymptoms, runny_nose),
    not_has_symptom(PatientSymptoms, cough).

% Rule 9: Bronchitis
possible_disease(PatientSymptoms, bronchitis) :-
    (has_all_symptoms(PatientSymptoms, [cough, chest_pain]);
     has_all_symptoms(PatientSymptoms, [cough, fatigue]);
     (has_patient_symptom(PatientSymptoms, cough), has_patient_symptom(PatientSymptoms, shortness_of_breath))).

% Rule 10: Food Poisoning
possible_disease(PatientSymptoms, food_poisoning) :-
    (has_all_symptoms(PatientSymptoms, [nausea, vomiting]);
     has_all_symptoms(PatientSymptoms, [diarrhea, nausea]);
     has_all_symptoms(PatientSymptoms, [vomiting, diarrhea, fever])).

% Rule 11: Sinusitis
possible_disease(PatientSymptoms, sinusitis) :-
    (has_all_symptoms(PatientSymptoms, [headache, runny_nose]);
     has_all_symptoms(PatientSymptoms, [headache, sore_throat, runny_nose]);
     (has_patient_symptom(PatientSymptoms, headache), has_patient_symptom(PatientSymptoms, fever), has_patient_symptom(PatientSymptoms, runny_nose))).

% Rule 12: Asthma
possible_disease(PatientSymptoms, asthma) :-
    (has_all_symptoms(PatientSymptoms, [shortness_of_breath, cough]);
     (has_patient_symptom(PatientSymptoms, shortness_of_breath), has_patient_symptom(PatientSymptoms, chest_pain))).

% Rule 13: Anxiety/Panic Attack
possible_disease(PatientSymptoms, anxiety_panic_attack) :-
    (has_all_symptoms(PatientSymptoms, [shortness_of_breath, dizziness]);
     has_all_symptoms(PatientSymptoms, [chest_pain, dizziness]);
     has_all_symptoms(PatientSymptoms, [nausea, dizziness, shortness_of_breath])).

% Rule 14: Dehydration
possible_disease(PatientSymptoms, dehydration) :-
    (has_all_symptoms(PatientSymptoms, [dizziness, fatigue]);
     has_all_symptoms(PatientSymptoms, [headache, dizziness, fatigue])).

% Rule 15: Arthritis conditions
possible_disease(PatientSymptoms, inflammatory_arthritis) :-
    has_patient_symptom(PatientSymptoms, joint_pain),
    has_patient_symptom(PatientSymptoms, fever).

possible_disease(PatientSymptoms, arthritis) :-
    has_patient_symptom(PatientSymptoms, joint_pain),
    not_has_symptom(PatientSymptoms, fever).

% Single symptom conditions
possible_disease(PatientSymptoms, fever_unknown_cause) :-
    has_patient_symptom(PatientSymptoms, fever),
    length(PatientSymptoms, 1).

possible_disease(PatientSymptoms, tension_headache) :-
    has_patient_symptom(PatientSymptoms, headache),
    length(PatientSymptoms, 1).

possible_disease(PatientSymptoms, skin_condition) :-
    has_patient_symptom(PatientSymptoms, rash),
    length(PatientSymptoms, 1).

% Main prediction predicate
predict_diseases(PatientSymptoms, Diseases) :-
    findall(Disease, possible_disease(PatientSymptoms, Disease), DiseaseList),
    sort(DiseaseList, Diseases).

% Alternative: Get diseases with confidence scores
predict_diseases_with_confidence(PatientSymptoms, DiseasesWithScores) :-
    findall(Disease-Score, (
        possible_disease(PatientSymptoms, Disease),
        count_matching_symptoms(PatientSymptoms, Disease, Score)
    ), DiseaseScorePairs),
    sort(2, @>=, DiseaseScorePairs, DiseasesWithScores).

% Query helpers for interactive use

% Simple query: What diseases match these symptoms?
% Usage: ?- diagnose([fever, cough], Diseases).
diagnose(PatientSymptoms, Diseases) :-
    predict_diseases(PatientSymptoms, Diseases).

% Detailed query with confidence scores
% Usage: ?- diagnose_detailed([fever, cough, headache], Results).
diagnose_detailed(PatientSymptoms, Results) :-
    predict_diseases_with_confidence(PatientSymptoms, Results).

% Interactive diagnosis - shows explanation
explain_diagnosis(PatientSymptoms) :-
    format('Patient symptoms: ~w~n', [PatientSymptoms]),
    predict_diseases(PatientSymptoms, Diseases),
    (   Diseases = []
    ->  format('No matching conditions found.~n')
    ;   format('Possible conditions:~n'),
        forall(member(Disease, Diseases), format('  - ~w~n', [Disease]))
    ).
