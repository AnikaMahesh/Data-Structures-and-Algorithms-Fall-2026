import random
from KDTree import *

random.seed(42)

points = [
    (random.random(), random.random())
    for _ in range(1000)
]

tree = KDtree(points)
brute = BruteForce(points)


# Test brute force and KDtree return the same point for nearest neighbor for 100 points
for _ in range(100):
    query = (random.random(), random.random())

    kd_result = tree.findNearestNeighbor(
        tree.root, query
    ).point

    brute_result = brute.findNearestNeighbor(query)

    assert euclidian_distance(kd_result, query) == \
           euclidian_distance(brute_result, query)


#Empty dataset should return None
empty_tree = KDtree([])
empty_brute = BruteForce([])

assert empty_tree.findNearestNeighbor(empty_tree.root, (1, 2)) is None
assert empty_brute.findNearestNeighbor((1, 2)) is None


# Single point should always be returned
single_tree = KDtree([(3, 4)])
single_brute = BruteForce([(3, 4)])

assert single_tree.findNearestNeighbor(single_tree.root, (10, 10)).point == (3, 4)
assert single_brute.findNearestNeighbor((10, 10)) == (3, 4)


# Exact match
exact_points = [(1, 2), (3, 4), (5, 6)]
exact_tree = KDtree(exact_points)
exact_brute = BruteForce(exact_points)

assert exact_tree.findNearestNeighbor(exact_tree.root, (3, 4)).point == (3, 4)
assert exact_brute.findNearestNeighbor((3, 4)) == (3, 4)


# Three-dimensional points
points_3d = [(1, 2, 3), (4, 5, 6), (8, 9, 10)]
tree_3d = KDtree(points_3d)
brute_3d = BruteForce(points_3d)

assert tree_3d.findNearestNeighbor(tree_3d.root, (4, 5, 7)).point == (4, 5, 6)
assert brute_3d.findNearestNeighbor((4, 5, 7)) == (4, 5, 6)

print("All tests passed!")