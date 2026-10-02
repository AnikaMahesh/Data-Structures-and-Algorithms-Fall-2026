#pragma once

#include <algorithm>
#include <limits>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>
#include <fstream>
#include <iostream>
#include <string>

/**
 * @brief Represents a directed, weighted graph.
 * Stores vertices and their outgoing edges using adjacency maps.
 * VertexType must be usable as a key in std::unordered_map.
 */
template <typename VertexType>
class Graph {
public:
    // Maps each source vertex to its outgoing neighbors and edge costs.
    std::unordered_map<
        VertexType,
        std::unordered_map<VertexType, double>
    > edges;

    /**
     * @brief Gets all vertices in the graph.
     * Collects every vertex stored as a key in the adjacency map.
     *
     * @return A set containing all vertices in the graph.
     */
    std::set<VertexType> getVertices() const {
        std::set<VertexType> keys;

        for (const auto& entry : edges) {
            keys.insert(entry.first);
        }

        return keys;
    }

    /**
     * @brief Adds a directed edge to the graph.
     * Stores an edge from one vertex to another with the given cost.
     *
     * @param from The source vertex.
     * @param to The destination vertex.
     * @param cost The cost of the directed edge.
     *
     * @return Nothing.
     */
    void addEdge(
        const VertexType& from,
        const VertexType& to,
        double cost)
    {
        edges[from][to] = cost;

        // Ensure the destination exists even if it has no outgoing edges.
        edges.try_emplace(to);
    }

    /**
     * @brief Gets the outgoing edges from a vertex.
     * Returns a map from each neighboring vertex to its edge cost.
     *
     * @param from The vertex whose outgoing edges are requested.
     *
     * @return A reference to the map of neighbors and edge costs.
     */
    const std::unordered_map<VertexType, double>&
        getEdges(const VertexType& from) const {
        return edges.at(from);
    }

    /**
     * @brief Clears the graph.
     * Removes all vertices and edges from the graph.
     *
     * @return Nothing.
     */
    void clear() {
        edges.clear();
    }
};


/**
 * @brief Implements a minimum binary heap.
 * Stores elements with priorities and removes lower-priority values first.
 * An index map provides direct lookup of each element's heap position.
 */
template <typename T>
class MinHeap {
private:
    // Each entry stores an element and its associated priority.
    std::vector<std::pair<T, double>> vertices;

    // Maps each element to its current index in vertices.
    std::unordered_map<T, int> indexMap;

public:
    /**
     * @brief Checks whether the heap is empty.
     * Tests whether the heap currently contains any elements.
     *
     * @return true if the heap is empty, otherwise false.
     */
    bool isEmpty() const {
        return vertices.empty();
    }

    /**
     * @brief Inserts an element into the heap.
     * Adds an element with the given priority and restores heap ordering.
     * Duplicate elements are not inserted.
     *
     * @param data The element to insert.
     * @param heapNumber The priority assigned to the element.
     *
     * @return true if the element was inserted, otherwise false.
     */
    bool insert(const T& data, double heapNumber) {
        // Each element must be unique so indexMap has one valid position.
        if (contains(data)) {
            return false;
        }

        // Add at the end to preserve the complete binary-tree structure.
        vertices.push_back({ data, heapNumber });
        int index = static_cast<int>(vertices.size()) - 1;

        // Record the new element's position before moving it through the heap.
        indexMap[data] = index;

        // Restore min-heap ordering after the insertion.
        percolateUp(index);

        return true;
    }

    /**
     * @brief Removes the minimum-priority element.
     * Removes and returns the root, then restores the min-heap property.
     * Returns T{} if the heap is empty.
     *
     * @return The element with the smallest priority, or T{} if empty.
     */
    T getMin() {
        if (vertices.empty()) {
            return T{};
        }

        // The root always contains the element with the smallest priority.
        T minimum = vertices[0].first;

        // A one-element heap can be removed without reordering anything.
        if (vertices.size() == 1) {
            vertices.pop_back();
            indexMap.erase(minimum);
            return minimum;
        }

        // Move the root to the end so it can be removed in constant time.
        swapEntries(
            0,
            static_cast<int>(vertices.size()) - 1
        );
        vertices.pop_back();
        indexMap.erase(minimum);

        // The replacement root may now violate min-heap ordering.
        bubbleDown(0);

        return minimum;
    }

    /**
     * @brief Changes an element's priority.
     * Updates the priority and moves the element until heap ordering is restored.
     * Does nothing if the element is not present.
     *
     * @param vertex The element whose priority should change.
     * @param newNumber The new priority for the element.
     *
     * @return Nothing.
     */
    void adjustHeapNumber(const T& vertex, double newNumber) {
        int index = getIndex(vertex);

        if (index == -1) {
            return;
        }

        vertices[index].second = newNumber;

        // A decreased priority can require moving the element upward.
        percolateUp(index);

        // Its index may have changed, so look it up again before moving down.
        index = getIndex(vertex);

        // An increased priority can require moving the element downward.
        bubbleDown(index);
    }

