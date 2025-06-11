#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"

int main() {
    srand(time(NULL));

    // Размеры данных для тестирования
    long data_sizes[] = { 1000, 10000, 50000, 100000, 200000, 500000, 1000000 };
    int num_sizes = sizeof(data_sizes) / sizeof(data_sizes[0]);
    int num_hash_funcs = 3;

    FILE* file_ptr;
    for(int i = 0; i < num_hash_funcs; ++i) {
        char collisions_filename[32];
        char times_filename[32];
        sprintf(collisions_filename, "collisions_h%d.dat", i + 1);
        sprintf(times_filename, "search_times_h%d.dat", i + 1);
        
        file_ptr = fopen(collisions_filename, "w");
        if (file_ptr) fclose(file_ptr);
        
        file_ptr = fopen(times_filename, "w");
        if (file_ptr) fclose(file_ptr);
    }

    for (int i = 0; i < num_hash_funcs; i++) {
        printf("Testing Hash Function %d (%s)\n", i + 1, options[i]);
        char collisions_filename[32];
        char times_filename[32];
        sprintf(collisions_filename, "collisions_h%d.dat", i + 1);
        sprintf(times_filename, "search_times_h%d.dat", i + 1);

        FILE* collisions_file = fopen(collisions_filename, "a");
        FILE* times_file = fopen(times_filename, "a");

        if (!collisions_file || !times_file) {
            return 1;
        }

        for (int j = 0; j < num_sizes; j++) {
            long current_size = data_sizes[j];
            long table_capacity = current_size * 2;
            printf("  Testing with N = %ld... ", current_size);
            School* teachers = genArray(current_size);
            if (!teachers) {
                continue;
            }
            hash_func_type hf = get_hash_func(i);
            HashTable* table = create_hash_table(table_capacity, hf);
            for (long k = 0; k < current_size; k++) {
                hash_table_set(table, teachers[k].full_name, &teachers[k]);
            }
            fprintf(collisions_file, "%ld %ld\n", current_size, table->collisions);
            clock_t start = clock();
            clock_t end = clock();
            double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
            fprintf(times_file, "%ld %f\n", current_size, time_spent);
            printf("Collisions: %ld, Search time: %f s\n", table->collisions, time_spent);
            destroy_hash_table(table);
            free(teachers);
        }
        fclose(collisions_file);
        fclose(times_file);
    }
    printf("Finished\n");
    return 0;
}
