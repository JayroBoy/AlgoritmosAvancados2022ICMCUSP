#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
/*INTRO
	Jayro Boy Neto - Sep. 2022 - ICMC USP
	
	-----Input & Output-----
	This program receives the following input, in the following order:
	- 2 integers, n and m
	- A char matrix consisting of n lines and m columns 
	- 1 integer, k
	- A string with k characters
	
	And outputs "Yes" if we can form the string with the letters in the
	matrix, with the following restrictions:
		- No jumping squares. We are only allowed to move north,
		west, south or east from any given square.
		- No repeating squares. A letter can only be used as many
		times as there are squares with it in the block.
	If it isn't possible to form the word respecting these restrictions, 
	it outputs "No".
	
	-------Examples--------
	1 - Possible
	Input:
		3 3
		ABE
		BEE
		LED
		4
		BABE
	Output:
		Yes
		
	2 - Impossible(No path)
	Input:
		4 4
		LOVE
		ROME
		MOWN
		NEWT
		5
		TWEEN
	Output:
		No
		
	3 - Impossible(Not enough B's)
	Input:
		3 3
		ABB
		AAB
		AAA
		5
		ABBABBA
	Output:
		No
		
	4 - Impossible(Word is too big)
	Input:
		2 2
		AB
		CD
		5
		ABCDA
	Output:
		No
		
	
	
	-----Logic-----
	After reading all inputs, the program first tests for example 4: Not enough
	letters. This is the simplest check, just a multiplication. If k > n * m, then 
	there aren't enough letters in the block.
	If this check doesn't finish the program, we check example 3: Not enough specific
	letters. This is achieved by hashing the frequency of each letter in the block while
	counting up, then doing it again for the target word while counting down. If at any
	point we reach a negative frequency for any letter, there aren't enough specific letters
	on the block.
	If this check doesn't finish the program, we go through every position on the block and 
	recursively try to form the word starting from that position. If at any point we find the
	final letter of the word, we can form it. If we don't then the program outputs "No" and ends.
*/

/*
	Recursive function - Checks if current letter in w matches current
	letter in b. If it does, branches the search out in all possible
	cardinal directions. If it doesn't return false. If it reaches the end
	of w, returns true.
*/
bool backtrack(char *w, int index, char **b, int i, int j, int maxI, int maxJ){
//Base cases of recursion - Dead end or Success
	if(b[i][j] != w[index]) return false; //If this square doesn't have the letter we want, dead end;
	
	//The (-2) here is because strlen(w) = k + 1, so positions are [0..k] 
	//with w[k] being '\0'. This means the word we're looking for is w[0]w[1]...w[k-1];
	if(index == strlen(w) - 2) return true; //If it's the last letter of the word, success.


//Setup for the next step
	bool ans;
	char c = b[i][j]; //Saving it for later
	b[i][j] = '*';  //Temporarily removing the letter we just used in this step, 
					//because we can't use it again in this sequence, only if we 
					//backtrack
	

//4-way recursive step
	//Up
	if(i > 0){
		ans |= backtrack(w, index+1, b, i - 1, j, maxI, maxJ); //(A |= B) == (A = A | B) - Bitwise OR
		if(ans) return true; //We only want to exit the function here if we have a positive result
	}
	//Left
	if(j > 0){
		ans |= backtrack(w, index+1, b, i, j - 1, maxI, maxJ); 
		if(ans) return true; 
	}
	//Down
	if(i < maxI - 1){
		ans |= backtrack(w, index+1, b, i + 1, j, maxI, maxJ);
		if(ans) return true; 
	}
	//Right
	if(j < maxJ){//No (-1) here because of the extra space at the end of each string for the '\0'
		ans |= backtrack(w, index+1, b, i, j + 1, maxI, maxJ); 
		if(ans) return true; 
	}
	
	
	b[i][j] = c; //Putting it back in case we backtrack and come through here again 
	return false;//If we've reached this point, we can't form w starting from b[i][j]
}

