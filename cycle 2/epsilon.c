#include<stdio.h>
#include<stdlib.h>

struct node {
	int stateNum;
	int curValue;
	char transValue[20];
	struct node* transNode[20];
};

int len(int A[]) {
	return sizeof(A)/sizeof(A[0]);
}

struct result {
	int closures[20];
};

struct node* createNode(int state) {
	struct node *newNode = (struct node*) malloc(sizeof(struct node));
	newNode->stateNum = state;
	newNode->curValue = 0;
	for(int i = 0; i< 20; i++) {
		newNode->transValue[i] = -1;
		newNode->transNode[i] = NULL;
	}
	return newNode;
}

struct result* mergeArray(int A[20], int B[20]) {
	int i=0,j=0,flag=1,c;
	struct result *mergeRes = (struct result*)malloc(sizeof(struct result));
	for (i = 0; i < 20; i++) {
		mergeRes->closures[i] = A[i] || B[i];
	}
	return mergeRes;
}

void createTransition(struct node* root, char transVal, struct node* transState) {
	root -> transValue[root->curValue] = transVal;
	root -> transNode[root->curValue] = transState;
	root -> curValue += 1;
}

struct result* findClosure(struct node *root) {
	int i,j,k,flag,c = 0;
	struct result *newRes;
	struct result *res = (struct result *)malloc(sizeof(struct result));
	(res -> closures)[root->stateNum] = 1;
	for(i = 0; i < root -> curValue; i++) {
		if(root -> transValue[i] == 'e') {
			res->closures[root->transNode[i]->stateNum] = 1;
			newRes = findClosure(root->transNode[i]);
			res = mergeArray(res->closures, newRes->closures);
		}
	}
	return res;
}

int main() {
	int statesNum, transNum, i, j, stateVal, transState;
	char transVal;
	struct node *nodes[20];
	struct result *res;
	printf("Enter no. of states: ");
	scanf("%d",&statesNum);
	for(i = 0; i < statesNum; i++) {
		nodes[i] = createNode(i);
	}
	printf("\nEnter no. of transitions: ");
	scanf("%d", &transNum);
	printf("\nEnter transitions: ");
	for(i=0; i<transNum; i++) {
		scanf("%d %c %d", &stateVal, &transVal, &transState);
		createTransition(nodes[stateVal-1], transVal, nodes[transState-1]);
	}
	for(i = 0; i < statesNum; i++) {
		res = findClosure(nodes[i]);
		printf("\nq%d: ",i+1);
		for(j = 0; j < 20; j++) {
			if(res->closures[j] > 0)
				printf("%d ", j+1);
		}
		res = (struct result*)malloc(sizeof(struct result));
	}
}