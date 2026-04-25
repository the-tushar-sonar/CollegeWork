import heapq

class Graph:
    def __init__(self, vertices, directed=False):
        self.V = vertices
        self.graph = {i: [] for i in range(vertices)}
        self.directed = directed

    def add_edge(self, u, v, w):
        self.graph[u].append((v, w))
        if not self.directed:
            self.graph[v].append((u, w))

    def dijkstra(self, src):
        dist = [float("inf")] * self.V
        dist[src] = 0

        pq = [(0, src)]  # (distance, node)

        while pq:
            current_dist, u = heapq.heappop(pq)

            for v, weight in self.graph[u]:
                if dist[v] > current_dist + weight:
                    dist[v] = current_dist + weight
                    heapq.heappush(pq, (dist[v], v))

        return dist

def main():
    V = int(input("Enter number of vertices: "))
    directed = input("Directed graph? (y/n): ").lower() == "y"

    g = Graph(V, directed)

    E = int(input("Enter number of edges: "))
    print("Enter edges (u v weight):")

    for _ in range(E):
        u, v, w = map(int, input().split())
        g.add_edge(u, v, w)

    src = int(input("Enter source node: "))

    distances = g.dijkstra(src)

    print("\nShortest distances from source node", src)
    for i in range(V):
        print(f"Node {i} -> Distance: {distances[i]}")

if __name__ == "__main__":
    main()