package lab05;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.temporal.ChronoUnit;

public class DateDemo {

    // Function to calculate difference in days
    public static long getDaysBetween(LocalDate d1, LocalDate d2) {
        return ChronoUnit.DAYS.between(d1, d2);
    }

    public static void main(String[] args) {

        // LocalDate example
        LocalDate date1 = LocalDate.of(2024, 1, 1);
        LocalDate date2 = LocalDate.of(2024, 1, 10);

        System.out.println("LocalDate 1: " + date1);
        System.out.println("LocalDate 2: " + date2);

        // Difference in days
        long days = getDaysBetween(date1, date2);
        System.out.println("Difference in days: " + days);

        // LocalDateTime example
        LocalDateTime dateTime1 = LocalDateTime.now();
        LocalDateTime dateTime2 = dateTime1.plusDays(5).plusHours(3);

        System.out.println("\nLocalDateTime 1: " + dateTime1);
        System.out.println("LocalDateTime 2: " + dateTime2);

        long daysBetweenDateTime = ChronoUnit.DAYS.between(dateTime1, dateTime2);
        System.out.println("Difference (DateTime in days): " + daysBetweenDateTime);
    }
}