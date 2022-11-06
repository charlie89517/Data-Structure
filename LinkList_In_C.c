#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct LinkNode{
	int data;
	struct LinkNode *nextNode;	
	
};

struct LinkList{
	struct LinkNode *topNode;
	
};


void SetDataInToANode(struct LinkNode *self, int inputData){
	self->data = inputData;
	self->nextNode = NULL;
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
		struct LinkNode *newNode = (struct LinkNode *)calloc(1, sizeof(struct LinkNode));
		SetDataInToANode(newNode, data);
		self->topNode = newNode;
	} else {
		struct LinkNode *temp = self->topNode;
		while(temp->nextNode != NULL) {
			temp = temp->nextNode;
		}
		struct LinkNode *newNode = (struct LinkNode *)calloc(1, sizeof(struct LinkNode));
		SetDataInToANode(newNode, data);
		temp->nextNode = newNode;
	}
}

int PopData(struct LinkList *self) {
	if(self->topNode !=  NULL) {
		int outputData = self->topNode->data;
		self->topNode = self->topNode->nextNode;
		return outputData;
	}
	return INT_MIN;
}

int main() {
	struct LinkList *list =(struct LinkList*) calloc(1, sizeof(struct LinkList));
	list->topNode = NULL;
	int input;
	int OutPutData = INT_MIN;
	while(1) {
		int InputData;
		printf("pop out temp: %d (while it is int_min means error or init)\n", OutPutData);
		printf("Data :");
		PrintAllData(list);
		printf("1. add data in to a link list\n");
		printf("2. pop a data in a link list\n");
		printf("input option :");
		scanf(" %d", &input);
		switch(input){
			case 1:
				printf("input data :");
				scanf(" %d", &InputData);
				AddData(list, InputData);
				break;
			case 2:
				OutPutData = PopData(list);	
				break;	
		}
		system("cls");
	}
}


