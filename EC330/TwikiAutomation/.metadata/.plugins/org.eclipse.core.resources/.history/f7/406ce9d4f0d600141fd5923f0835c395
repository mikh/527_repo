package data_structures;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;

public class LinkStruct {
	public String l_name = "", l_href = "", l_class = "", l_target = "", l_page = "", l_view_link = "", l_edit_link = "", l_error = "";
	
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
}
