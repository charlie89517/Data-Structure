#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#define MAX 500
//HEAP CREATE O(nlogn)
//HEAP PUSH O(logn)
//HEAP POP O(logn)
//HEAP FIND A NUMBER O(n)
//HEAP FIND MIN/MAX NUMBER O(1)

typedef struct MinHeapQueue {
	
	int nums;
	int heap[MAX];
	bool (*IsEmpty)(struct MinHeapQueue *);
	bool (*IsFull)(struct MinHeapQueue *);
	int (*Top)(struct MinHeapQueue *);
	int (*Pop)(struct MinHeapQueue *);
	void (*Push)(struct MinHeapQueue *, int);
	void (*Swap)(struct MinHeapQueue *, int, int);
	void (*PrintHeap)(struct MinHeapQueue *);
	int (*GetHeapQueueData)(struct MinHeapQueue *, int);
};

bool IsEmpty(struct MinHeapQueue *queue) {
	if(*(queue->heap + 1) == INT_MAX) {
		return true;
	} else {
		return false;
	}
}

bool IsFull(struct MinHeapQueue *queue) {
	if(queue->nums >= MAX) {
		return true;
	} else {
		return false;
	}
}

int Top(struct MinHeapQueue *queue) {
	return (*queue->heap + 1);
}

void Swap(struct MinHeapQueue *queue, int changeIndex, int changeOtherIndex) {
	int temp = *(queue->heap + changeIndex);
	*(queue->heap + changeIndex) = *(queue->heap + changeOtherIndex);
	*(queue->heap + changeOtherIndex) = temp;
}

int Pop(struct MinHeapQueue *queue) {
	if(queue->IsEmpty(queue)) {
		return INT_MAX;	
	}
	queue->Swap(queue, 1, queue->nums);
	int output = *(queue->heap + queue->nums);
	*(queue->heap + queue->nums) = INT_MAX;
	queue->nums--;
	int parentTemp = 1;
	while(parentTemp * 2 < queue->nums) {
		
		if((queue->GetHeapQueueData(queue, parentTemp * 2) != INT_MAX && \
				queue->GetHeapQueueData(queue, parentTemp * 2 + 1) != INT_MAX) && (\
				queue->GetHeapQueueData(queue, parentTemp * 2) < queue->GetHeapQueueData(queue, parentTemp * 2 + 1))) {
			if(queue->GetHeapQueueData(queue, parentTemp * 2) < queue->GetHeapQueueData(queue, parentTemp)) {
				queue->Swap(queue, parentTemp, parentTemp * 2);
				parentTemp *= 2;
			} else {
				break;
			}
		} else if(queue->GetHeapQueueData(queue, parentTemp * 2) != INT_MAX && \
				queue->GetHeapQueueData(queue, parentTemp * 2 + 1) != INT_MAX && \
				queue->GetHeapQueueData(queue, parentTemp * 2) > queue->GetHeapQueueData(queue, parentTemp * 2 + 1)) {
			if(queue->GetHeapQueueData(queue, parentTemp * 2 + 1) < queue->GetHeapQueueData(queue, parentTemp)) {
				queue->Swap(queue, parentTemp, parentTemp * 2 + 1);
				parentTemp *= 2;
				parentTemp++;
			} else {
				break;
			}
		}
	}
	
	return output;
}

void Push(struct MinHeapQueue *queue, int pushNumber) {
	if(queue->IsFull(queue)) {
		return;
	}
	//
	*(queue->heap + (++(queue->nums))) = pushNumber;
	int currentTemp = queue->nums;
	while(currentTemp != 1) {
		if(*(queue->heap + currentTemp / 2) > *(queue->heap + currentTemp)) {
			queue->Swap(queue, currentTemp, currentTemp / 2);
		}
		currentTemp /= 2;
	}
}

void PrintHeap(struct MinHeapQueue *queue) {
	if(queue->IsEmpty(queue)) {
		return;
	}
	int index = 1;
	printf("index max = %d\n", queue->nums); 
	for(index; index <= queue->nums; index++) {
		printf("%d ", *(queue->heap + index));
		if(((index + 1) & index) == 0) {
			printf("\n");
		}
	}
	printf("\n");
}

int GetHeapQueueData(struct MinHeapQueue *queue, int index) {
	if(queue->nums < index) {
		return INT_MAX;
	} else {
		return *(queue->heap + index);
	}
}

struct MinHeapQueue *MinHeapQueueCreater() {
	struct MinHeapQueue *newQueue = (struct MinHeapQueue *)calloc(1, sizeof(struct MinHeapQueue));
	newQueue->nums = 0;
	//memset(newQueue->heap, INT_MIN, MAX * sizeof(int));
	int index = 0;
	for(index; index < MAX; index++) {
		*(newQueue->heap + index) = INT_MAX;
	}
	
	newQueue->IsEmpty = IsEmpty;
	newQueue->IsFull = IsFull;
	newQueue->Pop = Pop;
	newQueue->Push = Push;
	newQueue->Swap = Swap;
	newQueue->Top = Top;
	newQueue->PrintHeap = PrintHeap;
	newQueue->GetHeapQueueData = GetHeapQueueData;
	return newQueue;
}

int main() {
	struct MinHeapQueue *queue = MinHeapQueueCreater();
	int option;
	int inputNumber;
	int topNumber = INT_MIN;
	while(true) {
		queue->PrintHeap(queue);
		printf("1. push\n");
		printf("2. top\n");
		printf("3. pop\n");
		scanf(" %d", &option);
		switch(option) {
			case 1:
				printf("input a number:");
				scanf(" %d", &inputNumber);
				queue->Push(queue, inputNumber);
				break;
			case 2:
				printf("top number is :%d\n", queue->Top(queue));
				break;
			case 3:
				printf("pop number %d\n", queue->Pop(queue));
				break;			
		}
	}
}
