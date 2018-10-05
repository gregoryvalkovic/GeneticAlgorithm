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

	chrom = myMalloc(sizeof(int) * numAlleles);

	/* Loop through all indexes and assign a random int */
	for (i=0; i < numAlleles; i++) {
		chrom[i] = rand() % (MINFN_MAX + 1);
	}
	return chrom;
}


Gene * mutate_pcbmill(Gene *g){
	int index1, index2, temp;
	Gene *mutant = gene_init(g->num_alleles);

	/* Copy gene but reset fitness and raw_score */
	gene_copy(g, mutant);
	mutant->fitness = 0.0;
	mutant->raw_score = 0.0;

	#ifdef DEBUG
		index1 = 2;
		index2 = 4;
	#else
		/* Randomises the indices to swap, looping if they are identical*/
		index1 = rand() % g->num_alleles;
		do {
			index2 = rand() % g->num_alleles;
		}while (index2 == index1);
	#endif

	/* Swap the indices */
	temp = mutant->chromosome[index1];
	mutant->chromosome[index1] = mutant->chromosome[index2];
	mutant->chromosome[index2] = temp;

	return mutant;
}


Gene * mutate_minfn(Gene *g){
	int index;
	Gene *mutant = gene_init(g->num_alleles);

	/* Copy gene but reset fitness and score */
	gene_copy(g, mutant);
	mutant->raw_score = 0.0;
	mutant->fitness = 0.0;

	/* Set index to mutate */
	#ifdef DEBUG
		index  = 2;
	#else
		index = rand() % mutant->num_alleles;
	#endif

	mutant->chromosome[index] = rand() % (MINFN_MAX + 1);
	return mutant;
}


Gene * crossover_pcbmill(Gene *g1, Gene *g2){
	/* TO DO */
	int index1, index2, i, childIndex = 0;

	/* Initialise child gene */
	Gene *child = gene_init(g1->num_alleles);
	child->num_alleles = g1->num_alleles;

	#ifdef DEBUG
		index1 = 2;
		index2 = 4;
	#else
		/* Randomise indices until index2 <= index1*/
		index1 = rand() % g1->num_alleles;
		do {
			index2 = rand() % g1->num_alleles;
		}while (index1 > index2);
	#endif

	/* Copy the values in g1 chromosome that are between indices */
	for (i=index1; i <= index2; i++) {
		child->chromosome[childIndex] = g1->chromosome[i];
		childIndex++;
	}

	i = 0;
	/* Loop through child chromomsome */
	for (; childIndex < child->num_alleles; childIndex++) {

		/* Loop in g2 to find value not already in child */
		while (chromosomeHas(child, g2->chromosome[i]) &&
			   i < g2->num_alleles) {
			i++;
		}
		/* Assign the value from g2 and increment i */
		child->chromosome[childIndex] = g2->chromosome[i];
		i++;
	}

	return child;
}


Gene * crossover_minfn(Gene *g1, Gene *g2){
	int i, index;
	Gene *gCross = gene_init(g1->num_alleles);

	/* Set index */
	#if DEBUG
		index = 2;
	#else
		index = rand() % g1->num_alleles;
	#endif

	/* Loop to the point of the randomised index and copy */
	for (i=0; i <= index; i++) {
		gCross->chromosome[i] = g1->chromosome[i];
	}

	/* Copy the remaining values from */
	for (; i < g1->num_alleles; i++) {
		gCross->chromosome[i] = g2->chromosome[i];
	}
	return gCross;
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

	gene = myMalloc(sizeof(Gene));
	gene->chromosome = create_chrom(numAlleles);
	gene->num_alleles = numAlleles;
	gene->raw_score = 0.0;
	gene->fitness = 0.0;
	return gene;
}


void gene_calc_fitness(Gene *gene, EvalFn evaluate_fn, InVTable *invTab){
	gene->raw_score = evaluate_fn(invTab, gene);
	gene->fitness = 1 / (gene->raw_score + 1.0);
}


void gene_normalise_fitness(Gene *gene, double total_fitness){
	gene->fitness = gene->fitness / total_fitness;
}


void gene_free(Gene *gene){
	free(gene->chromosome);
	free(gene);
}


double gene_get_fitness(Gene *gene){
	return gene->fitness;
}


void gene_print(Gene *gene) {
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
	printf("fit: %.3f raw:  %.3f\n", gene->fitness, gene->raw_score);
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


Gene * gene_init(int numAlleles) {
	Gene *gene = myMalloc(sizeof(Gene));
	gene->chromosome = myCalloc(numAlleles, sizeof(int));
	gene->num_alleles = numAlleles;
	gene->raw_score = 0.0;
	gene->fitness = 0.0;
	return gene;
}


Boolean chromosomeHas(Gene *g, int x) {
	int i;

	/* Linear search for x */
	for (i=0; i < g->num_alleles; i++) {
		if (g->chromosome[i] == x)
			return TRUE;
	}
	return FALSE;
}
