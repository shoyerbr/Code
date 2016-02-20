package hw8;

public class NotExp extends CompositeExp
{
	private BooleanExp right;
	private BooleanExp left;
	
	public NotExp(BooleanExp l)
	{
		left = l;
		right = null;
	}
	
	public BooleanExp get_right()
	{
		return right;
	}
	
	public BooleanExp get_left()
	{
		return left;
	}
	
	public String get_varstring()
	{
		return null;
	}

	public boolean get_value()
	{
		return !left.get_value();
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
		out.append("NOT " + get_left().toString());
		return out.toString();
	}
}
