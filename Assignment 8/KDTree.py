
import math
import sys
from typing import Optional, TypeAlias

Point: TypeAlias = tuple[float, ...]


def euclidian_distance(point1: Point, point2: Point) -> float:
    """
    Calculates the Euclidean distance between two points.

    Args:
        point1: The first point.
        point2: The second point.

    Returns:
        The Euclidean distance between the two points.
    """
    sum = 0
    for i in range(len(point1)):
        sum = sum + (point1[i] - point2[i])**2
    return math.sqrt(sum)


def closest(
    query: Point,
    node1: Optional["Node"],
    node2: Optional["Node"]
) -> Optional["Node"]:
    """
    Finds which of two nodes is closest to a query point.

    Args:
        query: The point to compare distances against.
        node1: The first node, or None.
        node2: The second node, or None.

    Returns:
        The node closest to the query, or None if both
        nodes are None.
    """
    if node1 is None:
        return node2
    if node2 is None:
        return node1

    query_node1 = euclidian_distance(node1.point, query)
    query_node2 = euclidian_distance(node2.point, query)

    if query_node1 < query_node2:
        return node1
    else:
        return node2


class Node:
    """
    Represents a node in a KD-tree.

    Attributes:
        point: The k-dimensional point stored in the node.
        left: The left child node.
        right: The right child node.
    """

    def __init__(self, point: Point) -> None:
        """
        Initializes a KD-tree node.

        Args:
            point: The point stored in this node.
        """
        self.point: Point = point
        self.left: Optional["Node"] = None
        self.right: Optional["Node"] = None


class KDtree:
    """
    A KD-tree for organizing k-dimensional points and
    performing nearest-neighbor searches.

    Attributes:
        points: The original collection of points.
        root: The root node of the KD-tree.
    """

    def __init__(self, points: list[Point]) -> None:
        """
        Initializes and constructs the KD-tree.

        Args:
            points: A list of k-dimensional points.
        """
        self.points: list[Point] = points
        self.root: Optional[Node] = self.setup(points)

    def setup(
        self,
        points: list[Point],
        depth: int = 0
    ) -> Optional[Node]:
        """
        Recursively constructs a balanced KD-tree by
        splitting points along alternating dimensions.

        Args:
            points: The points to organize into a subtree.
            depth: The current depth of the tree.

        Returns:
            The root node of the constructed subtree,
            or None if the list is empty.
        """
        if len(points) == 0:
            return None

        k = len(points[0])
        axis = depth % k

        points = sorted(points, key=lambda p: p[axis])
        mid = len(points) // 2

        node = Node(points[mid])
        node.left = self.setup(points[:mid], depth + 1)
        node.right = self.setup(points[mid + 1:], depth + 1)

        return node

    def findNearestNeighbor(
        self,
        root: Optional[Node],
        query: Point,
        depth: int = 0
    ) -> Optional[Node]:
        """
        Recursively finds the nearest neighbor to a query
        point using KD-tree traversal and branch pruning.

        Searches the subtree on the query's side of the
        splitting plane first. The opposite subtree is
        searched only if it could contain a closer point.

        Args:
            root: The current subtree root.
            query: The point whose nearest neighbor is sought.
            depth: The current depth of the search.

        Returns:
            The node containing the nearest point,
            or None if the subtree is empty.
        """
        if root is None:
            return None

        k = len(self.points[0])

        if query[depth % k] < root.point[depth % k]:
            nextBranch = root.left
            otherBranch = root.right
        else:
            otherBranch = root.left
            nextBranch = root.right

        temp = self.findNearestNeighbor(
            nextBranch, query, depth + 1
        )
        best = closest(query, temp, root)

        radius = euclidian_distance(query, best.point)
        dist = abs(
            query[depth % k] - root.point[depth % k]
        )

        if radius >= dist:
            temp = self.findNearestNeighbor(
                otherBranch, query, depth + 1
            )
            best = closest(query, temp, best)

        return best
    def printTree(self, node=None, depth=0):
        """
        Recursively prints the KD-tree structure.

        Args:
            node: The current node.
            depth: The current depth of the tree.
        """
        if depth == 0:
            node = self.root

        if node is None:
            return

        print("  " * depth + str(node.point))

        self.printTree(node.left, depth + 1)
        self.printTree(node.right, depth + 1)

class BruteForce:
    """
    Implements brute-force nearest-neighbor search.

    Attributes:
        points: The collection of points to search.
    """

    def __init__(self, points: list[Point]) -> None:
        """
        Initializes the brute-force search.

        Args:
            points: A list of k-dimensional points.
        """
        self.points: list[Point] = points

    def findNearestNeighbor(
        self,
        query: Point
    ) -> Optional[Point]:
        """
        Finds the nearest neighbor by checking every point.

        Args:
            query: The point whose nearest neighbor is sought.

        Returns:
            The closest point, or None if the list is empty.
        """
        selection: Optional[Point] = None
        minDist: float = sys.maxsize

        for point in self.points:
            dist = euclidian_distance(point, query)

            if dist < minDist:
                selection = point
                minDist = dist

        return selection
