/*****************************************************************************/
/*
* Routines to manipulate populations
*
* MALIS Lab Session
*
/*****************************************************************************/
#define null (void *)0

#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>

#include "population.h"

/*****************************************************************************/
/* compare the fitness of two chromosomes */
/* returns -1 if c1 is fitter, or 1 if c2 is fitter, 0 for equality */
static int chromosome_compare_fitness(const Chromosome * c1, const Chromosome * c2){
	double f1=c1->fitness;
	double f2=c2->fitness;

	if (f1 == f2) return 0;
	if (f1 < f2) return -1;
	else return  1;
}

/*****************************************************************************/
/* sort population according to fitness: fittest first (shortest round-trip) */
void population_sort(Population * pop) {
	qsort((Chromosome *)pop->chromosome,
	pop->current_size,
	sizeof(Chromosome),
	(int(*)(const void *,const void *)) chromosome_compare_fitness);
}

/*****************************************************************************/
/* Initialize population with random chromosomes */
void population_random(Population *pop, int size){
	int i;
	assert(size <= MAX_POP_SIZE);
	for(i=0;i< size ;i++){
		chromosome_random(&pop->chromosome[i]);
	}
	pop->current_size = size;
}

/*****************************************************************************/
void population_print(Population * pop){
	int i;
	printf("Population size %d:\n",pop->current_size);
	for(i=0; i<pop->current_size; i++){
		chromosome_print(&pop->chromosome[i]);
	}
}

/*****************************************************************************/
/* Select the best chromosomes of the population */ 
void population_selection(Population * pop,int n_best){
	
	assert(1<n_best && n_best<MAX_POP_SIZE);
	/* Be careful not to extinct the population */
	/* BEGIN IMPLEMENTATION */
	population_sort(pop);
	pop->current_size = n_best;
	/* END IMPLEMENTATION */
}

/*****************************************************************************/
/* mutate the population: apply one mutation to each chromosome with a given probability */
void population_mutation(Population * pop, double mutation_rate) {
	assert(0<=mutation_rate && mutation_rate<=1);

	/* BEGIN IMPLEMENTATION */
	for (int i = 0; i < pop->current_size; i++) 
	{
		int tmp = rand() % 100;
		mutation_rate *= 100;

		if (tmp <= mutation_rate)
		{
			chromosome_mutation(&pop->chromosome[i]);
		}
	}
	/* END IMPLEMENTATION */
}

/*****************************************************************************/
/* Crossover the population: select parents at random and generate offspring until
the new size is reached */
void population_crossover(Population * pop, int new_size){

	assert(new_size <= MAX_POP_SIZE);

	/* BEGIN IMPLEMENTATION */
	while (pop->current_size < new_size)
	{
		int mother = rand() % pop->current_size;
		int father = rand() % pop->current_size;

		Chromosome offspring;
		chromosome_crossover(&pop->chromosome[mother], &pop->chromosome[father], &offspring);
		pop->chromosome[pop->current_size++] = offspring;
	}
	/* END IMPLEMENTATION */
}
