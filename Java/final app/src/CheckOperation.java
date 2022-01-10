public class CheckOperation {

    public double turnToNumber(String input, double number) throws NumberFormatException
    {
        if(!input.equals("")){
            number = Double.parseDouble(input);
        }

        return number;
    }

}
