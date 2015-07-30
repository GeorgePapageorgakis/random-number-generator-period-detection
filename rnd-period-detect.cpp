/**
    rnd-period-detect.cpp Defines the entry point for the console application.
	
    Purpose: detect the period of a pseudorandom number generator. More specifically,
	given a linear generator remainder, it produces consecutive numbers of the sequence and 
	as soon as it finds the first value that is equal to a previous value, it stops and 
	returns the number of steps intervening between these two same values. A key feature 
	in this technique is to determine whether the current value of the sequence is equal 
	to one of the values that have been previously appeared.
	
    @author George Papageorgakis
    @version 1.0 9/2014
*/
#include <stdio.h>
#include <stdlib.h>

#define A 3
#define C 19
#define M 15001
#define SEED 27
#define HTSIZE 500

typedef struct node {
	int value;
	int counter;	// order of insertion
	struct node *next;
} t_listnode;

typedef struct {
	t_listnode *head;
	t_listnode *tail;
} t_htentry;


int insertElement (int x, int counter, t_htentry *ht, int htsize); 	/* Entries into the hash table */
int searchElement (int x, t_htentry *ht, int htsize); 			/* Search the hash table */
int generate(int a, int c, int m, int x); 				/* Random Number Generator */
int findPeriod(int a, int c, int m, int x);  				/* Period detection of the pseudo-random number sequence */

int main() {
	int period;
	period = findPeriod(A, C, M, SEED);
	
	printf("The period of the sequence is: %d\n", period);
	
	return 0;
}

/* Entries into the hash table.                 			*/
/* The function receives as arguments the element x inserted,		*/
/* the turn input counter, the hash table ht and the size of the table  */
int insertElement (int x, int counter, t_htentry *ht, int htsize) {
	t_listnode *new_node;
	int ht_index = (x % htsize);
	
	//initialize a new node of type t_listnode
	new_node = (t_listnode *) malloc(sizeof(t_listnode));
	if (!new_node){
		printf("Memory allocation failed!\n"); fflush(stdout);
		exit (1);
	}
	new_node->value   = x;
	new_node->counter = counter;
	new_node->next    = NULL;
	
	//assign new node and update hash table pointers
	if(ht[ht_index].head == NULL){
		ht[ht_index].head = new_node;
		ht[ht_index].tail = new_node;
	}
	else{
		ht[ht_index].tail->next = new_node;
		ht[ht_index].tail       = new_node;
	}
	if (ht[ht_index].tail->value == x)
		return 1;
	else
		return 0;
}

/* Search the hash table. The function receives as arguments the number x 	*/
/* that we seek, the hash table ht and the size of the table. Returns the 	*/
/* input range of the element or 0 if the item is not found.			*/
int searchElement (int x, t_htentry *ht, int htsize) {
	t_listnode *aux = NULL;
	int ht_index    = (x % htsize);
	
	aux = ht[ht_index].head;
	while(aux != NULL){
		if(aux->value != x)
			aux = aux->next;
		else
			return aux->counter;
	}
	return 0;
}

/* Generate a pseudorandom number. The function receives as arguments the 	*/
/* parameters a, c, m of the generator and the previous number x. Returns 	*/
/* the next pseudorandom number. 											*/
int generate(int a, int c, int m, int x) {
	return ((a * x) + c) % m;
}

/* Find the period for a sequence of pseudorandom numbers. The function receives	*/
/* as arguments the parameters a, c, m of the generator and the number x which		*/
/* initially seeds the generator and returns the period of the sequence.		*/
int findPeriod(int a, int c, int m, int x) {
	int i, counter = 1;
	int rand_val = x;
	int period = 0;
	
	//initialize hash table
	t_htentry *ht = (t_htentry *) malloc(HTSIZE * sizeof(t_htentry));
	for(i=0; i<HTSIZE; i++){
		ht[i].head = NULL;
		ht[i].tail = NULL;
	}
	
	//repeat as long as we havent found a period
	while(!period){
	//generate the pseydo random value
	rand_val = generate(a, c, m, rand_val);
	
	//search for the value in the hash table
	period = searchElement(rand_val, ht, HTSIZE);
	
	//insert the sequence "random" value
	//if period != 0 then rand_val already exist in hash table
	if (!period)
		counter += insertElement(rand_val, counter, ht, HTSIZE);
	}
	
	//free memory
	//TODO
	//ht_destroy(ht);
	free(ht);
	return (counter - period);
}
