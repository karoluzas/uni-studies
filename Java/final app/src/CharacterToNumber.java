public class CharacterToNumber{

    public int convertCharToInt (char x){
        /*Converts a char into int*/
        ASCIIConverter number = ASCIIConverter.getInstance();
        int numberToNumber = number.NUMBER_TO_NUMBER;
        int numberToChar = number.NUMBER_TO_CHAR;

        int num = x;

        //number = x;
        if(x <= '9'){
            num -= numberToNumber;
        }else{
            num -= numberToChar;
        }
        return num;
    }
}
