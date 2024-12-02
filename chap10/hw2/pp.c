#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

void addq(int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("fail.\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = NULL;
    if (tail == NULL) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

int delete() {
    if (head == NULL) {
        printf("Queue is empty.\n");
        return -1;
    }
    struct node *temp = head;
    int data = temp->data;
    head = head->next;
    if (head == NULL) {
        tail = NULL;
    }
    free(temp);
    return data;
}

void print_queue() {
    struct node *current = head;
    printf("Print queue\n");
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    float input;

    while (1) {
        if (scanf("%f", &input) != 1 || input <= 0) {
            break;
        }

        if ((int)input != input) {
            int value = (int)input;
            addq(value);
            break;
        }
        addq((int)input);
    }
    print_queue();
    return 0;
}
