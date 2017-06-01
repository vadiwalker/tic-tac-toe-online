import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.util.Optional;

/**
 * Created by vadim on 01/06/17.
 */
public class Field {
    private char field[][];
    private int size;

    public Field(int size) {
        assert size != 0;
        this.size = size;
        this.field = new char[size + 1][size + 1];
        initField();
    }

    public void initField() {
        for (int i = 1; i <= size; i++) {
            for (int j = 1; j <= size; j++) {
                field[i][j] = '.';
            }
        }
        for (int i = 1; i <= size; i++) {
            field[0][i] = field[i][0] = (char) ('0' + i);
        }
    }

    public boolean inside(int x, int y) {
        return 1 <= x && x <= 3 && 1 <= y && y <= 3;
    }

    public boolean makeMove(int x, int y, char player) {
        if (inside(x, y) && field[x][y] == '.') {
            field[x][y] = player;
            return true;
        } else {
            return false;
        }
    }

    public Optional<Character> isFinished() {
        for (int i = 1; i <= size; i++) {
            if (field[i][1] == '.') continue;
            boolean win = true;
            for (int j = 2; j <= size; j++) {
                if (field[i][j] != field[i][j - 1]) {
                    win = false;
                }
            }
            if (win) {
                return Optional.of(field[i][1]);
            }
        }
        for (int j = 1; j <= size; j++) {
            if (field[1][j] == '.') continue;
            boolean win = true;
            for (int i = 2; i <= size; i++) {
                if (field[i][j] != field[i - 1][j]) {
                    win = false;
                }
            }
            if (win) {
                return Optional.of(field[1][j]);
            }
        }
        if (field[1][1] != '.') {
            boolean win = true;
            for (int i = 2; i <= size; i++) {
                if (field[i][i] != field[i - 1][i - 1]) {
                    win = false;
                }
            }
            if (win) {
                return Optional.of(field[1][1]);
            }
        }
        if (field[1][size] != '.') {
            boolean win = true;
            for (int i = 2; i <= size; i++) {
                if (field[i][size + 1 - i] != field[i - 1][size + 2 - i]) {
                    win = false;
                }
            }
            if (win) {
                return Optional.of(field[1][size]);
            }
        }
        for (int i = 1; i <= size; i++) {
            for (int j = 1; j <= size; j++) {
                if (field[i][j] == '.') {
                    return Optional.empty();
                }
            }
        }
        return Optional.of('D');
    }

    public void display() {
        for (int i = 0; i <= size; i++) {
            for (int j = 0; j <= size; j++) {
                System.out.print(field[i][j] + " ");
            }
            System.out.println();
        }
    }
}
