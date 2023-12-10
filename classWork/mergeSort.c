#include <stdio.h>
#include <stdlib.h>

struct Node
{
	int num;
	struct Node* next;
	struct Node* prev;
};

typedef struct List
{
	struct Node* head;
	struct Node* tail;
} List;

struct Node* createNode(int value)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	if (newNode == NULL)
	{
		printf("Error allocating memmory\n");
		exit(1);
	}
	newNode->num = value;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

void pushFront(int value, List* list)
{
	struct Node *newNode = createNode(value);
	newNode->next = list->head;
	if(list->head != NULL)
	{
		list->head->prev = newNode;
	}
	list->head = newNode;
	if(list->tail == NULL)
	{
		list->tail = newNode;
	}
}

void printList(List* list)
{
	struct Node* cur = list->head;
	while(cur != NULL)
	{
		printf("%d ", cur->num);
		cur = cur->next;
	}
}

void freeMemmory(List* list)
{
	struct Node* cur = list->head;
	while(cur != NULL)
	{
		struct Node* temp = cur;
		cur = cur->next;
		free(temp);
	}
	list->head = NULL;
	list->tail = NULL;
}

struct Node* merge(struct Node* left, struct Node* right)
{
	if(left == NULL)
	{
		return right;
	}
	if(right == NULL)
	{
		return left;
	}

	struct Node* combined = (struct Node*)malloc(sizeof(struct Node));

	if(left->num <= right->num)
	{
		combined->num = left->num;
		combined->next = merge(left->next, right);
		combined->next->prev = combined;
	}
	else
	{
		combined->num = right->num;
		combined->next = merge(left, right->next);
		combined->next->prev = combined;
	}
	return combined;
}

void split(struct Node* start, struct Node** lPartStart, struct Node** rPartStart)
{
	struct Node* countBy1;
	struct Node* countBy2;

	if(start == NULL || start->next == NULL)
	{
		*lPartStart = start;
		*rPartStart = NULL;
	}
	else
	{
		countBy1 = start;
		countBy2 = start->next;
	}

	while(countBy2 != NULL)
	{
		countBy2 = countBy2->next;
		if(countBy2 != NULL)
		{
			countBy1 = countBy1->next;
			countBy2 = countBy2->next;
		}
	}
	*lPartStart = start;
	*rPartStart = countBy1->next;
	countBy1->next = NULL; //separate by the middle
}

void mergeSort(struct Node** listHeadPointer)
{
	struct Node* head = *listHeadPointer;
	struct Node* left;
	struct Node* right;

	if (head == NULL || head->next == NULL)
	{
		return;
	}

	split(head, &left, &right);

	mergeSort(&left);
	mergeSort(&right);

	*listHeadPointer = merge (left, right);
}

int main()
{
	List linkedList = {head:NULL, tail: NULL};
	while(1)
	{
		int num;
		printf("Enter number to push: ");
		scanf("%d", &num);
		pushFront(num, &linkedList);
		int choose;
		printf("Enter 1 to continue pushing or 0 to sort the List: ");
		scanf("%d", &choose);
		if(choose == 0)
		{
			break;
		}
	}
	printf("\n\nEntered list:\n");
	printList(&linkedList);

	mergeSort(&linkedList.head);

	printf("\n\nSorted list:\n");
	printList(&linkedList);

	freeMemmory(&linkedList);

	return 0;
}