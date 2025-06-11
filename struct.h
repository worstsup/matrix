#ifndef DATABASE_H
#define DATABASE_H

#include <stdio.h>

#define MAX_LENGTH 40

// Структура для хранения данных об объекте
typedef struct {
    char full_name[MAX_LENGTH];
    char qualification[MAX_LENGTH];
    char home_address[MAX_LENGTH];
    char date_birth[MAX_LENGTH];
    char phone_number[MAX_LENGTH];
    char employment_date[MAX_LENGTH];
} School;

// Узел для хранения записей с одинаковым ключом
typedef struct RecordNode {
    void* value; // Указатель на структуру School
    struct RecordNode* next;
} RecordNode;

// Запись в хэш-таблице
typedef struct HashTableEntry {
    char* key;          // Ключ (full_name)
    RecordNode* head;   // Голова связанного списка записей
} HashTableEntry;

// Типы для хэш-функций
typedef unsigned long long hash_type;
typedef hash_type (*hash_func_type)(const char*);

// Структура хэш-таблицы
typedef struct HashTable {
    HashTableEntry* entries;
    hash_func_type hash_func;
    long capacity;      // Вместимость таблицы
    long size;          // Текущее количество уникальных ключей
    long collisions;    // Количество коллизий
} HashTable;


hash_type hash_1(const char*);
hash_type hash_2(const char*);
hash_type hash_3(const char*);
hash_func_type get_hash_func(long option);
extern const char* options[3];

HashTable* create_hash_table(long capacity, hash_func_type hash_func);
void destroy_hash_table(HashTable* hash_table);

void hash_table_set(HashTable* hash_table, const char* key, void* value);
RecordNode* hash_table_get(HashTable* hash_table, const char* key);

School* genArray(long n);
void print_school_data(const School* rec);
void printSchoolArray(const School* arr, long n, const char* title);

#endif
