package hw9;
import hw7.InputParser;
import hw6.Path;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.Arrays;

public class DisplayGui implements ActionListener
{	
	private JButton okay;
	private JButton reset;
	
	private InputParser data;
	private RouteDisplay route;
	
	private JFrame frame;
	
	private JPanel panel1;
	private JPanel panel3;
	
	private JTextField primary;
	private JTextField secondary;

	
	public DisplayGui()
	{
		data = new InputParser();
		try {
			data.readin("src/hw7/data/all_restaurants_troy.dat");
			data.closed("src/hw7/data/closed_paths.dat");
		}
		catch(Exception e) {}
		
		data.makegraph();
		
		frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
	public void showGUI()
	{
		JLabel uno = new JLabel("Starting Restaurant: ");
		JLabel dos = new JLabel("Destination Restaurant: ");
		
		primary = new JTextField();
		secondary = new JTextField();
		
		okay = new JButton("Okay");
		okay.addActionListener(this);
		okay.setPreferredSize(new Dimension(75,30));
		
		reset = new JButton("Reset");
		reset.addActionListener(this);
		reset.setPreferredSize(new Dimension(75,30));
		
		panel1 = new JPanel();
		panel1.setLayout(new BoxLayout(panel1, BoxLayout.PAGE_AXIS));
		panel1.add(uno);
		panel1.add(primary);
		panel1.add(dos);
		panel1.add(secondary);
		
		route = new RouteDisplay();
		
		panel3 = new JPanel();
		panel3.add(okay);
		panel3.add(reset);
		
		frame.setLayout(new BorderLayout());
		frame.add(panel1, BorderLayout.NORTH);
		frame.add(route, BorderLayout.CENTER);
		frame.add(panel3, BorderLayout.SOUTH);
		frame.setPreferredSize(new Dimension(1024,768));
		frame.pack();
		frame.setLocationRelativeTo(null);
		frame.setVisible(true);
	}
public void actionPerformed(ActionEvent e)
	{
		String uno = primary.getText();
		String dos = secondary.getText();
		
		JButton source = (JButton)e.getSource();
		
		if(source.equals(reset)) {
			primary.setText("");
			secondary.setText("");
			
			route.setPath(1, null);
			route.repaint();
		}
		else if(source.equals(okay)) {
			Path<String> path = data.findPath(uno, dos);
			int code = 4;
			if(path == null)
				code = 2;
			if(uno.equals(dos))
				code = 3;
			route.setPath(code, path);
			frame.repaint();
		}
	}
}