    /**
     * @brief Checks whether an element is in the heap.
     * Uses the index map to test membership without scanning the heap.
     *
     * @param vertex The element to search for.
     *
     * @return true if the element is present, otherwise false.
     */
    bool contains(const T& vertex) const {
        return indexMap.find(vertex) != indexMap.end();
    }

private:
    /**
     * @brief Gets an element's heap index.
     * Looks up the current position of an element using the index map.
     *
     * @param vertex The element whose index is requested.
     *
     * @return The element's index, or -1 if it is not present.
     */
    int getIndex(const T& vertex) const {
        auto it = indexMap.find(vertex);

        if (it == indexMap.end()) {
            return -1;
        }

        return it->second;
    }

    /**
     * @brief Moves an element downward in the heap.
     * Repeatedly swaps with the smaller child until min-heap ordering is restored.
     *
     * @param startIndex The index where downward movement begins.
     *
     * @return Nothing.
     */
    void bubbleDown(int startIndex) {
        int current = startIndex;

        while (true) {
            int left = getLeftIndex(current);
            int right = getRightIndex(current);
            int smallest = current;

            // Find the smallest-priority entry among the node and its children.
            if (left < static_cast<int>(vertices.size()) &&
                vertices[left].second < vertices[smallest].second) {
                smallest = left;
            }

            if (right < static_cast<int>(vertices.size()) &&
                vertices[right].second < vertices[smallest].second) {
                smallest = right;
            }

            // No swap is needed once the current node is already smallest.
            if (smallest == current) {
                return;
            }

            // Swap with the smaller child and continue from its old position.
            swapEntries(current, smallest);
            current = smallest;
        }
    }

    /**
     * @brief Moves an element upward in the heap.
     * Repeatedly swaps with its parent until min-heap ordering is restored.
     *
     * @param startIndex The index where upward movement begins.
     *
     * @return Nothing.
     */
    void percolateUp(int startIndex) {
        int current = startIndex;

        while (current > 0) {
            int parent = getParentIndex(current);

            // Stop once the parent already has an equal or smaller priority.
            if (vertices[parent].second <= vertices[current].second) {
                return;
            }

            swapEntries(parent, current);
            current = parent;
        }
    }

    /**
     * @brief Swaps two heap entries.
     * Swaps the entries and updates their positions in the index map.
     *
     * @param index1 The index of the first entry.
     * @param index2 The index of the second entry.
     *
     * @return Nothing.
     */
    void swapEntries(int index1, int index2) {
        // Update positions before swapping while each element is easy to identify.
        indexMap[vertices[index1].first] = index2;
        indexMap[vertices[index2].first] = index1;

        std::swap(vertices[index1], vertices[index2]);
    }

    /**
     * @brief Gets the parent index of a heap entry.
     * Computes the parent position for an array-based binary heap.
     *
     * @param index The child index.
     *
     * @return The index of the parent entry.
     */
    int getParentIndex(int index) const {
        return (index - 1) / 2;
    }

    /**
     * @brief Gets the left-child index of a heap entry.
     * Computes the left-child position for an array-based binary heap.
     *
     * @param index The parent index.
     *
     * @return The index where the left child would be stored.
     */
    int getLeftIndex(int index) const {
        return index * 2 + 1;
    }

    /**
     * @brief Gets the right-child index of a heap entry.
     * Computes the right-child position for an array-based binary heap.
     *
     * @param index The parent index.
     *
     * @return The index where the right child would be stored.
     */
    int getRightIndex(int index) const {
        return index * 2 + 2;
    }
};


/**
 * @brief Implements a minimum-priority queue.
 * Wraps MinHeap so elements are removed in order of increasing priority.
 */
template <typename T>
class MinPriorityQueue {
private:
    MinHeap<T> heap;

public:
    /**
     * @brief Checks whether the priority queue is empty.
     * Tests whether the underlying heap contains any elements.
     *
     * @return true if the queue is empty, otherwise false.
     */
    bool isEmpty() const {
        return heap.isEmpty();
    }

    /**
     * @brief Adds an element with a priority.
     * Inserts the element into the underlying minimum heap.
     *
     * @param elem The element to add.
     * @param priority The priority assigned to the element.
     *
     * @return Nothing.
     */
    void addWithPriority(const T& elem, double priority) {
        heap.insert(elem, priority);
    }

    /**
     * @brief Removes the next element from the queue.
     * Removes and returns the element with the smallest priority.
     *
     * @return The element with the smallest priority, or T{} if empty.
     */
    T next() {
        return heap.getMin();
    }

    /**
     * @brief Changes an element's priority.
     * Updates the priority of an element already stored in the queue.
     *
     * @param elem The element whose priority should change.
     * @param newPriority The new priority for the element.
     *
     * @return Nothing.
     */
    void adjustPriority(const T& elem, double newPriority) {
        heap.adjustHeapNumber(elem, newPriority);
    }

    /**
     * @brief Checks whether an element is in the queue.
     * Tests membership using the underlying heap's index map.
     *
     * @param elem The element to search for.
     *
     * @return true if the element is present, otherwise false.
     */
    bool contains(const T& elem) const {
        return heap.contains(elem);
    }
};


