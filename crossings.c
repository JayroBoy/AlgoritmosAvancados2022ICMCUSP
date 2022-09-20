#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/*The maximum crossing problem can be found on codeforces on the
following link:https://codeforces.com/problemset/problem/1676/H2

It is not difficult to understand. However, the description on codeforces
is not very good, so I will try to explain it better here.

The idea behind maximum crossings is to find a worst case scenario
in order to make sure some model can stand to the task. The particular
case here is two parallel train terminals, let's call them A and B.

Each terminal is comprised of N segments of equal size, numbered 1 - n.
So if N is 5, for example, we have the following model:

	A:	_1_   _2_   _3_   _4_   _5_  

	B:	_1_   _2_   _3_   _4_   _5_

Each segment of A has exactly one path that exits is and arrives 
at some segment of B. So for N = 5, we could have the following
array: Paths = [1, 2, 3, 4, 5]. This represents the following configuration:

	A:	_1_   _2_   _3_   _4_   _5_  
		 |     |	 | 	   |	 |
	B:	_1_   _2_   _3_   _4_   _5_
	

That is, the paths that connect segments of A to segments of B are i - Paths[i]

Since the components of A and B are segments, and not points, this means we have
some liberty on how to establish these paths. For example, we could do a slightly
different configuration for the situation above, which would look like this:

	A:	_1_   _2_   _3_   _4_   _5_  
		  |  |	    | 	    |	 |
	B:	_1_   _2_   _3_   _4_   _5_
	
	
The restriction is that we can't have paths leaving from or arriving at the endpoints
of any segments. Our job is to, given N and Paths, find the configuration that maximizes
the amount of times one path crosses another. In the case of the terminals, for example
this would represent the worst-case scenario for a particular train station, the one in
which the maximum amount of people have to cross each other's paths, and thus, the slowest
rate of movement.  

*/


/*Reads n destinations and saves them to a n+1 sized array. The n+1 here is just so 
segment 1 is on position 1 and so on*/
int *readDestinations(int n){
	int *res = (int*)malloc((n + 1) * sizeof(int)), //N+1 to adjust indexes
	i = 1;
	
	while(i <= n){
		scanf("%d", &res[i]);
		i++;
	}
	
	return res;
}

/*Given a number of segments and the ends of the paths, finds the
maximum number of crossings*/
long long int findMax(int *paths, int number){
	long long int ans = 0;
	int	*s = (int*)calloc((number + 1), sizeof(int)); //S[i] registers how many paths arrive at position i in terminal B
	
	//For every segment in terminal A
	for(int i = number; i >= 1; i--){
		for(int x = paths[i]; x != 0; x-= x&-x) ans+= s[x]; //Starting on the endpoint of the 
															//path that leaves this segment, 
															//add up the crossings
															
		for(int x = paths[i]; x <= number; x+= x&-x)s[x]++; //Recount the number of crossings 
															//for future iterations
	}
		
	free(s);
	
	return ans;
}

long long int tryNewCase(void){
	int n,
	   *dests;
	long long int ans;
	   
	scanf("%d", &n);
	//if(n < 2) return 0;
	
	dests = readDestinations(n);
	
	ans = findMax(dests, n);
	
	free(dests);
	
	return ans;
}



int main(void){
	int testCases;
	scanf("%d", &testCases);
	
	while(testCases){
		printf("%lld\n", tryNewCase());
		testCases--;
	}
	
	return 0;
}