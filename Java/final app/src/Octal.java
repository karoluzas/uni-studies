public class Octal implements ConverterFactoryDesign{

    public String convertFormat (int x){
        /* Method converts a integer value
        into an octal value and
        returns it as a string */

        String word = "";
        int reminder;
        while(x > 0){
            reminder = x % 8;
            word = reminder + word;
            x = x / 8;
        }

        return word;
    }
}
