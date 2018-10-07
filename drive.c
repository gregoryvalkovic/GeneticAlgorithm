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
void initPopList(Pop_list **popList, char *geneType);
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
		int gens, sizePop, sizeAlleles, numCrossovers, i;
		double numMutants;
		Pop_list *popList, *newPopList;

		popList = newPopList = NULL;

		/* Validate all args except files */
		inputValidation(argc, argv);
		gens = atoi(argv[numGen]);
		sizePop = atoi(argv[popSize]);
		sizeAlleles = atoi(argv[alleleSize]);

		/* 	Calc number of mutants and crossovers for populations
			-1 to numCrossovers to account for the fittest gene
			being cloned into the next generation */
		numMutants = (sizePop * MUTATE_RATE) / 100;
		numCrossovers = sizePop - numMutants - 1;

		/* Initialise and build invector table */
		invector_init(&invt);
		if (!invector_buildTable(&invt, argv[inputFile])) {
			printf("Could not open %s", argv[inputFile]);
			return EXIT_FAILURE;
		}

		/* Initial popList initialisation */
		initPopList(&popList, argv[geneType]);

		/* Create initial population*/
		pop_initialPopulate(popList, &invt, sizeAlleles, sizePop);

		/* WIP: Loop to do the following for each generation */
		for (i=0; i < gens; i++) {

			/* 	Populate next generation with mutants and crossovers
				Skip for first generation as it's already populated */
			if (i != 0) {
				
				/* Initialise the newPopList */
				initPopList(&newPopList, argv[geneType]);

				/* Clone fittest gene to new population */
				cloneFittest(popList, newPopList);

				/* Add mutants to new population */
				pop_addMutants(popList, newPopList, &invt, numMutants);

				/* Add crossovers to the new population  */
				pop_addCrossovers(popList, newPopList, &invt, numCrossovers);

				/* Free the previous generation */
				pop_free(popList);
				popList = newPopList;
				newPopList = NULL;

			}

			/* Calculate the fitness and normalise it */
			pop_calcfitness(popList, &invt);
			pop_normalise(popList);

			/* Print the fittest */
			printf("Gen:%4d ", i);
			pop_print_fittest(popList);
		}
		
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


void initPopList(Pop_list **popList, char *geneType) {
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
	
	/* Make clone of fittest node in popList */
	fittest = popList->head;
	fittestClone = pop_nodeCopy(popList, fittest);
	
	/* Insert clone into newPopList */
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
