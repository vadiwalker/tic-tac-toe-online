/**
 * Created by vadim on 01/06/17.
 */
public class Utils {
    public static boolean checkFinished(Field field, char ME) {
        if (field.isFinished().isPresent()) {
            System.out.println("GAME OVER!");
            if (field.isFinished().get().equals('D')) {
                System.out.println("It is draw!");
            } else if (field.isFinished().get().equals(ME)) {
                System.out.println("Congrats, You won!");
            } else {
                System.out.println("Unfortunately, You lost!");
            }
            return true;
        } else {
            return false;
        }
    }
}
