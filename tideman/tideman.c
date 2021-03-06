#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
//Added Fxn to Initialize the preferences array
void initialise_preferences(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }
    initialise_preferences();

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
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

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for(int i = 0; i < candidate_count; i++){
        if(strcmp(name, candidates[i]) == 0){
        ranks[rank] = i;
        return true;
        }
    }
    return false;
}

void initialise_preferences(void){

    for(int i =0; i < candidate_count; i++){
        for(int j= 0; j < candidate_count; j++){
            preferences[i][j] = 0;
        }
    }
    return;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO

    for(int i = 0; i < candidate_count; i++){
        for(int j = 1; j < candidate_count; j++){
            if(i >= j) continue;
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    // int mostpreferred = ranks[0];
    // preferences[ranks[0]][ranks[1]]++;
    // preferences[ranks[0]][ranks[2]]++;

    // preferences[ranks[0]][ranks[3]]++;

    // preferences[ranks[1]][ranks[2]]++;
    // preferences[ranks[1]][ranks[3]]++;

    // preferences[ranks[2]][ranks[3]]++;


    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int counter = 0;
    for(int row = 0; row < candidate_count; row++){
        for(int column = 0; column < candidate_count; column++){
            int max = preferences[row][column];
            if(max > preferences[column][row]){
                //The row is the winning candidate
                pairs[counter].winner = row;
                //The column is the losing candidate
                pairs[counter].loser = column;
                pair_count++;
                counter++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for(int i = 0; i < pair_count; i++){
        int temp = preferences[pair[i].winner][pair[i].loser];
        int tempWinner = pair[i].winner;
        int tempLoser = pair[i].loser
        for(int j = i+1; j < pair_count; j++){
            if(temp > preferences[pair[j].winner][pair[j].loser]){

            }
        }

    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    return;
}

