import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

class SASKaiSubPanelRegist extends JPanel implements ActionListener{
	private JButton[] button; 
	private JLabel[] label;
	private JTextField[] text;
	private SASKaiCtrl ctrl;
//	private JComboBox cb;
	GridBagLayout gbl = new GridBagLayout();
	
	SASKaiSubPanelRegist(){
		ctrl = new SASKaiCtrl();
//		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(600, 300);
//		setTitle("");
		setLayout(new FlowLayout());
		JPanel p=registForm();
		add(p);
	}
	

	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == button[0]){
			int i;
			String[] temp=new String[4];
			for(i=0;i<4;i++){
				temp[i]=text[i].getText();
			}
			ctrl.regi(temp,SASKaiView.tm);
		}
		else if(e.getSource() == button[1]){
			int i;
			for(i=0;i<4;i++){
				text[i].setText("");
			}
		}
		else if(e.getSource() == button[2]){
			System.exit(0);
		}
	}
	
	public JPanel registForm(){
		JPanel rf=new JPanel();
		rf.setSize(450, 200);
		rf.setLayout(new BorderLayout());
		JLabel titleLabel=new JLabel("<<<Regist Student Data>>>");
		titleLabel.setPreferredSize(new Dimension(400, 20));
		rf.add(titleLabel,BorderLayout.NORTH);
		JPanel p1=entryForm();
		rf.add(p1,BorderLayout.CENTER);
		JPanel p2=buttonForm();
		rf.add(p2,BorderLayout.SOUTH);
//		rf.setVisible(true);
		return rf;
	}
	public JPanel entryForm(){
		JPanel p1=new JPanel();
		p1.setPreferredSize(new Dimension(400,80));
		int i;
		String labelName[]={"number","name","address","age"};
		label=new JLabel[4];
		p1.setLayout(new GridLayout(2,4));
		for(i=0;i<4;i++){
			label[i]=new JLabel(labelName[i]);
			label[i].setHorizontalAlignment(JLabel.CENTER);
			label[i].setPreferredSize(new Dimension(100, 20));
			p1.add(label[i]);
		}
		text=new JTextField[4];
		for(i=0;i<4;i++){
			text[i]=new JTextField("");
			text[i].setPreferredSize(new Dimension(150, 20));
			text[i].addActionListener(this);
			p1.add(text[i]);
		}
		return p1;
	}
	public JPanel buttonForm(){
		JPanel p1=new JPanel();
		p1.setPreferredSize(new Dimension(400,100));
       p1.setLayout(new GridLayout(2,3));
		int i;
		String[] buttonname={"Regist","Clear","Close Window"};
		JLabel[] empty=new JLabel[3];
		for(i=0;i<3;i++){
			empty[i]=new JLabel();
			p1.add(empty[i]);
		}
		button=new JButton[3];
		for(i=0;i<3;i++){
			button[i]=new JButton(buttonname[i]);
			button[i].addActionListener(this);
			p1.add(button[i]);
		}
		return p1;
	}

	public JPanel DeleteForm(){
		JPanel rf=new JPanel();
		rf.setSize(450, 200);
		rf.setLayout(new BorderLayout());
		JLabel titleLabel=new JLabel("<<<Delete Student Data>>>");
		titleLabel.setPreferredSize(new Dimension(400, 20));
		rf.add(titleLabel,BorderLayout.NORTH);
		JPanel p1=entryForm();
		rf.add(p1,BorderLayout.CENTER);
		JPanel p2=buttonForm();
		rf.add(p2,BorderLayout.SOUTH);
		rf.setVisible(true);
		return rf;
	}
}