public class EqualsOperation {
    public double performOperation(double number1, double number2, char operation) throws EmptyStringException {
        double result;

        switch(operation){
            case '+':
                result = number1 + number2;
                break;
            case '-':
                result = number1 - number2;
                break;
            case '*':
                result = number1 * number2;
                break;
            case '/':
                result = number1 / number2;
                break;
            case '%':
                result = number1 % number2;
                break;
            default:
                result = 0;
                throw new EmptyStringException("No operation has been selected");
        }
        return result;
    }

    public void checkIfInputIsEmpty(String input) throws EmptyStringException{
        if(input.equals("")){
            throw new EmptyStringException("The input field is empty");
        }
    }
}
