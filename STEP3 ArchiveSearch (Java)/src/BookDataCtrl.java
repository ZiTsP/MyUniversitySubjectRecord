import javax.swing.JTextArea;

public class BookDataCtrl {
	    private BookDataModel mdl;
	    BookDataCtrl(){
	        mdl = new BookDataModel();
	    }

	    public int bookEnter(String title,String writer,String publisher,String ISBN,JTextArea a1){
	    	int res =mdl.bookEnter(title,writer,publisher,ISBN,a1);
	    	return res;
	    }
	    public void bookSearch(String title,String writer,String publisher,String ISBN,JTextArea a1){
	    	mdl.bookSearch(title,writer,publisher,ISBN,a1);
	    }
	    public void showall(JTextArea a1){
	    	mdl.showall(a1);
	    }
	}