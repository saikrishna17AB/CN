import java.net.*;
import java.util.*;

public class client7{
    public static void main(String[] args) {

        try {
            DatagramSocket socket = new DatagramSocket();

            Scanner sc = new Scanner(System.in);

            System.out.print("Enter a string: ");

            String str = sc.nextLine();

            byte[] sendData = str.getBytes();

            InetAddress address =
                    InetAddress.getByName("localhost");

            DatagramPacket sendPacket =
                    new DatagramPacket(
                            sendData,
                            sendData.length,
                            address,
                            5000);

            socket.send(sendPacket);

            byte[] receiveData = new byte[1024];

            DatagramPacket receivePacket =
                    new DatagramPacket(
                            receiveData,
                            receiveData.length);

            socket.receive(receivePacket);

            String result =
                    new String(
                            receivePacket.getData(),
                            0,
                            receivePacket.getLength());

            System.out.println("Server response: " + result);

            socket.close();
            sc.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}