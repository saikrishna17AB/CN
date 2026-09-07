import java.io.*;
import java.net.*;

public class server3{
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

            int n = Integer.parseInt(input.readLine());

            long factorial = 1;

            for (int i = 1; i <= n; i++) {
                factorial = factorial * i;
            }

            output.println(factorial);

            System.out.println("Factorial sent: " + factorial);

            input.close();
            output.close();
            socket.close();
            serverSocket.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}