/**
 * @brief Finds a shortest path using Dijkstra's algorithm.
 * Computes the minimum-cost path from start to end by repeatedly
 * processing the vertex with the smallest currently known distance.
 * The path is reconstructed using predecessor information.
 * All edge weights are assumed to be nonnegative.
 *
 * @param graph The directed, weighted graph to search.
 * @param start The vertex where the path begins.
 * @param end The destination vertex.
 *
 * @return A vector containing the vertices of the shortest path,
 *         ordered from start to end.
 * @return An empty vector if no path exists or if start or end
 *         is not present in the graph.
 */
template <typename VertexType>
std::vector<VertexType> shortest_path_with_dijkstra(
    const Graph<VertexType>& graph,
    const VertexType& start,
    const VertexType& end)
{
    // Track the shortest distance currently known from start to each vertex.
    std::unordered_map<VertexType, double> distance;

    // Track each vertex's predecessor so the final path can be reconstructed.
    std::unordered_map<VertexType, VertexType> previous;

    // Process vertices in order of their currently known shortest distance.
    MinPriorityQueue<VertexType> queue;
    std::set<VertexType> vertices = graph.getVertices();

    // A path cannot exist if either endpoint is absent from the graph.
    if (vertices.find(start) == vertices.end() ||
        vertices.find(end) == vertices.end()) {
        return {};
    }

    // Initially all vertices except start have an unknown, infinite distance.
    for (const VertexType& vertex : vertices) {
        distance[vertex] = std::numeric_limits<double>::infinity();
    }
    distance[start] = 0.0;

    // Begin exploration from the start vertex at distance zero.
    queue.addWithPriority(start, 0.0);

    while (!queue.isEmpty()) {
        // Always expand the unprocessed vertex with the smallest known distance.
        VertexType current = queue.next();

        // Once end is removed from the queue, its shortest path is finalized.
        if (current == end) {
            break;
        }

        // Relax every outgoing edge from the current vertex.
        for (const auto& edge : graph.getEdges(current)) {
            VertexType neighbor = edge.first;
            double edgeCost = edge.second;

            // Compute the cost of reaching neighbor through current.
            double newDistance = distance[current] + edgeCost;

            // Keep this route only if it improves the best known distance.
            if (newDistance < distance[neighbor]) {
                distance[neighbor] = newDistance;
                previous[neighbor] = current;

                // Keep the queue priority synchronized with the new distance.
                if (queue.contains(neighbor)) {
                    queue.adjustPriority(neighbor, newDistance);
                }
                else {
                    queue.addWithPriority(neighbor, newDistance);
                }
            }
        }
    }

    // If end has no predecessor, it was never reached unless start == end.
    if (start != end && previous.find(end) == previous.end()) {
        return {};
    }

    std::vector<VertexType> path;
    VertexType current = end;
    path.push_back(current);

    // Follow predecessor links backward from end until start is reached.
    while (current != start) {
        current = previous[current];
        path.push_back(current);
    }

    // Predecessor traversal builds end -> start, so reverse to start -> end.
    std::reverse(path.begin(), path.end());

    return path;
}

/**
 * @brief Finds the minimum-weight path through a matrix using Dijkstra's algorithm.
 * Reads a comma-separated matrix from a text file and constructs a graph where
 * each matrix cell is a node and its value is the cost of entering that node.
 * Finds the shortest path from the top-left cell to the bottom-right cell.
 *
 * @param filename The path to the text file containing the matrix.
 *
 * @return A vector containing the weights of the nodes along the shortest path.
 * @return An empty vector if the input file cannot be opened or no path exists.
 */
std::vector<int> euler_81(const std::string filename)
{
    Graph<int> graph;
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Could not open file.\n";
        return std::vector<int>{};
    }
    std::string line;
    std::vector<int> prev_line;
    std::vector<int> current;
    int prev_node = -1;
    int node_counter = 0;
    int start;
    int end;
    std::unordered_map<int, int> node_weights;

    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string value;
        int counter = 0;
        current.clear();
        prev_node = -1;
        while (std::getline(ss, value, ',')) {
            int weight = std::stoi(value);
            // Give this cell a unique node ID.
            int current_node = node_counter;
            node_counter++;
            // Store the node ID for this row.
            current.push_back(current_node);
            // Store the weight associated with this node.
            node_weights[current_node] = weight;
            // Connect the node on the left to this node.
            if (prev_node != -1) {
                graph.addEdge(
                    prev_node,
                    current_node,
                    weight
                );
            }
            // Connect the node above to this node.
            if (!prev_line.empty()) {
                graph.addEdge(
                    prev_line[counter],
                    current_node,
                    weight
                );
            }
            // The first node is the starting point.
            if (prev_line.empty() && prev_node == -1) {
                start = current_node;
            }

            prev_node = current_node;
            end = current_node;
            counter++;
        }
        prev_line = current;
    }
    inputFile.close();
    std::vector<int> node_path =
        shortest_path_with_dijkstra(graph, start, end);
    std::vector<int> weight_path;
    for (int node : node_path) {
        weight_path.push_back(node_weights[node]);
    }
    return weight_path;
}