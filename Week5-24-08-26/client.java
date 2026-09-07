import java.io.*;
import java.net.*;

public class client {
    public static void main(String[] args) {

        try {
            Socket socket = new Socket("localhost", 5000);

            System.out.println("Connected to server!");

            BufferedReader input =
                    new BufferedReader(
                        new InputStreamReader(socket.getInputStream())
                    );

            String dateTime = input.readLine();

            System.out.println("Server Date and Time: " + dateTime);

            input.close();
            socket.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}