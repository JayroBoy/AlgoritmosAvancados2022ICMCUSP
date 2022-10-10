#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

#define max(a,b) (((a) > (b))? (a) :(b))



//------------------------------------------DEBUG FUNCTIONS--------------------------------------------------------------

void printSolution(bool **sol){
    int d;
    for(int i = 0; i < 8; i++){
        printf("        ");
        for(int j = 0; j < 8; j++){
            printf(sol[i][j]? "Q " : "- ");
        }
        printf("\n");
    }
    scanf(" %d %d", &d, &d);

    return;
}

void printAllSolutions(bool ***sol){
    for(int i = 0; i < 92; i++){
        printf("    Solution %d:\n", i+1);
        printSolution(sol[i]);
        printf("---------------------\n");
    }
    return;
}


//---------------------------------------FINDING SOLUTIONS---------------------------------------------------------
/*Allocates and returns a 8*8 bool matrix*/
bool **createSolution(){
    bool **solution;
    solution=(bool**)malloc(sizeof(bool*) * 8);
    
    for(int i = 0; i < 8; i++){
        solution[i] = (bool*)malloc(8 * sizeof(bool));
        for(int j = 0; j < 8; j++){
            solution[i][j] = false;
        }
    }


    return solution;
}

/*Creates an array of 92 2D matrixes. Each matrix represents one possible solution for the 8-queens problem*/
bool ***createSolutionArray(){
    bool ***sol;
    sol= (bool***)malloc(92 * sizeof(bool**)); //For an 8*8 board with 8 queens, there are 92 solutions
    for(int i = 0; i < 92; i++){
        sol[i] = createSolution();
    }
    return sol;
}

/*Checks if a particular spot on the board is threatened*/
bool isSafe(bool **b, int r, int c){
    int i, j;

    //----------------COLUMN-------------------
    //Checking the column above for repetition
    /*
        - - - ?
        - - - ?
        - - - ?
        - - - Q
    */
    for(i = 0; i < r; i++){
        if(b[i][c]) return false;
    }
    //Checking the column below for repetition
    /*
        - - - Q
        - - - ?
        - - - ?
        - - - ?
    */
    for(i = r; i < 8; i++){
        if(b[i][c]) return false;
    }


    //----------------------------MAIN DIAGONAL------------------------------
    //Checking main diagonal from the left repetition
    /*
        ? - - -
        - ? - - 
        - - ? -
        - - - Q
    */
    for(i = r, j = c; i >=0 && j >= 0; i--, j--){
        if(b[i][j]) return false;
    }

    //Checking main diagonal from the right repetition
    /*
        Q - - -
        - ? - - 
        - - ? -
        - - - ?
    */
    for(i = r, j = c; i < 8 && j < 8; i++, j++){
        if(b[i][j]) return false;
    }


    //-----------------------SECONDARY DIAGONAL-------------------------------
    //Checking for secondary diagonal from the left repetition
    /*
        - - - Q
        - - ? -
        - ? - - 
        ? - - -
    */
    for(i = r, j = c; i < 8 && j >= 0; i++, j--){
        if(b[i][j]) return false;
    }

    //Checking for secondary diagonal from the right repetition
    /*
        - - - ?
        - - ? -
        - ? - - 
        Q - - -
    */
    for(i = r, j = c; i >= 0 && j < 8; i--, j++){
        if(b[i][j]) return false;
    }


    //If we reach this point, the position is not threatened
    return true;
}

/*Copies a particular solution to the solutions array*/
void saveSolution(bool **board, bool ***boards, int *index){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(board[i][j])boards[*index][i][j] = true;
        }
    }
    *index = *index+1;
    return;
}

/*Frees each line of a bool matrix and then frees the matrix itself*/
void freeSolution(bool **board){
    for(int i = 0; i < 8; i++){
        free(board[i]);
    }
    free(board);
    return;
}

