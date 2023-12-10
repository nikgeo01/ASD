#include <stdio.h>
#include <stdlib.h>

struct Node{
	float value;
	struct Node* next;
};

struct Bucket{
	int index;
	struct Bucket* nextBucket;
	struct Node* head;
};

typedef struct Buckets{
	struct Bucket* head;
}Buckets;

struct Node* createNode(float value)
{
	struct Node* node = (struct Node*) malloc (sizeof(struct Node));
	if(node == NULL)
	{
		printf("Error allocating memmory!\n");
		exit(1);
	}
	node->value = value;
	node->next = NULL;
	return node;
}

struct Bucket* createBucket(int index)
{
	struct Bucket* bucket = (struct Bucket*) malloc (sizeof(struct Bucket));
	if(bucket == NULL)
	{
		printf("Error allocating memmory!\n");
		exit(1);
	}

	bucket->index = index;
	bucket->nextBucket = NULL;
	bucket->head = NULL;

	return bucket;
}

struct Bucket* createAllBuckets(struct Bucket* bucket, int len, int index)
{
	if(bucket == NULL)
	{
		bucket = createBucket(index);
	}
	if(index == len - 1)
	{
		return bucket;
	}
	struct Bucket* newbucket = createBucket(index);
	bucket->nextBucket = createAllBuckets(newbucket, len, index + 1);
	return bucket;
}

void fillNodes(struct Bucket* bucket, float num)
{
	if(bucket->head == NULL)
	{
		struct Node* newNode = createNode(num);
		newNode->next = bucket->head;
		bucket->head = newNode;
		return;
	}
	else
	{
		if(bucket->head->next == NULL)
		{
			struct Node* newNode = createNode(num);
			if(num < bucket->head->value)
			{
				newNode->next = bucket->head;
				bucket->head = newNode;
				return;
			}
			else
			{
				newNode->next = bucket->head->next;
				bucket->head->next = newNode;
				return;
			}
		}
		struct Node* temp = bucket->head;
		while(temp->next)
		{
			if(temp->next->value >= num) {
				struct Node *newNode = createNode(num);
				newNode->next = temp->next;
				temp->next = newNode;
				return;
			}
			temp = temp->next;
		}
		temp->next = createNode(num);
	}
	return;
}

void fillBuckets(struct Bucket* bucket, int index, float num)
{
	struct Bucket* temp = bucket;
	while(temp->nextBucket != NULL && temp->index <= index)
	{
		temp = temp->nextBucket;
	}
	fillNodes(temp, num);

	return;
}

void refillArr(float *arr, struct Bucket* bucket)
{
	int i = 0;
	struct Bucket* tempBucket = bucket;
	while(tempBucket != NULL)
	{
		struct Node* tempNode = tempBucket->head;
		while(tempNode != NULL)
		{
			arr[i] = tempNode->value;
			i++;
			tempNode = tempNode->next;
		}
		tempBucket = tempBucket->nextBucket;
	}
	return;
}

int main()
{

	float arr[] = {0.32, 0.16, 0.34, 0.15, 0.65, 0.18, 0.98, 0.24, 0.78, 0.92};
	int n = 10;

	Buckets* buckets = (Buckets*) malloc (sizeof(Buckets));

	buckets->head = createAllBuckets(buckets->head, n, 0);

	for(int i = 0; i < n; i++)
	{
		int index = (int)(arr[i] * 10);
		fillBuckets(buckets->head, index, arr[i]);
	}

	refillArr(arr, buckets->head);

	for(int i = 0; i < n; i++)
	{
		printf("%f ", arr[i]);
	}

	return 0;
}