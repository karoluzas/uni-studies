public class ASCIIConverter {
    /* With this class I tried to implement a
    class hierarchy. Subclasses share the same variables
    used when converting from number to char and vice versa */

    // SINGLETON

    static ASCIIConverter ASCII = new ASCIIConverter();

    private ASCIIConverter(){ }

    public static ASCIIConverter getInstance(){
        return ASCII;
    }

    final int NUMBER_TO_CHAR = 55;
    final int NUMBER_TO_NUMBER = 48;
}
