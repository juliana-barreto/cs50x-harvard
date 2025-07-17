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
int vote(int rank, const char* name, int ranks[]) {
    for (int i = 0; i < candidate_count; i++) {
        if (strcmp (candidates[i], name) == 0) {
          ranks[rank] = i;
          return 1;
        }
    }
    return 0;
}
// Update preferences given one voter's ranks
void record_preferences(const int ranks[]) {
    for (int i = 0; i < candidate_count - 1; i++) {
        for (int j = i + 1; j < candidate_count; j++) {
          preferences[ranks[i]][ranks[j]]++;
        }
    }
}
// Record pairs of candidates where one is preferred over the other
void add_pairs(void) {
  for (int i = 0; i < candidate_count - 1; i++) {
      for (int j = i + 1; j < candidate_count; j++) {
          if (preferences[i][j] > preferences[j][i]) {
              pairs[pair_count].winner = i;
              pairs[pair_count].loser = j;
              pair_count++;
          } else if (preferences[i][j] < preferences[j][i]) {
              pairs[pair_count].winner = j;
              pairs[pair_count].loser = i;
              pair_count++;
          }
      }
  }
}
// Sort pairs in decreasing order by strength of victory
void sort_pairs(void) {
    for (int i = 0; i < pair_count - 1; i++) {
        for (int j = i + 1; j < pair_count; j++) {
            int strength_i = preferences[pairs[i].winner][pairs[i].loser] -
                preferences[pairs[i].loser][pairs[i].winner];
            int strength_j = preferences[pairs[j].winner][pairs[j].loser] -
                preferences[pairs[j].loser][pairs[j].winner];
            if (strength_i < strength_j) {
                pair aux = pairs[j];
                pairs[j] = pairs[i];
                pairs[i] = aux;
            }
        }
    }
}
//Checks if adding an edge creates a cycle
int check_cycle (int winner, int loser) {
    // If a path back to the winner is found, a cycle is detected
    if (winner == loser) {
        return 1;
    }
    for (int i = 0; i < candidate_count; i++) {
        // Check if there's a locked edge from 'loser' to 'i'
        if (locked[loser][i]) {
            // If the call finds the 'winner', a cycle exists.
            if (check_cycle(winner, i)) {
                return 1;
            }
        }
    }
    // If no cycles were found after checking all paths
    return 0;
}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) {
  for (int i = 0; i < pair_count; i++) {
      if (!check_cycle(pairs[i].winner, pairs[i].loser)) {
          locked[pairs[i].winner][pairs[i].loser] = 1;
      }
  }
}
// Print the winner of the election
void print_winner(void) {
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i] == 1) {
                break;
            }
            printf("%s wins\n", candidates[i]);
            return;
        }
    }
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

