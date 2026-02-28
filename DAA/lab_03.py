import time
import random

class Counter:
    def __init__(self):
        self.comparisons = 0
        self.swaps = 0

    def reset(self):
        self.comparisons = 0
        self.swaps = 0


class RecursiveSelectionSort:
    def __init__(self):
        self.counter = Counter()

    def find_min_index(self, arr, start, n):
        min_idx = start
        for j in range(start + 1, n):
            self.counter.comparisons += 1
            if arr[j] < arr[min_idx]:
                min_idx = j
        return min_idx

    def sort(self, arr, start=0):
        n = len(arr)
        if start >= n - 1:
            return

        min_idx = self.find_min_index(arr, start, n)

        if min_idx != start:
            arr[start], arr[min_idx] = arr[min_idx], arr[start]
            self.counter.swaps += 1

        self.sort(arr, start + 1)


def run_test(name, arr):
    sorter = RecursiveSelectionSort()
    data = arr.copy()

    start_time = time.perf_counter()
    sorter.sort(data)
    end_time = time.perf_counter()

    return {
        "name": name,
        "time": (end_time - start_time),
        "comparisons": sorter.counter.comparisons,
        "swaps": sorter.counter.swaps
    }


def print_table(results):
    print("\nRecursive Selection Sort Results:\n")
    print("{:<25} {:<20} {:<20} {:<15}".format(
        "Input Type", "Execution Time", "Comparisons", "Swaps"))
    print("-" * 80)

    for r in results:
        print("{:<25} {:<20.6f} {:<20} {:<15}".format(
            r["name"], r["time"], r["comparisons"], r["swaps"]))


def main():
    results = []

    # Given Test Cases
    results.append(run_test("Already Sorted", list(range(1, 26))))
    results.append(run_test("Reverse Sorted", list(range(25, 0, -1))))

    results.append(run_test("Random Order",
        [16,1,4,2,12,9,10,3,5,24,14,20,6,23,7,25,19,18,8,22,11,17,13,15,21]
    ))

    results.append(run_test("Nearly Sorted",
        [24,25,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,1,2]
    ))

    results.append(run_test("Single Unsorted",
        [2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,1]
    ))

    # Large Inputs
    large1 = random.sample(range(1, 1000), 60)
    large2 = random.sample(range(1, 10000), 250)

    results.append(run_test("Large Input (>50)", large1))
    results.append(run_test("Large Input (>200)", large2))

    print_table(results)


if __name__ == "__main__":
    main()