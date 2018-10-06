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

/* Return the fittest node in the population (the last node) */
Pop_node * getFittest (Pop_node *head);

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
	Pop_node *topNode = getFittest(p->head);
	gene_print(topNode->gene);
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


Pop_node * getFittest (Pop_node *head) {
	Pop_node *currNode = head;
	while (currNode->next != NULL) {
		currNode = currNode->next;
	}
	return currNode;
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
		if (currNode->gene->fitness >= insertNode->gene->fitness) {
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
	node->gene->chromosome = popList->create_rand_chrom(numAlleles);
	node->next = NULL;
	return node;
}


void pop_populate(Pop_list *popList, InVTable *invt, int numAlleles,
				  int popSize) {
	Pop_node *newNode;
	int i;

	/* Populate with appropriate number of new nodes */
	for (i=0; i < popSize; i++) {
		/* Initialise new node and create the random chromosome */
		newNode = pop_nodeInit(popList, numAlleles);
		popList->create_rand_chrom(newNode->gene->chromosome, numAlleles);

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
