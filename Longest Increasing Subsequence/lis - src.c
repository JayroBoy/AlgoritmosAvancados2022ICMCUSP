/*Jayro Boy V. Neto
9762880
Algoritmos Avançados - Ex: Longest Increasing Subsequence*/

/*
DESCRIPTION:
Given an array A of integers, find the length of the longest increasing subsequence
of A. A subsequence of an array is a set of elements that appear in the same order
as they do in the array. For example:
	A_s1 = {1, 3, 5, 7}, A_s2 = {2, 4, 6, 8}, A_s3 = {1, 2, 3, 5, 6, 7}
		are subsequences of 
	A = {1, 2, 3, 4, 5, 6, 7}
		however
	A_ns = {1, 2, 4, 3} 
		is not a subsequence of A, because elements 3 and 4 are in the wrong order
		
INPUT:
	Integer A between 1 and 2500, followed by A integers, each between 1 and 10^4.
	
SOLUTION:
	This is a dynamic programming problem. However, I've found that an iterative solution was more intuitive
	to me than the recursive one. We go from the start of the array to the end and count how many subsequences
	each element has. Then, we go through all subsequences, find the largest one and return it.
	
	PSEUDOCODE:
	
	size is the number of elements we have. It is part of the input.
	array[size] is the array with all elements. It is part of the input.
	longSub[size] is the array that holds the length of the longest increasing subsequence at each position. 
	
	function findLongests(array, longSub):
		For each element x in array:
			initialize longSub[x] to 1 *every element is the end of a subsequence of length 1*
			For each element before x, going backwards:
				If we can use this element to make a longer subsequence than longSub[x]:
					update longSub[x]
	return

	function findBiggest(longSub)
		biggest starts at 1;
		for each element in longSub:
			if element is larger than biggest, update biggest
	return biggest
	
	function findBiggestLongest(array, longSub):
		findLongests(array, longSub)
		answer = findBiggest(longSub)
	return answer
	
*/

#include<stdio.h>
#include<stdlib.h>

int *readInput(unsigned int *size){
	int *a;
	unsigned int b;
	
	scanf("%u", &b);
	*size = b;

	a = (int*)malloc((*size) * sizeof(int));
	
	for(int i = 0; i < *size; i++){
		scanf("%d", &a[i]);
	}
	
	return a;
}

/*Runs through an array and returns the biggest element in it*/
long long int findBiggest(long long int *array, unsigned int size){
	int index = 0; 

	for(int i = 0; i < size; i++) if(array[i] > array[index]) index = i;

	return array[index];
}
	
/*Calculates longest subsequence ending at each element in array*/
void findLongests(int *array, unsigned int size, long long int *longSub){
	for(int i = 0; i < size; i++){ 
		longSub[i] = 1;
		for(int j = size - 1; j >= 0; j--){ 
			if(array[i] > array[j] && longSub[j] >= longSub[i]) 
				longSub[i] = longSub[j] + 1; 
		}
	}
	return;
}

/*Calculates all subsequences and returns longest one*/
long long int findBiggestLongest(int *array, unsigned int size, long long int *longSub){
	findLongests(array, size, longSub);
	return findBiggest(longSub, size);
}

int main(void){
	unsigned int arraySize;
	int	*array;
	long long int *longSubEndAt; ///Longest Subsequence Ending at
	
	array = readInput(&arraySize);
	
	///Allocate array of subsequence lengths
	longSubEndAt = (long long int*)malloc(arraySize * sizeof(long long int));
	

	///Calculate and print longest subsequence
	printf("%lld\n", findBiggestLongest(array, arraySize, longSubEndAt));
	
	///Free dynamically allocated memory
	free(array);
	free(longSubEndAt);
	
	return 0;
}