/******************************************************************************
** Student name: 	...
** Student number: 	...
** Course: 			Advanced Programming Techniques - S2 2018
******************************************************************************/

#include "invector.h"

void invector_init(InVTable *invt) {
	invt->tot = 0;
    invt->width = INVT_WIDTH;
}

Boolean invector_buildTable(InVTable *invt, char *fileName) {
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


void invector_printTable(InVTable invt) {
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
