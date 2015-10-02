#include "header.h"

//-----Functions------
void ce_level::load_file(string filename){
	//Loop through each line of the given file and create a string which contains all the data from it.

	//Open the file and make buffer
	ifstream stream(filename);
	string line_buffer;
	string read_buffer;

	//Loop through each line and make a string
    while (getline(stream, line_buffer)){
		read_buffer.append(line_buffer);
		read_buffer.append("\n");
    }

	//Pass text to function to initialize the level obj
	decode_text(read_buffer);
}

//Decode Level
void ce_level::decode_text(string text){
	//Loop through the given string line by line and process into the level obj

	istringstream line_stream(text);
	string line_buffer;
	
	bool grid_read = true;
	int row = 0;
	int col = 0;
	while (getline(line_stream,line_buffer)){

		//Check if grid or parameter part of level file is being read
		if (line_buffer.compare("#") == 0){
			grid_read = false;
			continue;
		}

		if (grid_read){
			//Read the grid section of the file
			col = 0;

			//Read the levels grid into the bitmap var
			for (int i=0; i<line_buffer.length(); i++){
				int value = line_buffer.at(i) - 48;
				layout[row][col] = value;

				col++;
			}

			row++;

		}else{
			//Read the parameter section of the file

			//Get the individual parameter parts
			int delim = line_buffer.find("=");
			string key = line_buffer.substr(0,delim);
			string value = line_buffer.substr(delim+1,line_buffer.length() - (delim + 1));
			int value_n = atoi(value.c_str());

			//Store the value in the correct var
			if (key.compare("PX")==0){
				start.x = value_n * grid_w;
			}else if (key.compare("PY")==0){
				start.y = value_n * grid_h;
			}else if (key.substr(0,1).compare("S") == 0){
				int swan_num = atoi(key.substr(1,1).c_str()) - 1;
				if (key.substr(2,1).compare("X")==0){
					ce_cord swan;
					swans.push_back(swan);
					swans[swan_num].x = value_n * grid_w;
				}else if (key.substr(2,1).compare("Y")==0){
					swans[swan_num].y = value_n * grid_h;
				}
			}

		}
	}

	//Setup level size
	size.width = col;
	size.height = row;

	isLoaded = true;
}