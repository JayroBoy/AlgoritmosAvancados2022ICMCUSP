/*Jayro Boy de Vasconcellos Neto
9762880
Alg. Avançados - Ex PD2 

Resort Tickets
Given N days and prices X, Y and Z for 1, 7 and 30 days passes, find the minimum
amount of money needed to be on a resort for each of the N days.

*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#define min(a,b) (((a) < (b))? (a) : (b))
#define max(a,b) (((a) > (b))? (a) : (b))


//Reads all days that we will be in the resort and returns the last one
int getTripDays(bool *isOnTrip, int numberOfDays){
	int a;
	
	for(int i = 1; i <= numberOfDays; i++){
		scanf("%d", &a);
		isOnTrip[a] = true;
	}
	
	return a;
}

void getMinimumPrice(bool *isOnTrip, int o, int s, int t, long long int *costOfDay, int lastDay){
	//For every day until the last one on the resort
	for(int day = 1; day <= lastDay; day++){
		if(!isOnTrip[day]) costOfDay[day] = costOfDay[day - 1]; //If we don't have to be in the resort, price is unchanged
		else{
			int minCost;
		
			minCost = costOfDay[day - 1] + o; //Find out the price of buying a ticket just for today
			minCost = min(minCost, costOfDay[max(0, day-7)] + s); //Find out the price of having bought a 7-day ticket that ends today 7 days ago(Or at the beginning of the trip)
			minCost = min(minCost, costOfDay[max(0, day-30)] + t); //Find out the price of having bought a 30-day ticket that ends today 30 days ago (Or at the beginning of the trip)
			
			costOfDay[day] = minCost; //Save today's cost as the minimum among the three above
		}
	}
	
	return;
}
	

int main(void){
	int numberOfDays,
		o, s, t, //One, seven, thirty 
		lastDay;
	long long int *costOfDay = (long long int*) calloc(301, sizeof(long long int));
	bool *isOnTrip = (bool*)calloc(301, sizeof(bool));
	
	scanf("%d %d %d %d", &numberOfDays, &o, &s, &t);
	
	lastDay = getTripDays(isOnTrip, numberOfDays);
	getMinimumPrice(isOnTrip, o, s, t, costOfDay, lastDay);
	
	printf("%lld", costOfDay[lastDay]);
	
	free(isOnTrip);
	free(costOfDay);
	
	return 0;
}