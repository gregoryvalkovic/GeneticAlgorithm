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

/************************************************************************/
							/* My functions */

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


void pop_insert(Pop_list *popList, Pop_node *insertNode) {
	Pop_node *prevNode = NULL, *currNode = popList->head;

	/* If popList is empty insert at head */
	if (popList->head == NULL) {
		popList->head = currNode;
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
			return;
		}
		/* Onto the next node */
		prevNode = currNode;
		currNode = currNode->next;
	}
	/* Insert at the end of list if reached */
	prevNode->next = insertNode;
}


Pop_node * pop_nodeInit(int alleles) {
	Pop_node *node = myMalloc(sizeof(Pop_node)) ;
	node->gene = gene_init(alleles);
	node->next = NULL;
	return node;
}
