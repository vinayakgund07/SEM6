import java.sql.*;
import java.util.*;

class DBConnection{
	public static void main(String[] args)
	{
		String url="jdbc:postgresql://192.168.0.102:5432/tycsdb38";
		String user="tycs38";
		String password="tycs38";

		try{
			Class.forName("org.postgresql.Driver");

			Connection con=DriverManager.getConnection(url,user,password);

                        System.out.println("Connection Established sucessfully!");
	
	                con.close();
		  }

		catch(Exception e){
			e.printStackTrace();
	}
}
}

