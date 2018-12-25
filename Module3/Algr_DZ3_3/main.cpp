#include <iostream>
#include <vector>
#include <cassert>
#include <set>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddWeightEdge(int from, int to, int weight) = 0;

    virtual int VerticesCount() const = 0;

    virtual std::vector<std::pair<int, int>> GetNextWeightVertices(int vertex) const = 0;
    virtual std::vector<std::pair<int, int>> GetPrevWeightVertices(int vertex) const = 0;
};

class CListGraph: public IGraph {
public:
    CListGraph(int verticesCount): adjacencyListFromTo(verticesCount) {}
    CListGraph(const CListGraph& other) = delete;
    CListGraph(CListGraph&& other) = delete;
    ~CListGraph() {}
    CListGraph&operator=(const CListGraph& other) = delete;
    CListGraph&operator=(CListGraph&& other) = delete;

    void AddWeightEdge(int from, int to, int weight) override;
    int VerticesCount() const override { return adjacencyListFromTo.size(); }
    std::vector<std::pair<int, int>> GetNextWeightVertices(int vertex) const override;
    std::vector<std::pair<int, int>> GetPrevWeightVertices(int vertex) const override;

private:
    std::vector<std::vector<std::pair<int, int>>> adjacencyListFromTo;
    bool isValid(int index) const;
};

bool CListGraph::isValid(int index) const {
    return (index >= 0 && index < VerticesCount());
}

void CListGraph::AddWeightEdge(int from, int to, int weight) {
    assert(isValid(from));
    assert(isValid(to));

    adjacencyListFromTo[from].emplace_back(to, weight);
    adjacencyListFromTo[to].emplace_back(from, weight);
}

std::vector<std::pair<int, int>> CListGraph::GetNextWeightVertices(int vertex) const {
    assert(isValid(vertex));

    return adjacencyListFromTo[vertex];
}

std::vector<std::pair<int, int>> CListGraph::GetPrevWeightVertices(int vertex) const {
    assert(isValid(vertex));

    return adjacencyListFromTo[vertex];
}

int MinWayLength(const CListGraph& graph, int from, int to) {
    int verticesCount = graph.VerticesCount();
    std::vector<int> way(verticesCount, INT32_MAX);
    std::set<std::pair<int, int>> priorityQueue;
    way[from] = 0;
    priorityQueue.emplace(0, from);
    while(!priorityQueue.empty()) {
        std::pair<int, int> vertex = *priorityQueue.begin();
        std::vector<std::pair<int, int>> nextVertices = graph.GetNextWeightVertices(vertex.second);
        for (auto nextVertex : nextVertices) {
            if (way[nextVertex.first] > way[vertex.second] + nextVertex.second) {
                std::pair<int, int> weightNextVertex(way[nextVertex.first], nextVertex.first);
                auto vertexInQueue = priorityQueue.find(weightNextVertex);
                if (vertexInQueue != priorityQueue.end()) {
                    priorityQueue.erase(vertexInQueue);
                }
                way[nextVertex.first] = way[vertex.second] + nextVertex.second;
                priorityQueue.insert(std::pair<int, int>(way[nextVertex.first], nextVertex.first));
            }
        }
        priorityQueue.erase(priorityQueue.find(vertex));
    }

    return way[to];
}

int main() {
    int verticesCount = 0;
    int edgesCount = 0;
    std::cin >> verticesCount >> edgesCount;
    CListGraph graph(verticesCount);
    int from = 0;
    int to = 0;
    int weight = 0;
    for (int i = 0; i < edgesCount; i++) {
        std::cin >> from >> to >> weight;
        graph.AddWeightEdge(from, to, weight);
    }
    std::cin >> from >> to;
    std::cout << MinWayLength(graph, from, to);
    return 0;
}