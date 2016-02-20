package hw8;

public class OrExp extends CompositeExp
{
	private BooleanExp right;
	private BooleanExp left;
	
	public OrExp(BooleanExp l, BooleanExp r)
	{
		right = r;
		left = l;
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
		return new Boolean(null).booleanValue();
	}
	
	public String print2()
	{
		StringBuffer out = new StringBuffer();
		if (left instanceof NotExp)
			out.append("(" + left.print2() + ")" + " OR ");
		else
			out.append(left.print2() + " OR ");
		if (right instanceof OrExp)
			out.append("(" + right.print2() + ")");
		else
			out.append(right.print2());
		return out.toString();
	}
	
	public String toString()
	{
		StringBuffer out = new StringBuffer();
		out.append("OR " + get_left().toString() + " " + get_right().toString());
		return out.toString();
	}
}
