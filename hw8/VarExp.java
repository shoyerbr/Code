package hw8;

public class VarExp extends BooleanExp
{
	private String varstring;
	
	public VarExp(String VS)
	{
		varstring = VS;
	}
	
	public String get_varstring()
	{
		return varstring;
	}
	
	public boolean get_value()
	{
		return new Boolean(null).booleanValue();
	}
	
	public BooleanExp get_right()
	{
		return null;
	}
	
	public BooleanExp get_left()
	{
		return null;
	}
	
	public String print2()
	{
		StringBuffer out = new StringBuffer();
		out.append(toString());
		return out.toString();
	}
	
	public String toString()
	{
		StringBuffer out = new StringBuffer();
		out.append(varstring);
		return out.toString();
	}
}

