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
	int index;
	Gene *mutant = malloc(sizeof(Gene));

	gene_copy(g, mutant);
	/* Place random value at random index */
	index = rand() % mutant->num_alleles;
	mutant->chromosome[index] = rand() % (MINFN_MAX + 1);
	return mutant;
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
	/* TEST */
	int i, *currPos, *nextPos;
	double raw = 0.0;

	/* Iterate through all but last allele */
	for (i=0; i < gene->num_alleles - 1; i++) {

		/* Lookup current allele and next allele in the table */
		currPos = invt->table[gene->chromosome[i]];
		nextPos = invt->table[gene->chromosome[i+1]];

		/* Calculate the distance between both points */
		raw += sqrt(pow(nextPos[0] - currPos[0], 2) +
			pow(nextPos[1] - currPos[1], 2));
	}
	return raw;
}

double eval_minfn(InVTable *invt, Gene *gene){
	/* TEST */
	int i;
	double raw = 0.0;

	/* Iterate through all alleles and multiply with appropriate vector value*/
	for (i=0; i < gene->num_alleles; i++) {
		raw += invt->table[0][i] * gene->chromosome[i];
	}
	/* Subtract E and return the absolute value*/
	return abs(raw - invt->table[0][i]);
}

Gene * gene_create_rand_gene(int numAlleles, CreateFn create_chrom){
	Gene *gene;

	gene = malloc(sizeof(Gene));
	gene->chromosome = create_chrom(numAlleles);
	gene->num_alleles = numAlleles;
	gene->raw_score = 0.0;
	gene->fitness = 0.0;
	return gene;
}

void gene_calc_fitness(Gene *gene, EvalFn evaluate_fn, InVTable *invTab){
	/* TO DO */
}

void gene_normalise_fitness(Gene *gene, double total_fitness){
	/* TO DO */
}

void gene_free(Gene *gene){
	free(gene->chromosome);
	free(gene);
}


double gene_get_fitness(Gene *gene){
	/* TO DO */
	return 0.0;
}

void gene_print(Gene *gene) {
	/* TO DO */
	int i;

	printf("chrom: ");

	/* Print the allele values */
	for (i=0; i < gene->num_alleles; i++) {
		printf("%d", gene->chromosome[i]);
		if (i != gene->num_alleles - 1) {
			printf(",");
		}else {
			printf(" ");
		}
	}
	printf("fit: %f raw:  %f\n", gene->fitness, gene->raw_score);
}


void gene_copy(Gene *g1, Gene *g2) {
	int i;

	g2->num_alleles = g1->num_alleles;
	g2->raw_score = g1->raw_score;
	g2->fitness = g1->fitness;

	for (i=0; i < g2->num_alleles; i++) {
		g2->chromosome[i] = g1->chromosome[i];
	}
}
