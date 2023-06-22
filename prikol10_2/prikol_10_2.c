#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024

struct City {
    char city[100];
    int population;
    struct City* next;
};
struct City* hashTable[SIZE];

unsigned int hash_func(const char* city) {
    unsigned int hash = 0;
    for (int i = 0; i < strlen(city); i++) {
        hash = hash * 31 + city[i];
    }
    return hash % SIZE;
}

void add(const char* city, long long population) {
    unsigned int index = hash_func(city);
    struct City* newCity = (struct City*)malloc(sizeof(struct City));
    strncpy(newCity->city, city, sizeof(newCity->city));
    newCity->population = population;
    newCity->next = NULL;
    if (hashTable[index] == NULL) {
        hashTable[index] = newCity;
    } else {
        struct City* current = hashTable[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newCity;
    }
}

void remove_city(const char* city) {
    unsigned int index = hash_func(city);
    struct City* current = hashTable[index];
    struct City* prev = NULL;
    while (current != NULL) {
        if (strcmp(current->city, city) == 0) {
            if (prev == NULL) {
                hashTable[index] = current->next;
            } 
            else {
                prev->next = current->next;
            }
            free(current);
            printf("City '%s' removed.\n", city);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("City '%s' not found.\n", city);
}

void list() {
    printf("All cities here:\n");
    for (int i = 0; i < SIZE; i++) {
        struct City* current = hashTable[i];
        while (current != NULL) {
            printf("%s %d\n", current->city, current->population);
            current = current->next;
        }
    }
}

int main() {
    int choice, population;
    char city[96];
    for (int k = 0; k < SIZE; k++) {
        hashTable[k] = NULL;
    }
    do {
        printf("Functions:\n");
        printf("exit - 0\n");
        printf("add - 1\n");
        printf("remove_city - 2\n");
        printf("list - 3\n");
        printf("Write number you want: ");
        scanf("%d", &choice);
        switch (choice) {
            case 0:
                printf("End.\n");
                break;
            case 1:
                printf("Write city: ");
                scanf("%s", city);
                printf("Write population: ");
                scanf("%d", &population);
                add(city, population);
                break;
            case 2:
                printf("Write city: ");
                scanf("%s", city);
                remove_city(city);
                break;
            case 3:
                list();
                break;
            default:
                printf("Wrong choice.\n");
                break;
        }
        printf("\n");
    } while (choice != 0);


    for (int i = 0; i < SIZE; i++) {
        struct City* current = hashTable[i];
        while (current != NULL) {
            struct City* temp = current;
            current = current->next;
            free(temp);
        }
    }
    return 0;
}
