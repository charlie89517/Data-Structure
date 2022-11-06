#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

#define stackLimits 5

typedef struct Stack {
	int top;
	int numbers[stackLimits];
	bool (*IsFull)(struct Stack *);
	bool (*IsEmpty)(struct Stack *);
	void (*Push)(struct Stack *, int);
	void (*ShowAllElement)(struct Stack*);
	int (*Pop)(struct Stack *);
};

bool IsFull(struct Stack *stack) {
	if (stack->top == stackLimits) {
		return true;
	}
	return false;
}
bool IsEmpty(struct Stack *stack) {
	if(stack->top == 0) {
		return true;
	}
	return false;
}
void Push(struct Stack *stack, int pushNumber) {
	if(stack->IsFull(stack)) {
		printf("error stack is full!");
	} else {
		*(stack->numbers + stack->top) = pushNumber;
		stack->top += 1;
	}
}
int Pop(struct Stack *stack) {
	if(stack->IsEmpty(stack)) {
		return INT_MIN;
	} else {
		printf("out\n");
		int popNumber;
		stack->top -= 1;
		popNumber = *(stack->numbers + stack->top);
		return popNumber;
	}
}
void ShowAllElement(struct Stack *stack) {
	if(stack->IsEmpty(stack)) {
		return;
	} else {
		int index = stack->top;
		printf("top = %d\n", stack->top);
		for(index -= 1; index >= 0; index--) {
			printf("|%d|\n", *(stack->numbers + index));
		}
	}
	
}

struct Stack* CreateNewStack() {
	struct Stack *newStack = (struct Stack*)calloc(1, sizeof(struct Stack));
	newStack->top = 0;
	int index = 0;
	for(index; index < stackLimits; index++) {
		*(newStack->numbers + index) = 0;
	}
	newStack->IsFull = IsFull;
	newStack->IsEmpty = IsEmpty;
	newStack->ShowAllElement = ShowAllElement;
	newStack->Push = Push;
	newStack->Pop = Pop;
	return newStack;
}



int main() {
	struct Stack *stack = CreateNewStack();
	int OutPutData = INT_MIN;
	while(true) {
		stack->ShowAllElement(stack);
		printf("1. push a number\n");
		printf("2. pop a number\n");
		printf("pop out temp: %d (while it is int_min means error or init)\n", OutPutData);
		int option;
		int pushNumber = 0;
		scanf(" %d", &option);
		
		switch(option) {
			case 1:
				printf("input push number :\n");
				scanf(" %d", &pushNumber);
				stack->Push(stack, pushNumber);
				break;
			case 2:
				OutPutData = stack->Pop(stack);
				break;
		}
		system("cls");
	}
	
	
	

}


