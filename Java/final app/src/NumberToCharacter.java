public class NumberToCharacter{

    public char convertToChar (int x){
        /* Converts a number between 0-15 into
        the proper hexadecimal symbol */
        ASCIIConverter number = ASCIIConverter.getInstance();
        int numberToChar = number.NUMBER_TO_CHAR;
        int numberToNumber = number.NUMBER_TO_NUMBER;
        char character;

        if(x <= 9){
            x += numberToNumber;
            character =(char)x;
        }else{
            x += numberToChar;
            character =(char)x;
        }
        return character;
    }
}
