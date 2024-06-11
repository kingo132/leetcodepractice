#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}
// -----> Bubble Sort
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = 1;
            }
        }

        if (! swapped)
            break;
    }
}
// -----> Selection Sort
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        if(min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }
}
// -----> Insertion Sort
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
// -----> Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];

    int i = (low - 1);
    for (int j = low; j <= high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// -----> Heap Sort
void heapify(int arr[], int N, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < N && arr[left] > arr[largest])
        largest = left;

    if (right < N && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, N, largest);
    }
}
void heapSort(int arr[], int N) {
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(arr, N, i);

    for (int i = N - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }
}

// -----> Hash table
#define TABLE_SIZE 10

typedef struct {
    int key; // Can be char[]
    int value;
    int is_occupied;
} HashTableEntry;

HashTableEntry hashTable[TABLE_SIZE];

unsigned int hash(int key) {
    return key % TABLE_SIZE;
}

void init_table() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].is_occupied = 0;
    }
}

int insert(int key, int value) {
    unsigned int index = hash(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int try = (index + i) % TABLE_SIZE;
        if (!hashTable[try].is_occupied) {
            hashTable[try].key = key;
            hashTable[try].value = value;
            hashTable[try].is_occupied = 1;
            return 1;  // Inserted successfully
        }
    }
    return 0;  // Hash table is full
}

int search(int key, int *value) {
    unsigned int index = hash(key);
    for (int i = 0; i < TABLE_SIZE; i++) {
        unsigned int try = (index + i) % TABLE_SIZE;
        if (hashTable[try].is_occupied && hashTable[try].key == key) {
            *value = hashTable[try].value;
            return 1;  // Key found
        }
    }
    return 0;  // Key not found
}

// -----> Monotone Stack
#define MAX 100

int stack[MAX], top = -1;

int is_full() {
    return top == MAX - 1;
}

int is_empty() {
    return top == -1;
}

void push(int val) {
    if (is_full()) {
        printf("Stack overflow\n");
        return;
    }
    // push的时候清理栈顶
    while (top != -1 && stack[top] >= val)
        top--;
    stack[++top] = val;
}

int pop() {
    if (is_empty()) {
        printf("Stack underflow\n");
        return -1; // Indicate an error
    }
    return stack[top--];
}

int peek() {
    if (is_empty()) {
        printf("Stack is empty\n");
        return -1; // Indicate an error
    }
    return stack[top];
}

// -----> Priority Queue
// 数据压缩：赫夫曼编码算法；
// 最短路径算法：Dijkstra 算法；
// 最小生成树算法：Prim 算法；
// 排序问题：查找第 k 个最小元素。
#define MAX 100

int heap[MAX];
int size = 0;

void insertPQ(int value) {
    if (size >= MAX) {
        printf("Priority Queue overflow\n");
        return;
    }
    heap[size] = value;
    int i = size;
    size++;
    // (i-1)/2 是父节点的位置
    while (i != 0 && heap[(i - 1) / 2] < heap[i]) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extract_max() {
    if (size <= 0) {
        printf("Priority Queue underflow\n");
        return -1;
    }
    int max = heap[0];
    heap[0] = heap[size - 1];
    size--;
    int i = 0;
    // 把左右节点中大的往上移 
    while ((2 * i + 1) < size) {
        int largest = i;
        int left = 2 * i + 1; // 左子节点
        int right = 2 * i + 2; // 右子节点
        if (left < size && heap[left] > heap[largest])
            largest = left;
        if (right < size && heap[right] > heap[largest])
            largest = right;
        if (largest != i) {
            swap(&heap[i], &heap[largest]);
            i = largest;
        } else {
            break;
        }
    }
    return max;
}

// -----> Huffman Coding

// -----> KMP
void computeLPSArray(char* pat, int M, int* lps) {
    int len = 0; // length of the previous longest prefix suffix
    lps[0] = 0;  // lps[0] is always 0
    int i = 1;

    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

char* KMPSearch(char* pat, char* txt) {
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M];

    // Preprocess the pattern (calculate lps array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt
    int j = 0; // index for pat
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            return &txt[i - j]; // Return the pointer to the first occurrence
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return NULL; // No match found
}

// -----> Disjoint Set
#define MAX 100

int parent[MAX];
int rank[MAX];

void makeSet(int n) {
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]); // Path compression
    }
    return parent[x];
}

