#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <stdlib.h>
#include <bits/stdc++.h>
using namespace std;

#define CAPACITY 50000 // Size of the Hash Table
#define ZONE_LENGTH 1.1 //length of a zone

typedef struct Lane{
    double length;
    int number;//# of zones
    double *zones;
    char id[20];//id of lane itself
    //char edge_id[20]; //id of edge container
    int neighborsIds[3];
    int numNeighbors ;
} Lane;

const char *getId(string str){
    string id = "";
    id = id + str.at(0) + str.at(1);
    
    for(int i = 2; i < str.length() - 1; i++){
        id = id + str.at(i);
        if(str.at(i + 1) == ' '){
            break;
        }
    }
    return id.c_str();
}

int getIndex(const char* str){
    int offset = 0;
    int index = 0;
    
    if(str[0] == '-'){
        index++; //skip '-'
        offset = 1;
    }
    index++; //skip 'E'
    char num[4];
    num[3] = '\0';
    int j = index;
    for(j = index; j < index + 3; j++){
        num[j - index] = str[j];
        if(str[j+1] == '_' && ((j - index + 1) < 3))
        {
            num[j - index + 1] = '\0';
            break;
        }
    }
    int x = atoi(num);
    x = (offset == 1) ? -x : x;
    int y = (2*abs(x) + offset);
    return y;
}

int adjust(int key){
    int newKey = key;

    #pragma region declare anchors
    int anchor0 = 143;
    int anchor1 = 152;
    //144, 145, 146, 147, 148, 149, 150, 151,
    int anchor2 = 173;
    int anchor3 = 180;
    //174, 175, 176, 177, 178, 179, 
    int anchor4 = 375;
    int anchor5 = 378;
    //376, 377,
    int anchor6 = 397;
    int anchor7 = 400;
    //398, 399, 
    int anchor8 = 831;
    int anchor9 = 834;
    //832, 833, 
    int anchor10 = 891;
    int anchor11 = 902;
    //892, 893, 894, 895, 896, 897, 898, 899, 900, 901, 
    int anchor12 = 933;
    int anchor13 = 948;
    //934, 935, 936, 937, 938, 939, 940, 941, 942, 943, 944, 945, 946, 947
    #pragma endregion
    if(key <= anchor0){
        return key;
    }
    else if(key >= anchor1 && key <= anchor2){
        newKey = key - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor3 && key <= anchor4){
        newKey = key - (anchor3 - anchor2 - 1) - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor5 && key <= anchor6){
        newKey = key - (anchor5 - anchor4 - 1) 
                     - (anchor3 - anchor2 - 1) 
                     - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor7 && key <= anchor8){
        newKey = key - (anchor7 - anchor6 - 1)
                     - (anchor5 - anchor4 - 1) 
                     - (anchor3 - anchor2 - 1) 
                     - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor9 && key <= anchor10){
        newKey = key - (anchor9 - anchor8 - 1)
                     - (anchor7 - anchor6 - 1)
                     - (anchor5 - anchor4 - 1) 
                     - (anchor3 - anchor2 - 1) 
                     - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor11 && key <= anchor12){
        newKey = key - (anchor11 - anchor10 - 1)
                     - (anchor9 - anchor8 - 1)
                     - (anchor7 - anchor6 - 1)
                     - (anchor5 - anchor4 - 1) 
                     - (anchor3 - anchor2 - 1) 
                     - (anchor1 - anchor0 - 1);
    }
    else if(key >= anchor13){
        newKey = key - (anchor13 - anchor12 - 1)
                     - (anchor11 - anchor10 - 1)
                     - (anchor9 - anchor8 - 1)
                     - (anchor7 - anchor6 - 1)
                     - (anchor5 - anchor4 - 1) 
                     - (anchor3 - anchor2 - 1) 
                     - (anchor1 - anchor0 - 1);
    }
    return newKey;
}
 
unsigned long hash_function(const char* str) {
    unsigned long i = 0;
    int y = getIndex(str);

    y = adjust(y);

    return y;
    //for (int j=0; str[j]; j++)
    //    i += str[j];
    //return i % CAPACITY;
}
 
typedef struct Ht_item Ht_item;
 
