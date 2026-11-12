'''
 * Benchmark [KDTree] against brute force nearest neighbor.
 * 1000 test points will be generated to test against the training
 * points.
 *
 * @param k: the dimensionality of the dataset to create
 * @param numPoints: the number of points to use to match against
 *   (1000 test points will be used)
 * @return the triple of [Duration] objects where the first specifies
 * the time to build the tree, the second specifies the time it takes
 * to query the tree with 1,000 points, and the third is the time it
 * takes to find the nearest neighbor to these points using the brute
 * force approach.
'''
import random
import time
import matplotlib.pyplot as plt
from KDTree import *

random.seed(42)

dimensions = [1, 2, 5, 7]
numPoints = [1, 10, 100, 1000, 10000]

num_queries = 100

kd_times = []
brute_times = []

for k in dimensions:
    kd_row = []
    brute_row = []

    for n in numPoints:
        print(f"Testing {k} dimensions, {n} points...")

        # Generate random k-dimensional points
        points = [
            tuple(random.random() for _ in range(k))
            for _ in range(n)
        ]

        queries = [
            tuple(random.random() for _ in range(k))
            for _ in range(num_queries)
        ]

        tree = KDtree(points)
        brute = BruteForce(points)

        # Benchmark KD-tree
        start = time.perf_counter()

        for query in queries:
            tree.findNearestNeighbor(tree.root, query)

        kd_avg = (time.perf_counter() - start) / num_queries

        # Benchmark brute force
        start = time.perf_counter()

        for query in queries:
            brute.findNearestNeighbor(query)

        brute_avg = (time.perf_counter() - start) / num_queries

        kd_row.append(kd_avg)
        brute_row.append(brute_avg)

    kd_times.append(kd_row)
    brute_times.append(brute_row)


# Plot results
fig, axes = plt.subplots(2, 2, figsize=(12, 9))

for i, k in enumerate(dimensions):
    ax = axes[i // 2][i % 2]

    ax.plot(numPoints, kd_times[i], marker="o", label="KD-tree")
    ax.plot(numPoints, brute_times[i], marker="o", label="Brute force")

    ax.set_title(f"{k} Dimensions")
    ax.set_xlabel("Number of Points")
    ax.set_ylabel("Average Query Time (seconds)")
    ax.set_xscale("log")
    ax.set_yscale("log")
    ax.legend()
    ax.grid(True)

plt.tight_layout()
plt.show()