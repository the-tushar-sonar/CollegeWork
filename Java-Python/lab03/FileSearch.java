package lab03;

import java.io.*;
import java.util.concurrent.*;

public class FileSearch {

    private static ExecutorService executor;

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java FileSearch <directory_path> <search_text>");
            return;
        }

        String dirPath = args[0];
        String searchText = args[1];

        executor = Executors.newFixedThreadPool(Runtime.getRuntime().availableProcessors());

        File root = new File(dirPath);

        if (!root.exists() || !root.isDirectory()) {
            System.out.println("Invalid directory path!");
            return;
        }

        traverseDirectory(root, searchText);

        executor.shutdown();
        try {
            executor.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        System.out.println("Search completed.");
    }

    // Recursive directory traversal
    private static void traverseDirectory(File dir, String searchText) {
        File[] files = dir.listFiles();
        if (files == null) return;

        for (File file : files) {
            if (file.isDirectory()) {
                traverseDirectory(file, searchText);
            } else {
                executor.submit(new FileTask(file, searchText));
            }
        }
    }
}

// Task for each file
class FileTask implements Runnable {
    private File file;
    private String searchText;

    public FileTask(File file, String searchText) {
        this.file = file;
        this.searchText = searchText;
    }

    @Override
    public void run() {
        int count = countOccurrences(file, searchText);
        if (count > 0) {
            System.out.println("File: " + file.getAbsolutePath() + " | Count: " + count);
        }
    }

    // Count occurrences of search text in file
    private int countOccurrences(File file, String searchText) {
        int count = 0;

        try (BufferedReader br = new BufferedReader(new FileReader(file))) {
            String line;

            while ((line = br.readLine()) != null) {
                int index = 0;
                while ((index = line.indexOf(searchText, index)) != -1) {
                    count++;
                    index += searchText.length();
                }
            }
        } catch (IOException e) {
            // Ignore unreadable files
        }

        return count;
    }
}