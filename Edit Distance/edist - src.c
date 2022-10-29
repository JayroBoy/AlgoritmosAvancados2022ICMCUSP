/*Jayro Boy V. Neto
9762880
Alg. Avançados - Ex. Edit Distance*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define min(a,b) (((a) < (b)) ? (a) : (b))


int minimum(int x, int y, int z) { 
    return min(min(x, y), z); 
}


void readInputs(char A[], char B[], int *aLength, int *bLength){
    //read and allocate string A
    scanf("%s", A);
    *aLength = strlen(A);

    //read and allocate string B
    scanf("%s", B);
    *bLength = strlen(B);
    return;
}
/**
 * @brief 
 * 
 * @param A String to be transformed
 * @param B Target String
 * @param remInA Characters remaining in A 
 * @param remInB Characters remaining in B
 * @return number of operations to turn string A[0: remInA - 1] into string B[0: remInB -1]
 */
int editDistance(char *A, char *B, int remInA, int remInB, int **eDist){
    if(remInA == 0) return remInB; //If A has no more characters, we need to insert the remaining from B
    if(remInB == 0) return remInA; //If B has no more characters, we need to remove the remaining from A
    if(eDist[remInA][remInB] == -1){ //If we haven't visited this position yet         
        if(A[remInA - 1] == B[remInB - 1]) //If the current char is equal
            eDist[remInA][remInB] =  editDistance(A, B, remInA - 1, remInB - 1, eDist); //Calculate for previous characters
        else //if it isn't, calculate all options
            eDist[remInA][remInB] = 1 + minimum(editDistance(A, B, remInA - 1, remInB, eDist), //Remove
                                                editDistance(A, B, remInA, remInB - 1, eDist), //Insert
                                                editDistance(A, B, remInA - 1, remInB - 1, eDist)); //Replace                                      )
    }

    return eDist[remInA][remInB];
}

int** allocate(int rows, int columns){
    int **eDist = malloc((rows + 1) * sizeof(int*));
    for(int i = 0; i <= rows; i++){
        eDist[i] = (int*)malloc((columns + 1) * sizeof(int));
        for(int j = 0; j <= columns; j++){
            eDist[i][j] = -1;
        }
    }
    return eDist;
}

void freeAll(int **eDist, int rows){
    for(int i = 0; i <= rows; i++) 
        if(eDist[i] != NULL) 
            free(eDist[i]);
    if(eDist != NULL) free(eDist);
    return;
}

int main(void){
    int remainingTestCases;
    char A[2001], 
         B[2001];
    int aLength,
        bLength,
        **eDist;

    scanf("%d", &remainingTestCases);

    while(remainingTestCases > 0){
        readInputs(A, B, &aLength, &bLength);
        
        eDist = allocate(aLength, bLength);
        printf("%d\n", editDistance(A, B, aLength, bLength, eDist));
        
        freeAll(eDist, aLength);    

        remainingTestCases--;
    }

    return 0;
}