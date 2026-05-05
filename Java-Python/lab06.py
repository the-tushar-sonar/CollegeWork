def groupAndSortOwners(files):
    result = {}

    # Group files by owner
    for file, owner in files.items():
        if owner not in result:
            result[owner] = []
        result[owner].append(file)

    # Sort file names for each owner
    for owner in result:
        result[owner].sort()

    return result


# Example usage
if __name__ == "__main__":
    files = {
        "Input.txt": "Albert",
        "Code.py": "Stanley",
        "Output.txt": "Albert",
        "btech.txt": "Albert",
    }

    grouped = groupAndSortOwners(files)
    print(grouped)
