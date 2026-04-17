# Base Class
class Animal:
    def __init__(self, name):
        self.name = name

    def sound(self):
        print("Animal makes a sound")

    # Method Overloading using default arguments
    def info(self, age=None):
        if age:
            print(f"{self.name} is {age} years old")
        else:
            print(f"{self.name} is an animal")

# Derived Class (Inheritance + Overriding)
class Dog(Animal):
    def __init__(self, name, breed):
        super().__init__(name)
        self.breed = breed

    # Method Overriding
    def sound(self):
        print("Dog barks")

    def display(self):
        print(f"Name: {self.name}, Breed: {self.breed}")

# Another Derived Class
class Cat(Animal):
    def sound(self):
        print("Cat meows")

# Main Program
if __name__ == "__main__":
    # Creating objects
    a = Animal("Generic Animal")
    d = Dog("Buddy", "Golden Retriever")
    c = Cat("Whiskers")

    print("\n--- Animal ---")
    a.sound()
    a.info()
    a.info(5)

    print("\n--- Dog ---")
    d.sound()   # Overridden method
    d.display()
    d.info(3)

    print("\n--- Cat ---")
    c.sound()   # Overridden method
    c.info()