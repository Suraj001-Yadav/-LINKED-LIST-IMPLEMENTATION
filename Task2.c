#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

LinkedList* createLinkedList();
Node* createNode(int data);
void insertAtBeginning(LinkedList* list, int data);
void insertAtEnd(LinkedList* list, int data);
void insertAtPosition(LinkedList* list, int data, int position);
void deleteFromBeginning(LinkedList* list);
void deleteFromEnd(LinkedList* list);
void deleteFromPosition(LinkedList* list, int position);
void deleteByValue(LinkedList* list, int value);
void displayList(LinkedList* list);
int search(LinkedList* list, int value);
int getSize(LinkedList* list);
void freeLinkedList(LinkedList* list);
void printMenu();

LinkedList* createLinkedList() {
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    if (list == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtBeginning(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    newNode->next = list->head;
    list->head = newNode;
    list->size++;
    printf("Inserted %d at the beginning.\n", data);
}

void insertAtEnd(LinkedList* list, int data) {
    Node* newNode = createNode(data);
    
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
    printf("Inserted %d at the end.\n", data);
}

void insertAtPosition(LinkedList* list, int data, int position) {
    if (position < 0 || position > list->size) {
        printf("Invalid position! Position should be between 0 and %d.\n", list->size);
        return;
    }
    
    if (position == 0) {
        insertAtBeginning(list, data);
        return;
    }
    
    if (position == list->size) {
        insertAtEnd(list, data);
        return;
    }
    
    Node* newNode = createNode(data);
    Node* current = list->head;
    
    for (int i = 0; i < position - 1; i++) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
    list->size++;
    printf("Inserted %d at position %d.\n", data, position);
}

void deleteFromBeginning(LinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return;
    }
    
    Node* temp = list->head;
    list->head = list->head->next;
    printf("Deleted %d from the beginning.\n", temp->data);
    free(temp);
    list->size--;
}

void deleteFromEnd(LinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return;
    }
    
    if (list->head->next == NULL) {
        printf("Deleted %d from the end.\n", list->head->data);
        free(list->head);
        list->head = NULL;
    } else {
        Node* current = list->head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        printf("Deleted %d from the end.\n", current->next->data);
        free(current->next);
        current->next = NULL;
    }
    list->size--;
}

void deleteFromPosition(LinkedList* list, int position) {
    if (list->head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return;
    }
    
    if (position < 0 || position >= list->size) {
        printf("Invalid position! Position should be between 0 and %d.\n", list->size - 1);
        return;
    }
    
    if (position == 0) {
        deleteFromBeginning(list);
        return;
    }
    
    Node* current = list->head;
    Node* previous = NULL;
    
    for (int i = 0; i < position; i++) {
        previous = current;
        current = current->next;
    }
    
    previous->next = current->next;
    printf("Deleted %d from position %d.\n", current->data, position);
    free(current);
    list->size--;
}

void deleteByValue(LinkedList* list, int value) {
    if (list->head == NULL) {
        printf("List is empty! Nothing to delete.\n");
        return;
    }
    
    Node* current = list->head;
    Node* previous = NULL;
    
    if (current != NULL && current->data == value) {
        list->head = current->next;
        printf("Deleted %d from the list.\n", value);
        free(current);
        list->size--;
        return;
    }
    
    while (current != NULL && current->data != value) {
        previous = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Value %d not found in the list.\n", value);
        return;
    }
    
    previous->next = current->next;
    printf("Deleted %d from the list.\n", value);
    free(current);
    list->size--;
}

void displayList(LinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }
    
    Node* current = list->head;
    printf("Linked List: ");
    while (current != NULL) {
        printf("%d", current->data);
        if (current->next != NULL) {
            printf(" -> ");
        }
        current = current->next;
    }
    printf("\n");
}

int search(LinkedList* list, int value) {
    Node* current = list->head;
    int position = 0;
    
    while (current != NULL) {
        if (current->data == value) {
            return position;
        }
        current = current->next;
        position++;
    }
    
    return -1;
}

int getSize(LinkedList* list) {
    return list->size;
}

void freeLinkedList(LinkedList* list) {
    Node* current = list->head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    free(list);
}

void printMenu() {
    printf("\n=== LINKED LIST OPERATIONS ===\n");
    printf("1. Insert at beginning\n");
    printf("2. Insert at end\n");
    printf("3. Insert at position\n");
    printf("4. Delete from beginning\n");
    printf("5. Delete from end\n");
    printf("6. Delete from position\n");
    printf("7. Delete by value\n");
    printf("8. Display list\n");
    printf("9. Search value\n");
    printf("10. Get size\n");
    printf("11. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    LinkedList* list = createLinkedList();
    int choice, data, position, value, result;
    
    printf("Welcome to Linked List Implementation!\n");
    
    while (1) {
        printMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data to insert at beginning: ");
                scanf("%d", &data);
                insertAtBeginning(list, data);
                break;
                
            case 2:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                insertAtEnd(list, data);
                break;
                
            case 3:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &position);
                insertAtPosition(list, data, position);
                break;
                
            case 4:
                deleteFromBeginning(list);
                break;
                
            case 5:
                deleteFromEnd(list);
                break;
                
            case 6:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleteFromPosition(list, position);
                break;
                
            case 7:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteByValue(list, value);
                break;
                
            case 8:
                displayList(list);
                break;
                
            case 9:
                printf("Enter value to search: ");
                scanf("%d", &value);
                result = search(list, value);
                if (result != -1) {
                    printf("Value %d found at position %d.\n", value, result);
                } else {
                    printf("Value %d not found in the list.\n", value);
                }
                break;
                
            case 10:
                printf("Current size of the list: %d\n", getSize(list));
                break;
                
            case 11:
                freeLinkedList(list);
                printf("Linked list freed. Exiting program.\n");
                exit(0);
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}