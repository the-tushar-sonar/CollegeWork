class Counter:
    def __init__(self):
        self.comparisons = 0
        self.shifts = 0

    def reset(self):
        self.comparisons = 0
        self.shifts = 0


class Stack:
    def __init__(self):
        self.stack = []
        self.counter = Counter()

    def create(self):
        self.stack = []
        self.counter.reset()

    def insert(self, value):   # push
        self.stack.append(value)

    def delete(self):          # pop
        if not self.stack:
            print("Stack Underflow!")
            return
        return self.stack.pop()

    def search(self, value):
        for i in range(len(self.stack) - 1, -1, -1):
            self.counter.comparisons += 1
            if self.stack[i] == value:
                return i
        return -1

    def update(self, pos, value):
        if pos < 0 or pos >= len(self.stack):
            print("Invalid position!")
            return
        self.stack[pos] = value

    def display(self):
        if not self.stack:
            print("Stack is empty")
        else:
            print("Stack:", self.stack)


class Queue:
    def __init__(self):
        self.queue = []
        self.counter = Counter()

    def create(self):
        self.queue = []
        self.counter.reset()

    def insert(self, value):   # enqueue
        self.queue.append(value)

    def delete(self):          # dequeue
        if not self.queue:
            print("Queue Underflow!")
            return
        self.counter.shifts += len(self.queue) - 1  # shifting cost
        return self.queue.pop(0)

    def search(self, value):
        for i in range(len(self.queue)):
            self.counter.comparisons += 1
            if self.queue[i] == value:
                return i
        return -1

    def update(self, pos, value):
        if pos < 0 or pos >= len(self.queue):
            print("Invalid position!")
            return
        self.queue[pos] = value

    def display(self):
        if not self.queue:
            print("Queue is empty")
        else:
            print("Queue:", self.queue)


def show_metrics(ds):
    print("Comparisons:", ds.counter.comparisons)
    print("Shifts:", ds.counter.shifts)


def main():
    stack = Stack()
    queue = Queue()

    while True:
        print("\n===== DATA STRUCTURE MENU =====")
        print("1. Stack")
        print("2. Queue")
        print("0. Exit")

        choice = int(input("Enter choice: "))

        if choice == 0:
            print("Exiting...")
            break

        elif choice == 1:
            while True:
                print("\nSTACK MENU")
                print("1. Create")
                print("2. Push")
                print("3. Pop")
                print("4. Search")
                print("5. Update")
                print("6. Display")
                print("0. Back")

                ch = int(input("Enter choice: "))

                if ch == 0:
                    break

                elif ch == 1:
                    stack.create()
                    print("Stack initialized.")

                elif ch == 2:
                    val = int(input("Enter value: "))
                    stack.insert(val)

                elif ch == 3:
                    stack.delete()

                elif ch == 4:
                    stack.counter.reset()
                    val = int(input("Enter value: "))
                    print("Index:", stack.search(val))
                    show_metrics(stack)

                elif ch == 5:
                    pos = int(input("Enter position: "))
                    val = int(input("Enter new value: "))
                    stack.update(pos, val)

                elif ch == 6:
                    stack.display()

                else:
                    print("Invalid choice!")

        elif choice == 2:
            while True:
                print("\nQUEUE MENU")
                print("1. Create")
                print("2. Enqueue")
                print("3. Dequeue")
                print("4. Search")
                print("5. Update")
                print("6. Display")
                print("0. Back")

                ch = int(input("Enter choice: "))

                if ch == 0:
                    break

                elif ch == 1:
                    queue.create()
                    print("Queue initialized.")

                elif ch == 2:
                    val = int(input("Enter value: "))
                    queue.insert(val)

                elif ch == 3:
                    queue.counter.reset()
                    queue.delete()
                    show_metrics(queue)

                elif ch == 4:
                    queue.counter.reset()
                    val = int(input("Enter value: "))
                    print("Index:", queue.search(val))
                    show_metrics(queue)

                elif ch == 5:
                    pos = int(input("Enter position: "))
                    val = int(input("Enter new value: "))
                    queue.update(pos, val)

                elif ch == 6:
                    queue.display()

                else:
                    print("Invalid choice!")

        else:
            print("Invalid main choice!")


if __name__ == "__main__":
    main()