
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.Socket;
import java.util.*;
import java.io.IOException;

/**
 * Created by vadim on 01/06/17.
 */
public class Client {

    public static void main(String[] args) throws IOException {
        (new Client()).startPlaying(Integer.parseInt(args[0]));
    }

    public void startPlaying(int port) throws IOException {
        char ME = 'x';
        char ENEMY = 'o';

        Scanner scanner = new Scanner(System.in);
        Socket socket = new Socket("localhost", port);

        DataInputStream inFromServer = new DataInputStream(socket.getInputStream());
        DataOutputStream outToServer = new DataOutputStream(socket.getOutputStream());

        int x, y;
        Field field = new Field(3);

        while (true) {
            while (true) {
                System.out.println("Make a step:");
                x = scanner.nextInt();
                y = scanner.nextInt();
                if (field.makeMove(x, y, ME)) {
                    outToServer.writeInt(x);
                    outToServer.writeInt(y);
                    field.display();
                    break;
                } else {
                    System.out.println("Invalid!");
                }
            }

            if (Utils.checkFinished(field, ME)) {
                break;
            }

            x = inFromServer.readInt();
            y = inFromServer.readInt();

            field.makeMove(x, y, ENEMY);
            field.display();

            if (Utils.checkFinished(field, ME)) {
                break;
            }
        }
    }
}
