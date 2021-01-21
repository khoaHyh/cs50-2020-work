// A program that runs a Tideman election
#include <cs50.h>
#include <stdio.h>
#include <string.h>

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
bool cycle(int temp_loser, int start);
void source(void);

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
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            // Ex. rank[0] = 0 (Alice)
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Ex. preferences[0][1]++ since i < j will always be true in this loop pyramid
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            // If [i][j] > [j][i] then i is the winner
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[j][i] > preferences [i][j])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory using Insertion Sort
void sort_pairs(void)
{
    // initialize copy of temp array to compare
    pair temp;
    // Go through each pair of elements of pairs array
    for (int i = 1; i < pair_count; i++)
    {
        // Compare with the previous element
        int j = i - 1;
        temp = pairs[i];

        // only perform this when pref[j][i] < pref[i][j]
        while (j >= 0 && preferences[pairs[j].winner][pairs[j].loser] < preferences[temp.winner][temp.loser])
        {
            // moves the smaller pair one position ahead
            pairs[j + 1] = pairs[j];
            j--;
        }
        // moves the bigger pair to where the smaller pair was
        pairs[j + 1] = temp;
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // goes over pairs array in order of decreasing strength of victory
    for (int i = 0; i < pair_count; i++)
    {
        // if this lock won't create a cycle, then put this pair in the lock graph
        if (!cycle(pairs[i].loser, pairs[i].winner))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

// Determines if an edge/arrow will create a cycle
bool cycle(int temp_loser, int start)
{
    // if this temp_loser points winner, it will form a cycle
    if (locked[temp_loser][start])
    {
        return true;
    }
    // loop over all candidates to see what the loser points to
    for (int i = 0; i < candidate_count; i++)
    {
        // if there is an edge, restart the function now with [i] being in [temp_loser]'s place
        if (locked[temp_loser][i])
        {
            // check the output of this function recursively with 'i' as temp_loser
            // if we returned this recursive function, the temp_loser value we were working with doesn't get
            // thoroughly checked in this for loop
            if (cycle(i, start))
            {
                // if it is true, then there is a cycle
                return true;
            }
            // if it is not true, keep running the j loop to check because temp_loser could still create a cycle
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // iterate through rows or [i] in locked
    for (int i = 0; i < pair_count; i++)
    {
        // iterate through columns or [j] in locked
        for (int j = 0; j < pair_count; j++)
        {
            // checks if any other candidate in the locked graph wins against [i]
            if (locked[j][i])
            {
                // if so, go to OUTER to skip printing the name
                goto OUTER;
            }

        }
        printf("%s\n", candidates[i]);
// Skips the current iteration of 'i' for loop
OUTER:
        continue;
    }
}