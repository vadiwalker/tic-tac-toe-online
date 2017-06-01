
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
        Scanner scanner = new Scanner(System.in);
        Socket socket = new Socket("localhost", port);
        DataOutputStream outToServer = new DataOutputStream(socket.getOutputStream());
        Scanner inFromServer = new Scanner(socket.getInputStream());
        int x, y;
        Field field = new Field(3);
        char ME = 'x';
        char ENEMY = 'o';
        while (true) {
            while (true) {
                System.out.println("Make a step:");
                x = scanner.nextInt();
                y = scanner.nextInt();
                System.err.println("x: " + x + " y: " + y);
                if (field.makeMove(x, y, ME)) {
                    System.err.println("Writing to server!");

                    outToServer.write(x);
                    outToServer.write(y);
                    outToServer.flush();

//                    outToServer.close();
//                    System.exit(0);

                    System.err.println("Wrote to server!");
                    break;
                } else {
                    System.out.println("Invalid!");
                }
            }

            if (field.isFinished()) {
                System.out.println("GAME OVER");
                break;
            }

            x = inFromServer.nextInt();
            y = inFromServer.nextInt();

            assert field.makeMove(x, y, ENEMY);
            if (field.isFinished()) {
                System.out.println("GAME OVER");
                break;
            }
        }
    }
}
