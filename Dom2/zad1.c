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

int fullSize(struct Node* node)
{
	if(node == NULL) return 0;
	return (size(node) - 1 + fullSize(node->left) + fullSize(node->right));
}

float weight(struct Node* node)
{
	float curWeight = node->value * (size(node) - 1);
	float lWeight = 0;
	float rWeight = 0;
	if(node->left != NULL) lWeight = weight(node->left);
	if(node->right != NULL) rWeight = weight(node->right);
	printf("CUR W: %f\n", curWeight);
	return (curWeight + lWeight + rWeight);
}

float avgWeight(struct Node* root)
{
	float treeSize = fullSize(root);
	float treeWeight = weight(root);
	printf("%f/%f\n", treeWeight, treeSize);
	return (treeWeight/treeSize);
}

void printTree(struct Node* cur)
{
	if(cur == NULL) return;
	printf("%f ", cur->value);
	printTree(cur->left);
	printTree(cur->right);
}

int main()
{
	struct Node* TreeRoot = createNode(5);
	TreeRoot->left = createNode(1);
	TreeRoot->left->right = createNode(3);
	TreeRoot->right = createNode(7);
	TreeRoot->right->right = createNode(12);
	TreeRoot->right->right->right = createNode(3.14);

	printTree(TreeRoot);
	printf("\nAVG WEIGHT: %f\n", avgWeight(TreeRoot));

	return 0;
}
