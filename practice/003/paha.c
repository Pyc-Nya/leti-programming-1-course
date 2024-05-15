#include <stdio.h>
#include <stdlib.h>

typedef struct nodeStruct {
    int data;
    struct nodeStruct* next;
} Node;

typedef struct queueHeadStruct {
    Node* first;
    Node* last;
    int count;
} QueueHead;

QueueHead* createQueue() {
    QueueHead* queue = (QueueHead*)malloc(sizeof(QueueHead));
    if (queue != NULL) {
        queue->first = NULL;
        queue->last = NULL;
        queue->count = 0;
    }
    return queue;
}

void enqueue(QueueHead* queue, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode != NULL) {
        newNode->data = value;
        newNode->next = NULL;
        if (queue->last == NULL) {
            queue->first = newNode;
        } else {
            queue->last->next = newNode;
        }
        queue->last = newNode;
        queue->count++;
    }
}

void freeQueue(QueueHead* queue) {
    Node* current = queue->first;
    Node* next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    free(queue);
}

int countBits(int n) {
    int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}

void clearStdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

int main() {
    QueueHead* queue;
    Node* current;
    FILE* file;
    int num;

    queue = createQueue();
    if (queue != NULL) {
        printf("Enter numbers (space to stop): ");
        
        do {
            num = getchar();
            clearStdin();
            if (num != ' ') {
                enqueue(queue, num);
            }
        } while (num != ' ');

        file = fopen("output.txt", "w");
        if (file != NULL) {
            current = queue->first;
            while (current != NULL) {
                if (countBits(current->data) % 2 == 0) {
                    fprintf(file, "%c\n", current->data);
                }
                current = current->next;
            }
            fclose(file);
            printf("Data has been written to 'output.txt'.\n");
        } else {
            printf("Error opening file!\n");
        }

        freeQueue(queue);
    }
    return 0;
}
