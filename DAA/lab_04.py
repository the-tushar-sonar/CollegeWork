import time
import random

class Counter:
    def __init__(self):
        self.comparisons = 0
        self.swaps = 0

    def reset(self):
        self.comparisons = 0
        self.swaps = 0

class IterativeSelectionSort:
    def __init__(self):
        self.counter = Counter()

    def sort(self, arr):
        n = len(arr)

        for i in range(n - 1):
            min_index = i

            for j in range(i + 1, n):
                self.counter.comparisons += 1
                if arr[j] < arr[min_index]:
                    min_index = j

            if min_index != i:
                arr[i], arr[min_index] = arr[min_index], arr[i]
                self.counter.swaps += 1

def run_test(name, arr):
    sorter = IterativeSelectionSort()
    data = arr.copy()

    start = time.perf_counter()
    sorter.sort(data)
    end = time.perf_counter()

    return {
        "name": name,
        "time": end - start,
        "comparisons": sorter.counter.comparisons,
        "swaps": sorter.counter.swaps
    }

def print_table(results):

    print("\nIterative Selection Sort Results:\n")

    print("{:<25} {:<18} {:<20} {:<10}".format(
        "Input Type", "Execution Time", "Comparisons", "Swaps"))

    print("-" * 80)

    for r in results:
        print("{:<25} {:<18.6f} {:<20} {:<10}".format(
            r["name"], r["time"], r["comparisons"], r["swaps"]))

def main():

    results = []

    results.append(run_test("Already Sorted", list(range(1, 26))))

    results.append(run_test("Reverse Sorted", list(range(25, 0, -1))))

    results.append(run_test(
        "Random Order",
        [16,1,4,2,12,9,10,3,5,24,14,20,6,23,7,25,19,18,8,22,11,17,13,15,21]
    ))

    results.append(run_test(
        "Nearly Sorted",
        [24,25,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,1,2]
    ))

    results.append(run_test(
        "Single Unsorted",
        [2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,1]
    ))

    large1 = random.sample(range(1,1000),60)
    large2 = random.sample(range(1,10000),250)

    results.append(run_test("Large Input (>50)", large1))
    results.append(run_test("Large Input (>200)", large2))

    print_table(results)

if __name__ == "__main__":
    main()