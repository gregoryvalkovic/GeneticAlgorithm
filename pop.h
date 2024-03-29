/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#ifndef POP_H
#define POP_H

#include "gene.h"
#include "invector.h"

#define MUTATE_RATE 5

typedef struct pop_node {
	Gene *gene;
	struct pop_node *next;
} Pop_node;

typedef struct pop_list {
	/* the head of the population list */
	Pop_node *head;
	/* the size of the population */
	int count;
	/* pointers to functions to perform
 	 * gene chromosome creation, mutation,
 	 * crossover and evaluation */
	CreateFn create_rand_chrom;
	MutateFn mutate_gene;
	CrossOverFn crossover_genes;
	EvalFn evaluate_fn;
} Pop_list;

/* Create and initialise the population list to a safe state.
 * Returns TRUE on success */
Boolean pop_init(Pop_list **);

/* Set the function pointers of a population list */
void pop_set_fns(Pop_list *p,CreateFn cf,MutateFn mf,CrossOverFn cof,EvalFn ef);

/* This function causes details of the fittest gene of the generation to
 * be printed out.
 * The function also prints out the number of the current generation.
 * This function must not be able to access any generation value outside
 * of the function. */
void pop_print_fittest(Pop_list *p);

/* TO DO - other functions as appropriate */
/* Initialises the poplist and all pops. Also sets fns for all pops */
void pop_initList(Pop_list *popList[], char *geneType, int gens);

/* Normalises a population's fitness score */
void pop_normalise(Pop_list *popList);

/* Initialise a new Pop_node and its gene */
Pop_node * pop_nodeInit(Pop_list *popList, int numAlleles);

/*	Creates new Pop_nodes from the genes in the InVTable and calculates the
	fitness for each population. Note the popList passed must be initialised
	already with appropriate values */
void pop_firstGen(Pop_list *popList, InVTable *invt, int numAlleles, int popSize);

/* Frees the gene, then the node */
void pop_nodeFree(Pop_node *node);

/* Free an entire popList */
void pop_free(Pop_list *popList);

/* 	Returns a pointer to a copy of a given node. Pointer to next node
	will be null however. */
Pop_node * pop_nodeCopy(Pop_list *popList, Pop_node *node);

/* Inserts a node, sorted by its fitness */
void pop_insert(Pop_list *popList, Pop_node *insertNode);

/* Roulette wheel selection of a node from popList */
Pop_node * pop_rouletteSelect(Pop_list *popList);

/* Sets the fitness and rawscore for every gene in a list */
void pop_calcfitness(Pop_list *p, InVTable *invt);

/* Generates mutants from the previous generation and inserts them into the new population */
void pop_addMutants(Pop_list *pop, Pop_list *newPop, InVTable *invt, int numMutants);

/* Create a mutant node of a given node */
Pop_node * pop_mutateNode(Pop_list *popList, Pop_node *parentNode);

/* Create crossover nodes from previous gen and insert into next gen */
void pop_addCrossovers(Pop_list *pop, Pop_list *newPop, InVTable *invt, int numCrossovers);

/* Create a crossover node from two given parent nodes */
Pop_node * pop_crossover(Pop_list *newPop, InVTable *invt, Pop_node *p1, Pop_node *p2);
#endif
