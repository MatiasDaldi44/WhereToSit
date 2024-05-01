///////////////////////
//// Matias Daldi  //// 
//// WhereToSitB.c //// 
//// 2/21/2024  ///////
///////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define a struct to hold person information
struct personInfo {
	char name[19];    // Name of the person
	int hasPopcorn;   // Flag indicating whether the person has popcorn (1 for true, 0 for false)
};

// Function to swap two elements in an array
void swap(struct personInfo person[], int i, int j){
	struct personInfo temp = person[i];
	person[i] = person[j];
	person[j] = temp;
}

// Function to check if two people can sit together
bool isAllowed(struct personInfo person[], int k, int j, int disallowedPairCount, char disallowedPairs[disallowedPairCount][2][19]) {
	// Iterate through disallowed pairs
	for (int d = 0; d < disallowedPairCount; d++) {
		// Check if the same person is mentioned in the disallowed pair
		if(strcmp(person[j].name, person[k].name) == 0)
			return true;

        // Check if the current pair is disallowed
        if ((strcmp(person[k].name, disallowedPairs[d][0]) == 0 && strcmp(person[j].name, disallowedPairs[d][1]) == 0) ||
            (strcmp(person[k].name, disallowedPairs[d][1]) == 0 && strcmp(person[j].name, disallowedPairs[d][0]) == 0)) {
				return false;
        }
    }
	
	// If no disallowed pair found, return true
	return true;
}

// Function to check if seating a person at a certain position is allowed
bool isSeatingAllowed(struct personInfo person[], int k, int disallowedPairCount, char disallowedPairs[disallowedPairCount][2][19], int numOfPeople) {
    if (k < 0 || k >= numOfPeople) return false; 

    int comparePrevious = k - 1;
    int compareNext = k + 1;

    // Iterate through disallowed pairs to check if seating is allowed
    for (int d = 0; d < disallowedPairCount; d++) {
        if ((comparePrevious >= 0 &&
             ((strcmp(person[k].name, disallowedPairs[d][0]) == 0 && strcmp(person[comparePrevious].name, disallowedPairs[d][1]) == 0) ||
              (strcmp(person[k].name, disallowedPairs[d][1]) == 0 && strcmp(person[comparePrevious].name, disallowedPairs[d][0]) == 0))) ||
            (compareNext < numOfPeople &&
             ((strcmp(person[k].name, disallowedPairs[d][0]) == 0 && strcmp(person[compareNext].name, disallowedPairs[d][1]) == 0) ||
              (strcmp(person[k].name, disallowedPairs[d][1]) == 0 && strcmp(person[compareNext].name, disallowedPairs[d][0]) == 0)))) {
            return false;
        }
    }

    // Check if the person has popcorn and if adjacent person has popcorn
    bool hasPopcornCondition = false;
    if ((comparePrevious >= 0 && (person[k].hasPopcorn || person[comparePrevious].hasPopcorn)) ||
        (compareNext < numOfPeople && (person[k].hasPopcorn || person[compareNext].hasPopcorn))) {
        hasPopcornCondition = true;
    }

    return hasPopcornCondition;
}

// Function to recursively generate permutations of seating arrangements
void recursivePermute(struct personInfo person[], int k, int numOfPeople, int disallowedPairCount, char disallowedPairs[disallowedPairCount][2][19], int *possibleIterations){
    int j;
    // Base case: If all people are seated, check if arrangement is valid
    if (k == numOfPeople){
		int checkIterator = 0;
        for (int i = 0; i < numOfPeople; i++){
			if(isSeatingAllowed(person, i, disallowedPairCount, disallowedPairs, numOfPeople))
				checkIterator++;
        }

		// If all arrangements are valid, increment possibleIterations count
		if(checkIterator == numOfPeople)
		{
			(*possibleIterations)++;
		}
		checkIterator = 0;	

    } else{
        // Recursive case: Generate permutations by swapping elements
        for (j = k; j < numOfPeople; ++j){
                swap(person, k, j);
				recursivePermute(person, k + 1, numOfPeople, disallowedPairCount, disallowedPairs, possibleIterations);
                swap(person, j, k);
        }
    }	
}

// Main function
int main(int argc, char *argv[]) {
	FILE *file = fopen(argv[1], "r");

	// Check if file exists
	if (file == NULL){
		printf("File does not exist, exiting.");
		exit(0);
	}

	int possibleIterations = 0;
	int numOfPeople = 0;
	int disallowedPairCount = 0;

	// Read number of people and disallowed pairs from file
	fscanf(file, "%d %d", &numOfPeople, &disallowedPairCount);

	char disallowedPairs[disallowedPairCount][2][19];

	// Create array to store people's information
	struct personInfo people[numOfPeople];

	// Read people's information from file
	for (int i = 0; i < numOfPeople; i++){
		fscanf(file, "%s %d", people[i].name, &people[i].hasPopcorn);
	}
	
	// Read disallowed pairs from file
	for (int i = 0; i < disallowedPairCount; i++){
		fscanf(file, "%s %s", disallowedPairs[i][0], disallowedPairs[i][1]);
	}

	// Generate permutations and count valid arrangements
	recursivePermute(people, 0, numOfPeople, disallowedPairCount, disallowedPairs, &possibleIterations);
	
	// Print the number of valid seating arrangements
	printf("%d", possibleIterations);
	
	return 0;
}