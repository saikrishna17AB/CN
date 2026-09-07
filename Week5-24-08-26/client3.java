import java.io.*;
import java.net.*;
import java.util.*;

public class client3{
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

            System.out.print("Enter an integer: ");

            int n = sc.nextInt();

            output.println(n);

            String result = input.readLine();

            System.out.println("Factorial: " + result);

            input.close();
            output.close();
            socket.close();
            sc.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}