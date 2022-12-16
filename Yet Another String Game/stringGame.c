/**
 * Jayro Boy V. Neto
 * 9762880
 * 
 * Ex Teoria dos Jogos 2
 * Algoritmos Avançados
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char *findGameResult(){
    long long int turn = 1;
    int size = 0;
    char *input = malloc(51 * sizeof(char));

    scanf("%s", input);
    size = strlen(input);

    for(int i = 0; i < size; i++){
        if(turn == 2){
            if(input[i] == 'z') input[i] = 'y';
            else if(input[i] != 'z') input[i] = 'z';
        }else{
            if(input[i] == 'a') input[i] = 'b';
            else if(input[i] != 'a') input[i] = 'a';
        }
        turn = 1 + (turn % 2); //1 becomes 2, 2 becomes 1
    }

    return input;
}

int main(void){
    int testCases;
    char *result;

    scanf("%d", &testCases);

    while(testCases){
        testCases--;
        result = findGameResult();
        printf("%s\n", result);
        free(result);
    }
    return 0;
}
 