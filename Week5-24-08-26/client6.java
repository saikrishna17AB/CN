import java.io.*;
import java.net.*;
import java.util.*;

public class client6{
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

            while (true) {

                System.out.print("Enter word: ");

                String word = sc.nextLine();

                if (word.equalsIgnoreCase("exit")) {
                    output.println("exit");
                    break;
                }

                System.out.print("Enter number: ");

                int number = sc.nextInt();
                sc.nextLine();

                output.println(word);
                output.println(number);

                String result = input.readLine();

                System.out.println("Result: " + result);
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