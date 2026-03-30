#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================= NODE =================
typedef struct Node {
    char data[100];
    struct Node *next;
    struct Node *prev;
} Node;

// ================= STACK =================
typedef struct {
    Node *top;
} Stack;

void initStack(Stack *s) {
    s->top = NULL;
}

int isEmptyStack(Stack *s) {
    return s->top == NULL;
}

void push(Stack *s, char data[]) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->next = s->top;
    s->top = newNode;
}

void pop(Stack *s) {
    if (isEmptyStack(s)) {
        printf("Nothing to undo\n");
        return;
    }
    Node *temp = s->top;
    printf("Undo: %s\n", temp->data);
    s->top = temp->next;
    free(temp);
}

// ================= QUEUE =================
typedef struct {
    Node *front;
    Node *rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = NULL;
}

int isEmptyQueue(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, char data[]) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    strcpy(newNode->data, data);
    newNode->next = NULL;

    if (isEmptyQueue(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

void dequeue(Queue *q) {
    if (isEmptyQueue(q)) {
        printf("No normal tasks\n");
        return;
    }

    Node *temp = q->front;
    printf("Processed (Queue): %s\n", temp->data);

    q->front = q->front->next;
    if (q->front == NULL) q->rear = NULL;

    free(temp);
}

// ================= DEQUE =================
typedef struct {
    Node *front;
    Node *rear;
} Deque;

void initDeque(Deque *d) {
    d->front = d->rear = NULL;
}

int isEmptyDeque(Deque *d) {
    return d->front == NULL;
}

void pushFront(Deque *d, char data[]) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    strcpy(newNode->data, data);

    if (isEmptyDeque(d)) {
        d->front = d->rear = newNode;
        newNode->next = newNode->prev = NULL;
    } else {
        newNode->next = d->front;
        newNode->prev = NULL;
        d->front->prev = newNode;
        d->front = newNode;
    }
}

void pushBack(Deque *d, char data[]) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    strcpy(newNode->data, data);

    if (isEmptyDeque(d)) {
        d->front = d->rear = newNode;
        newNode->next = newNode->prev = NULL;
    } else {
        newNode->prev = d->rear;
        newNode->next = NULL;
        d->rear->next = newNode;
        d->rear = newNode;
    }
}

void popFrontDeque(Deque *d) {
    if (isEmptyDeque(d)) return;

    Node *temp = d->front;
    printf("Processed (Priority): %s\n", temp->data);

    d->front = d->front->next;

    if (d->front != NULL)
        d->front->prev = NULL;
    else
        d->rear = NULL;

    free(temp);
}

// ================= DISPLAY =================
void displayAll(Deque *d, Queue *q) {
    printf("\n--- Priority Tasks (Deque) ---\n");
    Node *curr = d->front;
    if (!curr) printf("Empty\n");
    while (curr) {
        printf("- %s\n", curr->data);
        curr = curr->next;
    }

    printf("\n--- Normal Tasks (Queue) ---\n");
    curr = q->front;
    if (!curr) printf("Empty\n");
    while (curr) {
        printf("- %s\n", curr->data);
        curr = curr->next;
    }
}

// ================= MAIN =================
int main() {
    Stack s;
    Queue q;
    Deque d;

    initStack(&s);
    initQueue(&q);
    initDeque(&d);

    int choice;
    char task[100];

    while (1) {
        printf("\n=== TASK SYSTEM ===\n");
        printf("1. Add Normal Task (Queue)\n");
        printf("2. Add Priority Task (Deque)\n");
        printf("3. Process Task\n");
        printf("4. Undo\n");
        printf("5. Show All Tasks\n");
        printf("6. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter task: ");
                fgets(task, 100, stdin);
                task[strcspn(task, "\n")] = 0;

                enqueue(&q, task);
                push(&s, "Add Normal Task");
                break;

            case 2:
                printf("Enter priority task: ");
                fgets(task, 100, stdin);
                task[strcspn(task, "\n")] = 0;

                pushFront(&d, task);
                push(&s, "Add Priority Task");
                break;

            case 3:
                if (!isEmptyDeque(&d)) {
                    popFrontDeque(&d);
                } else {
                    dequeue(&q);
                }
                push(&s, "Process Task");
                break;

            case 4:
                pop(&s);
                break;

            case 5:
                displayAll(&d, &q);
                break;

            case 6:
                exit(0);
        }
    }
}