void unionSets(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
}

// -----> Minimal Spanning Tree - Prim
#define V 5 // Number of vertices in the graph

int minKey(int key[], bool mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

void primMST(int graph[V][V]) {
    int parent[V]; // Array to store constructed MST
    int key[V];    // Key values used to pick minimum weight edge in cut
    bool mstSet[V]; // To represent set of vertices not yet included in MST

    // Initialize all keys as INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = false;

    // Always include first 1st vertex in MST.
    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    for (int count = 0; count < V - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = true;
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }
}

// -----> Dijkstra
#define V 5 // Number of vertices in the graph

int minDistance(int dist[], bool sptSet[]) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void dijkstra(int graph[V][V], int src) {
    int dist[V]; // The output array. dist[i] will hold the shortest distance from src to i
    bool sptSet[V]; // sptSet[i] will be true if vertex i is included in the shortest path tree

    // Initialize all distances as INFINITE and stpSet[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed
        int u = minDistance(dist, sptSet);

        // Mark the picked vertex as processed
        sptSet[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex
        for (int v = 0; v < V; v++)
            // Update dist[v] if it is not in sptSet, there is an edge from u to v, and total weight of path from src to v through u is smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
}

// Another version, which use priority queue

#define V 5 // Number of vertices in the graph
#define MAX 100

int heap[MAX];
int sizeHeap = 0;

typedef struct {
    int vertex;
    int distance;
} Node;

Node nodes[V]; // Array to store the nodes corresponding to heap indices

void insertHead(int index) {
    if (sizeHeap >= MAX) {
        printf("Priority Queue overflow\n");
        return;
    }
    heap[sizeHeap] = index;
    int i = sizeHeap;
    sizeHeap++;
    while (i != 0 && nodes[heap[(i - 1) / 2]].distance > nodes[heap[i]].distance) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

int extract_min() {
    if (sizeHeap <= 0) {
        printf("Priority Queue underflow\n");
        return -1;
    }
    int min_index = heap[0];
    heap[0] = heap[sizeHeap - 1];
    sizeHeap--;
    int i = 0;
    while ((2 * i + 1) < sizeHeap) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        if (left < sizeHeap && nodes[heap[left]].distance < nodes[heap[smallest]].distance)
            smallest = left;
        if (right < sizeHeap && nodes[heap[right]].distance < nodes[heap[smallest]].distance)
            smallest = right;
        if (smallest != i) {
            swap(&heap[i], &heap[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return min_index;
}

/*
while (Haven’t found the End) {
    Node = PQ.RemoveFirst();

    for each (neighbors of Node) {
        // 1. Compute the new cost
        NewCost = Node.Cost + neighbor.Weight;
        if (NewCost < neighbor.Cost) {
            neighbor.Cost = NewCost;
            neighbor.Previous = Node;
        }

        // 2. Add Nodes to the priority queue
        if (neighbor is not visited) {
            Set neighbor as visited;
            PQ.Add(neighbor, Neighbor.Cost);
        }
    }
}
*/
void dijkstraPQ(int graph[V][V], int src) {
    int dist[V]; // Distance from source to each vertex
    bool visited[V]; // Visited vertices
    int parent[V]; // To store the shortest path tree

    // Initialize distances, visited and parent
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1; // Initialize parent array
        nodes[i].vertex = i;
        nodes[i].distance = INT_MAX;
    }

    dist[src] = 0;
    nodes[src].distance = 0;
    insertPQ(src);

    while (size > 0) {
        int u = extract_min();
        visited[u] = true; // Mark this vertex as processed

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !visited[v]) {
                int new_cost = dist[u] + graph[u][v];
                if (new_cost < dist[v]) {
                    dist[v] = new_cost; // If A*, add heuristic cost
                    parent[v] = u;
                    nodes[v].distance = new_cost;
                    insertPQ(v);
                }
            }
        }
    }
}

void dijkstra_without_minheap(int graph[V][V], int src) {
    int dist[V]; // Distance from source to each vertex
    bool visited[V]; // Visited vertices
    int parent[V]; // To store the shortest path tree

    // Initialize distances, visited and parent
    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[src] = 0;
    int que[V];
    int front = 0, tail = 0;
    que[tail++] = src;

    while (front != tail) {
        int u = que[front++];
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !visited[v]) {
                int new_cost = dist[u] + graph[u][v];
                if (new_cost < dist[v]) {
                    dist[v] = new_cost;
                    parent[v] = u;
                    que[tail++] = v;

                    // Sort the queue
                    for (int i = tail - 1; i > front; i--) {
                        if (dist[que[i]] < dist[que[i - 1]]) {
                            int temp = que[i];
                            que[i] = que[i - 1];
                            que[i - 1] = temp;
                        } else {
                            break;
                        }
                    }
                }
            }
        }
    }
}

// -----> Backtracking

// -----> Backpack Problem

// -----> Graph - Breadth First Search
#define MAX 100

// Function to perform BFS on the graph
void BFS(int graph[MAX][MAX], int startVertex, int numVertices) {
    bool visited[MAX] = {false}; // Array to keep track of visited vertices
    int queue[MAX];              // Queue to manage BFS
    int front = 0, rear = 0;     // Queue front and rear pointers

    visited[startVertex] = true;
    queue[rear++] = startVertex;

    while (front < rear) {
        int currentVertex = queue[front++];

        for (int i = 0; i < numVertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = true;
                queue[rear++] = i;
            }
        }
    }
}

