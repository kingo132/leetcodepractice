//
//  leetcode460.c
//  myleetcodetest
//
//  Created by jason on 2024-07-09.
//
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "leetcode460.h"


typedef struct HashNode {
    int key;
    int val;
    int isOccupied;
    int cnt;
    struct HashNode* prev;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode* hash;
    int hashMaxSize;
    int hashCurSize;
    HashNode* head;
    HashNode* tail;
    int capacity;
} LFUCache;

void dumpListLT460(const char* prefix, HashNode* head, HashNode* tail) {
    return;
    printf("%s\n", prefix);
    printf("--> Head -> ");
    while (head) {
        printf("(%d,%d:%d) -> ", head->key, head->val, head->cnt);
        head = head->next;
    }
    printf("\n");
    printf("--> Tail -> ");
    while (tail) {
        printf("(%d,%d:%d) -> ", tail->key, tail->val, tail->cnt);
        tail = tail->prev;
    }
    printf("\n");
}

LFUCache* lFUCacheCreate(int capacity) {
    LFUCache* lc = (LFUCache*)malloc(sizeof(LFUCache));
    lc->hash = (HashNode*)malloc(capacity * 3 * sizeof(HashNode));
    for (int i = 0; i < capacity * 3; i++) {
        lc->hash[i].key = 0;
        lc->hash[i].val = 0;
        lc->hash[i].isOccupied = 0;
        lc->hash[i].cnt = 0;
        lc->hash[i].prev = NULL;
        lc->hash[i].next = NULL;
    }
    lc->hashMaxSize = capacity * 3;
    lc->hashCurSize = 0;
    lc->head = NULL;
    lc->tail = NULL;
    lc->capacity = capacity;
    return lc;
}

void LFUMoveToHead(LFUCache* obj, int k) {
    if (&(obj->hash[k]) != obj->head) {
        // break the link
        if (obj->hash[k].prev) {
            obj->hash[k].prev->next = obj->hash[k].next;
        }
        if (obj->hash[k].next) {
            obj->hash[k].next->prev = obj->hash[k].prev;
        }

        if (obj->tail == &(obj->hash[k])) {
            if (obj->hash[k].next) {
                obj->tail = obj->hash[k].next;
            } else if (obj->hash[k].prev) {
                obj->tail = obj->hash[k].prev;
            } else {
                obj->tail = &(obj->hash[k]);
            }
        }

        obj->hash[k].next = obj->head;
        obj->hash[k].prev = NULL;
        if (obj->head != NULL) { // Add this check
            obj->head->prev = &(obj->hash[k]);
        }

        obj->head = &(obj->hash[k]);
    }
}

void LFUMoveToTail(LFUCache* obj, int k) {
    if (&(obj->hash[k]) != obj->tail) {
        // break the link
        if (obj->hash[k].prev) {
            obj->hash[k].prev->next = obj->hash[k].next;
        }
        if (obj->hash[k].next) {
            obj->hash[k].next->prev = obj->hash[k].prev;
        }

        if (obj->head == &(obj->hash[k])) {
            if (obj->hash[k].next) {
                obj->head = obj->hash[k].next;
            } else {
                obj->tail = &(obj->hash[k]);
            }
        }

        obj->hash[k].prev = obj->tail;
        obj->hash[k].next = NULL;
        if (obj->tail != NULL) { // Add this check
            obj->tail->next = &(obj->hash[k]);
        }

        obj->tail = &(obj->hash[k]);
    }
}

void LFURemoveTail(LFUCache* obj) {
    if (obj->tail) {
        obj->tail->isOccupied = 0;

        if (obj->tail->prev) {
            obj->tail->prev->next = NULL;
        }
        obj->tail->next = NULL;
        HashNode* t = obj->tail->prev;
        obj->tail->prev = NULL;
        obj->tail = t;
        obj->hashCurSize--;
    }
}

void LFURemoveHead(LFUCache* obj) {
    if (obj->head) {
        obj->head->isOccupied = 0;

        if (obj->tail == obj->head) {
            obj->tail = NULL;
        }

        if (obj->head->next) {
            obj->head->next->prev = NULL;
        }
        obj->head->prev = NULL;
        HashNode* t = obj->head->next;
        obj->head->next = NULL;
        obj->head = t;

        obj->hashCurSize--;
    }
}

