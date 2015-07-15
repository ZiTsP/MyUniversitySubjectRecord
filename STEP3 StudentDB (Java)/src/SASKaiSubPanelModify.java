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

class SASKaiSubPanelModify extends JPanel implements ActionListener{
	private JButton[] button; 
	private JButton bSearch;
	private JTextField[] text;
	private JTextField condition;
	private SASKaiCtrl ctrl;
	
	SASKaiSubPanelModify(){
		ctrl = new SASKaiCtrl();
//		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(600, 300);
//		setTitle("");
		setLayout(new FlowLayout());
		JPanel p=ModifyForm();
		add(p);
	}
	

	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == button[0]){
			int i;
			String str = condition.getText();
			String[] temp=new String[4];
			for(i=0;i<4;i++){
				temp[i]=text[i].getText();
			}
			ctrl.modi(str,temp,SASKaiView.tm);
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
		else if(e.getSource() == bSearch){
			SASKaiView.tm.setRowCount(0);
			String str = condition.getText();
			ctrl.expressResult(str,SASKaiView.tm);
		}
	}
	
	public JPanel ModifyForm(){
		JPanel basePanel=new JPanel();
		basePanel.setSize(450, 200);
		basePanel.setLayout(new BorderLayout());
		JLabel titleLabel=new JLabel("<<<Modify Student Data>>>");
		titleLabel.setPreferredSize(new Dimension(400, 20));
		basePanel.add(titleLabel,BorderLayout.NORTH);
		JPanel p1=conditionFormMod();
		basePanel.add(p1,BorderLayout.CENTER);
		JPanel p2=buttonFormMod();
		basePanel.add(p2,BorderLayout.SOUTH);
		basePanel.setVisible(true);
		return basePanel;
	}
	public JPanel conditionFormMod(){
		JPanel p1=new JPanel();
		p1.setPreferredSize(new Dimension(400,180));
		JLabel call=new JLabel("put condition which you want to modify");
		p1.add(call);
		condition=new JTextField();
		condition.setPreferredSize(new Dimension (200,25));
		p1.add(condition);
		bSearch=new JButton("Search");
		bSearch.addActionListener(this);
		p1.add(bSearch);
		JLabel canf1=new JLabel("check the seat.");
		p1.add(canf1);
		JLabel canf2=new JLabel("if you want to modify the data, ");
		p1.add(canf2);
		JLabel canf3=new JLabel("put new condition and click [Modify]");
		p1.add(canf3);
		JPanel p2=entryForm();
		p1.add(p2);
		return p1;
	}
	public JPanel enterFormMod(){
		JPanel p1=new JPanel();
		p1.setPreferredSize(new Dimension(400,100));
		p1.setLayout(new GridLayout(2,2));
		int i;
		String[] buttonname={"ConditionalDel","Clear","AllDel","Close Window"};
		button=new JButton[4];
		for(i=0;i<4;i++){
			button[i]=new JButton(buttonname[i]);
			p1.add(button[i]);
		}
		return p1;
		
	}
	public JPanel entryForm(){
		JPanel p1=new JPanel();
		p1.setPreferredSize(new Dimension(400,80));
		int i;
		String labelName[]={"number","name","address","age"};
		JLabel[] label=new JLabel[4];
		p1.setLayout(new GridLayout(2,4));
		for(i=0;i<=3;i++){
			label[i]=new JLabel(labelName[i]);
			label[i].setPreferredSize(new Dimension(100, 20));
			label[i].setHorizontalAlignment(JLabel.CENTER);
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
	
	public JPanel buttonFormMod(){
		JPanel p1=new JPanel();
		p1.setPreferredSize(new Dimension(400,50));
		p1.setLayout(new GridLayout(1,3));
		int i;
		String[] buttonname={"Modify","Clear","Close Window"};
		button=new JButton[3];
		for(i=0;i<3;i++){
			button[i]=new JButton(buttonname[i]);
			button[i].addActionListener(this);
			p1.add(button[i]);
		}
		return p1;
	}

}