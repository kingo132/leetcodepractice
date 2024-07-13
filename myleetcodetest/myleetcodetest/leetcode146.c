//
//  leetcode146.c
//  myleetcodetest
//
//  Created by jason on 2024-07-05.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode146.h"


typedef struct HASHNODE {
    int k;
    int v;
    int isOccupied;
    struct HASHNODE* next;
    struct HASHNODE* prev;
} HASHNODE;

typedef struct {
    HASHNODE* hash;
    int hashMaxSize;
    int hashCurSize;
    int capacity;
    HASHNODE* head;
    HASHNODE* tail;
} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* lru = (LRUCache*)malloc(sizeof(LRUCache));
    lru->hashMaxSize = capacity * 3;
    lru->hash = (HASHNODE*)malloc(lru->hashMaxSize * sizeof(HASHNODE));
    for (int i = 0; i < lru->hashMaxSize; i++) {
        lru->hash[i].k = 0;
        lru->hash[i].v = 0;
        lru->hash[i].isOccupied = 0;
        lru->hash[i].next = NULL;
        lru->hash[i].prev = NULL;
    }
    lru->hashCurSize = 0;
    lru->capacity = capacity;
    lru->head = NULL;
    lru->tail = NULL;
    return lru;
}

void dumpListLT146(const char* prefix, int d, int v, HASHNODE* head) {
    return;
    printf("%s %d,%d: ", prefix, d, v);
    while (head) {
        printf("(%d,%d,%d) ", head->k, head->v, head->isOccupied);
        head = head->next;
    }
    printf("\n");
}

int lRUCacheGet(LRUCache* obj, int key) {
    dumpListLT146("get1", key, -1, obj->head);
    int k = key % obj->hashMaxSize;
    for (int i = 0; i < obj->hashMaxSize; i++) {
        //printf("Try k: %d\n", k);
        if (obj->hash[k].isOccupied == 0) {
            //printf("Not occupied: %d for key %d\n", k, key);
            return -1;
        }
        if (obj->hash[k].k == key) {
            // Move node to head
            if (obj->head != &obj->hash[k]) {
                if (obj->tail == &obj->hash[k]) {
                    obj->tail = obj->hash[k].prev;
                }
                //dumpList("get21", key, obj->head);
                if (obj->hash[k].prev) {
                    obj->hash[k].prev->next = obj->hash[k].next;
                }
                if (obj->hash[k].next) {
                    obj->hash[k].next->prev = obj->hash[k].prev;
                }
                //dumpList("get22", key, obj->head);
                obj->hash[k].next = obj->head;
                //dumpList("get23", key, obj->head);
                obj->head->prev = &obj->hash[k];
                //dumpList("get24", key, obj->head);
                obj->head = &obj->hash[k];
                dumpListLT146("get2", -1, key, obj->head);
            }
            return obj->hash[k].v;
        }
        k = (k + 1) % obj->hashMaxSize;
    }
    return -1;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    dumpListLT146("put1", key, value, obj->head);
    int k = key % obj->hashMaxSize;
    int status = -1; // -1 no seat no duplicate, 0 have seat, 1 have duplicate
    for (int i = 0; i < obj->hashMaxSize; i++) {
        if (obj->hash[k].isOccupied == 0) {
            status = 0;
            break;
        } else if (obj->hash[k].k == key) {
            status = 1;
            break;
        }
        k = (k + 1) % obj->hashMaxSize;
    }
    if (status == 1) { // duplicate
        obj->hash[k].v = value;
        if (obj->head != &obj->hash[k]) {
            // move to head
            if (obj->tail == &obj->hash[k]) {
                obj->tail = obj->hash[k].prev;
            }
            if (obj->hash[k].prev) {
                obj->hash[k].prev->next = obj->hash[k].next;
            }
            if (obj->hash[k].next) {
                obj->hash[k].next->prev = obj->hash[k].prev;
            }
            obj->hash[k].next = obj->head;
            obj->head->prev = &obj->hash[k];
            obj->head = &obj->hash[k];
            dumpListLT146("put4", key, value, obj->head);
        }
        dumpListLT146("put2", key, value, obj->head);
        return;
    }
    
    if (status == 0) { // have seat
        if (obj->hashCurSize == obj->capacity) {
            // remove tail
            if (obj->tail) {
                obj->tail->isOccupied = 0;
                if (obj->tail->prev) {
                    obj->tail->prev->next = NULL;
                }
                if (obj->head == obj->tail) {
                    obj->head = NULL;
                }
                obj->tail = obj->tail->prev;
            }
            obj->hashCurSize--;
        }
        dumpListLT146("put3", key, value, obj->head);
        obj->hash[k].k = key;
        obj->hash[k].v = value;
        obj->hash[k].isOccupied = 1;
        obj->hash[k].next = obj->head;
        if (obj->head) {
            obj->head->prev = &obj->hash[k];
        }
        if (obj->tail == NULL) {
            obj->tail = &obj->hash[k];
        }
        obj->head = &obj->hash[k];

        obj->hashCurSize++;
        //printf("Put %d on %d\n", key, k);
        dumpListLT146("put4", key, value, obj->head);
        return;
    }

    printf("Hash is full!\n");
}

void lRUCacheFree(LRUCache* obj) {
    free(obj->hash);
    free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/
