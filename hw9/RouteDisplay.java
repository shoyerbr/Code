package hw9;

import javax.swing.*;
import java.awt.*;
import hw6.Path;
import java.util.ArrayList;

public class RouteDisplay extends JPanel
{
	private Path<String> rests;
	private int code; 
	
	public RouteDisplay()
	{  code = 0;  }
	
	public void paintComponent(Graphics g)
	{
	    super.paintComponent(g);
	    Graphics2D g2 = (Graphics2D) g;
	    //(below) all the corner cases for invlaid inputs
	    if(code == 0)
	    	return;
	    
	    if(code == 1)
	    {
	    	g2.dispose();
	    	return;
	    }
	    
	    if(code == 2)
	    {
	    	g2.drawString("There is no path.", 450, 75);
	    	return;
	    }
	    
	    if(code == 3)
	    {
	    	g2.drawString("The start and destination are the same!", 400, 75);
	    	return;
	    }
	    
	    ArrayList<String> nodes = rests.get_nodes();
	    int currx = 500;
	    int curry = 75;
	    
	    g2.drawString(rests.get_begin(), currx, curry);
	    curry += 5;
    	g2.drawLine(currx + 20, curry, currx + 20, curry+50);
    	curry += 60;
    	
	    for(int i=0; i<nodes.size(); i++) {
	    	g2.drawString(nodes.get(i), currx, curry);
	    	if(i != (nodes.size()-1)) {
	    		g2.drawLine(currx + 20, curry + 5, currx + 20, curry + 50);
	    		curry += 60;
	    	}
	    }
	    
	}
	
	public void setPath(int C, Path<String> R)
	{
		code = C;
		rests = R;  
	}
	
}
