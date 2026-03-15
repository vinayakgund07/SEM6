import java.util.*;
import java.sql.*;

class DisplayStudents{
            public static void main(String[] args)
             {
                String url="jdbc:postgresql://192.168.0.102:5432/tycsdb38";
                String user="tycs38";
                String password="tycs38";

                try{
                Class.forName("org.postgresql.Driver");
                Connection con=DriverManager.getConnection(url,user,password);
                Statement stmt=con.createStatement();

		String sql="SELECT * FROM student";

		ResultSet rs=stmt.executeQuery(sql);

		System.out.println("ID\tName\tMarks");
		System.out.println("---------------------------------------");

		while(rs.next())
		{
			int id=rs.getInt(1);
			String name=rs.getString(2);
			int marks=rs.getInt(3);

			System.out.println(id+"\t"+name+"\t"+marks);

		}

		rs.close();
		stmt.close();
		con.close();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	     }
}