/*
	Control function - For each char in a given block 
	that has n lines, recursively tries to form the 
	target word starting on that position. If it manages
	to form the word at any point, returns true. If 
	it doesn't, returns false.
*/
bool findWord(char **block, char *word, int lines, int columns){
	//Starting on each position on the block
	for(int i = 0; i < lines; i++){ 
		for(int j = 0; j < columns; j++){
			//Recursively try to form the word
			if(backtrack(word, 0, block, i, j, lines, columns))return true;
		}
	}
	return false;
}

/*
	Utility function - Allocates, reads and returns
	a char matrix with n lines and m columns
*/
char **readBlock(int n, int m){
	char **res;
	res = (char**)malloc(n * sizeof(char*));
	
	for(int i = 0; i < n; i++){
		res[i] = (char*)malloc((m + 1) * sizeof(char));
		scanf("%s", res[i]);
	}
	
	return res;
}

/*
	Debug function - prints a given char matrix that has n lines
*/
void printBlock(char **res, int n){
	printf("Printing block: \n");
	for(int i = 0; i < n; i++){
		printf("  %s\n", res[i]);
	}
	return;
}

/*
	Counts how many times each letter of the alphabet
	occurs in a given n*m char matrix. Only counts upper
	case letters and if there are lower case letters
	it will crash.
*/
void countLetters(int letter[], char **block, int n, int m){
	int index;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			index = (int)block[i][j] - 65; //'A' is 65 on the ASCII table
			letter[index]++;
		}
	}
	return;
}

/* 
	Goes through target word and deducts each of its 
	letters from frequency array. If at any point, any
	value in frequency array becomes negative, this means
	that some letter occurs more times in the target word
	than in the letter block, which means we can't form
	the target word with the given block of letters.
	Only counts upper case letters and if there are 
	lower case letters it will crash.
*/
bool checkPossible(char *target, int k, int letters[]){
	int index;
	for(int i = 0; i < k; i++){
		index = (int)target[i] - 65; //'A' is 65 on the ASCII table
		letters[index]--;
		if(letters[index] < 0) return false;
	}
	return true;
}

/*
	Quick checks of feasibility given we can't repeat letters:
		1 - Check if the overall number of letters in the block is
			greater or equal to the overall number of letters in the word
			(Can't form a 10-letter word with a 3x3 block)
		2 - Check if the number of the specific letters of the word
			is present in the block
			(Can't form ABBA if the block is ABCDE)
*/
bool isFeasible(char *target, char **block, int k, int n, int m){
	int letterHash[26] = { 0 };

	if(k > n * m) return false; //If the word is larger than the block, can't form target word
	
	countLetters(letterHash, block, n, m); //Count how many of each letter there are in the block
	
	//Check if the block has enough of the specific letters we need to form target word
	return checkPossible(target, k, letterHash);
}

/*
	Utility function - Frees each line of the 
	char matrix and then the pointer to the matrix
	itself
*/
void freeBlock(char **a, int b){
	for(int i = 0; i < b; i++){
		free(a[i]);
	}
	free(a);
	return;
}

/*
	Utility function - Prints 'Yes' if it receives
	a true value as argument and 'No' if it receives
	a false value as argument.
*/
void print(bool result){
	printf(result? "Yes\n" : "No\n");
	return;
}

/*
	Control function - Dictates the main flow
	of instructions.
*/
int main(void){
	int n, m, k;
	char **block,
		 *target;
	
	//Read block size and read block
	scanf("%d %d", &n, &m);
	block = readBlock(n, m);
	
	//Read target word size and read target word
	scanf("%d", &k);
	target = (char*)malloc((k + 1) * sizeof(char));
	scanf("%s", target);

	//Check if target word can be formed with available letters
	if(!isFeasible(target, block, k, n, m)){ //If it can't
		print(false); //Print 'No'
	}else{ //If it can
		print(findWord(block, target, n, m)); //Check if it *is* actually formed
	}
	
	//Free allocated memory
	freeBlock(block, n);
	free(target);
	return 0;
}

