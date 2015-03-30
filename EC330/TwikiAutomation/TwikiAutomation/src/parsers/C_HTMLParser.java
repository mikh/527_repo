package parsers;

import java.util.ArrayList;

import data_structures.LinkStruct;

public class C_HTMLParser {
	public static ArrayList<String> filter_html(String page, String start_pattern, String stop_pattern){
		ArrayList<String> matches = new ArrayList<String>();
		int close_index = 0;
		int index = page.indexOf(start_pattern, close_index);	//search for 1st opening pattern
		while(index != -1){	//while you can still find an opening pattern
			close_index = page.indexOf(stop_pattern, index + start_pattern.length());	//look for a close pattern after the current opening pattern index
			if(close_index == -1)	//if none found break
				break;
			matches.add(page.substring(index+start_pattern.length(), close_index));	//assuming found, add the text between the patterns to matches
			index = page.indexOf(start_pattern, close_index + stop_pattern.length());	//search for next opening pattern after end of current stop_pattern
		}
		
		return matches;
	}
	
	public static ArrayList<LinkStruct> parseLinks(ArrayList<String> links){
		ArrayList<LinkStruct> link_s = new ArrayList<LinkStruct>();
		for(String s:links){
			LinkStruct ls = new LinkStruct();
			
			//href="/twiki/bin/view/EC330/HomeworkThreeAdinHorovitz" class="twikiLink"
			ls.l_href = StringParser.get_first_filter(s, "href=\"", "\"");
			ls.l_class = StringParser.get_first_filter(s, "class=\"", "\"");
			ls.l_target = StringParser.get_first_filter(s, "target=\"", "\"");
			
			link_s.add(ls);
		}
		return link_s;
	}
	
	public static ArrayList<LinkStruct> filter_links_by_class(ArrayList<LinkStruct> links, String pass){
		for(int ii = links.size()-1; ii >= 0; ii--){
			if(!links.get(ii).l_class.equals(pass))
				links.remove(ii);
		}
		
		return links;
	}
}
