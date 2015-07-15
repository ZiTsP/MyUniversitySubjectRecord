import java.sql.*;
import javax.swing.table.DefaultTableModel;

class SASKaiModel {

    SASKaiModel(){
    }
    
    public void expressResult(String str,DefaultTableModel tm){
    	try {
    		Class.forName("org.sqlite.JDBC");
    		Connection con = DriverManager.getConnection("jdbc:sqlite:/home/b2122014/SQLite/stock3.s3db");
    		Statement st = con.createStatement();
    		String sql = "SELECT * FROM Student "+str;
    		ResultSet rs = st.executeQuery(sql);
    		while(rs.next()){
    		String sno = rs.getString("sno");
    		String sname = rs.getString("sname");
    		String address = rs.getString("address");
    		String age = rs.getString("age");
    		String[] sp={sno,sname,address,age};
    		tm.addRow(sp);
    		}
    		st.close();
    		con.close();
    		} catch (Exception e) {
    		}
    }
    
    public void del(String str,DefaultTableModel tm){
    	try {
    		Class.forName("org.sqlite.JDBC");
    		Connection con = DriverManager.getConnection("jdbc:sqlite:/home/b2122014/SQLite/stock3.s3db");
    		Statement st = con.createStatement();
    		String sql = "DELETE FROM Student"+str;
    		ResultSet rs = st.executeQuery(sql);
    		rs = st.executeQuery("SELECT * FROM Student");
    		while(rs.next()){
    		String sno = rs.getString("sno");
    		String sname = rs.getString("sname");
    		String address = rs.getString("address");
    		String age = rs.getString("age");
    		String[] sp={sno,sname,address,age};
    		tm.addRow(sp);
    		}
    		st.close();
    		con.close();
    		} catch (Exception e) {
    		}
    }
    public void modi(String str,DefaultTableModel tm){
    	if( str!= null && str.length() != 0 ){
    	try {
    		Class.forName("org.sqlite.JDBC");
    		Connection con = DriverManager.getConnection("jdbc:sqlite:/home/b2122014/SQLite/stock3.s3db");
    		Statement st = con.createStatement();
    		String sql = "UPDATE Student SET"+str;
    		st.executeUpdate(sql);
    		st.close();
    		con.close();
    		} catch (Exception e) {
    		}
    	}
    }
    public void regi(String str,DefaultTableModel tm){
    	if( str!= null && str.length() != 0 ){
    	try {
    		Class.forName("org.sqlite.JDBC");
    		Connection con = DriverManager.getConnection("jdbc:sqlite:/home/b2122014/SQLite/stock3.s3db");
    		Statement st = con.createStatement();
    		String sql = "INSERT INTO Student VALUES"+str;
    		st.executeUpdate(sql);
    		st.close();
    		con.close();
    		} catch (Exception e) {
    		}
    	}
    }
    public void allDel(DefaultTableModel tm){
    	try {
    		Class.forName("org.sqlite.JDBC");
    		Connection con = DriverManager.getConnection("jdbc:sqlite:/home/b2122014/SQLite/stock3.s3db");
    		Statement st = con.createStatement();
    		String sql = "DELETE FROM Student";
    		ResultSet rs = st.executeQuery(sql);
    		rs = st.executeQuery("SELECT * FROM Student");
    		while(rs.next()){
    		String sno = rs.getString("sno");
    		String sname = rs.getString("sname");
    		String address = rs.getString("address");
    		String age = rs.getString("age");
    		String[] sp={sno,sname,address,age};
    		tm.addRow(sp);
    		}
    		st.close();
    		con.close();
    		} catch (Exception e) {
    		}
    }

}