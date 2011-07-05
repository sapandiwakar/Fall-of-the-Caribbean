#include <fstream>
#include <vector>
#include <string>

using namespace std;

vector <string> wordlist;

void get_wordlist()
{
	fstream fin;
	fin.open("WordList.txt");

	string word;
	while (!fin.eof()) {
		fin >> word;
		wordlist.push_back(word);
	}
	fin.close ();
}