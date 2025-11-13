#include <stdio.h>
#include <stdlib.h>
#include "../include/graph.h"

void run_tests() {
    printf("Тест 1: Простой путь 0-1-2-3\n");
    G* g1 = createGraph(4);
    addEdge(g1, 0, 1);
    addEdge(g1, 1, 2);
    addEdge(g1, 2, 3);
    
    printf("До:\n");
    printGraph(g1);
    
    simplifyGraph(g1);
    
    printf("\nПосле:\n");
    printGraph(g1);
    
    freeGraph(g1);

    printf("\nТест 2: Граф К3\n");
    G* g2 = createGraph(3);
    addEdge(g2, 0, 1);
    addEdge(g2, 1, 2);
    addEdge(g2, 2, 0);

    printf("До:\n");
    printGraph(g2);
    simplifyGraph(g2);
    
    printf("\nПосле:\n");
    printGraph(g2);
    
    freeGraph(g2);

    printf("\nТест 3:\n");
    G* g3 = createGraph(7);
    addEdge(g3, 0, 1);
    addEdge(g3, 1, 2);
    addEdge(g3, 2, 3);
    addEdge(g3, 3, 4);
    addEdge(g3, 2, 5);
    addEdge(g3, 5, 6);
    
    printf("До:\n");
    printGraph(g3);
    
    simplifyGraph(g3);
    
    printf("\nПосле:\n");
    printGraph(g3);
    
    freeGraph(g3);

    printf("\nТест 4: Пустой граф\n");
    G* g4 = createGraph(0);
    printf("До:\n");
    printGraph(g4);
    simplifyGraph(g4);
    printf("\nПосле:\n");
    printGraph(g4);
    freeGraph(g4);

    printf("\nТест 5: Граф с одной вершиной\n");
    G* g5 = createGraph(1);
    printf("До:\n");
    printGraph(g5);
    simplifyGraph(g5);
    printf("\nПосле:\n");
    printGraph(g5);
    freeGraph(g5);

    printf("\nТест 6: Граф с двумя вершинами и ребром\n");
    G* g6 = createGraph(2);
    addEdge(g6, 0, 1);
    printf("До:\n");
    printGraph(g6);
    simplifyGraph(g6);
    printf("\nПосле:\n");
    printGraph(g6);
    freeGraph(g6);

    printf("\nТест 7: Звезда\n");
    G* g7 = createGraph(5);
    addEdge(g7, 0, 1);
    addEdge(g7, 0, 2);
    addEdge(g7, 0, 3);
    addEdge(g7, 0, 4);
    printf("До:\n");
    printGraph(g7);
    simplifyGraph(g7);
    printf("\nПосле:\n");
    printGraph(g7);
    freeGraph(g7);

    printf("\nТест 8: Граф K4\n");
    G* g8 = createGraph(4);
    addEdge(g8, 0, 1);
    addEdge(g8, 0, 2);
    addEdge(g8, 0, 3);
    addEdge(g8, 1, 2);
    addEdge(g8, 1, 3);
    addEdge(g8, 2, 3);
    printf("До:\n");
    printGraph(g8);
    simplifyGraph(g8);
    printf("\nПосле:\n");
    printGraph(g8);
    freeGraph(g8);

    printf("\nТест 9: Длинная цепочка\n");
    G* g9 = createGraph(10);
    for (int i = 0; i < 9; i++) {
        addEdge(g9, i, i + 1);
    }
    printf("До:\n");
    printGraph(g9);
    simplifyGraph(g9);
    printf("\nПосле:\n");
    printGraph(g9);
    freeGraph(g9);

    printf("\nТест 10: Граф-цикл\n");
    G* g10 = createGraph(5);
    for (int i = 0; i < 5; i++) {
        addEdge(g10, i, (i + 1) % 5);
    }
    printf("До:\n");
    printGraph(g10);
    simplifyGraph(g10);
    printf("\nПосле:\n");
    printGraph(g10);
    freeGraph(g10);
}

int main() {
    run_tests();
    return 0;
}
