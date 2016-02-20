package hw8;

public abstract class CompositeExp extends BooleanExp 
{
	public abstract BooleanExp get_left();
	public abstract BooleanExp get_right();
	public abstract boolean get_value();
	public abstract String get_varstring();
}
