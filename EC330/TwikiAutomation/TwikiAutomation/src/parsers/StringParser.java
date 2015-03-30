package parsers;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class StringParser {
	public static String get_first_filter(String s, String start_pattern, String end_pattern){
		int index = s.indexOf(start_pattern);
		if(index != -1){
			int end_index = s.indexOf(end_pattern, index + start_pattern.length());
			if(end_index != -1)
				return s.substring(index + start_pattern.length(), end_index);
		}
		return "";
	}
	
	public static ArrayList<String> parse_list_file(String file) throws IOException{
		BufferedReader br = new BufferedReader(new FileReader(file));
		ArrayList<String> lines = new ArrayList<String>();
		String line = "";
		while((line = br.readLine()) != null){
			line = line.trim();
			if(!line.equals(""))
				lines.add(line);			
		}
		br.close();
		return lines;
	}
}
