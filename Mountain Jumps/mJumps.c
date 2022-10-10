/*Jayro Boy de Vasconcellos Neto
9762880
Alg. Avançados - Ex PD1 

Mountain Jumps

Given N mountains and the heights of each mountain, calculate the minimum amount of energy
needed in order to go from mountain 1 to mountain n. Going from mountain A to mountain B
costs, in energy, the vertical distance between them. You can go from mountain x to mountains
x+1 or x+2.
*/

#include<stdio.h>
#include<stdlib.h>
#define min(a,b) (((a) < (b))? (a) : (b))


//Reads all heights and initialize the costs array as -1 for all of them. 
void readHeights(int n, int *mounHei, long long int *costToMountain){
	int a;

	for(int i = 1; i <= n; i++){
		scanf("%d", &a);
		mounHei[i] = a;
		costToMountain[i] = -1;
	}

	return;
}

long long int getMinimumEnergy(int nMoun, int *mounHei, long long int *costToMountain){
	if(nMoun < 2) return 0; //If it is the first mountain or we have gone before the start

	//If we haven't calculated the minimum energy to reach this mountain
	if(costToMountain[nMoun] == -1){
		long long int costPrev = (long long int)abs(mounHei[nMoun] - mounHei[nMoun - 1]), //Calculate the cost to reach current mountain from previous mountain 
					  costBefPrev = (long long int)abs(mounHei[nMoun] - mounHei[nMoun - 2]); //Calculate the cost to reach current mountain from mountain before the previous mountain
			
		//Figure out if it's better to come to it from the previous or from the one before the previous
		costToMountain[nMoun] = min((getMinimumEnergy(nMoun - 1, mounHei, costToMountain) + costPrev), (getMinimumEnergy(nMoun - 2, mounHei, costToMountain) + costBefPrev)); 
	}
	
	return(costToMountain[nMoun]);
}	
	
int main(void){
	int numberOfMountains;
	long long int *costToMountain;
	int	*mounHei;

	scanf("%d", &numberOfMountains);
	
	mounHei = (int*)malloc((numberOfMountains + 1) * sizeof(int));
	costToMountain = (long long int*)malloc((numberOfMountains + 1) * sizeof(long long int));
	
	readHeights(numberOfMountains, mounHei, costToMountain);
	
	printf("%lld\n", getMinimumEnergy(numberOfMountains, mounHei, costToMountain));
	
	free(mounHei);
	free(costToMountain);
	
	return 0;
}