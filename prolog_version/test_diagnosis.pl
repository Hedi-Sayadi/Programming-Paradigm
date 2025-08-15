% Test cases and examples for the MediCheck Prolog diagnosis system
% This file demonstrates how to use the diagnosis system

:- consult(diagnosis).

% Test cases with known symptom combinations

test_common_cold :-
    format('Testing Common Cold diagnosis:~n'),
    diagnose([runny_nose, sore_throat], Diseases1),
    format('  [runny_nose, sore_throat] -> ~w~n', [Diseases1]),
    diagnose([runny_nose, cough], Diseases2),
    format('  [runny_nose, cough] -> ~w~n', [Diseases2]).

test_flu :-
    format('Testing Flu diagnosis:~n'),
    diagnose([fever, cough], Diseases1),
    format('  [fever, cough] -> ~w~n', [Diseases1]),
    diagnose([fever, muscle_aches, fatigue], Diseases2),
    format('  [fever, muscle_aches, fatigue] -> ~w~n', [Diseases2]).

test_covid19 :-
    format('Testing COVID-19 diagnosis:~n'),
    diagnose([loss_of_taste, loss_of_smell], Diseases1),
    format('  [loss_of_taste, loss_of_smell] -> ~w~n', [Diseases1]),
    diagnose([fever, cough, loss_of_taste], Diseases2),
    format('  [fever, cough, loss_of_taste] -> ~w~n', [Diseases2]).

test_pneumonia :-
    format('Testing Pneumonia diagnosis:~n'),
    diagnose([fever, cough, shortness_of_breath], Diseases1),
    format('  [fever, cough, shortness_of_breath] -> ~w~n', [Diseases1]).

test_gastroenteritis :-
    format('Testing Gastroenteritis diagnosis:~n'),
    diagnose([nausea, vomiting, diarrhea], Diseases1),
    format('  [nausea, vomiting, diarrhea] -> ~w~n', [Diseases1]).

test_strep_throat :-
    format('Testing Strep Throat diagnosis:~n'),
    diagnose([sore_throat, fever], Diseases1),
    format('  [sore_throat, fever] (should include strep_throat) -> ~w~n', [Diseases1]).

test_single_symptoms :-
    format('Testing single symptom conditions:~n'),
    diagnose([fever], Diseases1),
    format('  [fever] -> ~w~n', [Diseases1]),
    diagnose([headache], Diseases2),
    format('  [headache] -> ~w~n', [Diseases2]),
    diagnose([rash], Diseases3),
    format('  [rash] -> ~w~n', [Diseases3]).

test_complex_case :-
    format('Testing complex case with multiple possible diseases:~n'),
    diagnose([fever, cough, headache, fatigue], Diseases),
    format('  [fever, cough, headache, fatigue] -> ~w~n', [Diseases]).

% Run all tests
run_all_tests :-
    format('=== MediCheck Prolog Diagnosis System Tests ===~n~n'),
    test_common_cold, nl,
    test_flu, nl,
    test_covid19, nl,
    test_pneumonia, nl,
    test_gastroenteritis, nl,
    test_strep_throat, nl,
    test_single_symptoms, nl,
    test_complex_case, nl,
    format('=== Tests completed ===~n').

% Interactive examples for README
example_queries :-
    format('=== Example Queries ===~n'),
    format('1. Basic diagnosis:~n'),
    format('   ?- diagnose([fever, cough], Diseases).~n'),
    format('2. Detailed diagnosis with confidence:~n'),
    format('   ?- diagnose_detailed([fever, cough, headache], Results).~n'),
    format('3. Explain diagnosis:~n'),
    format('   ?- explain_diagnosis([loss_of_taste, loss_of_smell]).~n'),
    format('4. Check if specific disease is possible:~n'),
    format('   ?- possible_disease([fever, cough], flu).~n'),
    format('5. Run tests:~n'),
    format('   ?- run_all_tests.~n').

% Show available symptoms
show_symptoms :-
    format('Available symptoms:~n'),
    findall(Symptom, symptom(Symptom), Symptoms),
    sort(Symptoms, SortedSymptoms),
    forall(member(S, SortedSymptoms), format('  - ~w~n', [S])).

% Show available diseases
show_diseases :-
    format('Available diseases:~n'),
    findall(Disease, disease(Disease), Diseases),
    sort(Diseases, SortedDiseases),
    forall(member(D, SortedDiseases), format('  - ~w~n', [D])).

% Quick start guide
help :-
    format('=== MediCheck Prolog Diagnosis System Help ===~n~n'),
    show_symptoms, nl,
    show_diseases, nl,
    example_queries.
