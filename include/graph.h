#ifndef GRAPH_H
#define GRAPH_H

// Узел для списка смежности
typedef struct E_i {
    int dest; // Куда ведет ребро (номер вершины)
    struct E_i* next; // Следующий сосед
} E_i;

// Сам граф
typedef struct G {
    int n; // Число вершин
    E_i** E_lists; // Массив указателей на списки соседей
} G;

// Функции для работы с графом
E_i* newListNode(int dest);
G* createGraph(int n);
void addEdge(G* g, int from, int to);
void freeGraph(G* g);
void removeEdge(G* g, int from, int to);
int hasEdge(G* g, int u, int v);
void printGraph(G* g);
void simplifyGraph(G* g);

#endif