import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JTextArea;

public class ColorPanel extends JPanel implements ActionListener{
	private JButton[] b=new JButton[13];
	static int colorPatern;
	StatePanel sp;
	static JTextArea help;
	public ColorPanel(){
		colorPatern=0;
		setPreferredSize(new Dimension(950,130));
		setBackground(Color.BLACK);
       setLayout(new FlowLayout());
       help=new JTextArea("Line : PLEASE drag and release");
       help.setPreferredSize(new Dimension(950, 20));
       add(help);
       for(int i=0;i<13;i++){
    	   b[i]=new JButton();
    	   b[i].setPreferredSize(new Dimension(70, 65));
    	   add(b[i]);
    	   b[i].addActionListener(this);
		}
       sp=new StatePanel();
       add(sp);
	   b[0].setBackground(Color.BLACK);
	   b[1].setBackground(Color.WHITE);
	   b[2].setBackground(Color.RED);
	   b[3].setBackground(Color.GREEN);
	   b[4].setBackground(Color.BLUE);
	   b[5].setBackground(Color.YELLOW);
	   b[6].setBackground(Color.DARK_GRAY);
	   b[7].setBackground(Color.GRAY);
	   b[8].setBackground(Color.LIGHT_GRAY);
	   b[9].setBackground(Color.PINK);
	   b[10].setBackground(Color.CYAN);
	   b[11].setBackground(Color.MAGENTA);
	   b[12].setBackground(Color.ORANGE);
	    System.out.println("color");
	}

	public void actionPerformed(ActionEvent e){
        if(e.getSource()==b[0]){
        	colorPatern=0;
        	StatePanel.t2.setText("Black");
        	setBackground(Color.BLACK);
        }else if(e.getSource()==b[1]){
        	colorPatern=1;
        	StatePanel.t2.setText("White");
        	setBackground(Color.WHITE);
        }else if(e.getSource()==b[2]){
        	colorPatern=2;
        	StatePanel.t2.setText("Red");
        	setBackground(Color.RED);
        }else if(e.getSource()==b[3]){
        	colorPatern=3;
        	StatePanel.t2.setText("Green");
        	setBackground(Color.GREEN);
        }else if(e.getSource()==b[4]){
        	colorPatern=4;
        	StatePanel.t2.setText("Blue");
        	setBackground(Color.BLUE);
        }else if(e.getSource()==b[5]){
        	colorPatern=5;
        	StatePanel.t2.setText("Yellow");
        	setBackground(Color.YELLOW);
        }else if(e.getSource()==b[6]){
        	colorPatern=6;
        	StatePanel.t2.setText("DarkGray");
        	setBackground(Color.DARK_GRAY);
        }else if(e.getSource()==b[7]){
        	colorPatern=7;
        	StatePanel.t2.setText("Gray");
        	setBackground(Color.GRAY);
        }else if(e.getSource()==b[8]){
        	colorPatern=8;
        	StatePanel.t2.setText("LightGray");
        	setBackground(Color.LIGHT_GRAY);
        }else if(e.getSource()==b[9]){
        	colorPatern=9;
        	StatePanel.t2.setText("Pink");
        	setBackground(Color.PINK);
        }else if(e.getSource()==b[10]){
        	colorPatern=10;
        	StatePanel.t2.setText("Cyan");
        	setBackground(Color.CYAN);
        }else if(e.getSource()==b[11]){
        	colorPatern=11;
        	StatePanel.t2.setText("Magenta");
        	setBackground(Color.MAGENTA);
        }else if(e.getSource()==b[12]){
        	colorPatern=12;
        	StatePanel.t2.setText("Orange");
        	setBackground(Color.ORANGE);
        }
    }
}
