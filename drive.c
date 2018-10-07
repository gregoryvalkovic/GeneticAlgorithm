/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "drive.h"
#include "invector.h"
#include "pop.h"
#include "gene.h"

/* Function Prototypes */
void initPopList(Pop_list **popList, char *geneType, int gens);
void cloneFittest(Pop_list *popList, Pop_list *newPopList);

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


	/* The only point at which srand should be called */
	srand(SRAND_SEED);

	#ifdef DEBUG
		test_minfn();
		test_pcbmill();
		return EXIT_SUCCESS;
	#else
		InVTable invt;
		int gens, sizePop, sizeAlleles, i;
		Pop_list *popList, *newPopList;
		popList = newPopList = NULL;

		/* Validate all args except files */
		inputValidation(argc, argv);
		gens = atoi(argv[numGen]);
		sizePop = atoi(argv[popSize]);
		sizeAlleles = atoi(argv[alleleSize]);


		/* Initialise and build invector table */
		invector_init(&invt);
		if (!invector_buildTable(&invt, argv[inputFile])) {
			printf("Could not open %s", argv[inputFile]);
			return EXIT_FAILURE;
		}

		/* TODO: Loop to do the following for each generation */

		/* Initial popList initialisation */
		initPopList(&popList, argv[geneType], gens);

		/* Create initial population*/
		pop_populate(popList, &invt, sizeAlleles, sizePop);

		/* Print the fittest */
		pop_print_fittest(popList);

		/* Clone the fittest gene into newPopList */
		pop_init(&newPopList);
		cloneFittest(popList, newPopList);
		
		/* Normalise the fitness */
		pop_normalise(popList);

		/* TODO: Put one mutant into newPopList */

		/* TODO: Crossover parents for the rest of the population*/

		
		pop_free(popList);
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


void initPopList(Pop_list **popList, char *geneType, int gens) {
	/* Initialise popList */
	pop_init(popList);

	/* Set pop functions */
	if (isMinFn(geneType)) {
		pop_set_fns(*popList, &create_minfn_chrom, &mutate_minfn,
					&crossover_minfn, &eval_minfn);
	}else {
		pop_set_fns(*popList, &create_pcbmill_chrom, &mutate_pcbmill,
			&crossover_pcbmill, &eval_pcbmill);
	}
}


void cloneFittest(Pop_list *popList, Pop_list *newPopList) {
	Pop_node *fittest, *fittestClone;
	
	fittest = pop_getFittest(popList->head);
	fittestClone = pop_nodeCopy(popList, fittest);

	assert(newPopList->head == NULL);
	pop_insert(newPopList, fittestClone);
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
