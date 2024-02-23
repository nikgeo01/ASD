#include <stdio.h>
#include <stdlib.h>

struct Node{
	char value;
	struct Node* left;
	struct Node* right;
};

struct Node* createNode(char value)
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

void arrange(int* arr, struct Node* cur)
{
	if(cur == NULL) return;
	int index = (int)(cur->value) - 97;
	arr[index]++;
	arrange(arr, cur->left);
	arrange(arr, cur->right);
}

void letters(int* arr, struct Node* cur)
{
	for(int i = 0; i < 26; i++)
	{
		arr[i] = 0;
	}
	arrange(arr, cur);
	for(int i = 25; i >= 0; i--)
	{
		if(arr[i] != 0)
		{
			printf("%c - %d\n", (char)(i + 97), arr[i]);
		}
	}
}

int main()
{
	struct Node* TreeRoot = createNode('v');
	TreeRoot->left = createNode('g');
	TreeRoot->left->left = createNode('a');
	TreeRoot->left->left->right = createNode('a');
	TreeRoot->left->left->right->right = createNode('a');
	TreeRoot->left->right = createNode('j');
	TreeRoot->left->right->right = createNode('k');
	TreeRoot->right = createNode('z');
	TreeRoot->right->left = createNode('v');
	TreeRoot->right->left->right = createNode('x');

	int arr[26];
	letters(arr, TreeRoot);

	return 0;
}
