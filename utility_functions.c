#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct.h"

// Функции генерации данных

void generate_full_name(char* full_name) {
    const char* first_names[] = {
        "John", "Mikhail", "Jack", "Emma", "Mike", "Sarah", "Tom", "Lucy", "Sam", "Grace",
        "Ashab", "Vitaliy", "Kirill", "Mell", "Ivan", "Alexander", "Elena", "Dmitry", "Sophia", "Daniel",
        "Boris", "Vladimir", "Anatoly", "Sergei", "Nikolai", "Andrei", "Pavel", "Oleg", "Igor", "Maxim",
        "Artem", "Roman", "Yuri", "Viktor", "Konstantin", "Ruslan", "Vadim", "Evgeny", "Timur", "Gleb",
        "Valery", "Leonid", "Grigory", "Arseniy", "Denis", "Stanislav", "Fyodor", "Anton", "Alexey", "Ilya",
        "Maria", "Anna", "Tatiana", "Olga", "Natalia", "Svetlana", "Irina", "Ekaterina", "Galina", "Valentina"
    };
    const char* patronymics[] = {
        "Ivanovich", "Petrovich", "Sergeevich", "Alexandrovich", "Dmitrievich", "Andreevich", "Nikolaevich", "Mikhailovich", "Vladimirovich", "Alekseevich",
        "Borisovich", "Victorovich", "Pavlovich", "Vasilievich", "Grigorievich", "Romanovich", "Fedorovich", "Antonovich", "Anatolievich", "Konstantinovich",
        "Leonidovich", "Genadievich", "Valeryevich", "Arsenievich", "Denisovich", "Stanislavovich", "Olegovich", "Yuryevich", "Maksimovich", "Igorevich",
        "Ivanovna", "Petrovna", "Sergeevna", "Alexandrovna", "Dmitrievna", "Andreevna", "Nikolaevna", "Mikhailovna", "Vladimirovna", "Alekseevna",
        "Borisovna", "Victorovna", "Pavlovna", "Vasilievna", "Grigorievna", "Romanovna", "Fedorovna", "Antonovna", "Anatolievna", "Konstantinovna",
        "Leonidovna", "Genadievna", "Valeryevna", "Arsenievna", "Denisovna", "Stanislavovna", "Olegovna", "Yuryevna", "Maksimovna", "Igorevna"
    };
    const char* last_names[] = {
        "Wick", "Litvin", "Daniels", "Watson", "Tyson", "Davis", "Miller", "Wilson", "Taylor", "Moore",
        "Tamaev", "Tsal", "Pavlov", "Stroy", "Zolo", "Smith", "Johnson", "Williams", "Brown", "Jones",
        "Ivanov", "Petrov", "Sidorov", "Kuznetsov", "Popov", "Sokolov", "Lebedev", "Kozlov", "Novikov", "Morozov",
        "Volkov", "Alekseev", "Romanov", "Smirnov", "Fedorov", "Golubev", "Vinogradov", "Bogdanov", "Vorobyov", "Andreev",
        "Stepanov", "Yakovlev", "Sorokin", "Mikhailov", "Belov", "Orlov", "Kiselev", "Makarov", "Zaytsev", "Loginov",
        "Kovalev", "Korolev", "Gusev", "Titov", "Semenov", "Vasiliev", "Nikolaev", "Krylov", "Nikitin", "Isakov"
    };
    int first_index = rand() % 60;
    int patronymic_index = rand() % 60;
    int last_index = rand() % 60;
    snprintf(full_name, MAX_LENGTH, "%s %s %s", first_names[first_index], patronymics[patronymic_index], last_names[last_index]);
}

void generate_quailification(char* qualification) {
    const char* qualifications[] = { "First", "Second", "High" };
    int index = rand() % 3;
    strncpy(qualification, qualifications[index], MAX_LENGTH-1);
    qualification[MAX_LENGTH-1] = '\0';
}

void generate_home_address(char* home_address) {
    const char* home_addresses[] = { "Litvinburg", "Bikini Bottom", "Mondstadt", "Springfield", "Cheboksary", "Kanash", "Pukovo", "Tsivilsk", "Odintsovo", "Orehovo-Zuevo" };
    int index = rand() % 10;
    strncpy(home_address, home_addresses[index], MAX_LENGTH-1);
    home_address[MAX_LENGTH-1] = '\0';
}

void generate_date_birth(char* date_birth) {
    snprintf(date_birth, MAX_LENGTH, "%02d.%02d.%d", rand() % 28 + 1, rand() % 12 + 1, 1980 + rand() % 25);
}

void generate_phone_number(char* phone_number) {
    snprintf(phone_number, MAX_LENGTH, "+7%03d%03d%02d%02d", rand() % 900+100, rand() % 900+100, rand() % 90+10, rand()%90+10);
}

