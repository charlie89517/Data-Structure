#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
//CREATE BINARY TREE average O(nlogn)
//CREATE BINARY TREE worst O(n^2) (skew tree)
//SEARCH BINARY TREE average O(logn)
//SEARCH BINARY TREE worst O(n)


typedef struct Node {
	int data;
	struct Node *parentNode;
	struct Node *leftNode;
	struct Node *rightNode;
};

typedef struct BinarySearchTree {
	struct Node *topNode;
	
	bool (*IsEmpty)(struct BinarySearchTree *);
	struct Node *(*Search)(struct Node *, int);
	struct Node *(*Delete)(struct BinarySearchTree *, int, struct Node *);
	void (*Insert)(struct BinarySearchTree *, int);
	void (*Swap)(struct Node *, struct Node *);
	void (*PrintInorder)(struct BinarySearchTree *, struct Node *);

};

struct Node *NodeCreater(int data) {
	struct Node *newNode = (struct Node *)calloc(1, sizeof(struct Node));
	newNode->data = data;
	newNode->leftNode = NULL;
	newNode->rightNode = NULL;
	newNode->parentNode = NULL;
	
	return newNode;
}

bool IsEmpty(struct BinarySearchTree *BST){
	if(BST->topNode->leftNode == NULL) {
		return true;
	} else {
		return false;
	}
}

struct Node *Search(struct Node *currentNode, int searchTarget) {
	if(currentNode == NULL) {
		return NULL;
	}
	if(currentNode->data == searchTarget) {
		return currentNode;
	}
	if(currentNode->data > searchTarget) {
		return Search(currentNode->leftNode, searchTarget);
	} else if(currentNode->data < searchTarget) {
		return Search(currentNode->rightNode, searchTarget);
	}
}

void Swap(struct Node *source, struct Node *target) {
	int temp = source->data;
	source->data = target->data;
	target->data = temp; 
}

struct Node *Delete(struct BinarySearchTree *BST, int deleteTarget, struct Node *searchNode) {
	
	if(BST->IsEmpty(BST)) {
		return NULL;
	}
	if(BST->topNode->data == deleteTarget && (BST->topNode->rightNode == NULL && BST->topNode->leftNode == NULL)) {
		struct Node *temp = BST->topNode;
		BST->topNode = NULL;
		return temp;
	}
	
	if(searchNode != NULL) {
		if(searchNode->rightNode == NULL && searchNode->leftNode == NULL) {
			if(searchNode->parentNode->leftNode == searchNode) {
				searchNode->parentNode->leftNode = NULL;
			} else if(searchNode->parentNode->rightNode == searchNode) {
				searchNode->parentNode->rightNode = NULL;
			}
		}
		if(searchNode->leftNode != NULL && searchNode->rightNode == NULL) {
			if(searchNode->parentNode->leftNode == searchNode) {
				searchNode->parentNode->leftNode = searchNode->leftNode;
			} else if(searchNode->parentNode->rightNode == searchNode) {
				searchNode->parentNode->rightNode = searchNode->leftNode;
			}
		}
		if(searchNode->leftNode == NULL && searchNode->rightNode != NULL) {
			if(searchNode->parentNode->leftNode == searchNode) {
				searchNode->parentNode->leftNode = searchNode->rightNode;
			} else if(searchNode->parentNode->rightNode == searchNode) {
				searchNode->parentNode->rightNode = searchNode->rightNode;
			}
		} 
		if(searchNode->leftNode != NULL && searchNode->rightNode != NULL) {
			struct Node *temp = searchNode->rightNode;
			while(temp->leftNode != NULL) {
				temp = temp->leftNode;
			}
			BST->Swap(searchNode, temp);
			BST->PrintInorder(BST, BST->topNode->leftNode);
			return BST->Delete(BST, deleteTarget, temp);
		} 
	}
	return searchNode;
}
//insert 
void Insert(struct BinarySearchTree *BST, int insertData) {
	struct Node *newNode = NodeCreater(insertData);
	if(BST->IsEmpty(BST)) {
		BST->topNode->leftNode = newNode;
		BST->topNode->parentNode = BST->topNode;
		return;
	}
	struct Node *temp = BST->topNode->leftNode;
	while(temp->data != insertData) {
		if(temp->data == insertData) {
			break;
		}
		if(temp->data > insertData && temp->leftNode == NULL) {
			temp->leftNode = newNode;
			newNode->parentNode = temp;
			break;
		} else if (temp->data > insertData && temp->leftNode != NULL) {
			temp = temp->leftNode;
		}
		
		if(temp->data < insertData && temp->rightNode == NULL) {
			temp->rightNode = newNode;
			newNode->parentNode = temp;
			break;
		} else if (temp->data < insertData && temp->rightNode != NULL) {
			temp = temp->rightNode;
		}
	}
}

void PrintInorder(struct BinarySearchTree *BST, struct Node *node) {
	if(node == NULL) {
		return;
	}
	BST->PrintInorder(BST, node->leftNode);
	printf("%d ", node->data);
	BST->PrintInorder(BST, node->rightNode);
}

struct BinarySearchTree *BinarySearchTreeCreater() {
	struct BinarySearchTree *newBST = (struct BinarySearchTree *)calloc(1, sizeof(struct BinarySearchTree));
	newBST->topNode = NodeCreater(INT_MAX);
	
	newBST->Search = Search;
	newBST->Delete = Delete;
	newBST->Swap = Swap;
	newBST->Insert = Insert;
	newBST->IsEmpty = IsEmpty;
	newBST->PrintInorder = PrintInorder;
	return newBST;
}

int main() {
	struct BinarySearchTree *BST = BinarySearchTreeCreater();
	BST->Insert(BST, 0);
	BST->Insert(BST, 4);
	BST->Insert(BST, 3);
	BST->Insert(BST, 0);
	BST->Insert(BST, 8);
	BST->PrintInorder(BST, BST->topNode->leftNode);
	printf("\n");
	BST->Insert(BST, 3);
	BST->PrintInorder(BST, BST->topNode->leftNode);
	printf("\n");
	
	int popNumber = 1;//change number!!
	
	struct Node *searchNode = BST->Search(BST->topNode->leftNode, popNumber);
	if(searchNode == NULL) {
		printf("there is no number on the binary search tree!\n");
	} else {
		printf("pop %d\n", BST->Delete(BST, popNumber, searchNode)->data);
	}
	
	BST->PrintInorder(BST, BST->topNode->leftNode);
	printf("\n");
}

