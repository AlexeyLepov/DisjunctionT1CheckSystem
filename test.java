import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

public class test {
    private static final int timeoutTime = 1;

    private static void read(String filename) {
        // Your code for reading the file goes here
    }

    private static void find(String filename) throws InterruptedException {
        // Your code for finding the file goes here

        // Simulate some random processing time
        // Random random = new Random();
        // int sleepTime = random.nextInt(2)*1000; // Sleep between 1-4 seconds
        // Thread.sleep(sleepTime);
    }

    private static void findTimeout(String filename) throws InterruptedException {
        Thread t = new Thread(() -> {
            try {
                find(filename);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        });
        t.start();
        t.join(timeoutTime * 1000);
    }

    public static void main(String[] args) {
        File folder = new File("./tests");
        File[] files = folder.listFiles();

        List<Double> times = new ArrayList<>();

        // Measure the execution time for each file
        for (File file : files) {
            long startTime = System.nanoTime();

            try {
                findTimeout(file.getName());
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            long endTime = System.nanoTime();
            double duration = (endTime - startTime) / 1_000_000_000.0;
            times.add(duration);
        }

        // Print the measured times in a single line
        StringBuilder output = new StringBuilder();
        for (double time : times) {
            if (time < timeoutTime) {
                output.append(time).append(" ");
            } else {
                output.append("inf ");
            }
        }
        output.deleteCharAt(output.length() - 1); // Remove the trailing space

        System.out.println(output);
        System.exit(0);
    }
}