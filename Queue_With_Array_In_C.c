#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#define QueueLimits 5


typedef struct Queue {
	int top;
	int rear;
	int elements[QueueLimits];	
	bool (*IsEmpty)(struct Queue *);
	bool (*IsFull)(struct Queue *);
	void (*ShowAllElements)(struct Queue *);
	void (*ReBuild)(struct Queue *);
	void (*AddQueue)(struct Queue *, int);
	int (*DeleteQueue)(struct Queue *);
};

bool IsEmpty(struct Queue* queue) {
	if(queue->top == queue->rear) {
		return true;
	} else {
		return false;
	}
}
bool IsFull(struct Queue* queue) {
	if(queue->rear - queue->top == QueueLimits) {
		return true;
	} else {
		return false;
	}
}
void ReBuild(struct Queue *queue) {
	if(queue->rear < QueueLimits) {
		return;
	}
	if(queue->IsFull(queue)) {
		return;
	} else {
		int index = 0;
		for (index; index <= queue->rear - queue->top; index++) {
			*(queue->elements + index) = *(queue->elements + queue->top + index);
		}
		queue->rear = queue->rear - queue->top;
		queue->top = 0;
	}
}
void ShowAllElements(struct Queue *queue) {
	if(queue->IsEmpty(queue)) {
		return;
	}
	int index;
	for(index = queue->top ; index < queue->rear; index++) {
		printf("|%d|\n", *(queue->elements + index));
	}
}
void AddQueue(struct Queue *queue, int InputData) {
	if(queue->IsFull(queue)) {
		return;
	} else {
		*(queue->elements + queue->rear) = InputData;
		queue->rear += 1;
		printf("in\n");
		queue->ReBuild(queue);
	}
}
int DeleteQueue(struct Queue *queue) {
	if(queue->IsEmpty(queue)) {
		return INT_MIN;
	} else {
		int OutPutData = *(queue->elements + queue->top);
		queue->top += 1;
		return OutPutData;
	}
}


struct Queue *CreateNewQueue() {
	struct Queue *newQueue = (struct Queue *) calloc (1, sizeof(struct Queue));
	newQueue->top = 0;
	newQueue->rear = 0;
	int index = 0;
	for(index; index < QueueLimits; index++) {
		*(newQueue->elements + index) = 0;
	}
	newQueue->IsEmpty = IsEmpty;
	newQueue->IsFull = IsFull;
	newQueue->ShowAllElements = ShowAllElements;
	newQueue->ReBuild = ReBuild;
	newQueue->AddQueue = AddQueue;
	newQueue->DeleteQueue = DeleteQueue;
}

int main() {
	struct Queue *queue = CreateNewQueue();
	int outputTemp = INT_MIN;
	int insertNumber = 0;
	while(true) {
		queue->ShowAllElements(queue);
		printf("1. insert a number\n");
		printf("2. pop a number\n");
		printf("pop out temp: %d (while it is int_min means error or init)\n", outputTemp);
		int option;
		
		scanf(" %d", &option);
		
		switch(option) {
			case 1:
				printf("input insert number :\n");
				scanf(" %d", &insertNumber);
				queue->AddQueue(queue, insertNumber);
				break;
			case 2:
				outputTemp = queue->DeleteQueue(queue);
				break;
		}
		system("cls");
	}	
	
}
