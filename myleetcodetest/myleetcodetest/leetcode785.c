#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>

bool isConnected(int** graph, int graphSize, int* graphColSize, int ii, int jj) {
    for (int j = 0; j < graphColSize[ii]; j++) {
        if (graph[ii][j] == jj) {
            return true;
        }
    }
    return false;
}

bool isBipartiteHelper(int** graph, int graphSize, int* graphColSize, int* group, int ii, int jj) {
    for (int i = ii; i < graphSize; i++) {
        int j = 0;
        if (i == ii) {
            j = jj;
        }
        for (; j < graphColSize[i]; j++) {
            printf("Testing %d,%d\n", i, j);
            int groupI = group[i], groupJ = group[graph[i][j]];
            if (groupI != 0 && groupI == groupJ) {
                printf("group i: %d == group j: %d, false\n", i, graph[i][j]);
                return false;
            }
            if (groupI == 0) {
                if (groupJ == 0) {
                    // just set the group
                    group[i] = 1;
                    group[graph[i][j]] = 2;
                    if (isBipartiteHelper(graph, graphSize, graphColSize, group, i, j + 1)) {
                        return true;
                    }
                    group[i] = 2;
                    group[graph[i][j]] = 1;
                    if (isBipartiteHelper(graph, graphSize, graphColSize, group, i, j + 1)) {
                        return true;
                    }
                    return false;
                } else {
                    // groupI is the oppsite
                    if (isConnected(graph, graphSize, graphColSize, i, j)) {
                        group[i] = group[graph[i][j]] == 1 ? 2 : 1;
                    } else {
                        group[i] = 1;
                        group[graph[i][j]] = 2;
                        if (isBipartiteHelper(graph, graphSize, graphColSize, group, i, j + 1)) {
                            return true;
                        }
                        group[i] = 2;
                        group[graph[i][j]] = 1;
                        if (isBipartiteHelper(graph, graphSize, graphColSize, group, i, j + 1)) {
                            return true;
                        }
                        return false;
                    }
                }
            } else {
                if (groupJ == 0) {
                    if (isConnected(graph, graphSize, graphColSize, i, j)) {
                        group[graph[i][j]] = group[i] == 1 ? 2 : 1;
                    } else {
                        group[i] = 1;
                        group[graph[i][j]] = 2;
                        if (isBipartiteHelper(graph, graphSize, graphColSize, group, i, j + 1)) {
                            return true;
                        }
                        group[i] = 2;
                        group[graph[i][j]] = 1;
                        if (isBipartiteHelper(graph, graphSize, graphColSize, group, i, j + 1)) {
                            return true;
                        }
                        return false;
                    }
                } else {
                    // remain the same
                }
            }
        }
    }

    return true;
}

bool isBipartiteOldWrong(int** graph, int graphSize, int* graphColSize) {
    int* group = (int*)malloc(100 * sizeof(int)); // 0 undefined, 1 group1, 2 group2
    memset(group, 0, 100 * sizeof(int));

    bool ret = isBipartiteHelper(graph, graphSize, graphColSize, group, 0, 0);

    free(group);
    return ret;
}

void dumpArray(const char* prefix, int* ary, int n) {
    printf("%s", prefix);
    for (int i = 0; i < n; i++) {
        printf("%d ", ary[i]);
    }
    printf("\n");
}

bool isBipartite(int** graph, int graphSize, int* graphColSize) {
    int* group = (int*)malloc(graphSize * sizeof(int)); // 0 undefined, 1 group1, 2 group2
    memset(group, 0, graphSize * sizeof(int));

    int* visited = (int*)malloc(graphSize * sizeof(int));
    memset(visited, 0, graphSize * sizeof(int));

    int* que = (int*)malloc(graphSize * sizeof(int));
    int front = 0, tail = 0, queSize = 0;

    for (int k = 0; k < graphSize; k++) {
        if (visited[k] == 0) {
            front = 0, tail = 0, queSize = 0;
            que[tail++] = k;
            queSize++;
            while (queSize > 0) {
                int v = que[front];
                front = (front + 1) % graphSize;
                queSize--;

                visited[v] = 1;

                int groupVCanBe = 0;
                for (int i = 0; i < graphColSize[v]; i++) {
                    //printf("%d,%d,%d,%d\n", graphSize, v, i, graph[v][i]);
                    if (visited[graph[v][i]] == 0) {
                        que[tail] = graph[v][i];
                        tail = (tail + 1) % graphSize;
                        queSize++;
                    } else {
                        if (group[graph[v][i]] != 0) {
                            int oppsite = group[graph[v][i]] == 1 ? 2 : 1;
                            if (groupVCanBe != 0) {
                                if (oppsite != groupVCanBe) {
                                    return false;
                                }
                            } else {
                                groupVCanBe = oppsite;
                            }
                        }
                    }
                }

                printf("%d: groupv: %d, groupVCanBe: %d\n", v, group[v], groupVCanBe);
                if (group[v] == 0) {
                    if (groupVCanBe != 0) {
                        group[v] = groupVCanBe;
                    } else {
                        group[v] = 1;
                    }
                } else {
                    if (groupVCanBe != 0 && group[v] != groupVCanBe) {
                        return false;
                    }
                }
            }
        }
    }

    dumpArray("Group: ", group, graphSize);
    dumpArray("Visited: ", visited, graphSize);

    free(group);
    free(visited);
    free(que);
    return true;
}