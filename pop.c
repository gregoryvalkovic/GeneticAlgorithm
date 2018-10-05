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


void pop_initList(Pop_list *popList[], char *geneType, int gens) {
	Pop_list *currPop;
	int i;

	/* Initialise popList */
	popList = myMalloc(sizeof(Pop_list *) * gens);

	for (i=0; i < gens; i++) {
		currPop = popList[i];
		pop_init(&currPop);

		/* Set pop functions */
		if (isMinFn(geneType)) {
			pop_set_fns(currPop + i, create_minfn_chrom, mutate_minfn,
						crossover_minfn, eval_minfn);
		}
		pop_set_fns(currPop + i, create_pcbmill_chrom, mutate_pcbmill,
					crossover_pcbmill, eval_pcbmill);
	}
}


void pop_normalise(Pop_list *popList) {
	Pop_node currPop = popList->head;
	double fitSum = 0;

	/* Sum the entire population's fitness */
	while (currPop != NULL) {
		fitSum += currPop->gene->fitness;
		currPop = currPop->next;
	}

	/* Divide each pop's fitness with the sum */
	currPop = popList->head;
	while (currPop != NULL) {
		currPop->gene->fitness = currPop->gene->fitness / fitSum;
		currPop = currPop->next;
	}
}

/* TO DO - other functions as appropriate */
