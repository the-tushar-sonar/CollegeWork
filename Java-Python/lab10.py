import sqlite3
import threading


# Database setup
def setup_database():
    try:
        conn = sqlite3.connect("students.db")
        cursor = conn.cursor()

        cursor.execute(
            """
            CREATE TABLE IF NOT EXISTS students (
                id INTEGER PRIMARY KEY,
                name TEXT,
                age INTEGER
            )
        """
        )

        conn.commit()
        conn.close()
    except Exception as e:
        print("Database setup error:", e)


# Insert data (Thread task)
def insert_data(student):
    try:
        conn = sqlite3.connect("students.db")
        cursor = conn.cursor()

        cursor.execute("INSERT INTO students (id, name, age) VALUES (?, ?, ?)", student)

        conn.commit()
        conn.close()
        print(f"Inserted: {student}")

    except sqlite3.IntegrityError:
        print(f"Duplicate ID error for {student[0]}")
    except Exception as e:
        print("Insert error:", e)


# Fetch data
def fetch_data():
    try:
        conn = sqlite3.connect("students.db")
        cursor = conn.cursor()

        cursor.execute("SELECT * FROM students")
        rows = cursor.fetchall()

        print("\nDatabase Records:")
        for row in rows:
            print(row)

        conn.close()
    except Exception as e:
        print("Fetch error:", e)


# Main function
if __name__ == "__main__":
    setup_database()

    students = [
        (1, "Tushar", 21),
        (2, "Aman", 22),
        (3, "Riya", 20),
        (1, "Duplicate", 25),  # will trigger exception
    ]

    threads = []

    # Multithreading for insert
    for student in students:
        t = threading.Thread(target=insert_data, args=(student,))
        threads.append(t)
        t.start()

    # Wait for all threads
    for t in threads:
        t.join()

    # Fetch data
    fetch_data()
