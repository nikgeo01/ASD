#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value;
    int height;
    struct Node *right;
    struct Node *left;
};

struct Node *createNode(int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    if (newNode == NULL)
    {
        printf("Error allocating mammory!");
        exit(1);
    }
    newNode->value = value;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->height = 0;

    return newNode;
}

int depth(struct Node *node)
{
    if (node == NULL || (node->left == NULL && node->right == NULL))
    {
        return 0;
    }
    return (1 + ((depth(node->left) > depth(node->right)) ? depth(node->left) : depth(node->right)));
}

void printTree(struct Node *cur)
{
    if (cur == NULL)
    {
        return;
    }

    printf("value: %d height: %d\n", cur->value, cur->height);
    printTree(cur->left);
    printTree(cur->right);
}

struct Node *rightRot(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = depth(y);
    x->height = depth(x);
    return x;
}

struct Node *leftRot(struct Node *y)
{
    struct Node *x = y->right;
    struct Node *T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = depth(y);
    x->height = depth(x);

    return x;
}

struct Node *leftRightRot(struct Node* cur)
{
    cur->left = leftRot(cur->left);
    return rightRot(cur);
}
struct Node *rightLeftRot(struct Node* cur)
{
    cur->right = rightRot(cur->right);
    return leftRot(cur);
}

struct Node *push(struct Node *cur, int value)
{
    
    if (cur == NULL)
    {
        return createNode(value);
    }
    
    if (cur->value > value)
    {
        cur->left = push(cur->left, value);
        cur->height = depth(cur);
    }
    else
    {
        if (cur->value < value)
        {
            cur->right = push(cur->right, value);
            cur->height = depth(cur);
        }
    }

    int cmp = 0;
    if (cur->left != NULL && cur->right != NULL)
    {
        cmp = cur->left->height - cur->right->height;
    }
    else
    {
        if ((cur->left != NULL && cur->right == NULL) || (cur->height > 1 && cur->right == NULL))
        {
            cmp = cur->left->height;
        }
        else
        {
            if ((cur->right != NULL && cur->left == NULL) || (cur->height > 1 && cur->left == NULL))
            {
                cmp = 0 - cur->right->height;
            }
        }
    }

    if (cmp > 1)
    {
        if (cur->left->left == NULL && cur->left->right != NULL)
        {
            leftRightRot(cur);
        }
        else
        {
            cur = rightRot(cur);
        }
    }
    else
    {
        if (cmp < -1)
        {
            if (cur->right->right == NULL && cur->right->left != NULL)
            {
                rightLeftRot(cur);
            }
            else
            {
                cur = leftRot(cur);
            }
        }
    }

    return cur;
}

int size(struct Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return (1 + size(node->left) + size(node->right));
}

int isBST(struct Node *node)
{
    if (node == NULL)
    {
        return 1;
    }

    if (node->right != NULL && node->right->value <= node->value)
    {
        return 0;
    }

    if (node->left != NULL && node->left->value >= node->value)
    {
        return 0;
    }

    return (isBST(node->left) && isBST(node->right));
}

int isBalanced(struct Node *node)
{
    if (node == NULL)
    {
        return 1;
    }

    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);

    if (abs(leftDepth - rightDepth) > 1)
    {
        return 0;
    }
    return (isBalanced(node->left) && isBalanced(node->right));
}

void freeMem(struct Node *cur)
{
    if (cur == NULL)
    {
        return;
    }

    freeMem(cur->left);
    freeMem(cur->right);

    free(cur);
}

int subTree(struct Node *r1, struct Node *r2, int started)
{
    if (r1 == NULL && r2 == NULL)
    {
        return 1;
    }
    else
    {
        if (r1 == NULL || r2 == NULL)
        {
            return 0;
        }
    }
    if (started)
    {
        if (r1->value != r2->value)
        {
            return 0;
        }
        else
        {
            return (subTree(r1->left, r2->left, 1) && subTree(r1->right, r2->right, 1));
        }
    }
    else
    {
        if (r2->value == r1->value)
        {
            return subTree(r1, r2, 1);
        }
        if (r2->value < r1->value)
        {
            return subTree(r1->left, r2, 0);
        }
        else
        {
            return subTree(r1->right, r2, 0);
        }
    }
}

int isIdentical(struct Node *r1, struct Node *r2)
{
    if (r1 == NULL && r2 == NULL)
    {
        return 1;
    }
    else
    {
        if (r1 == NULL || r2 == NULL)
        {
            return 0;
        }
    }
    if (r1->value != r2->value)
    {
        return 0;
    }
    else
    {
        return (isIdentical(r1->left, r2->left) && isIdentical(r1->right, r2->right));
    }
}

int main()
{
    struct Node *TreeRoot1 = NULL;
    TreeRoot1 = push(TreeRoot1, 90);
    TreeRoot1 = push(TreeRoot1, 80);
    TreeRoot1 = push(TreeRoot1, 70);
    TreeRoot1 = push(TreeRoot1, 50);
    TreeRoot1 = push(TreeRoot1, 40);
    TreeRoot1 = push(TreeRoot1, 60);

    printf("TREE:\n");
    printTree(TreeRoot1);

    printf("\nSize: %d\n", size(TreeRoot1));
    printf("Is BST: %d\n", isBST(TreeRoot1));
    printf("Depth: %d\n", depth(TreeRoot1));
    printf("Is balanced: %d\n", isBalanced(TreeRoot1));

    struct Node *TreeRoot2 = NULL;
    TreeRoot2 = push(TreeRoot2, 70);
    push(TreeRoot2, 60);

    printf("SUBTREE:\n");
    printTree(TreeRoot2);
    printf("\nIs sub tree: %d\n", subTree(TreeRoot1, TreeRoot2, 0));
    printf("\nIs identical: %d\n", isIdentical(TreeRoot1, TreeRoot2));

    freeMem(TreeRoot1);
    freeMem(TreeRoot2);

    return 0;
}