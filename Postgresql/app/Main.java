import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.util.List;

public class Main {

    /********************************************************/
    public static void loadDriver(){
        try {
            Class.forName("org.postgresql.Driver");
        }
        catch (ClassNotFoundException cnfe) {
            System.out.println("Couldn't find driver class!");
            cnfe.printStackTrace();
            System.exit(1);
        }
    }
    /********************************************************/
    public static Connection getConnection() {
        Connection postGresConn = null;
        try {
            postGresConn = DriverManager.getConnection(UserInfo.dataBaseConnection, UserInfo.userName, UserInfo.password) ;
        }
        catch (SQLException sqle) {
            System.out.println("Couldn't connect to database!");
            sqle.printStackTrace();
            return null ;
        }
        System.out.println("Successfully connected to Postgres Database");

        return postGresConn ;
    }
    /********************************************************/
    public static void printUserInterface(){
        System.out.println("==========================================================");
        System.out.println("Galimi tolimesni veiksmai: ");
        System.out.println("1 - Surasti klienta (pagal pavadinima arba ID)");
        System.out.println("2 - Prideti nauja klienta");
        System.out.println("3 - Parodyti visus sunkvezimius");
        System.out.println("4 - Uzregistruoti nauja uzsakyma");
        System.out.println("5 - Koreguoti uzsakyma (krovinio dydi, atstuma, adresa)");
        System.out.println("6 - Uzbaigti uzsakyma");
        System.out.println("0 - Iseiti is programos");
        System.out.println("==========================================================");
    }
    /********************************************************/
    public static void printList(List<String> list){
        if(list != null){
            for(String row : list) {
                System.out.println(row);
            }
        }
    }
    /********************************************************/
    public static void main(String[] args) throws SQLException{
        boolean endProgram = false;
        loadDriver();
        Connection con = getConnection();

        while(!endProgram) {
            printUserInterface();

            switch (System.console().readLine()) {
                case "0":
                    endProgram = true;
                    break;
                case "1":
                    System.out.print("Iveskite kliento pavadinima arba ID: ");
                    List<String> klientas = SQLExecutions.rastiKlienta(con, System.console().readLine());
                    printList(klientas);
                    break;
                case "2":
                    System.out.println("Esami klientai: ");
                    List<String> klientai = SQLExecutions.getAllKlientai(con);
                    printList(klientai);
                    System.out.print("Iveskite kliento pavadinima (Pavadinimas negali sutapti su jau esamu klientu sarase): ");
                    String pavadinimas = System.console().readLine();
                    System.out.print("Iveskite kliento kontaktini numeri: ");
                    String kontaktinis_nr = System.console().readLine();
                    System.out.print("Iveskite kliento sandelio adresa: ");
                    String sandelio_adresas = System.console().readLine();
                    SQLExecutions.addKlientas(con, pavadinimas, kontaktinis_nr, sandelio_adresas);
                    break;
                case "3":
                    System.out.println("Laisvi sunkvezimiai:");
                    printList(SQLExecutions.getLaisviSunkvezimiai(con));
                    System.out.println("Uzimti sunkvezimiai:");
                    printList(SQLExecutions.getUzimtiSunkvezimiai(con));
                    break;
                case "4":
                    System.out.println("Laisvi sunkvezimiai:");
                    printList(SQLExecutions.getLaisviSunkvezimiai(con));
                    System.out.println("Klientu sarasas");
                    printList(SQLExecutions.getAllKlientai(con));
                    System.out.println("Dabartiniai uzsakymai:");
                    printList(SQLExecutions.rodytiUzsakymus(con));
                    System.out.print("Iveskite laisvo sunkvezimio ID: ");
                    int sunkvezimio_id = Integer.parseInt(System.console().readLine());
                    System.out.print("Iveskite kliento ID: ");
                    int kliento_id = Integer.parseInt(System.console().readLine());
                    System.out.print("Iveskite krovinio dydi: ");
                    int krovinio_dydis = Integer.parseInt(System.console().readLine());
                    System.out.print("Iveskite pristatymo adresa: ");
                    String pristatymo_adresas = System.console().readLine();
                    System.out.print("Iveskite atstuma: ");
                    int atstumas = Integer.parseInt(System.console().readLine());
                    SQLExecutions.registruotiUzsakyma(con, sunkvezimio_id, kliento_id, krovinio_dydis, pristatymo_adresas, atstumas);
                    System.out.print("");
                    break;
                case "5":
                    printList(SQLExecutions.rodytiUzsakymus(con));
                    System.out.print("Iveskite uzsakymo ID kuri norite koreguoti (iveskite 0 norint nutraukti): ");
                    int uzsakymo_id = Integer.parseInt(System.console().readLine());
                    if (uzsakymo_id != 0) {
                        System.out.print("Krovinio dydis: ");
                        int krovinio_dydis2 = Integer.parseInt(System.console().readLine());
                        System.out.print("Atstumas: ");
                        int atstumas2 = Integer.parseInt(System.console().readLine());
                        System.out.print("Pristatymo adresas: ");
                        String pristatymo_adresas2 = System.console().readLine();
                        SQLExecutions.atnaujintiUzsakyma(con, uzsakymo_id, krovinio_dydis2, atstumas2, pristatymo_adresas2);
                    }
                    break;
                case "6":
                    printList(SQLExecutions.rodytiUzsakymus(con));
                    System.out.print("Iveskite uzsakymo ID kuri noretumete uzdaryti (iveskite 0 norint nutraukti): ");
                    int uzsakymo_id2 = Integer.parseInt(System.console().readLine());
                    if (uzsakymo_id2 != 0) {
                        SQLExecutions.istrintiUzsakyma(con, uzsakymo_id2);
                    }
                    break;
                default:
                    System.out.println("Neatpazinta komanda");
                    break;
            }
        }

        if( null != con ) {
            try {
                con.close() ;
            } catch (SQLException exp) {
                System.out.println("Can not close connection!");
                exp.printStackTrace();
            }
        }
    }
}
