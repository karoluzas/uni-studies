import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

public class SQLExecutions {
    public static List<String> rastiKlienta(Connection connection, String name) {
        if (connection == null) {
            System.out.println("Kazkas netiketo nutiko su duomenu baze!");
            return null;
        }

        List<String> result = new ArrayList<String>();
        Statement statement = null;
        ResultSet resultSet = null;

        try {
            int name_id, counter = 0;
            try {
                name_id = Integer.parseInt(name);
            } catch (NumberFormatException nfe) {
                name_id = 0;
            }

            statement = connection.createStatement();
            resultSet = statement.executeQuery(
                    "SELECT * " +
                            "FROM Klientas " +
                            "WHERE (pavadinimas  = '" + name + "' " +
                            "OR kliento_ID = '" + name_id + "')" );

            while (resultSet.next()) {
                result.add(resultSet.getString(1) + " | " + resultSet.getString(2) + " | " + resultSet.getString(3) + " | " + resultSet.getString(4));
                counter++;
            }
            if(counter == 0){
                System.out.println("Nerastas toks klientas, patikrinkite ar gerai ivedete kliento pavadinima arba ID!");
            }


        } catch (SQLException e) {
            System.out.println("Ivyko klaida vykdant SQL uzklausa!");
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) {
                    resultSet.close();
                }
                if (statement != null) {
                    statement.close();
                }
            } catch (SQLException e) {
                System.out.println("Ivyko klaida uzdarant SQL uzklausas!");
                e.printStackTrace();
            }
        }
        return result;
    }
    /********************************************************/
    public static List<String> getAllKlientai(Connection connection) {
        if (connection == null) {
            System.out.println("Kazkas netiketo nutiko su duomenu baze!");
            return null;
        }

        List<String> result = new ArrayList<String>();
        Statement statement = null;
        ResultSet resultSet = null;

        try {
            statement = connection.createStatement();
            resultSet = statement.executeQuery(
                    "SELECT * FROM Klientas");
            while (resultSet.next()) {
                result.add(resultSet.getString(1) + " | " + resultSet.getString(2) + " | " + resultSet.getString(3) + " | " + resultSet.getString(4));
            }
        } catch (SQLException e) {
            System.out.println("Ivyko klaida vykdant SQL uzklausa!");
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) {
                    resultSet.close();
                }
                if (statement != null) {
                    statement.close();
                }
            } catch (SQLException e) {
                System.out.println("Ivyko klaida uzdarant SQL uzklausas!");
                e.printStackTrace();
            }
        }
        return result;
    }
    /********************************************************/
    public static void addKlientas(Connection connection, String pavadinimas, String kontaktinis_nr, String sandelio_adresas) throws SQLException {
        if (connection == null) {
            System.out.println("Kazkas netiketo nutiko su duomenu baze!");
        } else {
            Statement statement = null;

            try {
                connection.setAutoCommit(false);

                statement = connection.createStatement();
                statement.executeUpdate(
                        "INSERT INTO Klientas (pavadinimas, kontaktinis_nr, sandelio_adresas)" +
                                "VALUES ( '" + pavadinimas + "', '" + kontaktinis_nr + "', '" + sandelio_adresas + "')");

                connection.commit();
                connection.setAutoCommit(true);
                System.out.println("Klientas buvo sekmingai pridetas i sarasa!");
            } catch (SQLException e) {
                System.out.println("Ivyko klaida vykdant SQL uzklausa!");
                e.printStackTrace();

                connection.rollback();
                connection.setAutoCommit(true);
            } finally {
                try {
                    if (statement != null) {
                        statement.close();
                    }
                } catch (SQLException e) {
                    System.out.println("Ivyko klaida uzdarant SQL uzklausas!");
                    e.printStackTrace();
                }
            }
        }
    }
    /********************************************************/
    public static List<String> getLaisviSunkvezimiai(Connection connection) {
        if (connection == null) {
            System.out.println("Kazkas netiketo nutiko su duomenu baze!");
            return null;
        }

        List<String> result = new ArrayList<String>();

        Statement statement = null;
        ResultSet resultSet = null;

        // Naudojamos dvi tarpusavyje susijusios lenteles:
        try {
            statement = connection.createStatement();
            resultSet = statement.executeQuery(
                    "SELECT sunkvezimio_ID, vardas, pavarde, marke, rida, talpa, euro_standartas " +
                            "FROM Sunkvezimis, Vairuotojas " +
                            "WHERE Sunkvezimis.vairuotojo_ID = Vairuotojas.vairuotojo_ID AND laisvas IS TRUE"
            );
            while (resultSet.next()) {
                result.add(resultSet.getString(1) + " | " + resultSet.getString(2) + " | " + resultSet.getString(3) + " | " + resultSet.getString(4) + " | " + resultSet.getString(5) + " | " + resultSet.getString(6) + " | ");
            }
        } catch (SQLException e) {
            System.out.println("Ivyko klaida vykdant SQL uzklausa!");
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) {
                    resultSet.close();
                }
                if (statement != null) {
                    statement.close();
                }
            } catch (SQLException e) {
                System.out.println("Ivyko klaida uzdarant SQL uzklausas!");
                e.printStackTrace();
            }
        }
        return result;
    }
    /********************************************************/
    public static List<String> getUzimtiSunkvezimiai(Connection connection) {
        if (connection == null) {
            System.out.println("Kazkas netiketo nutiko su duomenu baze!");
            return null;
        }

        List<String> result = new ArrayList<String>();

        Statement statement = null;
        ResultSet resultSet = null;
        try {
            statement = connection.createStatement();
            resultSet = statement.executeQuery(
                    "SELECT sunkvezimio_ID, vardas, pavarde, marke, rida, talpa, euro_standartas " +
                            "FROM Sunkvezimis, Vairuotojas " +
                            "WHERE Sunkvezimis.vairuotojo_ID = Vairuotojas.vairuotojo_ID AND laisvas IS FALSE"
            );
            while (resultSet.next()) {
                result.add(resultSet.getString(1) + " | " + resultSet.getString(2) + " | " + resultSet.getString(3) + " | " + resultSet.getString(4) + " | " + resultSet.getString(5) + " | " + resultSet.getString(6) + " | ");
            }
        } catch (SQLException e) {
            System.out.println("Ivyko klaida vykdant SQL uzklausa!");
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) {
                    resultSet.close();
                }
                if (statement != null) {
                    statement.close();
                }
            } catch (SQLException e) {
                System.out.println("Ivyko klaida uzdarant SQL uzklausas!");
                e.printStackTrace();
            }
        }

        return result;
    }
    /********************************************************/
    public static void registruotiUzsakyma(Connection connection, int sunkvezimioID, int klientoID, int krovinioDydis, String adresas, int atstumas) throws SQLException{
        if(connection == null){
            System.out.println("Kazkas netiketo nutiko su duomenu baze!");
        } else {
            Statement statement = null;

            try{
                statement = connection.createStatement();
                statement.executeUpdate(
                        "INSERT INTO Uzsakymai (sunkvezimio_id, kliento_id, krovinio_dydis, pristatymo_adresas, atstumas) " +
                            "Values ( " + sunkvezimioID + ", " + klientoID +  ", " + krovinioDydis + ", '" + adresas + "', " + atstumas + " )"
                );
                System.out.println("Uzsakymas sekmingai pridetas i sarasa!");
            } catch (SQLException e) {
                System.out.println("Ivyko klaida vykdant SQL uzklausa!");
                e.printStackTrace();
            } finally {
                try {
                    if (statement != null) {
                        statement.close();
                    }
                } catch (SQLException e) {
                    System.out.println("Ivyko klaida uzdarant SQL uzklausas!");
                    e.printStackTrace();
                }
            }
        }
    }
    /********************************************************/
    public static List<String> rodytiUzsakymus (Connection connection){
        if (connection == null) {
            System.out.println("Kazkas netiketo nutiko su duomenu baze!");
            return null;
        }

        List<String> result = new ArrayList<String>();

        Statement statement = null;
        ResultSet resultSet = null;
        try {
            statement = connection.createStatement();
            resultSet = statement.executeQuery(
                    "SELECT uzsakymo_id, sunkvezimio_id, pavadinimas, uzsakymo_data, pristatymo_terminas, krovinio_dydis, pristatymo_adresas, atstumas, numatyta_kaina " +
                        "FROM Uzsakymai, Klientas " +
                        "WHERE Uzsakymai.kliento_ID = Klientas.kliento_ID"
            );
            while (resultSet.next()) {
                result.add(resultSet.getString(1) + " | " + resultSet.getString(2) + " | " + resultSet.getString(3) + " | " + resultSet.getString(4) + " | " + resultSet.getString(5) + " | " + resultSet.getString(6) + " | " + resultSet.getString(7) + " | " + resultSet.getString(8) + " | " + resultSet.getString(9) + " | ");
            }
        } catch (SQLException e) {
            System.out.println("Ivyko klaida vykdant SQL uzklausa!");
            e.printStackTrace();
        } finally {
            try {
                if (resultSet != null) {
                    resultSet.close();
                }
                if (statement != null) {
                    statement.close();
                }
            } catch (SQLException e) {
                System.out.println("Ivyko klaida uzdarant SQL uzklausas!");
                e.printStackTrace();
            }
        }

        return result;
    }
    /********************************************************/
    public static void atnaujintiUzsakyma (Connection connection, int uzsakymoID, int krovinioDydis, int atstumas, String adresas) throws SQLException{
        if (connection == null) {
            System.out.println("Kazkas netiketo nutiko su duomenu baze!");

        }

        Statement statement = null;
        try{
            statement = connection.createStatement();
            statement.executeUpdate(
                    "UPDATE Uzsakymai " +
                        "SET krovinio_dydis = " + krovinioDydis + ", " +
                            "atstumas = " + atstumas + ", " +
                            "pristatymo_adresas = '" + adresas + "' " +
                            "WHERE uzsakymo_ID = " + uzsakymoID
            );
            System.out.println("Uzsakymas buvo sekmingai atnaujintas!");
        }catch (SQLException e) {
            System.out.println("Ivyko klaida vykdant SQL uzklausa!");
            e.printStackTrace();
        } finally {
            try {
                if (statement != null) {
                    statement.close();
                }
            } catch (SQLException e) {
                System.out.println("Ivyko klaida uzdarant SQL uzklausas!");
                e.printStackTrace();
            }
        }
    }
    /********************************************************/
    public static void istrintiUzsakyma (Connection connection, int uzsakymo_id){
        if (connection == null) {
            System.out.println("Kazkas netiketo nutiko su duomenu baze!");
        }

        Statement statement = null;

        try{
            statement = connection.createStatement();
            statement.executeUpdate(
                    "DELETE FROM uzsakymai WHERE uzsakymo_ID = " + uzsakymo_id
            );
            System.out.println("Uzsakymas sekminga istrintas!");
        } catch (SQLException e) {
            System.out.println("Ivyko klaida vykdant SQL uzklausa!");
            e.printStackTrace();
        } finally {
            try {
                if (statement != null) {
                    statement.close();
                }
            } catch (SQLException e) {
                System.out.println("Ivyko klaida uzdarant SQL uzklausas!");
                e.printStackTrace();
            }
        }
    }
}

