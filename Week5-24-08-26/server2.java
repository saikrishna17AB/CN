import java.io.*;
import java.net.*;
import java.util.*;

public class server2{
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

            HashMap<String, String> dictionary = new HashMap<>();

            dictionary.put("apple", "a fruit");
            dictionary.put("book", "a collection of written pages");
            dictionary.put("computer", "an electronic machine");
            dictionary.put("river", "a natural flowing watercourse");
            dictionary.put("school", "a place for education");
            dictionary.put("teacher", "a person who teaches");
            dictionary.put("student", "a person who studies");
            dictionary.put("house", "a building for living");
            dictionary.put("car", "a road vehicle");
            dictionary.put("tree", "a plant with a trunk");
            dictionary.put("sun", "the star at the center of our solar system");
            dictionary.put("moon", "the natural satellite of Earth");
            dictionary.put("water", "a transparent liquid");
            dictionary.put("food", "substance consumed for nutrition");
            dictionary.put("friend", "a person whom you know and like");

            String word = input.readLine();

            System.out.println("Word received: " + word);

            if (dictionary.containsKey(word.toLowerCase())) {

                output.println(dictionary.get(word.toLowerCase()));

            } else {

                output.println("NOT_FOUND");

                String meaning = input.readLine();

                dictionary.put(word.toLowerCase(), meaning);

                output.println("Word added to dictionary.");

                System.out.println("New word added: " + word);
                System.out.println("Meaning: " + meaning);
            }

            input.close();
            output.close();
            socket.close();
            serverSocket.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}