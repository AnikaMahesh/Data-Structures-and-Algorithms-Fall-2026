#include "pch.h"
#include "graph_traversal.h"

// -------------------- MinHeap Tests --------------------

TEST(MinHeapTest, RemovesInPriorityOrder) {
	MinHeap<std::string> heap;

	heap.insert("B", 5.0);
	heap.insert("A", 1.0);
	heap.insert("C", 10.0);

	EXPECT_EQ(heap.getMin(), "A");
	EXPECT_EQ(heap.getMin(), "B");
	EXPECT_EQ(heap.getMin(), "C");

	EXPECT_TRUE(heap.isEmpty());
}

TEST(MinHeapTest, DecreasePriority) {
	MinHeap<std::string> heap;

	heap.insert("A", 1.0);
	heap.insert("B", 5.0);
	heap.insert("C", 10.0);

	// C should move all the way to the front.
	heap.adjustHeapNumber("C", 0.5);

	EXPECT_EQ(heap.getMin(), "C");
	EXPECT_EQ(heap.getMin(), "A");
	EXPECT_EQ(heap.getMin(), "B");
}

TEST(MinHeapTest, IncreasePriority) {
	MinHeap<std::string> heap;

	heap.insert("A", 1.0);
	heap.insert("B", 2.0);
	heap.insert("C", 3.0);

	// A should move toward the bottom.
	heap.adjustHeapNumber("A", 10.0);

	EXPECT_EQ(heap.getMin(), "B");
	EXPECT_EQ(heap.getMin(), "C");
	EXPECT_EQ(heap.getMin(), "A");
}


// -------------------- MinPriorityQueue Tests --------------------

// Testing isEmpty() is true when a fresh priority queue is created
TEST(MinPriorityQueueTest, NewQueueIsEmpty) {
	MinPriorityQueue<int> queue;

	EXPECT_TRUE(queue.isEmpty());
}

// Testing elements are returned in increasing priority order
TEST(MinPriorityQueueTest, ReturnsLowestPriorityFirst) {
	MinPriorityQueue<std::string> queue;

	queue.addWithPriority("third", 3.0);
	queue.addWithPriority("first", 1.0);
	queue.addWithPriority("second", 2.0);

	EXPECT_EQ(queue.next(), "first");
	EXPECT_EQ(queue.next(), "second");
	EXPECT_EQ(queue.next(), "third");

	EXPECT_TRUE(queue.isEmpty());
}

// Testing adjustPriority() changes the order of the queue
TEST(MinPriorityQueueTest, AdjustPriorityChangesOrder) {
	MinPriorityQueue<std::string> queue;

	queue.addWithPriority("A", 1.0);
	queue.addWithPriority("B", 5.0);
	queue.addWithPriority("C", 10.0);

	queue.adjustPriority("C", 0.5);

	EXPECT_EQ(queue.next(), "C");
	EXPECT_EQ(queue.next(), "A");
	EXPECT_EQ(queue.next(), "B");
}


// -------------------- Dijkstra Tests --------------------
// Testing Dijkstra finds a direct path
TEST(DijkstraTest, DirectPath) {
	Graph<std::string> graph;

	graph.addEdge("A", "B", 1.0);

	std::vector<std::string> expected = { "A", "B" };

	EXPECT_EQ(
		shortest_path_with_dijkstra(
			graph,
			std::string("A"),
			std::string("B")
		),
		expected
	);
}


// Testing Dijkstra chooses the cheaper path
TEST(DijkstraTest, ChoosesShortestPath) {
	Graph<std::string> graph;
	graph.addEdge("A", "D", 10.0);
	graph.addEdge("A", "B", 2.0);
	graph.addEdge("B", "D", 3.0);

	std::vector<std::string> expected = {
		"A", "B", "D"
	};

	EXPECT_EQ(
		shortest_path_with_dijkstra(
			graph,
			std::string("A"),
			std::string("D")
		),
		expected
	);
}


// Testing Dijkstra returns an empty vector when no path exists
TEST(DijkstraTest, NoPath) {
	Graph<std::string> graph;

	graph.addEdge("A", "B", 1.0);
	graph.addEdge("C", "D", 1.0);

	std::vector<std::string> expected = {};

	EXPECT_EQ(
		shortest_path_with_dijkstra(
			graph,
			std::string("A"),
			std::string("D")
		),
		expected
	);
}


// euler 81 on a problem and solution
TEST(Euler81, fiveelementTestCase) {
	std::vector<int> vect = euler_81("0081_matrix_5element.txt");
	std::vector<int> vect1 = { 131, 201, 96, 342, 746, 422, 121, 37, 331 };
	EXPECT_EQ(vect, vect1);
}