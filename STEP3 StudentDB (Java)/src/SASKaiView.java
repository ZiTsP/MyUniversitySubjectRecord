import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;

class SASKaiView extends JFrame implements ActionListener{
public static DefaultTableModel tm;
public JTable tb;
public JScrollPane sp;
public JTextField tf1;
public JButton bn1, bn2;
private SASKaiCtrl ctrl;
private JButton[] button; 
private JLabel[] label;
private JTextField[] text;

public SASKaiView() {
	ctrl = new SASKaiCtrl();
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	setSize(800, 800);
	setTitle("SelAddSearch");
	Container c = getContentPane();
	c.setLayout(new FlowLayout());
	JPanel p1=viewForm();
	add(p1);
	pack();
	}
public JPanel viewForm(){
	JPanel basePanel=new JPanel();
	basePanel.setSize(450, 200);
	basePanel.setLayout(new BorderLayout());
	JPanel p1=searchForm();
	basePanel.add(p1,BorderLayout.NORTH);
	JPanel p2=SelForm();
	basePanel.add(p2,BorderLayout.SOUTH);
//	basePanel.setVisible(true);
	return basePanel;
}


public JPanel searchForm(){
	JPanel p1=new JPanel();
	p1.setPreferredSize(new Dimension(400,50));
	p1.setLayout(new FlowLayout());
	JLabel ll1 = new JLabel("Condition:");
	tf1 = new JTextField("", 12);
	bn1 = new JButton("Show");
	bn2 = new JButton("Quite");
	p1.add(ll1);
	p1.add(tf1);
	p1.add(bn1);
	p1.add(bn2);
	bn1.addActionListener(this);
	bn2.addActionListener(this);
	return p1;
	}


public JPanel SelForm(){
	JPanel p1=new JPanel();
	p1.setPreferredSize(new Dimension(400,250));
	p1.setLayout(new FlowLayout());
	String[][] rowData = {};
	String[] colNames = { "number(sno)", "name(sname)", "address", "age"};
	tm = new DefaultTableModel(rowData, colNames);
	tb = new JTable(tm);
	sp = new JScrollPane(tb);
	sp.setPreferredSize(new Dimension(400, 200));
	p1.add(sp);
	return p1;
	}

public void actionPerformed(ActionEvent e){
	if(e.getSource() == bn1){
		tm.setRowCount(0);
		String str = tf1.getText();
		ctrl.expressResult(str,tm);
	}else if(e.getSource() == bn2){
	System.exit(0);
	}
	}

public static void main(String[] args) {
	SASKaiView obj = new SASKaiView();
	obj.setVisible(true);
	SASKaiSubPanel obj2 = new SASKaiSubPanel();
	obj2.setVisible(true);
}
}