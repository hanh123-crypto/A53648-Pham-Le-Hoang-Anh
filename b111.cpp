#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =======================
// 1. KHAI BAO CAU TRUC
// =======================

typedef struct {
    char id[10];
    char name[50];
    char serviceType[20];
    int arrivalTime;
    int processingTime;
    int waitingWeight;
} Customer;

typedef struct Node {
    Customer data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
    int size;
} Queue;


// =======================
// 2. KHOI TAO QUEUE
// =======================

void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
}


// =======================
// 3. KIEM TRA QUEUE RONG
// =======================

int isEmpty(Queue *q) {
    return q->front == NULL;
}


// =======================
// 4. TAO NODE
// =======================

Node* createNode(Customer c) {
    Node *p = (Node*)malloc(sizeof(Node));

    p->data = c;
    p->next = NULL;

    return p;
}


// =======================
// 5. THEM KHACH VAO QUEUE
// =======================

void enqueue(Queue *q, Customer c) {

    Node *p = createNode(c);

    if (isEmpty(q)) {
        q->front = p;
        q->rear = p;
    }
    else {
        q->rear->next = p;
        q->rear = p;
    }

    q->size++;

    printf("Them khach thanh cong!\n");
}


// =======================
// 6. PHUC VU KHACH
// =======================

void dequeue(Queue *q) {

    if (isEmpty(q)) {
        printf("Queue dang rong!\n");
        return;
    }

    Node *temp = q->front;

    printf("\nKhach duoc phuc vu:\n");
    printf("Ma: %s\n", temp->data.id);
    printf("Ten: %s\n", temp->data.name);
    printf("Dich vu: %s\n", temp->data.serviceType);

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);

    q->size--;
}


// =======================
// 7. HIEN THI QUEUE
// =======================

void displayQueue(Queue *q) {

    if (isEmpty(q)) {
        printf("Queue dang rong!\n");
        return;
    }

    Node *p = q->front;

    printf("\n===== DANH SACH KHACH DANG CHO =====\n");

    while (p != NULL) {

        printf("Ma: %s | Ten: %s | Dich vu: %s\n",
               p->data.id,
               p->data.name,
               p->data.serviceType);

        p = p->next;
    }

    printf("So khach dang cho: %d\n", q->size);
}


// =======================
// 8. TIM KIEM KHACH
// =======================

void searchCustomer(Queue *q) {

    char id[10];

    printf("Nhap ma khach can tim: ");
    scanf("%s", id);

    Node *p = q->front;

    while (p != NULL) {

        if (strcmp(p->data.id, id) == 0) {

            printf("\nTim thay khach!\n");
            printf("Ma: %s\n", p->data.id);
            printf("Ten: %s\n", p->data.name);
            printf("Dich vu: %s\n", p->data.serviceType);
            printf("Thoi gian den: %d\n", p->data.arrivalTime);
            printf("Thoi gian xu ly: %d\n", p->data.processingTime);
            printf("Trong so cho: %d\n", p->data.waitingWeight);

            return;
        }
        p = p->next;
    }
    printf("Khong tim duoc khac!\n");
}


