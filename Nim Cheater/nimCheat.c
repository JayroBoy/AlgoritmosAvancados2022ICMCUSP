#include<stdio.h>
#include<stdlib.h>

void readPiles(int *V, int amount){
    for(int i = 0; i < amount; i++){
        scanf("%d", &V[i]);
    }
}

int *readInput(int *amount){
    int *result;
    scanf("%d", amount);

    result = malloc((*amount) * sizeof(int));

    readPiles(result, *amount);

    return result;
}

//Cumulative xor between all piles
int getNimSum(int *stonesPerPile, int piles)
{
    int nimSum = stonesPerPile[0];
    for (int i = 1; i < piles; i++)
        nimSum = nimSum ^ stonesPerPile[i];
    return nimSum;
}
 

int findMinimumRemoves(int piles, int *stonesPerPile){
    int ans = 1;
    if(getNimSum(stonesPerPile, piles)) ans = 0;
    
    free(stonesPerPile);
    
    return ans;
}

int main(void){
    int testCases,
        piles,
        *stonesPerPile;

    scanf("%d", &testCases); 

    while(testCases){
        stonesPerPile = readInput(&piles);
        printf("%d\n", findMinimumRemoves(piles, stonesPerPile));
        testCases--;
    }

    return 0;
}