// -----> Graph - Depth First Search (Recursive)
void DFS(int graph[MAX][MAX], int vertex, bool visited[], int numVertices) {
    visited[vertex] = true;

    for (int i = 0; i < numVertices; i++) {
        if (graph[vertex][i] == 1 && !visited[i]) {
            DFS(graph, i, visited, numVertices);
        }
    }
}

// Non-Recursive
#define MAX 100

void DFSNonRecursive(int graph[MAX][MAX], int startVertex, int numVertices) {
    bool visited[MAX] = {false};
    int stack[MAX];
    int top = -1;

    stack[++top] = startVertex;

    while (top != -1) {
        int currentVertex = stack[top--];

        if (!visited[currentVertex]) {
            visited[currentVertex] = true;
        }

        for (int i = 0; i < numVertices; i++) {
            if (graph[currentVertex][i] == 1 && !visited[i]) {
                stack[++top] = i;
            }
        }
    }
}

// -----> Tree - Pre-order Search
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} TreeNode;

// Recursive pre-order traversal
void preorderRecursive(TreeNode* root) {
    if (root == NULL)
        return;

    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

// Non-Recursive
void preorderNonRecursive(TreeNode* root) {
    if (root == NULL)
        return;

    TreeNode* stack[MAX];
    int top = -1;

    stack[++top] = root;

    while (top != -1) {
        TreeNode* node = stack[top--];

        if (node->right != NULL) {
            stack[++top] = node->right;
        }
        if (node->left != NULL) {
            stack[++top] = node->left;
        }
    }
}

// -----> AVL Tree Insert
struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
    int height;
};

int height(struct TreeNode* node) {
    return node ? node->height : 0;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct TreeNode* rightRotate(struct TreeNode* y) {
    struct TreeNode* x = y->left;
    struct TreeNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

struct TreeNode* leftRotate(struct TreeNode* x) {
    struct TreeNode* y = x->right;
    struct TreeNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(struct TreeNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

struct TreeNode* insertIntoAVL(struct TreeNode* node, int val) {
    if (!node) {
        node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
        node->val = val;
        node->left = node->right = NULL;
        node->height = 1;
        return node;
    }

    if (val < node->val)
        node->left = insertIntoAVL(node->left, val);
    else if (val > node->val)
        node->right = insertIntoAVL(node->right, val);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && val < node->left->val)
        return rightRotate(node);

    if (balance < -1 && val > node->right->val)
        return leftRotate(node);

    if (balance > 1 && val > node->left->val) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && val < node->right->val) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}