/* A recursive utility function that solves the N(8) queens problem*/
void nQueen(bool **board, int r, bool ***boards, int *index){
   
    //Base case: All queens have been placed
    if (r == 8){
        saveSolution(board, boards, index);
        return;
    }

    //Place a queen at each column in current row
    for (int i = 0; i < 8; i++){
        //If this position is safe
        if (isSafe(board, r, i)){
            //Place a queen here
            board[r][i] = true;
 
            //Check for the next row with this queen in place
            nQueen(board, r + 1, boards, index);

            //Remove the queen from here to test other columns
            board[r][i] = false;
        }
    }
}
 
/*Fills the solutions array*/
void findAllSolutions(bool ***boards){
    bool **board = createSolution();
    int i = 0;
    //printf("    Starting recursion...\n");
    nQueen(board, 0, boards, &i);
    //printf("    Recursion finished!\n");
    freeSolution(board);
    return;
}

/*Frees each matrix in an array of bool matrixes and then frees the array itself*/
void freeAllSolutions(bool ***board){
    for(int i = 0; i < 92; i++){
        freeSolution(board[i]);
    }

    free(board);

    return;
}


//--------------------------------------READING SCORE CONFIGURATIONS-----------------------------------------------------
/*Allocates and returns a sizeXsize int matrix*/
int **newBoard(int size){
    int **board = (int**)malloc(size * sizeof(int*));

    for(int i = 0; i < 8; i++){
        board[i] = (int*)malloc(size * sizeof(int));
    }

    return board;
}

/*Reads boardside lines, each with boardside positions*/
void readBoard(int **board, int boardSide){
    for(int i = 0; i < boardSide; i++){
        for(int j = 0; j < boardSide; j++){
            scanf("%d", &board[i][j]);
        }
    }
}

/*Frees each line of an int matrix and then frees the matrix itself*/
void freeBoard(int **board){
    for(int i = 0; i < 8; i++){
        free(board[i]);
    }
    free(board);
    return;
}


//------------------------------------CALCULATING SCORES FOR EACH SOLUTION-----------------------------------------------
/*Runs all possible solutions through a score configuration to calculate the score for each solution*/
void calculateScores(bool ***s, int **b, int *scores){
    for(int a = 0; a < 92; a++){ //Going through all 92 possible configurations
       scores[a] = 0; //Start the score at 0
        for(int i = 0; i < 8; i++){ //Go through all rows
            for(int j = 0; j < 8; j++){ //Go through all columns
                if(s[a][i][j]) scores[a] += b[i][j]; //If there is a queen in this position for this solution, increase the score
            }
        }      
    }
}

/*Finds the highest value on a 92 positions array*/
int getMax(int *s){
    int result = 0;

    for(int i = 0; i < 92; i++){
        result = max(result, s[i]);
    }

    return result;
}

/*Given a board B, finds the best score for B*/
int findBestScoreForThis(int **b, bool ***solution){
    int *scores = (int*)malloc(92 * sizeof(int)); //92 possible solutions, 92 positions on the scores vector
    calculateScores(solution, b, scores);
    return getMax(scores);
}


//-----------------------------------CONTROL FUNCTION FOR EACH SCORE CONFIGURATION---------------------------------------
/*Reads one board score configuration, tests it against all possible solutions, returns the highest possible score*/
int runTest(bool ***sol){
    int score,
      **board;

    board = newBoard(8); 
    readBoard(board, 8); //Read the score configuration for this test

    score = findBestScoreForThis(board, sol); //Test this score configuration with all solutions
    freeBoard(board); //Free the memory for this score configuration

    return score;
}



int main(void){
    int k;

    //Generate all possible solutions for 8 queens in a 8*8 board
    //printf("Generating solutions...\n");
    bool ***sol; 
    sol = createSolutionArray();
    int counter = 0;

    //printf("Array created!\n");

    findAllSolutions(sol); 

    //printf("Solutions generated!\n");
    //printAllSolutions(sol);

    //Read number of configurations
    scanf("%d", &k);

    //Test each configuration 
    while(counter < k ){
        printf("%5d\n", runTest(sol));
        counter++;
    }

    freeAllSolutions(sol); //Frees dynamically allocated memory
}
