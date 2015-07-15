import java.awt.*;
import java.awt.event.*;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;

class BookDataView extends JFrame implements ActionListener {
    private BookDataCtrl ctrl;
    private Container c;
    private JLabel  l1,l2,l3,l4;
    private JButton b1,b2,b3,b4;
    private JTextField tf1,tf2,tf3,tf4;
    private JTextArea a1;
    private JScrollPane sp;

    public void buttonPanel(){
    	getContentPane();
    	JPanel pEnter = new JPanel();
    	pEnter.setPreferredSize(new Dimension(260, 300));
    	pEnter.setBackground(Color.RED);
        setLayout(new FlowLayout());
        l1 = new JLabel("Title");
        l1.setPreferredSize(new Dimension(70, 15));
        l2 = new JLabel("Writer");
        l2.setPreferredSize(new Dimension(70, 15));
        l3 = new JLabel("Publisher");
        l3.setPreferredSize(new Dimension(70, 15));
        l4 = new JLabel("ISBN");
        l4.setPreferredSize(new Dimension(70, 15));
        tf1 = new JTextField(20);
        tf2 = new JTextField(20);
        tf3 = new JTextField(20);
        tf4 = new JTextField(20);
        b1 =new JButton("REGISTER");
        b2 =new JButton("SEARCH");
        b3 =new JButton("CLEAR");
        b4 =new JButton("SHOW ALL");
        pEnter.add(l1);
        pEnter.add(tf1);
        pEnter.add(l2);
        pEnter.add(tf2);
        pEnter.add(l3);
        pEnter.add(tf3);
        pEnter.add(l4);
        pEnter.add(tf4);
        pEnter.add(b1);
        pEnter.add(b2);
        pEnter.add(b3);
        pEnter.add(b4);
        tf1.addActionListener(this);
        tf2.addActionListener(this);
        tf3.addActionListener(this);
        tf4.addActionListener(this);
		 b1.addActionListener(this);
		 b2.addActionListener(this);
		 b3.addActionListener(this);
		 b4.addActionListener(this);
		 c.setLayout(new FlowLayout());
		 c.add(pEnter);
    }
    public BookDataView(){
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setTitle("BookDataView");
        ctrl = new BookDataCtrl();
        c = getContentPane();
        c.setLayout(new FlowLayout());
        buttonPanel();
        outputPanel();
        pack();
    }
    
    public void outputPanel() {
    	JPanel pEnter = new JPanel();
    	pEnter.setPreferredSize(new Dimension(250, 300));
    	pEnter.setBackground(Color.BLUE);
        setLayout(new FlowLayout());
    	a1 = new JTextArea();
    	sp = new JScrollPane(a1);
    	sp.setPreferredSize(new Dimension(250, 300));
    	add(sp);
    	setSize(450, 250);
    	}

    public void actionPerformed(ActionEvent e){
        if(e.getSource() == b1){
        	String eTitle =tf1.getText();
        	String eWriter =tf2.getText();
        	String ePublisher =tf3.getText();
        	String eISBN =tf4.getText();
        	int jud=ctrl.bookEnter(eTitle,eWriter,ePublisher,eISBN,a1);
        	if(jud==0){
        		System.out.println("something error");
        	}
        }else if(e.getSource() == b2){
        	String eTitle =tf1.getText();
        	String eWriter =tf2.getText();
        	String ePublisher =tf3.getText();
        	String eISBN =tf4.getText();
        	ctrl.bookSearch(eTitle,eWriter,ePublisher,eISBN,a1);
        }else if(e.getSource() == b3){
        	tf1.setText("");
        	tf2.setText("");
        	tf3.setText("");
        	tf4.setText("");
        	a1.setText("");
        }else if(e.getSource()==b4){
        	ctrl.showall(a1);
        }
    }    

    public static void main(String[] args) {
   	BookDataView tv = new BookDataView();
        tv.setVisible(true);
    }
}
