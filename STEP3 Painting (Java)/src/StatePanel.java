import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;

import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;

public class StatePanel extends JPanel{
	private JLabel l1,l2;
	static JTextArea t1,t2;

	public StatePanel(){
		setPreferredSize(new Dimension(1100, 30));
		setBackground(Color.LIGHT_GRAY);
		setLayout(new FlowLayout());
		l1=new JLabel("STATE");
		l1.setPreferredSize(new Dimension(50, 20));
		add(l1);
		t1=new JTextArea("Line");
		t1.setPreferredSize(new Dimension(100, 20));
		add(t1);
		JLabel spase=new JLabel("");
		spase.setPreferredSize(new Dimension(100, 20));
		add(spase);
		l2=new JLabel("COLOR");
		l2.setPreferredSize(new Dimension(50, 20));
		add(l2);
		t2=new JTextArea("black");
		t2.setPreferredSize(new Dimension(100, 20));
		add(t2);
	}
}
