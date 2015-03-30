package data_structures;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

import parsers.TwikiParser;

public class LinkStruct {
	public String l_name = "", l_href = "", l_class = "", l_target = "", l_page = "", l_view_link = "", l_edit_link = "", l_error = "", l_page_output = "";
	
	public void write_to_file(String path) throws IOException{
		BufferedWriter bw = new BufferedWriter(new FileWriter(path, false));
		bw.write(l_page);
		bw.close();
	}
	
	public void read_from_file(String path) throws IOException{
		String page = "";
		BufferedReader br = new BufferedReader(new FileReader(path));
		String line = "";
		
		while((line = br.readLine()) != null)
			page += line;
		br.close();
		l_page = page;
	}
	
	public ArrayList<QuestionFormat> qq = new ArrayList<QuestionFormat>();
	public int l_total = 0;
	public void calculate_total(){
		l_total = 0;
		for(QuestionFormat a : qq){
			a.calculate_total();
			l_total += a.total;
		}
	}
	public boolean print_global = false;
	
	
	
	public int add_grades(String question_header, String problem_header, String block_start_header, String block_end_header){
		String page = l_page;
		for(int ii = 0; ii < qq.size(); ii++){
			int q_index = TwikiParser.find_question(page, qq.get(ii).question_number, question_header);
			if(q_index == -1){
				System.out.println(String.format("Cannot find question #%d for %s\n", qq.get(ii).question_number, l_name));
				l_error = String.format("Cannot find question #%d for %s\n", qq.get(ii).question_number, l_name);
				return -1;
			}
			int p_index = TwikiParser.find_text_after_index(page, problem_header, q_index);
			if(p_index == -1){
				System.out.println(String.format("Cannot find grading section #%d for %s\n", qq.get(ii).question_number, l_name));
				l_error = String.format("Cannot find grading section #%d for %s\n", qq.get(ii).question_number, l_name);
				return -1;
			}
			
			int v_index_s = TwikiParser.find_text_after_index(page, block_start_header, p_index);
			if(v_index_s == -1){
				System.out.println(String.format("Cannot find block start section #%d for %s\n", qq.get(ii).question_number, l_name));
				l_error = String.format("Cannot find block start section #%d for %s\n", qq.get(ii).question_number, l_name);
				return -1;
			}
			int v_index_e = TwikiParser.find_text_after_index(page, block_start_header, v_index_s);
			if(v_index_e == -1){
				System.out.println(String.format("Cannot find block end section #%d for %s\n", qq.get(ii).question_number, l_name));
				l_error = String.format("Cannot find block start end #%d for %s\n", qq.get(ii).question_number, l_name);
				return -1;
			}
			v_index_e -= block_end_header.length();
			
			String output_text = qq.get(ii).build_output();
			page = TwikiParser.replace_between_indices(page, output_text, v_index_s, v_index_e);
		}
		
		l_page_output = page;
		return 0;
	}
	
	public void output_graded_pages(String debug_folder) throws IOException{
		String f = ((debug_folder + "\\") + l_name) + ".txt";
		BufferedWriter bw = new BufferedWriter(new FileWriter(f, false));
		bw.write(l_page_output);
		bw.close();
	}
}
