from collections import deque

class Graph:
    def __init__(self, vertices, directed=False):
        self.V = vertices
        self.graph = {i: [] for i in range(vertices)}
        self.directed = directed

    def add_edge(self, u, v):
        self.graph[u].append(v)
        if not self.directed:
            self.graph[v].append(u)

    def bfs(self, start, visited):
        queue = deque()
        queue.append(start)
        visited[start] = True

        traversal = []

        while queue:
            node = queue.popleft()
            traversal.append(node)

            for neighbor in self.graph[node]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    queue.append(neighbor)

        return traversal

    def bfs_disconnected(self, start):
        visited = [False] * self.V
        all_traversals = []
        total_nodes = 0

        # BFS from starting node
        traversal = self.bfs(start, visited)
        all_traversals.append(traversal)
        total_nodes += len(traversal)

        # Check for disconnected components
        for i in range(self.V):
            if not visited[i]:
                traversal = self.bfs(i, visited)
                all_traversals.append(traversal)
                total_nodes += len(traversal)

        return all_traversals, total_nodes

def main():
    V = int(input("Enter number of vertices: "))
    directed = input("Directed graph? (y/n): ").lower() == "y"

    g = Graph(V, directed)

    E = int(input("Enter number of edges: "))
    print("Enter edges (u v):")

    for _ in range(E):
        u, v = map(int, input().split())
        g.add_edge(u, v)

    start = int(input("Enter starting node: "))

    traversals, total = g.bfs_disconnected(start)

    print("\nBFS Traversal:")

    for i, t in enumerate(traversals):
        print(f"Component {i+1}: {' -> '.join(map(str, t))}")

    print("\nTotal nodes visited:", total)

if __name__ == "__main__":
    main()