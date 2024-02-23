#include <stdio.h>
#include <stdlib.h>

struct Node{
	float value;
	struct Node* left;
	struct Node* right;
};

struct Node* createNode(float value)
{
	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
	if(newNode == NULL)
	{
		printf("Error allocating mammory!");
		exit(1);
	}
	newNode->value = value;
	newNode->right = NULL;
	newNode->left = NULL;

	return newNode;
}

float size (struct Node* node)
{
	if(node == NULL)
	{
		return 0;
	}
	return (1 + size(node->left) + size(node->right));
}

float chain(struct Node* cur)
{
	if(cur == NULL) return 0;
	float lChain = chain(cur->left);
	float rChain = chain(cur->right);
	return cur->value + (lChain > rChain ? lChain : rChain);
}

int main()
{
	struct Node* TreeRoot = createNode(5);
	TreeRoot->left = createNode(4);
	TreeRoot->left->left = createNode(11);
	TreeRoot->left->left->left = createNode(7);
	TreeRoot->left->left->right = createNode(2);
	TreeRoot->right = createNode(8);
	TreeRoot->right->left = createNode(13);
	TreeRoot->right->right = createNode(4);
	TreeRoot->right->right->right = createNode(1);

	printf("%f\n", chain(TreeRoot));

	return 0;
}
