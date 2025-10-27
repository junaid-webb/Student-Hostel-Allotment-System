#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    char name[50];
    int room;
    char block[10];
    struct Student *next;
};

struct Student *head = NULL;

void add(int id, char name[], int room, char block[]) {
    struct Student *newNode = malloc(sizeof(struct Student));
    newNode->id = id;
    strcpy(newNode->name, name);
    newNode->room = room;
    strcpy(newNode->block, block);
    newNode->next = head;
    head = newNode;
}

void display() {
    struct Student *t = head;
    if (!t) { printf("No records.\n"); return; }
    printf("\n--- Hostel Allotments ---\n");
    while (t) {
        printf("ID:%d | Name:%s | Room:%d | Block:%s\n", t->id, t->name, t->room, t->block);
        t = t->next;
    }
}

void search(char key[]) {
    struct Student *t = head;
    int found = 0;
    while (t) {
        if (strcmp(t->name, key) == 0 || atoi(key) == t->room) {
            printf("Found -> ID:%d | Name:%s | Room:%d | Block:%s\n", t->id, t->name, t->room, t->block);
            found = 1;
        }
        t = t->next;
    }
    if (!found) printf("No match found.\n");
}

void removeStudent(int id) {
    struct Student *t = head, *prev = NULL;
    while (t && t->id != id) {
        prev = t;
        t = t->next;
    }
    if (!t) { printf("Student not found.\n"); return; }
    if (!prev) head = t->next;
    else prev->next = t->next;
    free(t);
    printf("Removed successfully!\n");
}

int main() {
    int ch, id, room;
    char name[50], block[10], key[50];
    while (1) {
        printf("\n1.Add 2.Display 3.Search 4.Remove 5.Exit\nEnter choice: ");
        scanf("%d", &ch);
        getchar();
        switch (ch) {
            case 1:
                printf("ID: "); scanf("%d", &id); getchar();
                printf("Name: "); fgets(name, 50, stdin); name[strcspn(name, "\n")] = 0;
                printf("Room: "); scanf("%d", &room); getchar();
                printf("Block: "); fgets(block, 10, stdin); block[strcspn(block, "\n")] = 0;
                add(id, name, room, block);
                break;
            case 2: display(); break;
            case 3:
                printf("Enter name or room no: ");
                fgets(key, 50, stdin); key[strcspn(key, "\n")] = 0;
                search(key);
                break;
            case 4:
                printf("Enter ID to remove: ");
                scanf("%d", &id);
                removeStudent(id);
                break;
            case 5: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
}
