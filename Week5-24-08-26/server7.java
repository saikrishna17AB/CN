import java.net.*;

public class server7{
    public static void main(String[] args) {

        try {
            DatagramSocket socket = new DatagramSocket(5000);

            System.out.println("UDP Server started...");
            System.out.println("Waiting for client...");

            byte[] receiveData = new byte[1024];

            DatagramPacket receivePacket =
                    new DatagramPacket(
                            receiveData,
                            receiveData.length);

            socket.receive(receivePacket);

            String str =
                    new String(
                            receivePacket.getData(),
                            0,
                            receivePacket.getLength());

            System.out.println("Received: " + str);

            String reverse = "";

            for (int i = str.length() - 1; i >= 0; i--) {
                reverse = reverse + str.charAt(i);
            }

            String result;

            if (str.equalsIgnoreCase(reverse)) {
                result = "Palindrome";
            } else {
                result = "Not a palindrome";
            }

            byte[] sendData = result.getBytes();

            InetAddress address = receivePacket.getAddress();

            int port = receivePacket.getPort();

            DatagramPacket sendPacket =
                    new DatagramPacket(
                            sendData,
                            sendData.length,
                            address,
                            port);

            socket.send(sendPacket);

            System.out.println("Result sent: " + result);

            socket.close();

        } catch (Exception e) {
            System.out.println(e);
        }
    }
}