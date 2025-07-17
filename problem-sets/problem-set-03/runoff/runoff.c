#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];
// Candidates have name, vote count, eliminated status
typedef struct {
    char name[100];
    int votes;
    int eliminated;
} candidate;
// Array of candidates
candidate candidates[MAX_CANDIDATES];
// Numbers of voters and candidates
int voter_count;
int candidate_count;
// Record preference if vote is valid
int vote(int voter, int rank, const char* name) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(name, candidates[i].name) == 0) {
            preferences[voter][rank] = i;
            return 1;
        }
    }
    return 0;
}
// Tabulate votes for non-eliminated candidates
void tabulate(void) {
    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            int index = preferences[i][j];
            if (candidates[index].eliminated == 0) {
                candidates[index].votes++;
                break;
            }
        }
    }
}
// Print the winner of the election, if there is one
int print_winner(void) {
    double majority = 0.5 * voter_count;
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > majority) {
            printf("%s wins\n", candidates[i].name);
            return 1;
        }
    }
    return 0;
}
// Return the minimum number of votes any remaining candidate has
int find_min(void) {
    int min_votes = MAX_VOTERS;
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes < min_votes) {
            min_votes = candidates[i].votes;
        }
    }
    return min_votes;
}
// Return true if the election is tied between all candidates, false otherwise
int is_tie(int min) {
    int remaining_candidates = 0;
    int candidates_with_min_votes = 0;
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].eliminated ==0) {
            remaining_candidates++;
        }
        if (candidates[i].votes == min) {
            candidates_with_min_votes++;
        }
    }
    if (remaining_candidates == candidates_with_min_votes) {
        return 1;
    } else {
        return 0;
    }
}
// Eliminate the candidate (or candidates) in last place
void eliminate(int min) {
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == min && candidates[i].eliminated == 0) {
            candidates[i].eliminated = 1;
        }
    }
}
int main(int argc, char* argv[]) {
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }
    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES) {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
        candidates[i].eliminated = 0;
    }
    printf("Number of voters: ");
    scanf("%i", &voter_count);
    getchar();
    if (voter_count > MAX_VOTERS) {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }
    // Keep querying for votes
    for (int i = 0; i < voter_count; i++) {
        // Query for each rank
        for (int j = 0; j < candidate_count; j++) {
            printf("Rank %i: ", j + 1);
            char name[100];
            fgets(name, sizeof(candidates[0].name), stdin);
            name[strcspn(name, "\n")] = 0;
            // Record vote, unless it's invalid
            if (!vote(i, j, name)) {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }
    // Keep holding runoffs until winner exists
    while (1) {
        // Calculate votes given remaining candidates
        tabulate();
        // Check if election has been won
        int won = print_winner();
        if (won) {
            break;
        }
        // Eliminate last-place candidates
        int min = find_min();
        int tie = is_tie(min);
        // If tied, everyone wins
        if (tie) {
            for (int i = 0; i < candidate_count; i++) {
                if (!candidates[i].eliminated) {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }
        // Eliminate anyone with minimum number of votes
        eliminate(min);
        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++) {
            candidates[i].votes = 0;
        }
    }
    return 0;
}
