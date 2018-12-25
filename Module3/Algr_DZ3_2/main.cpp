#include <iostream>
#include <vector>
#include <cassert>
#include <queue>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;
    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};

class CListGraph: public IGraph {
public:
    CListGraph(int verticesCount): adjacencyListFromTo(verticesCount) {}
    CListGraph(const IGraph* other);
    CListGraph(const CListGraph& other) = delete;
    CListGraph(CListGraph&& other) = delete;
    ~CListGraph() {}
    CListGraph&operator=(const CListGraph& other) = delete;
    CListGraph&operator=(CListGraph&& other) = delete;

    void AddEdge(int from, int to) override;
    int VerticesCount() const override { return adjacencyListFromTo.size(); }
    std::vector<int> GetNextVertices(int vertex) const override;
    std::vector<int> GetPrevVertices(int vertex) const override;

private:
    std::vector<std::vector<int>> adjacencyListFromTo;
    bool isValid(int index) const;
};

CListGraph::CListGraph(const IGraph *other): CListGraph(other->VerticesCount()) {
    for (int i = 0; i < adjacencyListFromTo.size(); i++) {
        std::vector<int> currentNextVertices = other->GetNextVertices(i);
        std::copy(currentNextVertices.begin(), currentNextVertices.end(), std::back_inserter(adjacencyListFromTo[i]));
    }
}

bool CListGraph::isValid(int index) const {
    return (index >= 0 && index < VerticesCount());
}

void CListGraph::AddEdge(int from, int to) {
    assert(isValid(from));
    assert(isValid(to));

    adjacencyListFromTo[from].push_back(to);
    adjacencyListFromTo[to].push_back(from);
}

std::vector<int> CListGraph::GetNextVertices(int vertex) const {
    assert(isValid(vertex));
    return adjacencyListFromTo[vertex];
}

std::vector<int> CListGraph::GetPrevVertices(int vertex) const {
    assert(isValid(vertex));
    return adjacencyListFromTo[vertex];
}

int BFS(const IGraph* graph, int from, int to) {
    std::queue<int> queue;
    queue.push(from);
    int verticesCount = graph->VerticesCount();
    std::vector<int> way(verticesCount, INT32_MAX);
    std::vector<int> waysCount(verticesCount, 0);
    way[from] = 0;
    waysCount[from] = 1;

    while (!queue.empty()) {
        int vertex = queue.front();
        queue.pop();
        std::vector<int> nextVertices = graph->GetNextVertices(vertex);
        for (auto nextVertex : nextVertices) {
            if (way[nextVertex] > way[vertex] + 1) {
                way[nextVertex] = way[vertex] + 1;
                queue.push(nextVertex);
            }
            if (way[nextVertex] == way[vertex] + 1) {
                waysCount[nextVertex] += waysCount[vertex];
            }
        }
    }
    return waysCount[to];
}

int main() {
    int verticesCount = 0;
    int edgesCount = 0;
    std::cin >> verticesCount;
    std::cin >> edgesCount;
    CListGraph graph(verticesCount);
    int from = 0;
    int to = 0;
    for (int i = 0; i < edgesCount; i++) {
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }
    std::cin >> from >> to;
    std::cout << BFS(&graph, from, to);
    return 0;
}