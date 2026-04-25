class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.edges = []  # edge list (u, v, w)

    def add_edge(self, u, v, w):
        self.edges.append((u, v, w))

    def bellman_ford(self, src):
        dist = [float("inf")] * self.V
        dist[src] = 0

        # Relax edges V-1 times
        for _ in range(self.V - 1):
            for u, v, w in self.edges:
                if dist[u] != float("inf") and dist[u] + w < dist[v]:
                    dist[v] = dist[u] + w

        # Check for negative weight cycle
        for u, v, w in self.edges:
            if dist[u] != float("inf") and dist[u] + w < dist[v]:
                print("Graph contains negative weight cycle")
                return None

        return dist

def main():
    V = int(input("Enter number of vertices: "))
    E = int(input("Enter number of edges: "))

    g = Graph(V)

    print("Enter edges (u v weight):")
    for _ in range(E):
        u, v, w = map(int, input().split())
        g.add_edge(u, v, w)

    src = int(input("Enter source node: "))

    result = g.bellman_ford(src)

    if result:
        print("\nShortest distances from source node", src)
        for i in range(V):
            print(f"Node {i} -> Distance: {result[i]}")

if __name__ == "__main__":
    main()