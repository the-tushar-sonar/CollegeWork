class Graph:
    def __init__(self, vertices, directed=False):
        self.V = vertices
        self.graph = {i: [] for i in range(vertices)}
        self.directed = directed

    def add_edge(self, u, v):
        self.graph[u].append(v)
        if not self.directed:
            self.graph[v].append(u)

    def dfs_util(self, node, visited, traversal):
        visited[node] = True
        traversal.append(node)

        for neighbor in self.graph[node]:
            if not visited[neighbor]:
                self.dfs_util(neighbor, visited, traversal)

    def dfs_disconnected(self, start):
        visited = [False] * self.V
        all_traversals = []
        total_nodes = 0

        # DFS from starting node
        traversal = []
        self.dfs_util(start, visited, traversal)
        all_traversals.append(traversal)
        total_nodes += len(traversal)

        # Handle disconnected components
        for i in range(self.V):
            if not visited[i]:
                traversal = []
                self.dfs_util(i, visited, traversal)
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

    traversals, total = g.dfs_disconnected(start)

    print("\nDFS Traversal:")

    for i, t in enumerate(traversals):
        print(f"Component {i+1}: {' -> '.join(map(str, t))}")

    print("\nTotal nodes visited:", total)

if __name__ == "__main__":
    main()