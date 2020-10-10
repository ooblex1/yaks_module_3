/* qtest3.c --- 
 * 
 * 
 * Author: Kevin D. Larkin
 * Created: Fri Oct  9 22:36:51 2020 (-0400)
 * Version: 1
 * 
 * Description: tests queue.c: qput, qget, qapply, qsearch, qremove, qconcat for empty queues only
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "queue.h"

typedef struct pivot_t {
	struct pivot_t *next;
	void *e;
} pivot_t;

typedef struct guide_t {
	pivot_t *front;
	pivot_t *back;
} guide_t;

void print(void *p) {
	car_t *cp = (car_t *)p;
	
	if (cp != NULL) {
		printf("%s\n", cp->plate);
	} else {
		printf("FAILURE: passed argument is NULL\n");
	}
}

void yearup(void *p) {
	car_t *cp = (car_t *)p;
	
	if (cp != NULL) {
		printf("old year: %d\n", cp->year);
		cp->year = cp->year + 1;
		printf("new year: %d\n", cp->year);
	} else {
		printf("FAILURE: passed argument is NULL\n");
	}
}

bool search(void *elp, const void *keyp) {
	car_t *cp = (car_t *)elp;
	if (strcmp(cp->plate, (char *)keyp) == 0 || cp->price == *(double *)keyp || cp->year == *(int *)keyp) {
		return true;
	}
	return false;
}

int main(void) {
	bool fail = false;
	queue_t *a, *b;
	guide_t *q;
	pivot_t *qf, *qb;
	car_t *cr_1;
	int y = 2013;
	const void *yp;
	
	yp = &y;
	
	cr_1 = (car_t *)malloc(sizeof(car_t));
	strcpy(cr_1->plate, "amy");
	cr_1->price = 5000;
	cr_1->year = 2012;
	cr_1->next = NULL;
	
	//call qopen
	a = qopen();
	
	//test qapply: function was not applied to empty queue
	qapply(a, yearup);
	q = (guide_t *)a;
	if (q->front != NULL || q->back != NULL) {
		fail = true;
		printf("\nFAIL: test qapply: function was not applied to empty queue\n");
	}
	
	//test qget: successful return (NULL) for empty queue
	if (qget(a) != NULL) {
		fail = true;
		printf("\nFAIL: test qget: successful return (NULL) for empty queue\n");
	}
		
	//test qsearch: successful return (NULL) for empty queue
	if (qsearch(a, search, yp) != NULL) {
		fail = true;
		printf("\nFAIL: test qsearch: successful return (NULL) when skeyp is not in queue\n");
	}
	
	//test qremove: successful return (NULL) for empty queue
	if (qremove(a, search, yp) != NULL) {
		fail = true;
		printf("\nFAIL: test qremove: successful return (NULL) for empty queue\n");
	}
	
	//make second empty queue
	b = qopen();

	printf("\nQueue a 1:\n");
	qapply(a, print);
	printf("\nQueue b 1:\n");
	qapply(b, print);
	
	//test qconcat: does nothing when queue to be added is empty
	qconcat(a, b);
	q = (guide_t *)a;
	if (q->front != NULL || q->back != NULL) {
		fail = true;
		printf("\nFAIL: test qconcat: does nothing when queue to be added is empty\n");
	}

	printf("\nQueue a 2:\n");
	qapply(a, print);
	printf("\nQueue b 2:\n");
	qapply(b, print);
	
	//fill second queue
	qput(b, cr_1);
	
	printf("\nQueue a 3:\n");
	qapply(a, print);
	printf("\nQueue b 3:\n");
	qapply(b, print);
	
	//test qconcat: successfully adds to empty queue
	qconcat(a, b);
	q = (guide_t *)a;
	qf = q->front;
	qb = q->back;
	if ((car_t *)qf != cr_1 || (car_t *)qb != cr_1) {
		fail = true;
		printf("\nFAIL: test qconcat: successfully adds to empty queue\n");
	}

	printf("\nQueue a 4:\n");
	qapply(a, print);
	printf("\nQueue b 4:\n");
	qapply(b, print);
	
	//deallocate memory
	qclose(a);
	free(cr_1);
	
	//exit with appropriate exit status
	if (fail) {
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
