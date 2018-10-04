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

/* TO DO - other functions as appropriate */
