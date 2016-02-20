package hw8;

public class Constant extends BooleanExp
{
	private Boolean value;
	
	public Constant(Boolean v)
	{
		value = v;
	}
	
	public String get_varstring()
	{
		return null;
	}
	
	public BooleanExp get_right()
	{
		return null;
	}
	
	public BooleanExp get_left()
	{
		return null;
	}
	
	public boolean get_value()
	{
		return value.booleanValue();
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
		out.append(value.toString());
		return out.toString();
	}
}
