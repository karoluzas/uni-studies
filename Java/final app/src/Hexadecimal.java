public class Hexadecimal implements ConverterFactoryDesign{

    public String convertFormat (int x){
        /* Method converts a integer value
        into a hexadecimal value and
        returns it as a string */

        String word = "";
        int reminder;
        NumberToCharacter symbol = new NumberToCharacter();
        while(x > 0){
            reminder = x % 16;
            word = symbol.convertToChar(reminder) + word;
            x = x / 16;
        }
        return word;
    }
}
