#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    struct Node* xor;
    struct Node* skipxor;
};

typedef struct LinkedList
{
    struct Node* head;
    struct Node* tail;
} LinkedList;

struct Node* xor(struct Node* a, struct Node*b)
{
    return (struct Node*)((size_t)a ^ (size_t)b);
}

struct Node* createNode(int value)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = value;
    newNode->xor = NULL;
    newNode->skipxor = NULL;
    return newNode;
}

void rearrange(LinkedList* list)
{
    printf("\nREARRANGING\n");
    struct Node* cur = list->head;
    struct Node* prev = NULL;
    struct Node* dprev = NULL;

    if(cur == NULL)
    {
        return;
    }
    if(cur->xor == NULL)
    {
        return;
    }
    while(1)
    {
        struct Node* next = xor(prev, cur->xor);
        cur->skipxor = dprev;
        if(next == NULL)
        {
            break;
        }
        struct Node* dnext = xor(cur, next->xor);

        //printing values-----------------------------
        if(dprev == NULL)
        {
            printf("%-7s", "NULL");
        }
        else
        {
            printf("%-6d ", dprev->value);
        }
        printf("%-6d ", cur->value);
        if(dnext == NULL)
        {
            printf("NULL\n");
        }
        else
        {
            printf("%-7d\n", dnext->value);
        }
        printf("------------------\n");
        //---------------------------------------------

        cur->skipxor = xor(dprev, dnext);
        dprev = prev;
        prev = cur;
        cur = next;
    }
}

void insert(LinkedList* list, int value)
{
    struct Node* cur = list->head;
    if(cur == NULL)
    {
        list->head = createNode(value);
        return;
    }
    if(cur->xor == NULL )
    {
        struct Node* newNode = createNode(value);
        newNode->xor = cur;
        cur->xor = newNode;
        return;
    }
    struct Node* next = xor(NULL, cur->xor);
    struct Node* prev = xor(cur->xor, next);
    struct Node* dcur = cur;
    struct Node* dnext = xor(NULL, dcur->skipxor);
    struct Node* dprev = xor(dcur->skipxor, dnext);

    if(cur->value < value)
    {   
        while(next != NULL && value > next->value)
        {
            struct Node* temp = next;
            next = xor(cur, next->xor);
            prev = cur;
            cur = temp;
        }
        struct Node* newNode = createNode(value);
        newNode->xor = xor(cur, next);
        cur->xor = xor(prev, newNode);
        if (next != NULL)
        {
            next->xor = xor(newNode, xor(cur, next->xor));
        }
    }
    else
    {
        struct Node* newNode = createNode(value);
        newNode->xor = xor(prev, next);
        cur->xor = xor(newNode, next);
    }
}

void delete(LinkedList* list, int value)
{
    struct Node* cur = list->head;
    if(cur == NULL)
    {
        printf("List is empty! Nothing to delete.\n");
        return;
    }
    if(cur->xor == NULL)
    {
        if(cur->value == value)
        {
            free(cur);
            list->head = NULL;
            return;
        }
        else
        {
            printf("Value not found!\n");
            return;
        }
    }
    struct Node* next = xor(NULL, cur->xor);
    struct Node* prev = xor(cur->xor, next);

    while (1)
    {
        if(cur == NULL)
        {
            printf("Value not found!\n");
            return;
        }
        if(cur->value > value)
        {
            printf("Value not found!\n");
            return;
        }
        if(cur->value == value)
        {
            if(cur == list->head)
            {
                list->head = next;
                next->xor = xor(NULL, xor(cur, next->xor));
                free(cur);
                return;
            }
            else
            {
                prev->xor = xor(xor(prev->xor, cur), next);
                next->xor = xor(xor(next->xor, cur), prev);
                free(cur);
                return;
            }
        }
        struct Node* temp = cur;
        cur = next;
        next = xor(temp, cur->xor);
        prev = xor(cur->xor, next);
    }
    
    
}

void print(struct Node* prev, struct Node* cur, struct Node* next)
{
    
    printf("%d ", cur->value);
    if (next == NULL)
    {
        return;
    }
    print(cur, next, xor(next->xor, cur));
}

void printd(LinkedList* list, struct Node* dcur, struct Node* dnext)
{
    printf("%d ", dcur->value);
    if(dnext == NULL)
    {
        return;
    }
    printd(list, dnext, xor(dnext->skipxor, dcur));
}


int main()
{
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;

    insert(list, 1);
    insert(list, 8);
    insert(list, 5);
    insert(list, 7);
    insert(list, 2);
    insert(list, 6);
    insert(list, 3);
    insert(list, 4);
    insert(list, 14);
    insert(list, 12);
    insert(list, 6);

    printf("\nPRINTING\n");
    print(NULL, list->head, xor(list->head->xor, NULL));
    printf("\n");

    rearrange(list);

    printf("\nSKIP PRINTING\n");
    printd(list, list->head, xor(list->head->skipxor, NULL));
    printf("\n");

    delete(list, 3);
    delete(list, 6);
    delete(list, 6);
    delete(list, 12);

    printf("\nPRINT AFTER DELETING ELEMENTS\n");
    print(NULL, list->head, xor(list->head->xor, NULL));
    printf("\n");

    rearrange(list);
    printf("\nSKIP PRINT AFTER DELETING ELEMENTS\n");
    printd(list, list->head, xor(list->head->skipxor, NULL));
    printf("\n");

    return 0;
}