/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "pop.h"

/* Function Prototype */
Pop_node * findTopNode(Pop_node *node);

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
	Pop_node *topNode = findTopNode(p->head);
	gene_print(topNode->gene);
}


Pop_node * findTopNode(Pop_node *node) {
	Pop_node *topNode = node;

	while (node != NULL) {
		if (node->gene->fitness > topNode->gene->fitness) {
			topNode = node;
		}
		node = node->next;
	}
	return topNode;
}


void pop_normalise(Pop_list *popList) {
	Pop_node *currPop = popList->head;
	double fitSum = 0;

	/* Sum the entire population's fitness */
	while (currPop != NULL) {
		fitSum += currPop->gene->fitness;
		currPop = currPop->next;
	}

	/* Divide each pop's fitness with the sum */
	currPop = popList->head;
	while (currPop != NULL) {
		gene_normalise_fitness(currPop->gene, fitSum);
	}
}

/* TO DO - other functions as appropriate */
