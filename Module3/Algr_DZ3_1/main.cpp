#include <iostream>
#include "CListGraph.h"
#include "CMatrixGraph.h"
#include "CArcGraph.h"
#include "CSetGraph.h"
#include <ctime>

void generatorNormalGraph(IGraph* graph, const int verticesCount) {
    for (int i = 0; i < verticesCount; i++) {
        for (int j = i + 1; j < verticesCount; j++) {
            graph->AddEdge(std::rand() % verticesCount, std::rand() % verticesCount);
        }
    }
}

void generatorFullGraph(IGraph* graph, const int verticesCount) {
    for (int i = 0; i < verticesCount; i++) {
        graph->AddEdge(std::rand() % verticesCount, std::rand() % verticesCount);
    }
}

void experimentNormal(IGraph* graph, int count) {
    unsigned int start = clock();
    generatorNormalGraph(graph, count);
    unsigned int end = clock();
    std::cout << "Generate normal " << end - start << std::endl;
}

void experiment(int count) {
    CListGraph graph1(count);
    CMatrixGraph graph2(count);
    CArcGraph graph3(count);
    CSetGraph graph4(count);
    std::cout << "List " << std::endl;
    experimentNormal(&graph1, count);
    std::cout << "Matrix " << std::endl;
    experimentNormal(&graph2, count);
    std::cout << "Arc " << std::endl;
    experimentNormal(&graph3, count);
    std::cout << "Set " << std::endl;
    experimentNormal(&graph4, count);
}

void experimentFullG(IGraph* graph, int count) {
    unsigned int start = clock();
    generatorFullGraph(graph, count);
    unsigned int end = clock();
    std::cout << "Generate Full " << end - start << std::endl;
}

void experimentFull(int count) {
    CListGraph graph1(count);
    CMatrixGraph graph2(count);
    CArcGraph graph3(count);
    CSetGraph graph4(count);
    std::cout << "List " << std::endl;
    experimentFullG(&graph1, count);
    std::cout << "Matrix " << std::endl;
    experimentFullG(&graph2, count);
    std::cout << "Arc " << std::endl;
    experimentFullG(&graph3, count);
    std::cout << "Set " << std::endl;
    experimentFullG(&graph4, count);
}

int main() {
    for (int count = 10; count < 11; count++) {
        experiment(count);
        experimentFull(count);
    }
    return 0;
}