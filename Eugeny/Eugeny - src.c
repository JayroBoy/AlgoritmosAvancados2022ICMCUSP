#include<stdio.h>
#include<stdlib.h>
/*
	Jayro Boy V. Neto     9762880
	This program receives a pre-informed number of informations about songs. Specifically, it receives
	the duration of each song and how many times the song repeats in the playlist. Songs are
	played in order of reception, so if we receive, for example:
	3 4
	5 1

	the first song will play during the first 12 minutes(3 minutes * 4 playthroughs)
	the second song will play during the next 5 minutes(5 minutes * 1 playthrough)
	
	After we receive all the information about the songs is received, we receive a pre-informed number 
	of moments in time. These moments can range from 1 to 10^9. Our task is to figure out which song 
	is playing at each of those moments in time.

	There are a couple of ways to do this. The most obvious one, to me, was to try to create an array that had the 
	length of the playlist in minutes and for each position, save which song was playing. This would make our program's
	complexity be O(1), because it would just be an access to an array. Reading and saving the information would be 
	computationally more expensive than actually finding the answer. However, since the maximum time for this problem
	is 10^9 minutes, this would require a computer with at least 8gb of memory available to run it(8 bytes for an int, 
	times 10^9, means 8gb). In the automatic correction platform we use, this problem was limited to 256mb of memory,
	so I had to discard this notion.

	My next idea was to save the final times for each song in and iterate through this array checking the intervals 
	for every moment in time we wanted to find. Again, this proved to be ineffective, this time because of the time limit:
	At worst, this would take over 2 seconds of execution, and I only had 1 second allowed in the testing platform.

	Finally, I adapted the previous solution using a recursive binary search instead of a linear search on the finalTimes
	array. This proved to be effective enough that the problem was accepted. Since this is a divide and conquer exercise,
	I also believe this was the expected method of resolution.
*/
typedef struct song{
	int duration;
	int repeats;
}song;

//Reads songs durations and number of repeats, calculates
//final time for each song
unsigned long long int* readSongs(int songs){
	unsigned long long int *result; 
	long long unsigned int accumulator = 0; 
	song aux;
	
	result = (unsigned long long int*) malloc((songs + 1) * sizeof(unsigned long long int));
	
	//Read all songs
	for(int i = 1; i < songs + 1; i++){
		scanf("%d", &(aux.repeats));
		scanf("%d", &(aux.duration));
		accumulator += aux.repeats * aux.duration;
		result[i] = accumulator;
	}
	
	return result;
}

//Reads an array of ints 
int *readFavorites(int favorites){
	int *result;
	result = (int *)malloc(favorites * sizeof(int));
	
	for(int i = 0; i < favorites; i++){
		scanf("%d", &result[i]);
	}
	
	return result;
}


int binSearch(int t, unsigned long long int *s, int min, int max){
	if(min > max) return 0;

	int mid = (min + max)/2;

	if(t > s[mid]) return binSearch(t, s, mid + 1, max); //If the time we want is after the end of this song
	if(t <= s[mid - 1]) return binSearch(t, s, min, mid - 1); //If the time we want is before the start of this song
	
	return mid;
}

//Goes through each int in wants and finds where it falls in moments
void findFavorites(unsigned long long int *moments, int *wants, int size, int songs){
	int songIndex;
	unsigned long long int time;
	
	//For each favorite, go through the songs until we find the first one that ends after or at the time being inquired
	for(int i = 0; i < size; i++){
		time = wants[i];
		songIndex = binSearch(time, moments, 0, songs + 1);
		printf("%d\n", songIndex);                                         
	}
	
	return;	
}

void printInts(int *array, int size){
	for(int i = 0; i < size; i++){
		printf("	%d\n", array[i]);
	}
	return;
}

void printUlls(unsigned long long int *array, int size){
	for(int i = 1; i < size; i++){
		printf("	%llu\n", array[i]);
	}
	return;
}


int main(void){
	int numberOfSongs, 
		numberOfFavorites,
		*wantedMoments;

    unsigned long long int *finalTimes;
	
	scanf("%d %d", &numberOfSongs, &numberOfFavorites);
	
	//printf("Reading song moments...\n");
	finalTimes = readSongs(numberOfSongs);
	//printf("Done! Final times for each song:\n");
	//printUlls(finalTimes, numberOfSongs + 1);

	//printf("Reading wanted moments...\n");
	wantedMoments = readFavorites(numberOfFavorites);
	//printf("Done! Wanted moments in time:\n");
	//printInts(wantedMoments, numberOfFavorites);

	findFavorites(finalTimes, wantedMoments, numberOfFavorites, numberOfSongs);
	
	free(finalTimes);
	free(wantedMoments);
	
	return 0;
}
	
	