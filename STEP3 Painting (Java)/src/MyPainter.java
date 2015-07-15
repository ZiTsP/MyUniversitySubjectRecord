import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;

import javax.swing.JFrame;

public class MyPainter extends JFrame{
	static Container c;
	public MyPainter(){
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setTitle("MyJPaint");
		setPreferredSize(new Dimension(1000, 800));
		setBackground(Color.BLACK);
		c = getContentPane();
		c.setLayout(new BorderLayout());
        MyDrawFix md=new MyDrawFix();
        c.add(md,BorderLayout.CENTER);
		MyPaintTool pt=new MyPaintTool();
        c.add(pt,BorderLayout.EAST);
		ColorPanel cp=new ColorPanel();
        c.add(cp,BorderLayout.SOUTH);
		pack();
	    System.out.println("main");
	}

	public static void main(String[] args) {
		MyPainter mp =new MyPainter();
		mp.setLocation(0, 0);
		mp.setVisible(true);
	}
}
