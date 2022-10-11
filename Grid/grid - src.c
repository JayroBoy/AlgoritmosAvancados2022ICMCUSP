/*Jayro Boy de Vasconcellos Neto
9762880
Algoritmos Avançados - Ex: Taro's paths
*/

/* Brief explanation
Given a H x W grid, calculate the number of paths from (1, 1) to (H, W) that Taro, our
protagonist for this exercise, can take. Taro can only move down or right. Since the answer
is possibly very big, it should be given mod 10^9 + 7 to avoid overflow.

SOLUTION:
The amount of paths that reach a particular square is the sum of the amount of paths that reach the
square above it and the the amount of paths that reach the square to it's left. 
This means we backtrack from the bottom right, but only up and to the left. Also, since
multiple paths can visit the same square, we can save a lot of computations by employing 
Dynamic Programming and storing the amount of paths that reach a particular square the first
time we visit it. Then, for every subsequent visit, we only need to check the amount instead
of calculating it again.


Pseudocode of the recursion:

getNumberOfPaths(square):
	If square is out of bounds, return 0 *No valid paths can come from somewhere other than the origin*
	If square is a wall, return 0 *No valid paths can cross through walls*
	If square is the origin, return 1 *There is only one path that reach the origin*
	
	If square is unvisited:
		Mark it as visited
		If there is a square above it:
			pathsToSquare[square] += getNumberOfPaths(square above)
		If there is a square to it's left:
			pathsToSquare[square] += getNumberOfPaths(square to the left)
	
	return pathsToSquare[square] % (10 ^ 9 + 7) *Take the mod when returning to avoid overflow*
}
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MOD 1000000007

//Allocate and return a H x W bool matrix 
bool **allocateBoard(int H, int W){
	bool **B = (bool**)malloc((H + 1) * sizeof(bool*));
	for(int i = 1; i <= H; i++){
		B[i] = (bool*)calloc((W + 1), sizeof(bool)); 
	}
	return B;
}

//Allocate and return an int H x W matrix filled with -1
int **allocatePaths(int H, int W){
	int **P = (int**)malloc((H + 1) * sizeof(int*));
	
	for(int i = 0; i <= H; i++){
		P[i] = (int*)malloc((W + 1) * sizeof(int));
			for(int j = 1; j <= W; j++) {
				P[i][j] = -1; //-1 means unvisited square
			}
	}
	
	return P;	
}

//Read a H x W matrix of characters. Save True for '.' and False for '#'.
void readLabyrinth(bool **B, int H, int W){
	char a[1001];
	for(int i = 1; i <= H; i++){
		scanf("%s", a);
		//printf("%s", a);
		for(int j = 1; j <= W; j++){
			if(a[j - 1] != '#') B[i][j] = true; //Walls are false squares, since we can't move through them
		}
		//printf("\n");
	}
	return;
}

//Recursively backtrack and save how many paths reach a particular square. 
int getPathsTo(int i, int j, bool **board, int **pathsTo){
	if(i < 1 || j < 1) return 0; //Out of bounds 
	if(!board[i][j]) return 0; //Wall 
	if(i == 1 && j == 1) return 1; //Reached the beginning
	
	if(pathsTo[i][j] == -1){ //Unvisited square
		pathsTo[i][j] = 0; //Mark it as visited
		if (i > 1) //If there is a square above it:
			pathsTo[i][j] += (getPathsTo(i - 1, j, board, pathsTo));//pathsToSquare[square] += getNumberOfPaths(square above)
		if (j > 1)//If there is a square to it's left:
			pathsTo[i][j] += (getPathsTo(i, j - 1, board, pathsTo));//pathsToSquare[square] += getNumberOfPaths(square to the left)
	}
	
	return (pathsTo[i][j] % MOD); //Take the MOD here to avoid overflow. 
}

//Free a bool and an int matrix with H lines each
void freeAll(bool **board, int **pathsTo, int H){
	for(int i = 1; i <= H; i++){
		free(board[i]);
		free(pathsTo[i]);
	}
	
	free(board);
	free(pathsTo);
	
	return;
}

//Program flow control function
int main(void){
	int H, W;
	bool **board;
	int **pathsTo;
	
	scanf("%d %d", &H, &W);
	
	board = allocateBoard(H, W);
	pathsTo = allocatePaths(H, W);
	
	readLabyrinth(board, H, W);

	printf("%d\n", getPathsTo(H, W, board, pathsTo));
	
	freeAll(board, pathsTo, H);

	return 0;
}

