def print_pattern(n):
    num = 2 * (n**2) - 1  # starting number

    for i in range(n):
        # print tabs for alignment
        print("\t" * i, end="")

        # number of elements in row
        count = 2 * (n - i) - 1

        temp = num
        for j in range(count):
            print(temp, end="\t")  # use tab between numbers
            temp -= 2

        print()
        num = temp


# Input
rows = int(input("Enter number of rows: "))
print_pattern(rows)