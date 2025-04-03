#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STATES 50
#define MAX_INPUTS 10

typedef struct {
    int elements[MAX_STATES];
    int count;
} StateCollection;

typedef struct {
    int transitions[MAX_STATES][MAX_INPUTS][MAX_STATES];
    int transitionCount[MAX_STATES][MAX_INPUTS];
    int totalStates;
    int totalInputs;
    bool finalStates[MAX_STATES];
} NonDeterministicFA;

typedef struct {
    int transitions[MAX_STATES][MAX_INPUTS];
    int totalStates;
    int totalInputs;
    bool finalStates[MAX_STATES];
    StateCollection dfaStates[MAX_STATES];
} DeterministicFA;

void initializeStateCollection(StateCollection* set) {
    set->count = 0;
}

void insertState(StateCollection* set, int state) {
    for (int i = 0; i < set->count; i++) {
        if (set->elements[i] == state) return;
    }
    set->elements[set->count++] = state;
    
    for (int i = 0; i < set->count - 1; i++) {
        for (int j = 0; j < set->count - i - 1; j++) {
            if (set->elements[j] > set->elements[j + 1]) {
                int temp = set->elements[j];
                set->elements[j] = set->elements[j + 1];
                set->elements[j + 1] = temp;
            }
        }
    }
}

void copyStateCollection(StateCollection* dest, StateCollection* src) {
    dest->count = src->count;
    for (int i = 0; i < src->count; i++) {
        dest->elements[i] = src->elements[i];
    }
}

bool isEqualStateCollection(StateCollection* set1, StateCollection* set2) {
    if (set1->count != set2->count) return false;
    for (int i = 0; i < set1->count; i++) {
        if (set1->elements[i] != set2->elements[i]) return false;
    }
    return true;
}

int locateStateSet(DeterministicFA* dfa, StateCollection* currSet) {
    for (int i = 0; i < dfa->totalStates; i++) {
        if (isEqualStateCollection(&dfa->dfaStates[i], currSet)) {
            return i;
        }
    }
    return -1;
}

void inputNFA(NonDeterministicFA* nfa) {
    printf("Enter number of states in NFA: ");
    scanf("%d", &nfa->totalStates);
    
    printf("Enter number of input symbols (excluding epsilon): ");
    scanf("%d", &nfa->totalInputs);

    memset(nfa->transitions, 0, sizeof(nfa->transitions));
    memset(nfa->transitionCount, 0, sizeof(nfa->transitionCount));
    memset(nfa->finalStates, 0, sizeof(nfa->finalStates));
    
    printf("\nProvide state transitions:\n");
    for (int state = 0; state < nfa->totalStates; state++) {
        for (int symbol = 0; symbol < nfa->totalInputs; symbol++) {
            printf("For state %d, on input %d:\n", state, symbol);
            printf("Enter number of reachable states: ");
            scanf("%d", &nfa->transitionCount[state][symbol]);
            
            if (nfa->transitionCount[state][symbol] > 0) {
                printf("Enter reachable states: ");
                for (int i = 0; i < nfa->transitionCount[state][symbol]; i++) {
                    scanf("%d", &nfa->transitions[state][symbol][i]);
                }
            }
        }
    }
    
    printf("\nEnter the number of final states: ");
    int numFinal;
    scanf("%d", &numFinal);
    
    printf("Enter final state numbers: ");
    for (int i = 0; i < numFinal; i++) {
        int finalState;
        scanf("%d", &finalState);
        if (finalState < nfa->totalStates) {
            nfa->finalStates[finalState] = true;
        }
    }
}

void nfaToDfaConversion(NonDeterministicFA* nfa, DeterministicFA* dfa) {
    dfa->totalInputs = nfa->totalInputs;
    dfa->totalStates = 0;
    memset(dfa->transitions, -1, sizeof(dfa->transitions));
    memset(dfa->finalStates, 0, sizeof(dfa->finalStates));
    
    initializeStateCollection(&dfa->dfaStates[0]);
    insertState(&dfa->dfaStates[0], 0);
    dfa->totalStates = 1;
    
    for (int currentState = 0; currentState < dfa->totalStates; currentState++) {

        for (int symbol = 0; symbol < nfa->totalInputs; symbol++) {
            StateCollection nextStateSet;
            initializeStateCollection(&nextStateSet);
            
            for (int i = 0; i < dfa->dfaStates[currentState].count; i++) {
                int presentState = dfa->dfaStates[currentState].elements[i];
                for (int j = 0; j < nfa->transitionCount[presentState][symbol]; j++) {
                    insertState(&nextStateSet, nfa->transitions[presentState][symbol][j]);
                }
            }

            if (nextStateSet.count > 0) {
                int existingState = locateStateSet(dfa, &nextStateSet);
                if (existingState == -1) {
                    copyStateCollection(&dfa->dfaStates[dfa->totalStates], &nextStateSet);
                    
                    for (int i = 0; i < nextStateSet.count; i++) {
                        if (nfa->finalStates[nextStateSet.elements[i]]) {
                            dfa->finalStates[dfa->totalStates] = true;
                            break;
                        }
                    }
                    
                    dfa->transitions[currentState][symbol] = dfa->totalStates;
                    dfa->totalStates++;
                } else {
                    dfa->transitions[currentState][symbol] = existingState;
                }
            }
        }
    }
}

void displayDFA(DeterministicFA* dfa) {
    printf("\nDFA Transition Table:\n");
    printf("State\tDFA Set\t\t");
    for (int i = 0; i < dfa->totalInputs; i++) {
        printf("Input %d\t\t", i);
    }
    printf("Final State?\n");
    
    for (int i = 0; i < dfa->totalStates; i++) {
        printf("%d\t", i);
        
        printf("{");
        for (int j = 0; j < dfa->dfaStates[i].count; j++) {
            printf("%d", dfa->dfaStates[i].elements[j]);
            if (j < dfa->dfaStates[i].count - 1) printf(",");
        }
        printf("}\t\t");
        
        for (int j = 0; j < dfa->totalInputs; j++) {
            if (dfa->transitions[i][j] == -1) {
                printf("null\t\t");
            } else {
                printf("{");
                StateCollection* nextSet = &dfa->dfaStates[dfa->transitions[i][j]];
                for (int k = 0; k < nextSet->count; k++) {
                    printf("%d", nextSet->elements[k]);
                    if (k < nextSet->count - 1) printf(",");
                }
                printf("}\t\t");
            }
        }
        printf("%s\n", dfa->finalStates[i] ? "Yes" : "No");
    }
}

int main() {
    NonDeterministicFA nfa;
    DeterministicFA dfa;
    
    inputNFA(&nfa);
    nfaToDfaConversion(&nfa, &dfa);
    displayDFA(&dfa);
    
    return 0;
}