// Define the Hash Table Item here
struct Ht_item {
    char* key;
    char* value;
};
 
 
typedef struct LinkedList LinkedList;
 
// Define the Linkedlist here
struct LinkedList {
    Ht_item* item; 
    LinkedList* next;
};
 
 
typedef struct HashTable HashTable;
 
// Define the Hash Table here
struct HashTable {
    // Contains an array of pointers
    // to items
    Ht_item** items;
    LinkedList** overflow_buckets;
    int size;
    int count;
};
 
 
static LinkedList* allocate_list () {
    // Allocates memory for a Linkedlist pointer
    LinkedList* list = (LinkedList*) malloc (sizeof(LinkedList));
    return list;
}
 
static LinkedList* linkedlist_insert(LinkedList* list, Ht_item* item) {
    // Inserts the item onto the Linked List
    if (!list) {
        LinkedList* head = allocate_list();
        head->item = item;
        head->next = NULL;
        list = head;
        return list;
    } 
     
    else if (list->next == NULL) {
        LinkedList* node = allocate_list();
        node->item = item;
        node->next = NULL;
        list->next = node;
        return list;
    }
 
    LinkedList* temp = list;
    while (temp->next->next) {
        temp = temp->next;
    }
     
    LinkedList* node = allocate_list();
    node->item = item;
    node->next = NULL;
    temp->next = node;
     
    return list;
}
 
static Ht_item* linkedlist_remove(LinkedList* list) {
    // Removes the head from the linked list
    // and returns the item of the popped element
    if (!list)
        return NULL;
    if (!list->next)
        return NULL;
    LinkedList* node = list->next;
    LinkedList* temp = list;
    temp->next = NULL;
    list = node;
    Ht_item* it = NULL;
    memcpy(temp->item, it, sizeof(Ht_item));
    free(temp->item->key);
    free(temp->item->value);
    free(temp->item);
    free(temp);
    return it;
}
 
static void free_linkedlist(LinkedList* list) {
    LinkedList* temp = list;
    while (list) {
        temp = list;
        list = list->next;
        free(temp->item->key);
        free(temp->item->value);
        free(temp->item);
        free(temp);
    }
}
 
static LinkedList** create_overflow_buckets(HashTable* table) {
    // Create the overflow buckets; an array of linkedlists
    LinkedList** buckets = (LinkedList**) calloc (table->size, sizeof(LinkedList*));
    for (int i=0; i<table->size; i++)
        buckets[i] = NULL;
    return buckets;
}
 
static void free_overflow_buckets(HashTable* table) {
    // Free all the overflow bucket lists
    LinkedList** buckets = table->overflow_buckets;
    for (int i=0; i<table->size; i++)
        free_linkedlist(buckets[i]);
    free(buckets);
}
 
 
Ht_item* create_item(std::string strKey, std::string strValue) {
    const char* key = strKey.c_str();
    const char* value = strValue.c_str();
    // Creates a pointer to a new hash table item
    Ht_item* item = (Ht_item*) malloc (sizeof(Ht_item));
    item->key = (char*) malloc (strlen(key) + 1);
    item->value = (char*) malloc (strlen(value) + 1);
     
    strcpy(item->key, key);
    strcpy(item->value, value);
 
    return item;
}
 
HashTable* create_table(int size) {
    // Creates a new HashTable
    HashTable* table = (HashTable*) malloc (sizeof(HashTable));
    table->size = size;
    table->count = 0;
    table->items = (Ht_item**) calloc (table->size, sizeof(Ht_item*));
    for (int i=0; i<table->size; i++)
        table->items[i] = NULL;
    table->overflow_buckets = create_overflow_buckets(table);
 
    return table;
}
 
void free_item(Ht_item* item) {
    // Frees an item
    free(item->key);
    free(item->value);
    free(item);
}
 
void free_table(HashTable* table) {
    // Frees the table
    for (int i=0; i<table->size; i++) {
        Ht_item* item = table->items[i];
        if (item != NULL)
            free_item(item);
    }
 
    free_overflow_buckets(table);
    free(table->items);
    free(table);
}
 
