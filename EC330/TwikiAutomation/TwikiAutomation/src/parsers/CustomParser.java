package parsers;

import java.util.ArrayList;

import data_structures.LinkStruct;

public class CustomParser {
	public static ArrayList<LinkStruct> filter_links_on_homework_name_and_get_student_name_and_make_full_links(ArrayList<LinkStruct> links, String hw_name, String web_name){
		for(int ii = links.size()-1; ii >= 0; ii--){
			String h = links.get(ii).l_href;
			// /twiki/bin/view/EC330/HomeworkThreeAdinHorovitz
			
			//find last /
			int index = h.indexOf("/"), l_index = 0;
			while(index != -1){
				l_index = index+1;
				index = h.indexOf("/",l_index);
			}
			h = h.substring(l_index);
			
			index = h.indexOf(hw_name);
			if(index == -1)
				links.remove(ii);
			else{
				links.get(ii).l_name = h.substring(index+hw_name.length());
				links.get(ii).l_view_link = web_name + links.get(ii).l_href;
				links.get(ii).l_edit_link = links.get(ii).l_view_link.replace("/view/", "/edit/");
			}
		}
		
		return links;
	}
}
