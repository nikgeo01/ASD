#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node *next;
    struct Node *dnext;
};

typedef struct LinkedList
{
    struct Node *head;
    struct Node *dhead;
} LinkedList;

struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->next = NULL;
    newNode->dnext = NULL;
    return newNode;
}
void rearange(struct Node *node)
{
    if (node->next == NULL)
        return;
    node->dnext = node->next->next;
    rearange(node->next);
}

void push(struct Node *cur, int value)
{
    struct Node *newNode = createNode(value);
    if (cur->next == NULL)
    {
        cur->next = newNode;
        return;
    }

    if (newNode->value >= cur->value && newNode->value <= cur->next->value)
    {
        struct Node *newNode = createNode(value);
        newNode->next = cur->next;
        cur->next = newNode;
        return;
    }
    push(cur->next, value);
}

int find(struct Node *cur, int value)
{
    if (cur == NULL)
    {
        return 0;
    }
    if (cur->value == value)
    {
        return 1;
    }
    if (cur->value < value)
    {
        int res = find(cur->dnext, value);
        if (res == 1)
        {
            return 1;
        }
        else
        {
            if (res == 2)
            {
                return find(cur->next, value);
            }
            else
            {
                return 0;
            }
        }
    }
    if (cur->value > value)
    {
        return 2;
    };
}

void print(struct Node *node)
{
    if (node == NULL)
        return;

    printf("%d ", node->value);
    print(node->next);
}

void printd(struct Node *node)
{
    if (node->dnext == NULL)
    {
        return;
    }

    printf("%d ", node->dnext->value);
    printd(node->dnext);
}

void freeList(struct Node *node)
{
    if (node == NULL)
    {
        return;
    }

    struct Node *temp;

    while (node != NULL)
    {
        temp = node;
        node = node->next;
        free(temp);
    }
}

int main()
{

    LinkedList list;
    list.head = NULL;
    list.dhead = NULL;

    list.head = createNode(0);

    push(list.head, 7);
    push(list.head, 5);
    push(list.head, 9);
    push(list.head, 1);
    printf("\n");
    print(list.head);
    printf("\n");
    rearange(list.head);
    print(list.head);
    printf("\n");
    printd(list.head);
    printf("\n");

    freeList(list.head);
    list.head = NULL;

    return 0;
}
