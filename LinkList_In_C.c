#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>


struct LinkNode{
	int data;
	struct LinkNode *nextNode;
	
	void (*SetDataInToANode)(struct LinkNode *, int );
};

struct Stack{
	struct LinkNode *topNode;
	
	void (*Initialize)(struct Stack*);
	void (*PushData)(struct Stack*, struct LinkNode*);
};

struct LinkList{
	struct LinkNode *topNode;

	void (*PrintAllData)(struct LinkList *);
	void (*AddData)(struct LinkList *,int );
	int (*PopData)(struct LinkList *);
	struct LinkNode *(*PopANode)(struct LinkList *self);
	bool (*InsertDataByValue)(struct LinkList *, int , int );
	struct LinkNode *(*SearchANodeByData)(struct LinkList *, int );
	void (*Reverse)(struct LinkList *, struct Stack *);
};

void Initialize(struct Stack *stack) {
	stack->topNode = NULL;
}

void SetDataInToANode(struct LinkNode *self, int inputData){
	self->data = inputData;
}
struct LinkNode *CreateALinkNode(int data){
	struct LinkNode *newNode = (struct LinkNode *)calloc(1, sizeof(struct LinkNode));
	newNode->nextNode = NULL;
	newNode->SetDataInToANode = SetDataInToANode;
	
	newNode->SetDataInToANode(newNode, data);
	return newNode;
}

void PrintAllData(struct LinkList *self){
	struct LinkNode *temp = self->topNode;
	while(temp != NULL) {
		printf("%d", temp->data);
		if(temp->nextNode != NULL) {
			printf("->");
			temp = temp->nextNode;
		} else {
			break;
		}
	}
	printf("\n");
}

void AddData(struct LinkList *self,int data) {
	if(self->topNode == NULL) {
		struct LinkNode *newNode = CreateALinkNode(data);
		self->topNode = newNode;
	} else {
		struct LinkNode *temp = self->topNode;
		while(temp->nextNode != NULL) {
			temp = temp->nextNode;
		}
		struct LinkNode *newNode = CreateALinkNode(data);
		temp->nextNode = newNode;
	}
}

bool InsertDataByValue(struct LinkList *self, int inputData, int searchData) {
	struct LinkNode *temp = self->SearchANodeByData(self, searchData);
	if(temp != NULL) {
		struct LinkNode *newNode = CreateALinkNode(inputData);
		newNode->nextNode = temp->nextNode;
		temp->nextNode = newNode;
		return true;
	} else {
		return false;
	}
}

struct LinkNode *SearchANodeByData(struct LinkList *self, int searchData) {
	struct LinkNode *temp = self->topNode;
	while(temp != NULL && temp->data != searchData) {
		temp = temp->nextNode;
	}
	return temp;
}

int PopData(struct LinkList *self) {
	if(self->topNode !=  NULL) {
		int outputData = self->topNode->data;
		self->topNode = self->topNode->nextNode;
		return outputData;
	}
	return INT_MIN;
}

void Reverse(struct LinkList *self, struct Stack *stack) {
	while(self->topNode != NULL) {
		stack->PushData(stack, self->PopANode(self));
	}
	self->topNode = stack->topNode;
}

void PushData(struct Stack *stack,struct LinkNode *inputData) {
	inputData->nextNode = stack->topNode;
	stack->topNode = inputData;
	
}

struct LinkNode *PopANode(struct LinkList *self) {
	struct LinkNode *OutPutNode = self->topNode;
	
	self->topNode = self->topNode->nextNode;
	OutPutNode->nextNode = NULL;
	return OutPutNode;
}

struct LinkList *CreateANewList() {
	struct LinkList *newLinkList = (struct LinkList *)calloc(1, sizeof(struct LinkList));
	newLinkList->topNode = NULL;
	
	newLinkList->AddData = AddData;
	newLinkList->PopData = PopData;
	newLinkList->PopANode = PopANode;
	newLinkList->PrintAllData = PrintAllData;
	newLinkList->SearchANodeByData = SearchANodeByData;
	newLinkList->InsertDataByValue = InsertDataByValue; 
	newLinkList->Reverse = Reverse;
	return newLinkList;
}

struct Stack *CreateANewStack() {
	struct Stack *newStack = (struct Stack *)calloc(1, sizeof(struct Stack));
	newStack->topNode = NULL;
	
	newStack->PushData = PushData;
	newStack->Initialize = Initialize;
	return newStack;
}

int main() {
	struct LinkList *list = CreateANewList();
	
	int input;
	int OutPutData = INT_MIN;
	int searchNumber;
	bool AddSuccess = false;
	struct Stack *stack = CreateANewStack();
	while(1) {
		int InputData;
		stack->Initialize(stack);
		printf("pop out temp: %d (while it is int_min means error or init)\n", OutPutData);
		printf("Data :");
		list->PrintAllData(list);
		printf("1. add data in to a link list\n");
		printf("2. pop a data in a link list\n");
		printf("3. Insert a value after the set value\n");
		printf("4. reverse list\n");
		if(!AddSuccess) {
			printf("search error!\n");
		}
		printf("input option :");
		scanf(" %d", &input);
		switch(input){
			case 1:
				printf("input data :");
				scanf(" %d", &InputData);
				list->AddData(list, InputData);
				break;
			case 2:
				OutPutData = list->PopData(list);	
				break;
			case 3:
				printf("search number :");
				scanf(" %d", &searchNumber);
				printf("input data :");
				scanf(" %d", &InputData);
				AddSuccess = list->InsertDataByValue(list, InputData, searchNumber);
				break;
			case 4:
				list->Reverse(list, stack);
				break;
		}
		system("cls");
	}
}


