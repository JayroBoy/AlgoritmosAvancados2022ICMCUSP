/** 
 * Jayro Boy Neto
 * 9762880
 * Algoritmos Avançados
 * 
 * Esse programa recebe n vértices de forma ordenada
 * e usa a shoelace formula para calcular a área do polígono
 * formado por esses vértices
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void readVertices(int **x, int **y, int size){
    *x = malloc(size * sizeof(int));
    *y = malloc(size * sizeof(int));

    for(int i = 0; i < size; i++){
        scanf("%d %d", &(*x)[i], &(*y)[i]);
    }

    return;
}

long long int polygonArea(int *X, int *Y, int n){
    long long int area = 0;
    int j = n - 1;
    
    for (int i = 0; i < n; i++)
    {
        area += ((long long)X[j] + (long long)X[i]) * ((long long)Y[j] - (long long)Y[i]);
        j = i; 
    }

    return area > 0? area : -area;
}

int main(void){
    int n,
        *x,
        *y;
    
    //Read all inputs
    scanf("%d", &n);
    readVertices(&x, &y, n);
    
    //Print expected output
    printf("%lld\n", polygonArea(x, y, n));
    
    //free used memory
    free(x);
    free(y);
    
    return 0;
}