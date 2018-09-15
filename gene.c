/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "gene.h"

int * create_pcbmill_chrom(int numAlleles){
	int *chrom, i, index;
	chrom = calloc(numAlleles, sizeof(int));

	/* Loop through possible values excluding zero */
	for (i=1; i < numAlleles; i++) {

		/* Only place value at index with value zero*/
		do {
			index = rand() % numAlleles;
		} while(chrom[index] != 0);
		chrom[index] = i;
	}
	return chrom;
}

int * create_minfn_chrom(int numAlleles){
	int *chrom, i;

	chrom = malloc(sizeof(int) * numAlleles);

	/* Loop through all indexes and assign a random int */
	for (i=0; i < numAlleles; i++) {
		chrom[i] = rand() % (MINFN_MAX + 1);
	}
	return chrom;
}

Gene * mutate_pcbmill(Gene *g){
	/* TO DO */
	return NULL;
}

Gene * mutate_minfn(Gene *g){
	/* TO DO */
	return NULL;
}

Gene * crossover_pcbmill(Gene *g1, Gene *g2){
	/* TO DO */
	return NULL;
}

Gene * crossover_minfn(Gene *g1, Gene *g2){
	/* TO DO */
	return NULL;
}

double eval_pcbmill(InVTable *invt, Gene *gene){
	/* TO DO */
	return 0.0;
}

double eval_minfn(InVTable *invt, Gene *gene){
	/* TO DO */
	return 0.0;
}

Gene * gene_create_rand_gene(int numAlleles, CreateFn create_chrom){
	/* TO DO */
	return NULL;
}

void gene_calc_fitness(Gene *gene, EvalFn evaluate_fn, InVTable *invTab){
	/* TO DO */
}

void gene_normalise_fitness(Gene *gene, double total_fitness){
	/* TO DO */
}

void gene_free(Gene *gene){
	/* TO DO */
}


double gene_get_fitness(Gene *gene){
	/* TO DO */
	return 0.0;
}

void gene_print(Gene *gene) {
	/* TO DO */
}
