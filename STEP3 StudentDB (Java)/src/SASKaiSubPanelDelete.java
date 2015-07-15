import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

class SASKaiSubPanelDelete extends JPanel implements ActionListener{
	private JButton[] button;
	private JButton bSearch;
	private JTextField condition;
	private SASKaiCtrl ctrl;
	
	SASKaiSubPanelDelete(){
		ctrl = new SASKaiCtrl();
//		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(600, 300);
//		setTitle("");
		setLayout(new FlowLayout());
		JPanel p=DeleteForm();
		add(p);
	}
	

	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == button[0]){
			String str = condition.getText();
			ctrl.del(str,SASKaiView.tm);
		}
		else if(e.getSource() == button[1]){
			condition.setText("");
		}
		else if(e.getSource() == button[2]){
			String str = "";
			ctrl.del(str,SASKaiView.tm);
		}
		else if(e.getSource() == button[3]){
			System.exit(0);
		}
		else if(e.getSource() == bSearch){
			SASKaiView.tm.setRowCount(0);
			String str = condition.getText();
			ctrl.expressResult(str,SASKaiView.tm);
		}
	}
	
	public JPanel DeleteForm(){
		JPanel rf=new JPanel();
		rf.setSize(450, 200);
		rf.setLayout(new BorderLayout());
		JLabel titleLabel=new JLabel("<<<Delete Student Data>>>");
		titleLabel.setPreferredSize(new Dimension(400, 20));
		rf.add(titleLabel,BorderLayout.NORTH);
		JPanel p1=conditionForm();
		rf.add(p1,BorderLayout.CENTER);
		JPanel p2=buttonFormDel();
		rf.add(p2,BorderLayout.SOUTH);
		rf.setVisible(true);
		return rf;
	}
	public JPanel conditionForm(){
		JPanel p1=new JPanel();
		p1.setPreferredSize(new Dimension(400,90));
		JLabel call=new JLabel("put condition which you want to delete");
		p1.add(call);
		condition=new JTextField();
		condition.setPreferredSize(new Dimension (200,25));
		condition.addActionListener(this);
		p1.add(condition);
		bSearch=new JButton("Search");
		bSearch.addActionListener(this);
		p1.add(bSearch);
		JLabel canf1=new JLabel("check the seat.");
		p1.add(canf1);
		JLabel canf2=new JLabel("if you wan to delete the data, click [ConditionalDel]");
		p1.add(canf2);
		return p1;
	}
	public JPanel buttonFormDel(){
		JPanel p1=new JPanel();
		p1.setPreferredSize(new Dimension(400,100));
		p1.setLayout(new GridLayout(2,2));
		int i;
		String[] buttonname={"ConditionalDel","Clear","AllDel","Close Window"};
		button=new JButton[4];
		for(i=0;i<4;i++){
			button[i]=new JButton(buttonname[i]);
			button[i].addActionListener(this);
			p1.add(button[i]);
		}
		return p1;
	}

}