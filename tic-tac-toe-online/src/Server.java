

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

            DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
            DataInputStream inFromClient = new DataInputStream(connectionSocket.getInputStream());
            Field field = new Field(3);

            int x, y;

            while (true) {

                x = inFromClient.readInt();
                y = inFromClient.readInt();

                field.makeMove(x, y, ENEMY);
                field.display();

                if (Utils.checkFinished(field, ME)) {
                    break;
                }

                while (true) {
                    System.out.println("Make a step:");
                    x = scanner.nextInt();
                    y = scanner.nextInt();
                    if (field.makeMove(x, y, ME)) {
                        outToClient.writeInt(x);
                        outToClient.writeInt(y);
                        field.display();
                        break;
                    } else {
                        System.out.println("Invalid step!");
                    }
                }

                if (Utils.checkFinished(field, ME)) {
                    break;
                }
            }
        }
    }
}
