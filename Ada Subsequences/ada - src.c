/*Jayro Boy de Vasconcellos Neto
9762880
Algoritmos Avançados - Ex: Ada Subsequences
*/

/*
DESCRIPTION:
	Given 2 strings and values for each letter in the alphabet, find the value of the most 
	expensive common subsequence between the two. In this problem, a subsequence is a set of 
	elements of the string that are adjacent.

SOLUTION:
	The best solution I could find was to turn this problem into a known problem - That of the
	longest common subsequence - and then solve that problem. The way to do this is pretty simple:
	when counting the size of the subsequence, instead of adding 1, we add the value of the letter 
	and simply calculate the longest common subsequence via the known solution of dynamic 
	programming.
	
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define max(a , b) (((a) > (b))? (a) :(b))



long long int **alloc(int M, int N){
	long long int **dp = (long long int**)malloc((M) * sizeof(long long int*));
	for(int i = 0; i < M; i++){
		dp[i] = (long long int*)malloc((N) * sizeof(long long int));
		for(int j = 0; j < N; j++){
			dp[i][j] = -1;
		}
	}
	return dp;
}


long long int **readInputs(int *M, int *N, int values[], char **A, char **B){
	long long int **dp;
	
	scanf("%d %d", M, N);
	
	*A = (char*)malloc(((*M) + 1) * sizeof(char));
	*B = (char*)malloc(((*N) + 1) * sizeof(char));
	
	for(int i = 0; i < 26; i++){
		scanf("%d", &values[i]);
	}
	
	/*
	printf("Vetor de valores: \n");
	for(int i  = 0; i < 26; i++) printf("%c: %d\n", i + 97, values[i]);
	printf("\n");
	*/

	scanf("%s %s", *A, *B);
	//printf("String A: %s\nString B: %s\n", *A, *B);
	
	//printf("	Alocando matriz de longSubs...\n");
	dp = alloc(*N, *N);
	//printf("	Alocada!\n");
	
	return dp;
}

int charToInt(char A){
	int ans = A - 97;
	return ans;
}


long long int longestCommonSubsequence(char *X, char *Y, int M, int N, long long int **longSubs, int *values){ 
	if (M == -1 || N == -1) return 0; //Base case: we've left one of the strings 
	if(longSubs[M][N] != -1) return longSubs[M][N]; //Base case: We've calculated this value already
	if (X[M] == Y[N]){ //If the letters are equal
		int index = charToInt(X[M]); //Find the position in the values vector
		longSubs[M][N] = (((long long int)values[index]) + longestCommonSubsequence(X, Y, M - 1, N - 1, longSubs, values)); //Calculate the value 
	}else{ //If the letters are different
		longSubs[M][N] = max(longestCommonSubsequence(X, Y, M, N - 1, longSubs, values),//Go back separately in each string and find largest value 
							longestCommonSubsequence(X, Y, M - 1, N, longSubs, values)); 
	}
	
	return longSubs[M][N];
} 



void freeAll(char *A, char *B, long long int **longSubs, int M){
	free(A);
	free(B);
	for(int i = 0; i < M; i++) {
		free(longSubs[i]);
	}
	free(longSubs);
	return;
}

long long int findLargest(long long int **A, int r, int c){
	long long int larg = 0;
	for(int i = 0; i < r; i++){
		for(int j = 0; j < c; j++){
			//printf("%lld ", A[i][j]);
			if(A[i][j] > larg) larg = A[i][j];
		}
		//printf("\n");
	}
	return larg;
}

int main(void){
	char *A,
		 *B;
	int M, N,
		values[26];
	long long int **longSubs;
	
	
	//printf("Lendo entradas...\n");
	longSubs = readInputs(&M, &N, values, &A, &B);
	
	
	longestCommonSubsequence(A, B, M - 1, N - 1, longSubs, values);
	
	
	printf("%lld\n", findLargest(longSubs, M, N));
	
	freeAll(A, B, longSubs, M);
	
	return 0;
}
	
	
	
	
	
	
	
	
	
	