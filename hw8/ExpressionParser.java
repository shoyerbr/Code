package hw8;

import java.util.*;

/** An immutable class, stores variable to {true,false} mappings
 */
class Context {

	HashMap<String,Boolean> map = new HashMap<String,Boolean>();
	boolean lookup(String var) {
		return map.get(var).booleanValue();
	}
	public Context(HashMap<String,Boolean> m) {
		map = new HashMap(m);
	}
}

/**
 * Class ExpressionParser encapsulates a Boolean expression and a Context in 
 * which the expression is evaluated
 */
public class ExpressionParser {
	
	private BooleanExp expression;
	private Context context;
	
	public void init(BooleanExp e, HashMap<String,Boolean> hm) {
		expression = e;
		context = new Context(hm);
	}
	
		
	/** 
	  *  @param: str the string expression in preorder. E.g., AND OR x y z represents (x OR y) AND z
	  *  @return: returns the corresponding Boolean expression
	  *  static "position" is used to avoid passing "position" as argument to the recursive calls
	  *  str must be a sequence of white-space separated strings, e.g., "OR x y", "AND OR x y OR z w"
	 */	
	public static int position;	
	public static BooleanExp parse(String str) {
		if (position >= str.length()) {
			return null;
		}
		String token;
		int i = str.indexOf(" ",position);

		// Read the next token from String str.
		if (i != -1)
			token = str.substring(position,i+1);
		else 
			token = str.substring(position);
		
		// Advance "position" beyond token
		position += token.length();

		// If token is AND, parse the left operand into "left", 
		// then parse the right operand into "right" and create 
		// an And Boolean Expression
		if (token.equals("AND ")) {
			BooleanExp left = parse(str);
			BooleanExp right = parse(str);
			if ((left == null) || (right == null)) { 
				return null;
			}
			return new AndExp(left,right);
		}
		else if (token.equals("OR ")) {
			BooleanExp left = parse(str);
			BooleanExp right = parse(str);
			if ((left == null) || (right == null)) {
				return null;
			}
			return new OrExp(left,right);			
		}
		else if (token.equals("true") || token.equals("true ")) {
			return new Constant(Boolean.TRUE);
		}
		else if (token.equals("false") || token.equals("false ")) {
			return new Constant(Boolean.FALSE);
		}
		else if(token.equals("NOT "))
		{
			BooleanExp left = parse(str);
			return new NotExp(left);
		}
		// Otherwise, the token is a variable (e.g., x, xyz). 
		// Get rid of the white space if necessary 
		else { 
		    if (token.charAt(token.length()-1)==' ') {
			token = token.substring(0,token.length()-1);
		    }
		    return new VarExp(token);
		}	
	}
	/**
	 * @return the boolean value of the enclosed expression,
	 *         evaluated in Context context.
	 */	
	public boolean evaluate() 
	{
		return evaluate(context, expression);		
	}

	/**
	 * 
	 * @param preorder  If True, returns expression in Preorder, False returns Inorder 
	 * @return string corresponding to Preorder of expression if preorder is True
	 * 	   string corresponding to Inorder of expression otherwise
	 */	
	private String print(boolean preorder)
	{
		return print(preorder, expression);
	}
	
	public String print(boolean preorder, BooleanExp exp)
	{
		StringBuffer out = new StringBuffer();
		if (preorder)
			out.append(exp.print());
		else
			out.append(exp.print2());
		return out.toString();
	}
	/**
	 * 
	 * @param context
	 * @param exp
	 * @return value of BooleanExp exp in Context context
	 */
	private boolean evaluate(Context context, BooleanExp exp) 
	{
			if (exp instanceof AndExp)
				return evaluate(context, exp.get_left()) && evaluate(context, exp.get_right());
			if (exp instanceof OrExp)
				return evaluate(context, exp.get_left()) || evaluate(context, exp.get_right());
			if (exp instanceof Constant)
				return ((Constant) exp).get_value();
			if (exp instanceof VarExp)
				return context.lookup(exp.get_varstring());
			return false;
	}
		
}
