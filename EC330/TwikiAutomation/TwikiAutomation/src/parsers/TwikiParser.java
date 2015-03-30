package parsers;

public class TwikiParser {
	public static int find_question(String twiki, int question, String question_header){
		String q = question_header + Integer.toString(question);
		int index = twiki.indexOf(q);
		if(index == -1)
			return -1;
		else
			return index + q.length();		
	}
	
	public static int find_text_after_index(String twiki, String text, int index){
		int i = twiki.indexOf(text, index);
		if(i == -1)
			return -1;
		else return i + text.length();
	}
	
	public static String replace_between_indices(String twiki, String text, int start_index, int end_index){
		String twiki1 = twiki.substring(0,start_index);
		String twiki2 = twiki.substring(end_index);
		String t = (twiki1 + text) + twiki2;
		return t;
	}
	
	
}
