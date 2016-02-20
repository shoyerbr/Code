package hw8;

/**
 * 
 * BooleanExp is an immutable class. It represents boolean constants, boolean variables,
 * Or boolean expressions and And boolean expressions.
 *
 */

public abstract class BooleanExp
{
	public abstract BooleanExp get_right();
	public abstract BooleanExp get_left();
	public abstract String get_varstring(); 
	public abstract String toString();
	public String print() {return toString();}
	public abstract boolean get_value();
	public abstract String print2();
}
