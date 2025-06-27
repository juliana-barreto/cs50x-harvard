#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct {
    char name[100];
    int votes;
} candidate;
// Array of candidates
candidate candidates[MAX];
// Number of candidates
int candidate_count;

int vote(char* name) {
    for (int i = 0; i < candidate_count; i++) {
        // Check if the name matches a candidate
        if (strcmp(candidates[i].name, name) == 0) {
            // Increment the vote count for the candidate
            candidates[i].votes++;
            return 1;
        }
    }
    return 0;
}
void print_winner(void) {
    int max_votes = 0, winners_index[candidate_count], winner_count = 0;
    // Find the maximum number of votes
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes > max_votes) {
            max_votes = candidates[i].votes;
        }
    }
    // Check the winner(s)
    for (int i = 0; i < candidate_count; i++) {
        if (candidates[i].votes == max_votes) {
            winners_index[winner_count] = i;
            winner_count++;
        }
    }
    if (winner_count == 1) {
        // If there's a single winner, print their name
        printf("%s\n", candidates[winners_index[0]].name);
    } else {
        // If there are multiple winners, print all their names
        printf("Tie between: ");
        for (int i = 0; i < winner_count; i++) {
            printf("%s\n", candidates[winners_index[i]].name);
        }
    }
}
int main(int argc, char *argv[]) {
    int voter_count;
    char name[100];
    // Check for invalid usage
    if (argc < 2) {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }
    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX) {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++) {
        strcpy(candidates[i].name, argv[i + 1]);
        candidates[i].votes = 0;
    }
    printf("Number of voters: ");
    scanf("%d", &voter_count);
    // Loop over all voters
    for (int i = 0; i < voter_count; i++) {
        printf("Vote: ");
        scanf("%s", name);
        // Check for invalid vote
        if (!vote(name))
            printf("Invalid vote.\n");
    }
    // Display winner of election
    print_winner();
}