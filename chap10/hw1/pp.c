#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *top = NULL;

void push(int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) {
        printf("fail.\n");
        exit(1);
    }
    new_node->data = data;
    new_node->next = top;
    top = new_node;
}

int pop() {
    if (top == NULL) {
        printf("Stack is empty.\n");
        return -1;
    }
    struct node *temp = top;
    int data = temp->data;
    top = top->next;
    free(temp);
    return data;
}

void print_stack() {
    struct node *current = top;
    printf("Print stack\n");
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
            push(value);
            break;
        }
        push((int)input);
    }
    print_stack();
    return 0;
}
