#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"

E_i* newListNode(int dest) {
    E_i* newNode = (E_i*)malloc(sizeof(E_i));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

G* createGraph(int n) {
    G* g = (G*)malloc(sizeof(G));
    g->n = n;
    g->E_lists = (E_i**)calloc(n, sizeof(E_i*)); 
    return g;
}

void addEdge(G* g, int from, int to) {
    // Ребро из from в to
    E_i* newNodeTo = newListNode(to);
    newNodeTo->next = g->E_lists[from];
    g->E_lists[from] = newNodeTo;

    // Ребро из to в from
    E_i* newNodeFrom = newListNode(from);
    newNodeFrom->next = g->E_lists[to];
    g->E_lists[to] = newNodeFrom;
}

void freeGraph(G* g) {
    if (g == NULL) return;

    for (int i = 0; i < g->n; i++) {
        E_i* current = g->E_lists[i];
        while (current != NULL) {
            E_i* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(g->E_lists);
    free(g);
}

void removeEdgeNode(E_i** head, int v) {
    E_i* current = *head;
    E_i* prev = NULL;

    while (current != NULL) {
        if (current->dest == v) {
            if (prev == NULL) { // Это первый элемент
                *head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void removeEdge(G* g, int from, int to) {
    if (g == NULL || from < 0 || from >= g->n || to < 0 || to >= g->n) {
        printf("Некорректный номер ребра\n");
        return;
    }
    // Удаляем v из списка u
    removeEdgeNode(&(g->E_lists[from]), to);
    
    // Удаляем u из списка v
    removeEdgeNode(&(g->E_lists[to]), from);
}

int hasEdge(G* g, int u, int v) {
    if (g == NULL || u < 0 || u >= g->n || v < 0 || v >= g->n) {
        return 0;
    }
    
    E_i* current = g->E_lists[u];
    while (current != NULL) {
        if (current->dest == v) {
            return 1; // Ребро есть
        }
        current = current->next;
    }
    return 0; // Ребра нет
}

void printGraph(G* g) {
    if (g == NULL || g->n == 0) {
        printf("Граф пуст.\n");
        return;
    }
    printf("Граф (n=%d):\n", g->n);
    for (int i = 0; i < g->n; i++) {
        printf("%d: ", i);
        E_i* current = g->E_lists[i];
        if (current == NULL) {
            printf("(пусто)");
        }
        while (current != NULL) {
            printf("%d ", current->dest);
            current = current->next;
        }
        printf("\n");
    }
}

void simplifyGraph(G* g) {
    if (g == NULL || g->n < 3) { // Упрощать можно только если вершин минимум 3
        return;
    }

    int simplified = 1; // Флаг, что на итерации было упрощение
    
    while (simplified) {
        simplified = 0;

        for (int v = 0; v < g->n; v++) { // Цикл для поиска вершины степени 2
            
            int deg = 0;
            int neighbors[2] = {-1, -1};
            
            E_i* current = g->E_lists[v];
            while (current != NULL) {
                if (deg < 2) {
                    neighbors[deg] = current->dest;
                }
                deg++;
                current = current->next;
            }

            if (deg == 2) {
                int u = neighbors[0];
                int w = neighbors[1];

                removeEdge(g, u, v); // Убираем (u,v)
                removeEdge(g, w, v); // Убираем (w,v)
                
                if (u != w) { // Если не петля
                    if (!hasEdge(g, u, w)) { // И такого ребра ещё не существует
                        addEdge(g, u, w); // Добавляем
                    }
                }
                
                simplified = 1; 
                
                break; 
            }
        }
    }
}