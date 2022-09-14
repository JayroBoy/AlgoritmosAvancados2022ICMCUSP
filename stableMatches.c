//Jayro Boy Neto   9762880

/*This program receives a number T, which is the number of test cases
It then repeats the following procedure T times:
 1 - Read the number C of couples
 2 - Read the preferences of C women, in the following format:
    [Woman#1][Man #1][Man #2]...[Man#C]
    .           .        .         .   
    .           .        .         .
    .           .        .         .
    [Woman#C][Man #1][Man #2]...[Man#C]

    (Without the []'s)
    Where the earlier a man appears on a given woman's list, the more she likes him

 3 - Read the preferences of C men, in the following format:
    [Man#1][Woman #1][Woman #2]...[Woman#C]
    .           .        .         .   
    .           .        .         .
    .           .        .         .
    [Man#C][Woman #1][Woman #2]...[Woman#C]
    (Without the []'s)
    Where the earlier a woman appears on a given man's list, the more he likes her

 4 - Based on these lists of preferences, produce a stable configuration of marriages, that is,
a configuration in which there is no (man, woman) pair that would benefit from separating from 
both's current partners to marry each other. In other words, if a man likes a woman more than 
he likes his wife, that woman likes her husband more than she likes this man, and if a woman likes
a man more than she likes her husband, that man likes his wife more than he likes this woman.

 5 - Print the final configurations for all test cases in order, in the following format
     M_1  W_M1
     M_2  W_M2
      .    .
      .    .
      .    .
     M_C  W_MC

    Where M_n means Man n and W_Mn means wife of Man n

*/
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
 
/**
 * @brief reads the _size_ preferences of a person
 * @param size 
 * @return int* 
 */
int* getNext(int size){
    int *person = (int*)malloc(size * sizeof(int));
    scanf("%d", &person[0]);//Reading the first integer to discard it
    for(int i = 0; i < size; i++){
        scanf("%d", &person[i]); //Reads the preferences of current person
        //printf("%d ", person[i]);
    }

    //printf("\n");
    return person;
}

/**
 * @brief Given size people, reads their preferences and saves them 
 * in an int matrix
 * @param size 
 * @return int** 
 */
int** getPreferencesOf(int size){
    int **people = (int**)malloc(size * sizeof(int*));

    for(int i = 0; i < size; i++){ 
        //printf("            %d: ", i + 1);
        people[i] = getNext(size);
    }

    return people;
}

/**
 * Checks for repeated first entries in the list of female
 * preferences. 1 if each first entry is unique, 0 if 
 * there are repetitions.
*/
int allFirstsDifferentW(int** list, int participants){
    int *checkTable = (int*)malloc(participants * sizeof(int));
    for(int i = 0; i < participants; i++){
        checkTable[i] = 0;
    }

    for(int i = 0; i < participants; i++){
        int index = list[i][0] - 1; //Find out who the i-th woman prefers 
        if(checkTable[index] != 0) return 0; //If this man is already preferred by another woman, there is repetition
        checkTable[index] = i + 1; //Register the number of the woman who prefers this man
    }

    for(int i = 0; i < participants; i++){
        printf("%d %d\n", i + 1, checkTable[i]); //The (i+1)th man marries the (checkTable[i])th woman
    }

    return 1; //If we reach this point, this means that each woman is married to her favorite guy :)
}

/**
 * Checks for repeated first entries in the list of male
 * preferences. 1 if each first entry is unique, 0 if 
 * there are repetitions
*/
int allFirstsDifferentM(int** list, int participants){
    int *checkTable = (int*)malloc(participants * sizeof(int));
    for(int i = 0; i < participants; i++){
        checkTable[i] = 0;
    }

    for(int i = 0; i < participants; i++){
        int index = list[i][0] - 1; //Find out which woman the i-th man prefers 
        if(checkTable[index] == 1) return 0; //If another man already prefers this woman, there is repetition 
        checkTable[index] = 1; //Register that there is a man who ranks this woman as his first choice
    }

    
    for(int i = 0; i < participants; i++){
        printf("%d %d\n", i + 1, list[i][0]);//The (i+1)th man marries the (list[i][0])th woman
    }

    return 1; //If we reach this point, this means that each man is married to his favorite girl :)
}

/**
 * Given a list of preferences, returns 1 if suitor 
 * is preferred to current and 0 if current is preferred to suitor
*/
int prefers(int *preferences, int suitor, int current, int max){
    int i = 0;

    while(i < max){  
        if(preferences[i] == current) return 0; //If current is found, return, he is preferred
        if(preferences[i] == suitor)return 1;//If suitor is found, return, he is preferred
        i++; //Find next entry on the list
    }

    return -1;
}

/**
 * @brief Logically removes(replaces the value with -1) thisGirl from the list of preferences of thisGuy 
 * 
 * @param allGuys 
 * @param thisGuy 
 * @param thisGirl 
 */
void removeFromList(int** allGuys, int thisGuy, int thisGirl){
    int i = 0;

    while(allGuys[thisGuy][i] != thisGirl){ //Find her on the list
        i++;
    }

    allGuys[thisGuy][i] = -1; //Remove her from his preferences

    return;

}

