import java.io.*;
import java.net.*;

public class client5{
    public static void main(String[] args) {

        try {
            Socket socket = new Socket("localhost", 5000);

            System.out.println("Connected to server!");

            BufferedReader input =
                    new BufferedReader(
                            new InputStreamReader(socket.getInputStream()));

            PrintWriter output =
                    new PrintWriter(socket.getOutputStream(), true);

            for (int i = 0; i <= 4; i++) {

                output.println(i);

                String result = input.readLine();

                System.out.println(i + " -> " + result);
            }

            input.close();
            output.close();
            socket.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}