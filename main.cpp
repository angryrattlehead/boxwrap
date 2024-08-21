#include <iostream>
#include <fstream>

#define DEBUG 0
#define DBG if (DEBUG)

using namespace std;

// Return the size of the longest line, given a file
int get_longest_line(ifstream& file )
{
	int longest_line = 0;
	string line = "";

	while (!file.eof()) {
		std::getline(file, line);
		int l = line.size();
		if (l > longest_line) 
			longest_line = l;
	}
	return longest_line;
}

// Return the number of lines/rows, given a file
int get_file_rows(ifstream &file)
{
	int i = 0;
	while (!file.eof()) {
		string line;
		getline(file, line);
		i++;
	}
	return i;
}

//Wrap a box around a text file, keeping the formatting of the text as is.
void draw(ifstream& file, int padding)
{
	file.clear();
	file.seekg(0);
	int longest_line = get_longest_line(file);
	file.clear();
	file.seekg(0);
	int file_lines = get_file_rows(file);
	file.clear();
	file.seekg(0);

	char c_cor='+'; // corner character
	char c_hor='-'; // horizontal character
	char c_ver='|'; // vertical character
	char c_fil=' ';	// filler character

	int rows = file_lines + padding + 2;
	int cols = longest_line + padding + 2;

	DBG cout << "Rows: " << rows << " and Cols: " << cols << endl;

	for (int r = 0; r < rows; r++) {

		// if is first and last row, draw the horizontal line
		if (r == 0 || r == rows-1) {
			cout << c_cor;
			for (int c = 1; c < cols; c++) 
				cout << c_hor;
			cout << c_cor;
		}

		// honor the padding for rows
		else if (r == 0 + padding || r == rows - padding) {
			cout << c_ver;
			for (int c = 1; c < cols; c++)
				cout << c_fil;
			cout << c_ver;
		}

		// else print the vertical char, padding with filler, and then the text;
		else {
			cout << c_ver;
			for (int p = 0; p < padding; p++)
				// padding at the start
				cout << c_fil;

			string line="";
			getline(file, line);
			cout << line;

			// if line length is less than 'cols', we need to fill
			if (cols > line.size()) {
				for (int i = 0; i < (cols-line.size()-padding-2); i++)
					cout << c_fil;
			}

			for (int p = 0; p < padding; p++)
				// padding on the back
				cout << c_fil;
			cout << c_ver;
		}

		cout << endl;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 2) {
		cerr << "ERROR: Please provide a filename as a single argument." << endl;
		return 2;
	}
	else {
		string filename = "";
		filename = argv[1];
		ifstream file(filename, ios_base::in);
		if (!file.is_open()) {
			cerr << "ERROR: Cannot open file" << endl;
			return 3;
		}

		int padding = 1;
		draw(file, padding);

		file.close();
	}

	return 0;
}
