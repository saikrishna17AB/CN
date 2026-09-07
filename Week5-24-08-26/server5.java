import java.io.*;
import java.net.*;

public class server5{
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

            int[] results = {3, 3, 7, 15, 27};

            for (int i = 0; i < 5; i++) {

                int number = Integer.parseInt(input.readLine());

                output.println(results[number]);

                System.out.println(
                        "Received: " + number +
                        " Sent: " + results[number]);
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