/*
The Gale Shapley algorithm, also known as the mating ritual, consists of a series of steps
to find out a stable matching configuration for N men and N women, considering all men and women
are willing to date any person of the opposite sex, have a well-ordered list of preferences and 
have static preferences.
It's steps are as follows:

1 - Initialize every man and woman as free
2 - While there is a free man with a non-empty list
    2.1 - Have this man propose to the first woman in his list and remove her from his list
    2.2 If this woman is free:
        2.2.1 She gets engaged to this man
    2.3 If this woman is not free:
        2.3.1 If this woman prefers this man to her current fiancee:
            2.3.1.1 She gets engaged to this man
            2.3.1.2 Her ex-fiancee becomes free
        2.3.2 If this woman prefers her current fiancee to this man:
            2.3.2.1 Nothing changes

Once there are no more free men with non-empty lists, 
every man will be partnered with the first woman on 
his list that will not cheat on him, and every woman will
be partnered with the last man on her list that she will 
not cheat on(Meaning this is man-optimal and woman-pessimal).
If we swap the roles of men and women in the algorithm, it
then becomes woman-optimal
*/
void galeShapley(int** men, int **women, int couples){
    int freeMen = couples, //Number of free men
        *whichWomen, //List of all women where each line is => [Current partner]
        *whichMen; //List of all men where each line is => [Current partner]
    
    //printf("        Começando Gale-Shapley...\n");

    /*-------------------- Memory Allocation -------------------*/
    whichWomen = (int*)malloc(sizeof(int) * couples + 1); //Couples + 1 to avoid index shenanigans. whichWomen[0] will not be used
    whichMen = (int*)malloc(sizeof(int) * couples + 1); //Couples + 1 to avoid index shenanigans. whichMen[0] will not be used

    
    /*------------------ Memory Inicialization -----------------*/
    for(int i = 1; i < couples + 1; i++){
        whichWomen[i] = -1; //-1 means a person has no assigned partner
        whichMen[i] = -1; //-1 means a person has no assigned partner

        //printf("           Homem e mulher %d inicializados\n", i);
    }
    
    /* Main logic of the algorithm starts here*/
    while(freeMen > 0){ //While there exists any free man
        for(int i = 1; i < couples + 1; i++){ //Starting on the first guy
            while(whichMen[i] == -1){//If he is free
                int firstWoman = -1;
                int wCount = 0;
                while(firstWoman == -1){ //Find the first woman on his list
                    firstWoman = men[i - 1][wCount];
                    wCount++;
                }
                if(whichWomen[firstWoman] ==  -1){ //If she is free
                    whichMen[i] = firstWoman; //He gets engaged to her
                    whichWomen[firstWoman] = i; //She gets engaged to him
                    freeMen--; //Reduce the number of free men
                }else if(prefers(women[firstWoman - 1], i, whichWomen[firstWoman], couples)){//If she likes this man more than her current fiancee
                    whichMen[whichWomen[firstWoman]] = -1; //her current fiancee becomes free
                    removeFromList(men, (whichWomen[firstWoman] - 1), firstWoman); //She is removed from the list of preferences of her ex
                    whichMen[i] = firstWoman; //He gets engaged to her
                    whichWomen[firstWoman] = i; //She gets engaged to him 
                }else{ //If she prefers her current fiancee
                    removeFromList(men, i - 1, firstWoman); //Remove her from his list of preferences
                }
            }
        }
    }

    //Prints the answers
    for(int i = 1; i < couples + 1; i++){
        printf("%d %d\n", i, whichMen[i]);
    }

    free(whichMen);
    free(whichWomen);

    return;
}

/**
 * Frees each line in a matriz then 
 * frees the matrix itself
*/
void freeAll(int **vector, int size){
    for(int i = 0; i < size; i++){
        free(vector[i]);
    }

    free(vector);

    return;
}

/**
 * @brief  receives a number, reads the inputs for that number of couples
 * and returns a configuration of stable marriages
 * @param numberOfCouples 
 * @return 0 if successful, -1 if not 
 */
int getStableMarriagesFor(int numberOfCouples){
    int **women, **men;

    //Creating the preferences matrixes
    //printf("        Preferências das mulheres:\n");
    women = getPreferencesOf(numberOfCouples); //Creates the women's preference matrix with women[n - 1] being the nth woman
    
    //printf("        Preferências dos homens:\n");
    men = getPreferencesOf(numberOfCouples); //Creates the men's preference matrix with men[n - 1] being the nth man

    //Checking some easier cases
    if(allFirstsDifferentW(women, numberOfCouples))return 0; //If each woman prefers a different man, every woman marrying her favorite is stable
    if(allFirstsDifferentM(men, numberOfCouples))return 0; //if each man prefers a different woman, every man marrying his favorite is stable

    //printf("        Não é nenhum dos casos triviais\n");

    galeShapley(men, women, numberOfCouples);

    freeAll(men, numberOfCouples);
    freeAll(women, numberOfCouples);

    return 0;
}

int main(void){
    int testCases, numberOfCouples;
    scanf("%d", &testCases);

    while(testCases > 0){
        testCases--;
        //printf("Casos de teste restantes: %d\n", testCases);
        scanf("%d", &numberOfCouples);
        //printf("    Número de casais: %d\n", numberOfCouples);
        getStableMarriagesFor(numberOfCouples);
    }


    return 0;
}