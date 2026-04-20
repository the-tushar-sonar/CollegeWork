import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;

public class JdbcInsertExample {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost:3306/testdb";
        String user = "root";
        String password = "12345678";

        try {
            // Load Driver (optional for newer versions)
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Establish Connection
            Connection con = DriverManager.getConnection(url, user, password);

            // Insert Query using PreparedStatement
            String query = "INSERT INTO students (id, name, age) VALUES (?, ?, ?)";
            PreparedStatement ps = con.prepareStatement(query);

            // Set values
            ps.setInt(1, 1);
            ps.setString(2, "Tushar");
            ps.setInt(3, 21);

            // Execute
            int rows = ps.executeUpdate();
            System.out.println(rows + " record inserted successfully!");

            // Close connection
            ps.close();
            con.close();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}