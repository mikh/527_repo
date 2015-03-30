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
}
