
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* taoNode(int x) {
    struct Node *p = (struct Node*)malloc(sizeof(struct Node));
    p->data = x;
    p->left = NULL;
    p->right = NULL;
    return p;
}

struct Node* themNode(struct Node *root, int x) {
    if (root == NULL)
        return taoNode(x);

    if (x < root->data)
        root->left = themNode(root->left, x);
    else if (x > root->data)
        root->right = themNode(root->right, x);

    return root;
}

void duyet(struct Node *root) {
    if (root != NULL) {
        duyet(root->left);
        printf("%d ", root->data);
        duyet(root->right);
    }
}

int main() {
    struct Node *root = NULL;
    int n, x, i;

    printf("Nhap so nut: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Nhap gia tri: ");
        scanf("%d", &x);
        root = themNode(root, x);
    }

    printf("Cay sau khi duyet: ");
    duyet(root);

    return 0;
}
