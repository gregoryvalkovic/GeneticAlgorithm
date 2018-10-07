/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "pop.h"

/*****************************************************************************/
						/* Function Prototype */

/* Return the sum of all fitness scores in a population */
double calcTotalFitness(Pop_list *popList);

/*****************************************************************************/
						/* Provided Functions */

Boolean pop_init(Pop_list **pop){
	Pop_list *newPop = myMalloc(sizeof(Pop_list));
	newPop->head = NULL;
	newPop->count = 0;
	*pop = newPop;
	return TRUE;
}

void pop_set_fns(Pop_list *p,CreateFn cf,MutateFn mf,CrossOverFn cof,EvalFn ef){
	p->create_rand_chrom = cf;
	p->mutate_gene = mf;
	p->crossover_genes = cof;
	p->evaluate_fn = ef;
}

void pop_print_fittest(Pop_list *p){
	gene_print(p->head->gene);
}

/*****************************************************************************/
							/* My functions */

void pop_normalise(Pop_list *popList) {
	Pop_node *currPop = popList->head;
	double totalFitness = calcTotalFitness(popList);

	/* Divide each pop's fitness with the sum */
	while (currPop != NULL) {
		gene_normalise_fitness(currPop->gene, totalFitness);
		currPop = currPop->next;
	}
}


double calcTotalFitness(Pop_list *popList) {
	Pop_node *currNode = popList->head;
	double totalFitness = 0.0;

	while (currNode != NULL) {
		totalFitness += currNode->gene->fitness;
		currNode = currNode->next;
	}
	return totalFitness;
}


void pop_insert(Pop_list *popList, Pop_node *insertNode) {
	Pop_node *prevNode = NULL, *currNode = popList->head;

	/* If popList is empty insert at head */
	if (popList->head == NULL) {
		popList->head = insertNode;
		popList->count++;
		return;
	}

	/* Iterate through the popList */
	while (currNode != NULL) {

		/* Insert node */
		if (currNode->gene->fitness <= insertNode->gene->fitness) {
			insertNode->next = currNode;

			/* For inserting before the head */
			if (currNode == popList->head) {
				popList->head = insertNode;
			}else {
				prevNode->next = insertNode;
			}
			popList->count++;
			return;
		}
		/* Onto the next node */
		prevNode = currNode;
		currNode = currNode->next;
	}
	/* Insert at the end of list if reached */
	prevNode->next = insertNode;
	popList->count++;
}


Pop_node * pop_nodeInit(Pop_list *popList, int numAlleles) {
	Pop_node *node = myMalloc(sizeof(Pop_node));
	
	node->gene = gene_init(numAlleles);

	/* Free the chrom that gene_init sets, replace with rand_chrom */
	free(node->gene->chromosome);
	node->gene->chromosome = popList->create_rand_chrom(numAlleles);
	node->next = NULL;
	return node;
}


void pop_initialPopulate(Pop_list *popList, InVTable *invt, int numAlleles,
				  int popSize) {
	Pop_node *newNode;
	int i;

	/* Populate with appropriate number of new nodes */
	for (i=0; i < popSize; i++) {
		/* Initialise new node  */
		newNode = pop_nodeInit(popList, numAlleles);

		gene_calc_fitness(newNode->gene, popList->evaluate_fn, invt);
		pop_insert(popList, newNode);
	}
}


void pop_free(Pop_list *popList) {
	Pop_node *currNode = popList->head;
	Pop_node *prevNode = NULL;

	/* Free each node one by one */
	while (currNode != NULL) {
		prevNode = currNode;
		currNode = currNode->next;
		pop_nodeFree(prevNode);
	}
	free(popList);
}


void pop_nodeFree(Pop_node *node) {
	gene_free(node->gene);
	free(node);
}


Pop_node * pop_nodeCopy(Pop_list *popList, Pop_node *node) {
	Pop_node *copyNode = NULL;
	
	/* 	Initialise the new node and copy the gene */
	copyNode = pop_nodeInit(popList, node->gene->num_alleles);
	gene_copy(node->gene, copyNode->gene);

	return copyNode;
}

Pop_node * pop_rouletteSelect(Pop_list *popList) {
	Pop_node *currNode = popList->head;
	double fitSum = 0.0, threshold;

	assert(popList->head != NULL);

	/* Random value from 0.1 to 1 */
	threshold = rand() % 10 + 1 ;
	threshold = 1 / threshold;

	/* Iterate through the whole population */
	while (TRUE) {
		
		/* Select node where threshold is reached/broken or last node */
		fitSum += currNode->gene->fitness;
		if (fitSum >= threshold || currNode->next == NULL) {
			break;
		}
		/* On to the next node */
		currNode = currNode->next; 
	}
	return currNode;
}

void pop_calcfitness(Pop_list *p, InVTable *invt) {
	Pop_node *currNode = p->head;
	
	/* Loop through each node and calculate the fitness */
	while (currNode != NULL) {
		gene_calc_fitness(currNode->gene, p->evaluate_fn, invt);

		/* On to the next node */
		currNode = currNode->next;
	}
}


void pop_addMutants(Pop_list *pop, Pop_list *newPop, InVTable *invt, int numMutants) {
	Pop_node *parentNode, *mutantNode;
	int i;

	/* Loop for the number of mutants that must be created */
	for (i=0; i < numMutants; i++) {	

		/* Select a parentNode to mutate from, and mutate it */
		parentNode = pop_rouletteSelect(pop);
		mutantNode = pop_mutateNode(pop, parentNode);

		/* Calculate the fitness and raw_score of the mutant node */
		gene_calc_fitness(mutantNode->gene, pop->evaluate_fn, invt);
		
		/* Insert the node into the new population list */
		pop_insert(newPop, mutantNode);
	}
}


Pop_node * pop_mutateNode(Pop_list *popList, Pop_node *parentNode) {
	
	/* Initialise the mutantNode */
	Pop_node *mutantNode = myMalloc(sizeof(Pop_node));
	mutantNode->next = NULL;

	/* Mutate the parent node */
	mutantNode->gene = popList->mutate_gene(parentNode->gene);
	return mutantNode;
}