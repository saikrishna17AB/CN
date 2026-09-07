import java.io.*;
import java.net.*;
import java.util.*;

public class server6{
    public static void main(String[] args) {

        try {
            ServerSocket serverSocket = new ServerSocket(5000);

            System.out.println("Server started...");
            System.out.println("Waiting for client...");

            Socket socket = serverSocket.accept();

            System.out.println("Client connected!");

            BufferedReader input =
                    new BufferedReader(
                            new InputStreamReader(socket.getInputStream()));

            PrintWriter output =
                    new PrintWriter(socket.getOutputStream(), true);

            while (true) {

                String word = input.readLine();

                if (word == null || word.equalsIgnoreCase("exit")) {
                    break;
                }

                int number = Integer.parseInt(input.readLine());

                HashMap<Character, Integer> count = new HashMap<>();

                for (char c : word.toCharArray()) {
                    count.put(c, count.getOrDefault(c, 0) + 1);
                }

                char answer = word.charAt(0);
                boolean found = false;

                for (char c : word.toCharArray()) {
                    if (count.get(c) == number) {
                        answer = c;
                        found = true;
                        break;
                    }
                }

                if (!found) {

                    int maximum = 0;

                    for (char c : word.toCharArray()) {
                        if (count.get(c) > maximum) {
                            maximum = count.get(c);
                            answer = c;
                        }
                    }
                }

                output.println(answer);

                System.out.println(
                        "Word: " + word +
                        ", Number: " + number +
                        ", Answer: " + answer);
            }

            input.close();
            output.close();
            socket.close();
            serverSocket.close();

            System.out.println("Connection terminated.");

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}