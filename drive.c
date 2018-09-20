/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "drive.h"
#include "invector.h"
#include "pop.h"
#include "gene.h"

/* Function prototypes */
void printTable(InVTable invt);
Boolean buildTable(InVTable *invt, char *fileName);

void test_pcbmill(void){
	/* TO DO */
	Gene *gene;

	printf("PCBMILL gene:\n");

	/* TO DO - create a random pcbmill gene by calling create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN */
	gene = gene_create_rand_gene(TEST_ALLELE_LEN, &create_pcbmill_chrom);

	/* TO DO - print the gene using gene_print */
	gene_print(gene);

	printf("\nMutate: ");
	/* TO DO - create a mutant copy of the gene using mutate_pcbmill */
	/* TO DO - print the mutant gene using gene_print */
	printf("\n");
	/* TO DO - free the original gene and the mutant */
	printf("PCBMILL genes:\n");
	/* TO DO - create 2 random pcbmill 'parent' genes using calls
	   to create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN */
	/* TO DO - print each gene */
	printf("\nCrossover: ");
	/* TO DO produce a new gene by calling crossover_pcbmill
	   with the parent genes */
	/* TO DO - print the new gene */
	printf("\n");
	/* TO DO - free both parents and the child gene */
}

void test_minfn(void){
	/* TO DO */
	Gene *gene, *mutant, *p1, *p2, *child;

	printf("MINFN gene:\n");

	/* TO DO - create a random minfn gene by calling create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN */
	gene = gene_create_rand_gene(TEST_ALLELE_LEN, &create_pcbmill_chrom);
	gene_print(gene);

	/* print the gene */
	printf("\nMutate: ");

	/* TO DO - create a mutant copy of the gene using mutate_minfn */
	mutant = mutate_minfn(gene);

	/* TO DO - print the mutant gene */
	printf("\n");
	gene_print(mutant);

	/* TO DO - free the original gene and the mutant */
	gene_free(gene);
	gene_free(mutant);

	printf("\nMINFN genes:\n");
	/* TO DO - create 2 random minfn 'parent' genes using calls
	   to create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN */
	p1 = gene_create_rand_gene(TEST_ALLELE_LEN, &create_minfn_chrom);
	p2 = gene_create_rand_gene(TEST_ALLELE_LEN, &create_minfn_chrom);

	/* TO DO - print each gene */
	gene_print(p1);
	gene_print(p2);

	printf("\nCrossover: ");
	/* TO DO produce a new gene by calling crossover_minfn
	   with the parent genes */
	child = crossover_minfn(p1, p2);

	/* TO DO - print the new gene */
	gene_print(child);
	printf("\n");
	/* TO DO - free both parents and the child gene */
	free(p1);
	free(p2);
	free(child);
}

int main(int argc, char *argv[]){
	char *fileName = argv[inputFile];
	InVTable invt;
	Gene *gene;

	/* The only point at which srand should be called */
	srand(SRAND_SEED);

	#ifdef DEBUG
		test_minfn();
	#else
		/* Initialise invector table */
		invector_init(&invt);
		if (!buildTable(&invt, fileName)) {
			printf("Could not open %s", fileName);
			return EXIT_FAILURE;
		}
		printTable(invt);

		printf("pcbmill\n");
		gene = gene_create_rand_gene(TEST_ALLELE_LEN, &create_pcbmill_chrom);
		gene_print(gene);
		printf("\n");

		printf("minfn\n");
		gene = gene_create_rand_gene(TEST_ALLELE_LEN, &create_minfn_chrom);
		gene_print(gene);
		printf("\n");
	#endif


	return EXIT_SUCCESS;
}


Boolean buildTable(InVTable *invt, char *fileName) {
	FILE *fp;
	char line[INV_LEN];
	char *allele;
	int i;

	/* Attempt to open the file */
	fp = fopen(fileName, "r");
	if (fp == NULL)
		return FALSE;

	/* Read file line by line*/
	while (fgets(line, INV_LEN, fp) != NULL) {
		allele = strtok(line, INV_DELIM2);
		allele = strtok(NULL, INV_DELIM2);
		allele = strtok(allele, INV_DELIM3);

		/* Build table */
		for (i=0; i < invt->width; i++) {
			invt->table[invt->tot][i] = atoi(allele);
			allele = strtok(NULL, INV_DELIM3);
		}
		invt->tot++;
	}
	fclose(fp);
	return TRUE;
}


void printTable(InVTable invt) {
	int i, j;

	/* Loop through all rows */
	for (i=0; i < invt.tot; i++) {
		printf("%d: ", i);

		/* Loop through each allele */
		for (j=0; j < invt.width; j++) {
			printf("%d ", invt.table[i][j]);
		}
		printf("\n");
	}
}