void removeNode(LFUCache* obj, HashNode* p) {
    if (p->prev) {
        p->prev->next = p->next;
    }
    if (p->next) {
        p->next->prev = p->prev;
    }
    if (obj->head == p) {
        obj->head = p->next;
    }
    if (obj->tail == p) {
        obj->tail = p->prev;
    }
}

void insertNodeBefore(LFUCache* obj, HashNode* node, HashNode* befo) {
    if (node == befo) {
        return;
    }
    node->next = befo;
    if (befo) {
        node->prev = befo->prev;
        if (befo->prev) {
            befo->prev->next = node;
        }
        if (obj->head == befo) {
            obj->head = node;
        }
        befo->prev = node;
    } else {
        node->prev = obj->tail;
        if (obj->tail) {
            obj->tail->next = node;
        }
        obj->tail = node;
        if (obj->head == NULL) {
            obj->head = node;
        }
    }
}

void adjustNodePos(LFUCache* obj, HashNode* node) {
    //HashNode* p = node->next;
    //while (p && p->cnt <= node->cnt) {
    //    p = p->next;
    //}
    HashNode* p = obj->tail;
    if (p->cnt > node->cnt) {
        while (p->prev && p->prev->cnt > node->cnt) {
            p = p->prev;
        }
    } else {
        p = NULL;
    }
    
    if (p) {
        if (p != node->next) {
            // break the link
            removeNode(obj, node);
            insertNodeBefore(obj, node, p);
        }
    } else {
        if (obj->tail != node) {
            // break the link
            removeNode(obj, node);

            // put after tail
            insertNodeBefore(obj, node, NULL);
        }
    }
}

int lFUCacheGet(LFUCache* obj, int key) {
    //printf("Get %d\n", key);
    dumpListLT460("Before get: ", obj->head, obj->tail);
    int k = key % obj->hashMaxSize;
    for (int i = 0; i < obj->capacity; i++) {
        if (obj->hash[k].isOccupied == 0) {
            return -1;
        } else if (obj->hash[k].key == key) {
            obj->hash[k].cnt++;

            adjustNodePos(obj, &(obj->hash[k]));
            dumpListLT460("After get: ", obj->head, obj->tail);
            return obj->hash[k].val;
        }
        k = (k + 1) % obj->hashMaxSize;
    }
    return -1;
}

void lFUCachePut(LFUCache* obj, int key, int value) {
    //printf("Put %d,%d\n", key, value);
    dumpListLT460("Before put: ", obj->head, obj->tail);
    int k = key % obj->hashMaxSize;
    for (int i = 0; i < obj->capacity; i++) {
        if (obj->hash[k].isOccupied == 0) {
            break;
        } else if (obj->hash[k].key == key) {
            obj->hash[k].cnt++;
            obj->hash[k].val = value;

            // move to head
            adjustNodePos(obj, &(obj->hash[k]));
            dumpListLT460("After put: ", obj->head, obj->tail);
            return;
        }
        k = (k + 1) % obj->hashMaxSize;
    }

    if (obj->hashCurSize >= obj->capacity) {
        LFURemoveHead(obj);
        dumpListLT460("After remove: ", obj->head, obj->tail);
    }
    
    k = key % obj->hashMaxSize;
    for (int i = 0; i < obj->capacity; i++) {
        if (obj->hash[k].isOccupied == 0) {
            obj->hash[k].key = key;
            obj->hash[k].val = value;
            obj->hash[k].isOccupied = 1;
            obj->hash[k].cnt = 1;

            if (obj->head == NULL) {
                obj->head = &(obj->hash[k]);
            }
            if (obj->tail == NULL) {
                obj->tail = &(obj->hash[k]);
            } else {
                HashNode* p = obj->tail;
                if (p->cnt > 1) {
                    while (p->prev && p->prev->cnt > 1) {
                        p = p->prev;
                    }
                } else {
                    p = NULL;
                }
                
                insertNodeBefore(obj, &(obj->hash[k]), p);
            }

            obj->hashCurSize++;
            break;
        }
        k = (k + 1) % obj->hashMaxSize;
    }
    dumpListLT460("After put: ", obj->head, obj->tail);
}

void lFUCacheFree(LFUCache* obj) {
    free(obj->hash);
    free(obj);
}

/**
 * Your LFUCache struct will be instantiated and called as such:
 * LFUCache* obj = lFUCacheCreate(capacity);
 * int param_1 = lFUCacheGet(obj, key);
 
 * lFUCachePut(obj, key, value);
 
 * lFUCacheFree(obj);
*/
