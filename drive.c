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
void inputValidation(int argc, char *argv[]);
Boolean isMinFn(char *geneType);
Boolean isPcbMill(char *geneType);
Boolean isPosIntNonZero(char *num);
Boolean isPosInt(char *num);
void myExit(char *errorMessage);
Boolean isNumber(char *num);

void test_pcbmill(void){
	/* TO DO */
	Gene *gene, *mutant, *p1, *p2, *child;

	printf("PCBMILL gene:\n");

	/* TO DO - create a random pcbmill gene by calling create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN */
	gene = gene_create_rand_gene(TEST_ALLELE_LEN, &create_pcbmill_chrom);

	/* TO DO - print the gene using gene_print */
	gene_print(gene);

	printf("\nMutate: ");
	mutant = mutate_pcbmill(gene);
	gene_print(mutant);
	/* TO DO - create a mutant copy of the gene using mutate_pcbmill */
	/* TO DO - print the mutant gene using gene_print */
	printf("\n");
	/* TO DO - free the original gene and the mutant */
	gene_free(gene);
	gene_free(mutant);
	printf("PCBMILL genes:\n");
	/* TO DO - create 2 random pcbmill 'parent' genes using calls
	   to create_rand_gene
	   The length of the gene's chromosome should be TEST_ALLELE_LEN */
	p1 = gene_create_rand_gene(TEST_ALLELE_LEN, &create_pcbmill_chrom);
	p2 = gene_create_rand_gene(TEST_ALLELE_LEN, &create_pcbmill_chrom);

	/* TO DO - print each gene */
	gene_print(p1);
	gene_print(p2);

	printf("\nCrossover: ");
	child = crossover_pcbmill(p1, p2);
	gene_print(child);
	/* TO DO produce a new gene by calling crossover_pcbmill
	   with the parent genes */
	/* TO DO - print the new gene */

	printf("\n");
	/* TO DO - free both parents and the child gene */
	gene_free(p1);
	gene_free(p2);
	gene_free(child);
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
	InVTable invt;
	Pop_list *popList;
	int gens, i;

	/* The only point at which srand should be called */
	srand(SRAND_SEED);

	#ifdef DEBUG
		test_minfn();
		test_pcbmill();
	#else
		/* Validate all args except files */
		inputValidation(argc, argv);
		gens = atoi(arg[numGen]);

		/* Initialise invector table */
		invector_init(&invt);
		if (!buildTable(&invt, argv[inputFile])) {
			printf("Could not open %s", argv[inputFile]);
			return EXIT_FAILURE;
		}

		/* Initialise popList */
		popList = myMalloc(sizeof(Pop_list) * gens);
		for (i=0; i < gens; i++) {

			pop_init(&&popList[i]);

			/* Set popList functions */
			if (isMinFn(argv[geneType])) {
				pop_set_fns(popList + i, create_minfn_chrom, mutate_minfn,
							crossover_minfn, eval_minfn);
			}
			pop_set_fns(popList + i, create_pcbmill_chrom, mutate_pcbmill,
						crossover_pcbmill, eval_pcbmill);
		}

		printTable(invt);

		return EXIT_SUCCESS;
	#endif
}

void inputValidation(int argc, char *argv[]) {
	Boolean isInvalid = FALSE;

	/* Check number of arguments */
	if (argc != CMD_ARG_MAX && argc != CMD_ARG_MAX - 1)
		myExit("Invalid number of arguments!");

	/* Check geneType */
	if (!isMinFn(argv[geneType]) &&	!isPcbMill(argv[geneType])) {
		isInvalid = TRUE;
		printf("Invalid geneType\n");
	}

	/* Check alleleSize */
	if (!isPosIntNonZero(argv[alleleSize])) {
		isInvalid = TRUE;
		printf("Invalid alleleSize\n");
	}

	/* Check popSize */
	if (!isPosIntNonZero(argv[popSize])) {
		isInvalid = TRUE;
		printf("Invalid popSize\n");
	}

	/* Check numGen */
	if (!isPosInt(argv[numGen])) {
		isInvalid = TRUE;
		printf("Invalid numGen\n");
	}

	if(isInvalid)
		exit(EXIT_FAILURE);
}

Boolean isPosIntNonZero(char *num) {
	if (isNumber(num)) {
		if (atoi(num) > 0)
			return TRUE;
	}
	return FALSE;
}

Boolean isPosInt(char *num) {
	if (isNumber(num)) {
		if (atoi(num) >= 0)
			return TRUE;
	}
	return FALSE;
}

Boolean buildTable(InVTable *invt, char *fileName) {
	FILE *fp;
	char line[INV_LEN];
	char *allele;
	int i;

	/* Attempt to open the file */
	fp = fopen(fileName, "r");
	if (fp == NULL) {
		fclose(fp);
		return FALSE;
	}

	/* Read file line by line*/
	while (fgets(line, INV_LEN, fp) != NULL) {
		/* Grab the allele token */
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

void myExit(char *errorMessage) {
	printf(errorMessage);
	exit(EXIT_FAILURE);
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

Boolean isMinFn(char *geneType) {
	if (strcmp(geneType, CMD_ARG_MINFN) == 0) {
		return TRUE;
	}
	return FALSE;
}

Boolean isPcbMill(char *geneType) {
	if (strcmp(geneType, CMD_ARG_PCBMILL) == 0) {
		return TRUE;
	}
	return FALSE;
}

Boolean isNumber(char *num) {
	int i = 0;
	char currChar = num[i];

	while (currChar != '\0') {
		if (!isdigit(currChar)) {
			return FALSE;
		}
		i++;
		currChar = num[i];
	}
	return TRUE;
}
