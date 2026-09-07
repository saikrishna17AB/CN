import java.io.*;
import java.net.*;
import java.util.*;

public class client2 {
    public static void main(String[] args) {

        try {
            Socket socket = new Socket("localhost", 5000);

            System.out.println("Connected to server!");

            BufferedReader input =
                    new BufferedReader(
                            new InputStreamReader(socket.getInputStream()));

            PrintWriter output =
                    new PrintWriter(socket.getOutputStream(), true);

            Scanner sc = new Scanner(System.in);

            String[] words = {
                    "apple", "book", "computer", "river", "school",
                    "teacher", "student", "house", "car", "tree",
                    "sun", "moon", "water", "food", "friend",
                    "keyboard", "phone", "garden", "ocean", "mountain"
            };

            Random random = new Random();

            String word = words[random.nextInt(words.length)];

            System.out.println("Random word: " + word);

            output.println(word);

            String response = input.readLine();

            if (response.equals("NOT_FOUND")) {

                System.out.println("Word not found in dictionary.");
                System.out.print("Enter meaning: ");

                String meaning = sc.nextLine();

                output.println(meaning);

                System.out.println(input.readLine());

            } else {

                System.out.println("Meaning: " + response);
            }

            input.close();
            output.close();
            socket.close();
            sc.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}