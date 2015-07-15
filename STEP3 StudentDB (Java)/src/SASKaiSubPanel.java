import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class SASKaiSubPanel extends JFrame implements ActionListener{

	private JButton previous,next;
	private JLabel now;
	private int k;
	private JPanel basePanel;
	CardLayout layout;
	private String[] buttonname={"Regist","Delete","Modify"};
	
	SASKaiSubPanel(){
		k=0;
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(450, 450);
		setTitle("");
		setLayout(new BorderLayout());
		JPanel p1=cardPanel();
		add(p1,BorderLayout.CENTER);
		JPanel p2=buttonForm();
		add(p2,BorderLayout.SOUTH);
		pack();
	}
	public JPanel cardPanel(){
		basePanel=new JPanel();
		basePanel.setSize(450, 200);
		layout = new CardLayout();
		basePanel.setLayout(layout);
		SASKaiSubPanelRegist regist=new SASKaiSubPanelRegist();
		SASKaiSubPanelDelete delete=new SASKaiSubPanelDelete();
		SASKaiSubPanelModify modify=new SASKaiSubPanelModify();
		basePanel.add(regist,"reg");
		basePanel.add(delete,"del");
		basePanel.add(modify,"mod");
		return basePanel;
	}
	public JPanel buttonForm(){
		JPanel p1=new JPanel();
		p1.setPreferredSize(new Dimension(400,100));
		p1.setLayout(new GridLayout(2,3));
		int i;
		JLabel[] empty=new JLabel[3];
		for(i=0;i<3;i++){
			empty[i]=new JLabel();
			p1.add(empty[i]);
		}
		previous=new JButton(buttonname[(k+1)%3]);
		previous.setBackground(Color.LIGHT_GRAY);
		previous.addActionListener(this);
		p1.add(previous);
		now=new JLabel(buttonname[k%3]);
		now.setHorizontalAlignment(JLabel.CENTER);
		p1.add(now);
		next=new JButton(buttonname[(k+2)%3]);
		next.setBackground(Color.LIGHT_GRAY);
		next.addActionListener(this);
		p1.add(next);
		return p1;
	}
	public void actionPerformed(ActionEvent e) {
//		if(e.getSource() == previous){
//			layout.next(basePanel);
//			k=+1;
//			previous.setText(buttonname[(k+1)%3]);
//			next.setText(buttonname[(k+2)%3]);
//			now.setText(buttonname[k=(k%3)]);
//		}
//		else if(e.getSource() == next){
//			layout.previous(basePanel);
//			k=+2;
//			previous.setText(buttonname[(k+1)%3]);
//			next.setText(buttonname[(k+2)%3]);
//			now.setText(buttonname[k=(k%3)]);
//		}
		String temp[]={now.getText(),previous.getText(),next.getText()};
		if(e.getSource() == previous){
			previous.setText(temp[2]);
			next.setText(temp[0]);
			now.setText(temp[1]);
			layout.next(basePanel);
			k=+1;
		}
		else if(e.getSource() == next){
			previous.setText(temp[0]);
			next.setText(temp[1]);
			now.setText(temp[2]);
			layout.previous(basePanel);
			k=+2;
		}
	}
	public static void main(String[] args) {
		SASKaiSubPanel obj = new SASKaiSubPanel();
		obj.setVisible(true);
	}
}
