import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class MyPaintTool extends JPanel implements ActionListener{
	private JButton[] b=new JButton[9];
	private JLabel l1;
	static int patern;

	private String bname[]={"Line","Triangle","Rectangle","Teragon","Pentagon","Hexagon","Elipse","clear","quite"};
	public MyPaintTool(){
		patern=0;
		setPreferredSize(new Dimension(150, 600));
		setBackground(Color.BLACK);
       setLayout(new FlowLayout());
		for(int i=0;i<9;i++){
			if(i==7){
				l1=new JLabel("");
		        l1.setPreferredSize(new Dimension(100, 50));
		        add(l1);
			}
			b[i]=new JButton(bname[i]);
	        b[i].setPreferredSize(new Dimension(100, 50));
	        add(b[i]);
	        b[i].addActionListener(this);
	        if(i>=3&&i<=5){
	        	b[i].setBackground(Color.BLACK);
	        }
		}
	}

	public void actionPerformed(ActionEvent e){
        if(e.getSource()==b[0]){
        	patern=0;
        	StatePanel.t1.setText(bname[0]);
        	ColorPanel.help.setText("Line : PLEASE drag and release");
        }else if(e.getSource()==b[1]){
        	patern=1;
        	StatePanel.t1.setText(bname[1]);
        	ColorPanel.help.setText("Triangle : PLEASE drag and release AND click 1 point");
        }else if(e.getSource()==b[2]){
        	patern=2;
        	StatePanel.t1.setText(bname[2]);
        	ColorPanel.help.setText("Rectangle : EASE drag and release");
        }else if(e.getSource()==b[3]){
        	patern=3;
        	StatePanel.t1.setText(bname[3]);
        	ColorPanel.help.setText("Teragon : PLEASE click 4 points");
        }else if(e.getSource()==b[4]){
        	patern=4;
        	StatePanel.t1.setText(bname[4]);
        	ColorPanel.help.setText("Pentagon : PLEASE click 5 points");
        }else if(e.getSource()==b[5]){
        	patern=5;
        	StatePanel.t1.setText(bname[5]);
        	ColorPanel.help.setText("Hexagon : PLEASE click 6 points");
        }else if(e.getSource()==b[6]){
        	patern=6;
        	StatePanel.t1.setText(bname[6]);
        	ColorPanel.help.setText("Orval : PLEASE drag and release");
        }else if(e.getSource()==b[7]){
        	patern=7;
        	StatePanel.t1.setText(bname[7]);
        	ColorPanel.help.setText("Clear : PLEASE click");
        }else if(e.getSource()==b[8]){
        	patern=8;
        	StatePanel.t1.setText(bname[8]);
        	ColorPanel.help.setText("Exit");
        	System.exit(0);
        }
    	MyDrawFix.i=0;
    }
}
