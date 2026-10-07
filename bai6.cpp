#include <stdio.h>

#define MAX 100
#define EMPTY -1

typedef struct {
    int id;
    char content;
    int left;
    int right;
} Node;

Node Tree[MAX];

/* Duyệt trước: N - L - R */
void preorder(int i) {
    if (i == EMPTY)
        return;

    printf("%d - %c\n", Tree[i].id, Tree[i].content);

    preorder(Tree[i].left);
    preorder(Tree[i].right);
}

/* Duyệt giữa: L - N - R */
void inorder(int i) {
    if (i == EMPTY)
        return;

    inorder(Tree[i].left);

    printf("%d - %c\n", Tree[i].id, Tree[i].content);

    inorder(Tree[i].right);
}

/* Duyệt sau: L - R - N */
void postorder(int i) {
    if (i == EMPTY)
        return;

    postorder(Tree[i].left);
    postorder(Tree[i].right);

    printf("%d - %c\n", Tree[i].id, Tree[i].content);
}

int main() {
    /*
          A
         / \
        B   C
       / \
      D   E
    */

    Tree[0].id = 1;
    Tree[0].content = 'A';
    Tree[0].left = 1;
    Tree[0].right = 2;

    Tree[1].id = 2;
    Tree[1].content = 'B';
    Tree[1].left = 3;
    Tree[1].right = 4;

    Tree[2].id = 3;
    Tree[2].content = 'C';
    Tree[2].left = EMPTY;
    Tree[2].right = EMPTY;

    Tree[3].id = 4;
    Tree[3].content = 'D';
    Tree[3].left = EMPTY;
    Tree[3].right = EMPTY;

    Tree[4].id = 5;
    Tree[4].content = 'E';
    Tree[4].left = EMPTY;
    Tree[4].right = EMPTY;

    printf("Duyet Preorder:\n");
    preorder(0);

    printf("\nDuyet Inorder:\n");
    inorder(0);

    printf("\nDuyet Postorder:\n");
    postorder(0);

    return 0;
}