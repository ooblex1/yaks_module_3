/* 
 * queue.c -- implements a generic queue.
 *
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <queue.h>

typedef struct pivot_t {
	struct pivot_t *next;
	void *e;
} pivot_t;

typedef struct guide_t {
	pivot_t *front;
	pivot_t *back;
} guide_t;

queue_t* qopen(void) {
	guide_t *q;
	
	q = (guide_t *)malloc(sizeof(guide_t));
	if (q == NULL) {
		printf("memory allocation failed");
		return 1;
	}
	
	return (queue_t *)q;
}

void qclose(queue_t *qp) {
	pivot_t *fp = NULL, *ip;
	guide_t *gp = (guide_t *)qp;
	
	for (ip = gp->front; ip != NULL; ip = ip->next) {
		free(fp);
		fp = ip;
	}
	
	free(qp);
	free(ip);
	free(gp);
}

int32_t qput(queue_t *qp, void *ep) {
	guide_t *q = (guide_t *)qp;
	pivot_t *p;
	
	p = (pivot_t *)malloc(sizeof(pivot_t));
	if (p == NULL) {
		printf("memory allocation failed");
		return 1;
	}

	p->e = ep;
	
	if (q->front == NULL) {
		q->front = p;
	} else {
		q->back->next = p;
	}
	q->back = p;
	
	if (q->back == p) {
		return 0;
	} else {
		return 1;
	}
}

void* qget(queue_t *qp) {
	guide_t *q = (guide_t *)qp;
	
	if (q->front == NULL) {
		printf("Queue is empty, cannot apply qget.\n");
		return NULL;
	}
	
	void *temp = q->front->e;
	if (q->front == q->back) {
		q->front = NULL;
		q->back = NULL;
	} else {
		q->front = q->front->next;
	}
	
	return temp;
}

void qapply(queue_t *qp, void (*fn)(void *ep)) {
	if (fn == NULL) {
		printf("Error: Invalid function.\n");
	}
	
	if (front == NULL || back == NULL) {
		printf("Queue is empty, cannot apply function.\n");
	} else {
		guide_t *q = (guide_t *)qp;
		pivot_t *p;
		
		printf("\n********\nApplying function to every element in queue...\n");
		
		for (p = q->front; p != NULL; p = p->next) {
			fn(p->e);
		}
		
		printf("...done.\n********\n");
	}
}

void* qsearch(queue_t *qp, bool (*searchfn)(void *ep, const void *keyp),
							const void *skeyp) {
	guide_t *q = (guide_t *)qp;
	pivot_t *p;
	
	if (q->front == NULL || q->back == NULL) {
		printf("Queue is empty.\n");
		return NULL;
	}
	
	for (p = p->front; p != NULL; p = p->next) {
		if (searchfn(p->e, skeyp)) {
			return p->e;
		}
	}

	printf("Element not found in queue.\n");
	return NULL;
}

void* qremove(queue_t *qp,
							bool (*searchfn)(void *ep, const void *keyp),
							const void *skeyp) {
	guide_t *q = (guide_t *)qp;
	pivot_t *p;
	void *temp;
	
	if (q->front == NULL || q->back == NULL) {
		printf("Queue is empty.\n");
		return NULL;
	}
	
	if (q->front == q->back) {
		if (searchfn(q->front->e, skeyp)) {
			temp = q->front->e;
			q->front = NULL;
			q->back = NULL;
			return temp;
		}
	} else {
		for (p = q->front; p->next != NULL; p = p->next) {
			if (p == q->front && searchfn(p->e, skeyp)) {
				q->front = q->front->next;
				return p->e;
			}
			
			if (searchfn(p->next->e, skeyp)) {
				temp = p->next->e;

				if (p->next == q->back) {
					p->next = NULL;
					q->back = p;
				} else {
					p->next = p->next->next;
				}

				return temp;
			}
		}
	}

	printf("Element not found in queue.\n");
	return NULL;
}

void qconcat(queue_t *qp1, queue_t *qp2) {
	guide_t *q1 = (guide_t *)qp1, *q2 = (guide_t *)qp2;

	if (q2->front == NULL || q2->back == NULL) {
		printf("Queue to be added is empty.\n");
	} else {
		if (q1->front == NULL) {
			q1->front = q2->front;
		} else {
			q1->back->next = q2->front;
		}
		q1->back = q2->back;
		
		free(q2);
	}
}
