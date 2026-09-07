import java.io.*;
import java.net.*;

public class server4{
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

            int marks = Integer.parseInt(input.readLine());

            String grade;

            if (marks >= 85 && marks <= 100) {
                grade = "Grade A";
            } else if (marks >= 70) {
                grade = "Grade B";
            } else if (marks >= 60) {
                grade = "Grade C";
            } else if (marks >= 50) {
                grade = "Grade D";
            } else if (marks >= 0) {
                grade = "Fail";
            } else {
                grade = "Invalid marks";
            }

            output.println(grade);

            System.out.println("Grade sent: " + grade);

            input.close();
            output.close();
            socket.close();
            serverSocket.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}