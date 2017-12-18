#include <iostream>
#include <fstream>  
#include <string>
#include <vector>
using namespace std;

bool IsReservedWords(string str){
	if ((str == "if") ||(str == "then") || (str =="else") || (str =="end") || (str =="repeat") || (str =="until") || (str =="read") || (str == "write")){ return true; }
	else { return false; }
}

int main(){
	ifstream inFile;
	inFile.open("inputfile.txt");
	if (inFile.fail())
	{
		cout << "Error openning the file" << endl;
	}
	char ch;
	int state = 0;
	const int START = 0; 
	const int INNUM = 1;
	const int INID = 2;
	const int INASSIGN = 3;
	const int INCOMMENT = 4;
	const int DONE = 5;
	int prev_state = 0;
	string str = "";
	std::vector<char> accum;
	fstream fin("inputfile.txt", fstream::in);
	ofstream outFile;
	outFile.open("outputfile.txt");
	while (fin >> noskipws >> ch)
	{
		switch (state)
		{
		case START:
			if (iswspace(ch)){ state = START; }
			else if (ch == '{'){ state = INCOMMENT; }
			else if (isdigit(ch)){ state = INNUM; accum.push_back(ch); }
			else if (isalpha(ch)){ state = INID; accum.push_back(ch); }
			else if (ch == ':'){ state = INASSIGN; accum.push_back(ch); }
			else{ prev_state = state; state = DONE; accum.push_back(ch); }

			break;

		case INCOMMENT:
			if (ch != '}'){
				state = INCOMMENT;
			}
			if (ch == '}'){ state = START; }

			break;

		case INID:
			if (isalpha(ch)){ accum.push_back(ch); state = INID; }
			else{ prev_state = state; state = DONE; }

			break;

		case INNUM:
			if (isdigit(ch)){ accum.push_back(ch); state = INNUM; }
			else{ prev_state = state; state = DONE; }

			break;

		case INASSIGN:
			if (ch == '='){ accum.push_back(ch); prev_state = state; state = DONE; }
			else { prev_state = state; state = DONE; }

			break;



		}

		if(state== DONE)
		{		// empty the vector
			for (std::vector<char>::iterator it = accum.begin(); it != accum.end(); ++it)
			{
				str += *it;
			}

			if (prev_state == 1){
				outFile << str << "--> number" << endl;
			}
			if (prev_state == 2){
				if (IsReservedWords(str)){ outFile << str << " --> Reserved word" << endl; }
				else{
					outFile << str << " --> identifier" << endl;
				}
			}
			if ((prev_state == 3) || (prev_state == 0)){
				outFile << str << " --> Special Symbols" << endl;
			}


			accum.clear();

			str = "";
			state = START;
	}
	}
	while (1)
	{

	}
}
