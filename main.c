#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"

int main() {
    srand(time(NULL));

    const long size = 500000;
    // Генерируем массив структур School длины size
    School* teachers = genArray(size);
    if (!teachers) {
        return 1;
    }
    
    printf("\nAvailable hash functions:\n1. %s\n2. %s\n3. %s\n", options[0], options[1], options[2]);
    printf("Choose hash function (1-3): ");
    
    int option_choice;
    if (scanf("%d", &option_choice) != 1 || option_choice < 1 || option_choice > 3) {
        fprintf(stderr, "Invalid input. Please enter a number between 1 and 3.\n");
        free(teachers);
        return 1;
    }
    while(getchar() != '\n'); 
    int option_index = option_choice - 1;
    HashTable* hash_table = create_hash_table(size * 2, get_hash_func(option_index));
    if (!hash_table) {
        free(teachers);
        return 1;
    }
    for (long i = 0; i < size; i++) {
        hash_table_set(hash_table, teachers[i].full_name, &teachers[i]);
    }
    printf("Hash table has been created and filled.\n");
    printf("Collisions: %ld\n", hash_table->collisions);


    // Поиск по ключу
    printf("\nEnter a key (full name) to search: ");
    char key[MAX_LENGTH];
    if (fgets(key, sizeof(key), stdin) == NULL) {
        fprintf(stderr, "No input received for search key.\n");
    } 
    else {
        key[strcspn(key, "\n")] = 0;
        // Получаем указатель на голову списка найденных записей
        RecordNode* found_records = hash_table_get(hash_table, key);
        if (found_records == NULL) {
            printf("No records found\n");
        }
        else {
            printf("Found records:\n");
            int count = 0;
            // Проходим по всему связанному списку и печатаем каждую запись
            for (RecordNode* current = found_records; current != NULL; current = current->next) {
                count++;
                printf("Record %d:\n", count);
                print_school_data((School*)current->value);
                printf("------------------------\n");
            }
        }
    }

    // Освобождаем память
    destroy_hash_table(hash_table);
    free(teachers);
    return 0;
}