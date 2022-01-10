public class Binary implements ConverterFactoryDesign{

    public String convertFormat (int x){
        /* Converts int into binary string
        value of that int */

        String word = "";
        int count = 0, reminder;
        while(x > 0){
            reminder = x % 2;
            word = reminder + word;
            x = x / 2;
            count++;
        }
        while(count % 4 != 0){
            word = 0 + word;
            count++;
        }

        return word;
    }
}
