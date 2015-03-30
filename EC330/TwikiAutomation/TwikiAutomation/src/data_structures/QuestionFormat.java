package data_structures;

import java.util.ArrayList;

public class QuestionFormat {
	public String question_owner = "";
	public int question_number = 0;
	public int total = 0;
	public String overall_comment = "";
	public boolean use_parts = false;
	public ArrayList<Integer> question_part_grades = new ArrayList<Integer>();
	public ArrayList<String> question_part_comments = new ArrayList<String>();
	
	public void calculate_total(){
		total = 0;
		for(int i : question_part_grades){
			total += i;
		}
	}
	
	public String build_output(){
		String output = "";
		output += String.format("Question %d Results:\n\n", question_number);
		if(use_parts){
			calculate_total();
		}
		output += String.format("Total Grade: %d", total);
		if(!use_parts)
			output+= ("\t\t" + overall_comment);
		else{
			output += "\n\n";
			for(int ii = 0; ii < question_part_grades.size(); ii++){
				output += String.format("\t%-10d\t\t%s\n", question_part_grades.get(ii), question_part_comments.get(ii));
			}
		}
		
		output += "\n\n";
		return output;
	}
}
