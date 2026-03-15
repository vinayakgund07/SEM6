import java.util.*;
import java.sql.*;

class Student
{
	public static void main(String[] args)
	{
		String url="jdbc:postgresql://192.168.0.102:5432/tycsdb38";
		String user="tycs38";
		String password="tycs38";

		try{
		Class.forName("org.postgresql.Driver");
		Connection con=DriverManager.getConnection(url,user,password);
		Statement stmt=con.createStatement();

		String create="CREATE TABLE student(id INT PRIMARY KEY,name VARCHAR(50),marks INT)";
		stmt.executeUpdate(create);
		System.out.println("Table created!!");

		stmt.executeUpdate("INSERT INTO student VALUES(1,'Abc',85)");
		stmt.executeUpdate("INSERT INTO student VALUES(2,'Xyz',90)");
                stmt.executeUpdate("INSERT INTO student VALUES(3,'Pqr',85)");
		System.out.println("Records inserted sucessfully!!");

		stmt.close();
		con.close();

	      }
        	catch(Exception e){
		e.printStackTrace();
		}
	}
}



