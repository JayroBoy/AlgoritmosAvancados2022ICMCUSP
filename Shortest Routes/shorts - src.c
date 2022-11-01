/* FLOYD-WARSHALL*/
/* Jayro Boy V. Neto
    9762880
    Alg. Avançados - Ex. Shortest Routes
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define INFINITY 10000000000000001

unsigned long long int **allocateGraph(int nodes){
    unsigned long long int **graph = malloc((nodes + 1) * sizeof *graph);
    for(int i = 1; i <= nodes; i++){ 
        graph[i] = calloc((nodes + 1), sizeof *(graph[i]));
        for(int j = 1; j <=nodes; j++){
            if(i == j) graph[i][j] = 0;
            else graph[i][j] = INFINITY;
        }
    }
    return graph;
}

void addEdge(unsigned long long int **graph, int a, int b, unsigned long long int len){
    graph[a][b] = len;
    graph[b][a] = len;
    
    return;
}

unsigned long long int **readInfo(int *cities, int *roads, int *trips){
    unsigned long long int **result;
    scanf("%d %d %d", cities, roads, trips);

    result = allocateGraph(*cities);

    for(int i = 0; i < *roads; i++){
        int a, b; 
        unsigned long long int length;
        scanf("%d %d %llu", &a, &b, &length);
        addEdge(result, a, b, length);
    } 

    return result;
}

/*
    Floyd - Warshall
        This algorithm is n^3, however, it calculates final distance from every point to every
        point. Therefore, we only have to do it once and then we only need to check the cost matrix. 
        Since FW's complexity is (nodes^3 + queries) and Dijkstra's is (queries * nodes^2), when 
        queries > nodes, FW is faster than Dijkstra.
*/
void getShortestPaths(unsigned long long int **graph, int nodes){
    for(int k = 1; k <= nodes; k++)
        for(int i = 1; i <= nodes; i++)
            for(int j = 1; j <= nodes; j++)
                if((graph[i][k] + graph[k][j]) <= graph[i][j]){
                    graph[i][j] = graph[i][k] + graph[k][j];
                }
    return;
}

/*
    Dijsktra
        This algorithm is n^2, however, it only calculates distances from a fixed starting
        point. Therefore, for every different starting point, we have to do it again. Since 
        FW's complexity is (nodes^3 + queries) and (naive)Dijkstra's is (queries * nodes^2), when 
        queries < nodes, Dijkstra is faster than FW
*/
unsigned long long int getShortestPath(unsigned long long int **graph, int nodes, int start, int end){
    int *previous = malloc((nodes + 1) * sizeof *previous), //+1 because indexes start at 0
        count,
        nextNode = end;
    unsigned long long int minimumDistance,  
                  *distance = malloc((nodes + 1) * sizeof *distance);
    bool *visited = malloc((nodes + 1) * sizeof(bool));

    //Initialize auxiliary information
    for(int i = 1; i <= nodes; i++){
        distance[i] = graph[start][i];  
        previous[i] = start;
        visited[i] = false;
    }

    //Mark we're starting from start
    distance[start] = 0;
    visited[start] = true;
    count = 1;

    while(count < (nodes - 1)){
        minimumDistance = INFINITY;
        //Get closest node
        for(int i = 1; i <= nodes; i++){
            if(distance[i] < minimumDistance && !visited[i]){
                minimumDistance = distance[i];
                nextNode = i;
            }
        }
        visited[nextNode] = true;
        //Optimize distance to unvisited nodes
        for(int i = 1; i <= nodes; i++){
            if(!visited[i])
                if(minimumDistance + graph[nextNode][i] < distance[i]){
                    distance[i] = minimumDistance + graph[nextNode][i];
                    previous[i] = nextNode;
                }
        }
        count++;
    }

    minimumDistance = distance[end];

    free(visited);
    free(distance);
    free(previous);

    return minimumDistance;
}

void freeGraph(unsigned long long int **graph, int cities){
    for(int i = 0 ; i <= cities; i++) free(graph[i]);
    free(graph);
    
    return;
}

int main(void){
    int cities,
        roads,
        trips,
        counter = 0;
    unsigned long long int **graph;

    graph = readInfo(&cities, &roads, &trips);

    if(trips > cities){
        getShortestPaths(graph, cities);
        while(counter < trips){
            int a, b;
            scanf("%d %d", &a, &b);
      
            unsigned long long int shortest = graph[a][b];

            shortest != INFINITY? printf("%llu\n", shortest):printf("-1\n");

            counter++;
        }
    }else{
        while(counter < trips){
            int a, b;
            scanf("%d %d", &a, &b);

            unsigned long long int shortest = getShortestPath(graph, cities, a, b);
            
            shortest != INFINITY? printf("%llu\n", shortest):printf("-1\n");

            counter++;
        }
    }

    freeGraph(graph, cities);
    return 0;
}
