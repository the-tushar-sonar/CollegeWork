class Counter:
    def __init__(self):
        self.comparisons = 0
        self.shifts = 0

    def reset(self):
        self.comparisons = 0
        self.shifts = 0

class ArrayDS:
    def __init__(self):
        self.arr = []
        self.counter = Counter()

    def create(self, elements):
        self.arr = elements
        self.counter.reset()

    def insert(self, pos, value):
        self.arr.append(0)
        for i in range(len(self.arr) - 1, pos, -1):
            self.arr[i] = self.arr[i - 1]
            self.counter.shifts += 1
        self.arr[pos] = value

    def search(self, value):
        for i in range(len(self.arr)):
            self.counter.comparisons += 1
            if self.arr[i] == value:
                return i
        return -1

    def delete(self, pos):
        for i in range(pos, len(self.arr) - 1):
            self.arr[i] = self.arr[i + 1]
            self.counter.shifts += 1
        self.arr.pop()

    def update(self, pos, value):
        self.arr[pos] = value

    def reverse(self):
        n = len(self.arr)
        for i in range(n // 2):
            self.arr[i], self.arr[n - i - 1] = self.arr[n - i - 1], self.arr[i]
            self.counter.shifts += 1

    def display(self):
        print(self.arr)


class SNode:
    def __init__(self, data):
        self.data = data
        self.next = None


class SinglyLinkedList:
    def __init__(self):
        self.head = None
        self.counter = Counter()

    def create(self, elements):
        self.head = None
        self.counter.reset()
        for e in elements:
            self.insert_end(e)

    def insert_end(self, value):
        new = SNode(value)
        if not self.head:
            self.head = new
            return
        temp = self.head
        while temp.next:
            temp = temp.next
        temp.next = new

    def insert(self, pos, value):
        new = SNode(value)
        if pos == 0:
            new.next = self.head
            self.head = new
            return
        temp = self.head
        for _ in range(pos - 1):
            temp = temp.next
        new.next = temp.next
        temp.next = new

    def search(self, value):
        temp = self.head
        idx = 0
        while temp:
            self.counter.comparisons += 1
            if temp.data == value:
                return idx
            temp = temp.next
            idx += 1
        return -1

    def delete(self, pos):
        if pos == 0:
            self.head = self.head.next
            return
        temp = self.head
        for _ in range(pos - 1):
            temp = temp.next
        temp.next = temp.next.next

    def update(self, pos, value):
        temp = self.head
        for _ in range(pos):
            temp = temp.next
        temp.data = value

    def reverse(self):
        prev = None
        curr = self.head
        while curr:
            nxt = curr.next
            curr.next = prev
            prev = curr
            curr = nxt
            self.counter.shifts += 1
        self.head = prev

    def display(self):
        temp = self.head
        while temp:
            print(temp.data, end=" -> ")
            temp = temp.next
        print("NULL")


class DNode:
    def __init__(self, data):
        self.data = data
        self.prev = None
        self.next = None


class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.counter = Counter()

    def create(self, elements):
        self.head = None
        self.counter.reset()
        for e in elements:
            self.insert_end(e)

    def insert_end(self, value):
        new = DNode(value)
        if not self.head:
            self.head = new
            return
        temp = self.head
        while temp.next:
            temp = temp.next
        temp.next = new
        new.prev = temp

    def insert(self, pos, value):
        new = DNode(value)
        if pos == 0:
            new.next = self.head
            if self.head:
                self.head.prev = new
            self.head = new
            return
        temp = self.head
        for _ in range(pos - 1):
            temp = temp.next
        new.next = temp.next
        new.prev = temp
        if temp.next:
            temp.next.prev = new
        temp.next = new

    def search(self, value):
        temp = self.head
        idx = 0
        while temp:
            self.counter.comparisons += 1
            if temp.data == value:
                return idx
            temp = temp.next
            idx += 1
        return -1

    def delete(self, pos):
        if pos == 0:
            self.head = self.head.next
            if self.head:
                self.head.prev = None
            return
        temp = self.head
        for _ in range(pos):
            temp = temp.next
        temp.prev.next = temp.next
        if temp.next:
            temp.next.prev = temp.prev

    def update(self, pos, value):
        temp = self.head
        for _ in range(pos):
            temp = temp.next
        temp.data = value

    def reverse(self):
        curr = self.head
        temp = None
        while curr:
            temp = curr.prev
            curr.prev = curr.next
            curr.next = temp
            curr = curr.prev
            self.counter.shifts += 1
        if temp:
            self.head = temp.prev

    def display(self):
        temp = self.head
        while temp:
            print(temp.data, end=" <-> ")
            temp = temp.next
        print("NULL")

def show_metrics(ds):
    print("Comparisons:", ds.counter.comparisons)
    print("Shifts:", ds.counter.shifts)


def main():
    array = ArrayDS()
    sll = SinglyLinkedList()
    dll = DoublyLinkedList()

    while True:
        print("\n===== DATA STRUCTURE MENU =====")
        print("1. Array 2. SLL 3. DLL 0. Exit")
        choice = int(input("Choice: "))

        if choice == 0:
            break

        if choice == 1:
            while True:
                print("\nARRAY: 1. Create 2. Insert 3. Search 4. Delete 5. Update 6. Reverse 7. Display 0. Back")
                ch = int(input("Choice: "))
                if ch == 0:
                    break
                if ch == 1:
                    array.create(list(map(int, input("Elements: ").split())))
                elif ch == 2:
                    array.counter.reset()
                    array.insert(int(input("Pos: ")), int(input("Value: ")))
                    show_metrics(array)
                elif ch == 3:
                    array.counter.reset()
                    print("Index:", array.search(int(input("Value: "))))
                    show_metrics(array)
                elif ch == 4:
                    array.counter.reset()
                    array.delete(int(input("Pos: ")))
                    show_metrics(array)
                elif ch == 5:
                    array.update(int(input("Pos: ")), int(input("Value: ")))
                elif ch == 6:
                    array.counter.reset()
                    array.reverse()
                    show_metrics(array)
                elif ch == 7:
                    array.display()

        elif choice == 2:
            while True:
                print("\nSLL: 1. Create 2. Insert 3. Search 4. Delete 5. Update 6. Reverse 7. Display 0. Back")
                ch = int(input("Choice: "))
                if ch == 0:
                    break
                if ch == 1:
                    sll.create(list(map(int, input("Elements: ").split())))
                elif ch == 2:
                    sll.insert(int(input("Pos: ")), int(input("Value: ")))
                elif ch == 3:
                    sll.counter.reset()
                    print("Index:", sll.search(int(input("Value: "))))
                    show_metrics(sll)
                elif ch == 4:
                    sll.delete(int(input("Pos: ")))
                elif ch == 5:
                    sll.update(int(input("Pos: ")), int(input("Value: ")))
                elif ch == 6:
                    sll.counter.reset()
                    sll.reverse()
                    show_metrics(sll)
                elif ch == 7:
                    sll.display()

        elif choice == 3:
            while True:
                print("\nDLL: 1. Create 2. Insert 3. Search 4. Delete 5. Update 6. Reverse 7. Display 0. Back")
                ch = int(input("Choice: "))
                if ch == 0:
                    break
                if ch == 1:
                    dll.create(list(map(int, input("Elements: ").split())))
                elif ch == 2:
                    dll.insert(int(input("Pos: ")), int(input("Value: ")))
                elif ch == 3:
                    dll.counter.reset()
                    print("Index:", dll.search(int(input("Value: "))))
                    show_metrics(dll)
                elif ch == 4:
                    dll.delete(int(input("Pos: ")))
                elif ch == 5:
                    dll.update(int(input("Pos: ")), int(input("Value: ")))
                elif ch == 6:
                    dll.counter.reset()
                    dll.reverse()
                    show_metrics(dll)
                elif ch == 7:
                    dll.display()

if __name__ == "__main__":
    main()