void generate_employment_date(char* employment_date) {
    snprintf(employment_date, MAX_LENGTH, "%02d.%02d.%d", rand() % 28 + 1, rand() % 12 + 1, 2010 + rand() % 14);
}

School* genArray(long n) {
    School* a = (School*)malloc(n * sizeof(School));
    if (!a) return NULL;
    for (long i = 0; i < n; i++) {
        generate_full_name(a[i].full_name);
        generate_quailification(a[i].qualification);
        generate_home_address(a[i].home_address);
        generate_date_birth(a[i].date_birth);
        generate_phone_number(a[i].phone_number);
        generate_employment_date(a[i].employment_date);
    }
    return a;
}

const char* options[] = { "DJB2", "SDBM", "ROT13" };

// DJB2
hash_type hash_1(const char* data) {
    unsigned long long hash = 5381;
    char c;
    while ((c = *data++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash;
}

// SDBM
hash_type hash_2(const char* data) {
    unsigned long long hash = 0;
    int c;
    while ((c = *data++)) {
        hash = c + (hash << 6) + (hash << 16) - hash;
    }
    return hash;
}

// ROT13
hash_type hash_3(const char* data) {
    unsigned int hash = 0;
    while (*data) {
        hash += (unsigned char)*data++;
        hash -= (hash << 13) | (hash >> 19);
    }
    return (hash_type)hash;
}

hash_func_type get_hash_func(const long option) {
    switch (option) {
        case 0: return hash_1;
        case 1: return hash_2;
        case 2: return hash_3;
        default:
            exit(1);
    }
}

HashTable* create_hash_table(const long capacity, const hash_func_type hash_func) {
    HashTable* table = malloc(sizeof(HashTable));
    if (!table) return NULL;
    
    table->capacity = capacity;
    table->hash_func = hash_func;
    table->size = 0;
    table->collisions = 0;
    table->entries = calloc(table->capacity, sizeof(HashTableEntry));
    if (!table->entries) {
        free(table);
        return NULL;
    }
    return table;
}

void destroy_hash_table(HashTable* table) {
    if (!table) return;

    for (long i = 0; i < table->capacity; i++) {
        if (table->entries[i].key != NULL) {
            // Освобождаем ключ, который был скопирован
            free(table->entries[i].key);

            // Освобождаем связанный список значений
            RecordNode* current = table->entries[i].head;
            while (current != NULL) {
                RecordNode* to_free = current;
                current = current->next;
                free(to_free);
            }
        }
    }
    free(table->entries);
    free(table);
}

void hash_table_set(HashTable* table, const char* key, void* value) {
    unsigned long long raw_hash = table->hash_func(key);
    long index = (long)(raw_hash % table->capacity);
    long original_index = index;
    // Линейное пробирование для поиска нужного слота
    while (table->entries[index].key != NULL && strcmp(table->entries[index].key, key) != 0) {
        table->collisions++;
        index = (index + 1) % table->capacity;
        if (index == original_index) { // Таблица заполнена
            return;
        }
    }

    // Создаем новый узел для списка значений
    RecordNode* newNode = (RecordNode*)malloc(sizeof(RecordNode));
    if (!newNode) return;
    newNode->value = value;
    newNode->next = NULL;

    if (table->entries[index].key == NULL) {
        // Новый ключ: вставляем в первый раз
        table->entries[index].key = strdup(key);
        if(!table->entries[index].key){
            free(newNode);
            return;
        }
        table->entries[index].head = newNode;
        table->size++;
    }
    else {
        newNode->next = table->entries[index].head;
        table->entries[index].head = newNode;
    }
}

// Поиск элемента. Возвращает указатель на голову списка значений.
RecordNode* hash_table_get(HashTable* table, const char* key) {
    unsigned long long raw_hash = table->hash_func(key);
    long index = (long)(raw_hash % table->capacity);
    long original_index = index;

    // Линейное пробирование
    while (table->entries[index].key != NULL) {
        if (strcmp(table->entries[index].key, key) == 0) {
            return table->entries[index].head; // Ключ найден
        }
        index = (index + 1) % table->capacity;
        if (index == original_index) {
            break; // Прошли полный круг
        }
    }
    return NULL; // Ключ не найден
}


// Функции вывода 

void print_school_data(const School* rec) {
    if (rec == NULL) return;
    printf("  Name: %s, Qual: %s, Address: %s, DoB: %s, Phone: %s, Hired: %s\n",
           rec->full_name, rec->qualification, rec->home_address,
           rec->date_birth, rec->phone_number, rec->employment_date);
}

void printSchoolArray(const School* arr, long n, const char* title) {
    printf("\n=== %s ===\n", title);
    for (long i = 0; i < n; i++) {
        printf("Element %ld: ", i + 1);
        print_school_data(&arr[i]);
    }
    printf("\n");
}