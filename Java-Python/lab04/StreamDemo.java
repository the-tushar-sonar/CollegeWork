package lab04;

import java.util.*;
import java.util.stream.*;

public class StreamDemo {
    public static void main(String[] args) {

        // List of integers
        List<Integer> numbers = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9);

        // Lambda + Stream (Filter even numbers)
        List<Integer> evenNumbers = numbers.stream()
                .filter(n -> n % 2 == 0)   // filter
                .collect(Collectors.toList());

        System.out.println("Even Numbers: " + evenNumbers);

        // Map (square each number)
        List<Integer> squares = numbers.stream()
                .map(n -> n * n)   // map
                .collect(Collectors.toList());

        System.out.println("Squares: " + squares);

        // Reduce (sum of all numbers)
        int sum = numbers.stream()
                .reduce(0, (a, b) -> a + b);   // reduce

        System.out.println("Sum: " + sum);

        // Optional Example
        List<String> names = Arrays.asList("Tushar", "Aman", "Riya");

        Optional<String> name = names.stream()
                .filter(n -> n.startsWith("Z")) // no match
                .findFirst();

        // Using Optional safely
        System.out.println("Result: " + name.orElse("No name found"));
    }
}