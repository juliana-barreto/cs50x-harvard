#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX] = {0};

// locked[i][j] means i is locked in over j
int locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct {
    int winner;
    int loser;
} pair;

// Array of candidates
char candidates[MAX][100];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count = 0;
int candidate_count = 0;

// Update ranks given a new vote
int vote(int rank, char* name, int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp(candidates[i], name) == 0) {
            ranks[rank] = i; // Store the index of the candidate in ranks
            return 1; // Vote is valid
        }
    }
    return 0;
}
// Update preferences given one voter's ranks
void record_preferences(const int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}
// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
            if (preferences[i][j] > preferences[j][i]) {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences[i][j]) {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
    for (int i = 0; i < pair_count; i++) {
        for (int j = i + 1; j < pair_count; j++) {
            int strength_i = preferences[pairs[i].winner][pairs[i].loser] -
                preferences[pairs[i].loser][pairs[i].winner];
            int strength_j = preferences[pairs[j].winner][pairs[j].loser] -
                preferences[pairs[j].loser][pairs[j].winner];
            if (strength_i < strength_j) {
                // Swap pairs[i] and pairs[j]
                pair temp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = temp;
            }
        }
    }
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) {

}
// Print the winner of the election
void print_winner(void) {
    // TODO
}
int main(int argc, char* argv[]) {
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }
    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        strcpy(candidates[i], argv[i + 1]);
    }
    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            locked[i][j] = 0;
        }
    }
    pair_count = 0;
    int voter_count;
    printf("Number of voters: ");
    scanf("%d", &voter_count);
    // Query for votes
    for (int i = 0; i < voter_count; i++) {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];
        // Query for each rank
        for (int j = 0; j < candidate_count; j++) {
            char name[100];
            printf("Rank %i: ", j + 1);
            scanf("%s", name);
            if (!vote(j, name, ranks)) {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);
        printf("\n");
    }
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

