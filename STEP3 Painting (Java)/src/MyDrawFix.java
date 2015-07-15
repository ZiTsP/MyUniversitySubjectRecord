import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JLabel;
import javax.swing.JPanel;

public class MyDrawFix extends JPanel implements MouseListener{
    private int width,height;
    static int i;
    private int[] px=new int[14];
    private int[] py=new int[14];
    static JLabel help;
    static JPanel f;
    static Graphics2D g2;

    public void update(Graphics g){
		    g2.clearRect(0, 0, getWidth(), getHeight());
		    paint(g);
      }

      public void paint(Graphics g){
    	  System.out.println("MyDraw");
    	  Graphics2D g2 = (Graphics2D)g;
          super.paintComponents(g);
          System.out.println("PaintComponent");
          switch(ColorPanel.colorPatern){
	          case (0):g.setColor(Color.BLACK);
	          System.out.println("brack");break;
	          case (1):g.setColor(Color.WHITE);break;
	          case (2):g.setColor(Color.RED);
	          System.out.println("red");break;
	          case 3:g.setColor(Color.GREEN);break;
	          case 4:g.setColor(Color.BLUE);break;
	          case 5:g.setColor(Color.YELLOW);break;
	          case 6:g.setColor(Color.DARK_GRAY);break;
	          case 7:g.setColor(Color.GRAY);break;
	          case 8:g.setColor(Color.LIGHT_GRAY);break;
	          case 9:g.setColor(Color.PINK);break;
	          case 10:g.setColor(Color.CYAN);break;
	          case 11:g.setColor(Color.MAGENTA);break;
	          case 12:g.setColor(Color.ORANGE);break;
          }
  		switch(MyPaintTool.patern){
	  		case(0):
	  	        g.drawLine(px[0],py[0],px[1],py[1]);
	  	        i=0;
	  	        break;
	  		case(1):
	  			if(i==4){
	  		        g.drawLine(px[0],py[0],px[1],py[1]);
	  		        g.drawLine(px[0],py[0],px[2],py[2]);
	  		        g.drawLine(px[2],py[2],px[1],py[1]);
	  			i=0;
	  			}
	  			break;
	  		case(2):
	  			width=px[1]-px[0];
	  			height=py[1]-py[0];
	  			g.drawRect(px[0], py[0], width, height);
	  			i=0;
	  			break;
	  		case(3):
	  			if(i==8){
	  				for(int k=1,l=0;k<=7;k+=2,l++){
	  					px[l]=px[k];
	  					py[l]=py[k];
	  				}
	  			g.drawPolygon(px,py,4);
	  			i=0;
	  			}break;
	  		case(4):
	  			if(i==10){
	  				for(int k=1,l=0;k<=9;k+=2,l++){
	  					px[l]=px[k];
	  					py[l]=py[k];
	  				}
	  			g.drawPolygon(px,py,5);
	  			i=0;
	  			}break;
	  		case(5):
	  			if(i==12){
	  				for(int k=1,l=0;k<=11;k+=2,l++){
	  					px[l]=px[k];
	  					py[l]=py[k];
	  				}
	  			g.drawPolygon(px,py,6);
	  			i=0;
	  			}break;
	  		case(6):
	  			width=px[1]-px[0];
	  			height=py[1]-py[0];
	  			g.drawOval((px[1]+px[0])/2, (py[1]+py[0])/2, width, height);
	  			i=0;
	  			break;
	  		case(7):
	  		    g2.clearRect(0, 0, getWidth(), getHeight());
	  		    i=0;
	  		    break;
  		}
      }

    public MyDrawFix(){
	i=0;
    setPreferredSize(new Dimension(800, 600));
    setLayout(new BorderLayout());
    addMouseListener(this);
    }

    public void paintComponent(Graphics g){
	}

    public void mousePressed(MouseEvent e){
    	px[i] = e.getX();
    	py[i] = e.getY();
        System.out.println("press");
    	i++;
    }
    
    public void mouseReleased(MouseEvent e){
    	px[i] = e.getX();
    	py[i] = e.getY();
        i++;
       repaint();
       System.out.println("drag repaint"+ColorPanel.colorPatern+MyPaintTool.patern);
    }

    public void mouseClicked(MouseEvent e){}
    public void mouseEntered(MouseEvent e){}
    public void mouseExited(MouseEvent e){}
}