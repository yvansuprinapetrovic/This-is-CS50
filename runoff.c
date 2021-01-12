#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
            printf("Voter number %i preference %i is %s\n", i, j, name);
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();

        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    // Looping through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Checking if candidate is found
        if (strcmp(name, candidates[i].name) == 0)
        {
            // Updating the two dimensional array of preferences using function inputs and loop
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Go through each voter
    for (int i = 0; i < voter_count; i++)
    {
        // Go through each preference
        for (int j = 0; j < candidate_count; j++)
        {
            // Go through each candidate
            for (int k = 0; k < candidate_count; k++)
            {
                // Double condition
                if (preferences[i][j] == k && candidates[k].eliminated == false)
                {
                    // Give vote to candidate
                    candidates[k].votes++;
                    // End the preference loop
                    j = candidate_count;
                    // End the candidate loop
                    break;
                }
                // Double condition
                else if (preferences[i][j] == k && candidates[k].eliminated == true)
                {
                    // Go to next preference
                    continue;
                }
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // Declaring two variables
    int even_majority = voter_count / 2 + 1;
    double odd_majority = ((double) voter_count / 2) + 0.5;

    // Going through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // In case of even voter count
        if (candidate_count % 2 == 0 && candidates[i].votes >= even_majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
        // In case of odd voter count
        else if (candidate_count % 2 == 1 && (double) candidates[i].votes >= odd_majority)
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // Declaring min equal to the number of votes of first canidate in list
    int min = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        // Swapping min value to smallest in array
        if (min <= candidates[i].votes && candidates[i].eliminated == false)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    //  Going through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            // If just one candidate's votes are higher than min, election is not a tie
            if (candidates[i].votes > min)
            {
                return false;
            }
        }
        // Ignoring already eliminated candidates
        else if (candidates[i].eliminated == true)
        {
            continue;
        }
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // Looping through each candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // Checking if any of the candidates' votes is equal to the min 
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}
