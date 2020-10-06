/*
 * queue.c -- implements a generic queue.
 *
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "queue.h"
static queue_t *front = NULL;
static queue_t *back = NULL;

queue_t* qopen(void) {
  queue_t *qp;

  qp = (queue_t*)malloc(sizeof(queue_t*));
  if (qp == NULL) {
    printf("memory allocation failed");
  }

  return (queue_t *)qp;
}

void qclose(queue_t *qp) {
  queue_t *ep;

  for (ep = qp; ep != NULL; ep = ep->next) {
    free(ep);
  }

  free(front);
  free(back);
}

int32_t qput(queue_t *qp, void *ep) {
  if (qp == NULL) {
    front = ep;
    back = ep;
  } else {
    back->next = ep;
    back = ep;
  }

  if (back == ep) {
    return 0;
  } else {
    return 1;
  }
}

void* qget(queue_t *qp) {
  if (front == NULL) {
    printf("Queue is empty, cannot apply qget.\n");
    return NULL;
  }

  queue_t *temp = front;
  front = front->next;

  return temp;
}

void qapply(queue_t *qp, void (*fn)(void* ep)) {
  if (fn == NULL) {
    printf("Error: Invalid function.\n");
  }

  if (front == NULL || back == NULL) {
    printf("Queue is empty, cannot apply function.\n");
  } else {
    queue_t *p;

    printf("\n********\nApplying function to every element in queue.\n");

    for (p = front; p != NULL; p = p->next) {
      fn(p);
    }

    printf("\n********\n");
  }
}

void* qsearch(queue_t *qp, bool (*searchfn)(void* ep, const void* keyp),
              const void* skeyp) {
  queue_t *p;

  if (front == NULL || back == NULL) {
    printf("Queue is empty.\n");
    return NULL;
  }

  for (p = front; p != NULL; p = p->next) {
    if (searchfn(p, skeyp)) {
      return p;
    }
  }

  printf("Element not found in queue.\n");
  return NULL;
}

void* qremove(queue_t *qp,
              bool (*searchfn)(void* ep, const void* keyp),
              const void* skeyp) {
  queue_t *p, *temp;

  if (front == NULL || back == NULL) {
    printf("Queue is empty.\n");
    return NULL;
  }

  if (front == back) {
    if (searchfn(front, skeyp)) {
      temp = front;
      front = NULL;
      back = NULL;
      return temp;
    }
  } else {
    for (p = front; p->next != NULL; p = p->next) {
      if (p == front) {
        if (searchfn(p, skeyp)) {
          front = p->next;
          return p;
        }
      }

      if (searchfn(p->next, skeyp)) {
        temp = p->next;

        if (p->next == back) {
          p->next = NULL;
          back = p;
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

void qconcat(queue_t *q1p, queue_t *q2p) {
  if (q1p == NULL) {
    q1p = q2p;
    qclose(q2p);
  } else {

  }
}

