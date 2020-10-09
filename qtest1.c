/* qtest1.c --- 
 * 
 * 
 * Author: Kevin D. Larkin
 * Created: Fri Oct  9 13:33:51 2020 (-0400)
 * Version: 1
 * 
 * Description: tests queue.c: qopen()
 * 
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "queue.h"

typedef struct

int main(void) {
	bool fail = false;
	int32_t pr;
	queue_t *a;
	car_t *cr_1, *cr_a;
	cr_1 = (car_t *)malloc(sizeof(car_t));
	cr_a = (car_t *)malloc(sizeof(car_t));
	
	//call qopen
	a = qopen();
	if (int(a) == 1) {
		fail = true;
	}
	
	strcpy(cr_1->plate, "max");
	cr_1->price = 5000;
	cr_1->year = 2012;
	cr_1->next = NULL;
	
	pr = qput(a, (void *)cr_1);
	if (pr != 0) {
		fail = true;
	}
	
	cr_a = (car_t *)qget();

	//Does qget remove the entry when it is the only entry in the queue?
	if ((car_t *)qget() != NULL) {
		fail = true;
	}
	
	qclose(a);

	if (fail) {
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
