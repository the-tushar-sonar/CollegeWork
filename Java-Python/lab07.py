import cmath  # for complex roots


class QuadraticEquationSolver:
    def __init__(self, a, b, c):
        self.a = a
        self.b = b
        self.c = c

    def findRoot(self):
        if self.a == 0:
            return "Not a quadratic equation"

        D = self.b**2 - 4 * self.a * self.c

        root1 = (-self.b + cmath.sqrt(D)) / (2 * self.a)
        root2 = (-self.b - cmath.sqrt(D)) / (2 * self.a)

        return root1, root2


# Example usage
if __name__ == "__main__":
    solver = QuadraticEquationSolver(1, -3, 2)
    roots = solver.findRoot()
    print("Roots:", roots)
