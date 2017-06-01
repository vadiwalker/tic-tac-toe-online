

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;

/**
 * Created by vadim on 01/06/17.
 */
public class Server {

    private char a[][] = new char[4][4];


    public static void main(String[] args) throws IOException {
        new Server().startPlaying(Integer.parseInt(args[0]));
    }

    private void startPlaying(int port) throws IOException {
        char ENEMY = 'x';
        char ME = 'o';

        ServerSocket serverSocket = new ServerSocket(port);
        Scanner scanner = new Scanner(System.in);

        while (true) {
            Socket connectionSocket = serverSocket.accept();
//            Scanner inFromClient = new Scanner(connectionSocket.getInputStream());
            DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
            DataInputStream inFromClient = new DataInputStream(connectionSocket.getInputStream());
            int x, y;
            BufferedReader br = new BufferedReader(
                    new InputStreamReader(connectionSocket.getInputStream()));

            Field field = new Field(3);
            while (true) {

                System.err.println("StartReading");
                x = inFromClient.readInt();
                System.err.println("One good!");
                y = inFromClient.readInt();
                System.err.println("x: " + x + " y: " + y);


                assert field.makeMove(x, y, ENEMY);

                if (field.isFinished()) {
                    System.out.println("GAME OVER");
                    break;
                }

                while (true) {
                    System.out.println("Make a step:");
                    x = scanner.nextInt();
                    y = scanner.nextInt();
                    if (field.makeMove(x, y, ME)) {
                        outToClient.write(x);
                        outToClient.write(y);
                        outToClient.flush();
                        break;
                    } else {
                        System.out.println("Invalid step!");
                    }
                }

                if (field.isFinished()) {
                    System.out.println("GAME OVER");
                    break;
                }
            }
        }
    }
}