void handle_collision(HashTable* table, unsigned long index, Ht_item* item) {
    LinkedList* head = table->overflow_buckets[index];
 
    if (head == NULL) {
        // We need to create the list
        head = allocate_list();
        head->item = item;
        table->overflow_buckets[index] = head;
        return;
    }
    else {
        // Insert to the list
        table->overflow_buckets[index] = linkedlist_insert(head, item);
        return;
    }
}


 
void ht_insert(HashTable* table, std::string strKey, std::string strValue) {
    const char* key = strKey.c_str();
    const char* value = strValue.c_str();
    // Create the item
    Ht_item* item = create_item(key, value);
 
    // Compute the index
    unsigned long index = hash_function(key);
 
    Ht_item* current_item = table->items[index];
     
    if (current_item == NULL) {
        // Key does not exist.
        if (table->count == table->size) {
            // Hash Table Full
            printf("Insert Error: Hash Table is full\n");
            // Remove the create item
            free_item(item);
            return;
        }
         
        // Insert directly
        table->items[index] = item; 
        table->count++;
    }
 
    else {
            // Scenario 1: We only need to update value
            if (strcmp(current_item->key, key) == 0) {
                strcpy(table->items[index]->value, value);
                return;
            }
     
        else {
            std::cout<<"Collision"<<std::endl;
            // Scenario 2: Collision
            handle_collision(table, index, item);
            return;
        }
    }
}
 
char* ht_search(HashTable* table, std::string strKey) {
    const char* key = strKey.c_str();
    
    // Searches the key in the hashtable
    // and returns NULL if it doesn't exist
    int index = hash_function(key);
    Ht_item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];
 
    // Ensure that we move to items which are not NULL
    while (item != NULL) {
        if (strcmp(item->key, key) == 0)
            return item->value;
        if (head == NULL)
            return NULL;
        item = head->item;
        head = head->next;
    }
    return NULL;
}
 
void ht_delete(HashTable* table, std::string strKey) {
    const char* key = strKey.c_str();
    
    // Deletes an item from the table
    int index = hash_function(key);
    Ht_item* item = table->items[index];
    LinkedList* head = table->overflow_buckets[index];
 
    if (item == NULL) {
        // Does not exist. Return
        return;
    }
    else {
        if (head == NULL && strcmp(item->key, key) == 0) {
            // No collision chain. Remove the item
            // and set table index to NULL
            table->items[index] = NULL;
            free_item(item);
            table->count--;
            return;
        }
        else if (head != NULL) {
            // Collision Chain exists
            if (strcmp(item->key, key) == 0) {
                // Remove this item and set the head of the list
                // as the new item
                 
                free_item(item);
                LinkedList* node = head;
                head = head->next;
                node->next = NULL;
                table->items[index] = create_item(node->item->key, node->item->value);
                free_linkedlist(node);
                table->overflow_buckets[index] = head;
                return;
            }
 
            LinkedList* curr = head;
            LinkedList* prev = NULL;
             
            while (curr) {
                if (strcmp(curr->item->key, key) == 0) {
                    if (prev == NULL) {
                        // First element of the chain. Remove the chain
                        free_linkedlist(head);
                        table->overflow_buckets[index] = NULL;
                        return;
                    }
                    else {
                        // This is somewhere in the chain
                        prev->next = curr->next;
                        curr->next = NULL;
                        free_linkedlist(curr);
                        table->overflow_buckets[index] = head;
                        return;
                    }
                }
                curr = curr->next;
                prev = curr;
            }
 
        }
    }
}
 
void print_search(HashTable* table, std::string strKey) {
    const char* key = strKey.c_str();
    
    char* val;
    if ((val = ht_search(table, key)) == NULL) {
        printf("%s does not exist\n", key);
        return;
    }
    else {
        printf("Key:%s, Value:%s\n", key, val);
    }
}
 
void print_table(HashTable* table) {
    printf("\n-------------------\n");
    for (int i=0; i<table->size; i++) {
        if (table->items[i]) {
            printf("Index:%d, Key:%s, Value:%s", i, table->items[i]->key, table->items[i]->value);
            if (table->overflow_buckets[i]) {
                printf(" => Overflow Bucket => ");
                LinkedList* head = table->overflow_buckets[i];
                while (head) {
                    printf("Key:%s, Value:%s ", head->item->key, head->item->value);
                    head = head->next;
                }
            }
            printf("\n");
        }
    }
    printf("-------------------\n");
}

 
