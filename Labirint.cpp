#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void labcout(vector<vector<int>> labirint) {
	for (int i = 0; i < labirint.size(); i++) {
		for (int j = 0; j < labirint[0].size(); j++) {
			cout << setw(3)<<labirint[i][j];
		}
		cout << '\n';
	}
}

void labFill(vector<vector<int>>& labirint, fstream& input) {
	vector<int> row;
	char c;
	labirint.push_back(row);
	for (int i = 1; !input.eof(); i++) {
		row.clear();
		row.push_back(0);//делает самый левый элемент строки равным 0
		c = input.get();
		while( c!='\n' && !input.eof()) {				
			row.push_back( c - '0');
			cout << c-'0';
			c = input.get();
		}
		cout << endl;
		row.push_back(0);//делает самый правый элемент строки равным 0
		labirint.push_back(row);
		if (input.eof()) break;
	}
	for (int i = 0; i < labirint[1].size(); i++) { //заполняет верхнюю и нижнюю строку нулями, лабиринт полностью "окаймлен" нулями
		labirint[0].push_back(0);
	}
	row = labirint[0];
	labirint.push_back(row);
}

int main()
{
	fstream input, output;
	vector<vector<int>> labirint;
	input.open("A1.txt");
	if (!input) {
		cerr << "File is closed";
		exit(0);
	}
	if (input.eof()) {
		cerr << "File is empty";
		exit(0);
	}
	labFill(labirint, input);
	input.close();
	output.open("A2.txt");
	if (!output) {
		cerr << "Output file is closed";
		exit(0);
	}
	labcout(labirint);
	int i = 1, j = 1, value = 1;
	bool flag = 1;
	output << "(" << i - 1 << ";" << j - 1 << ")" << ", ";
	while (flag) {
		if (labirint[i + 1][j] == 1) {
			i++;
			value++;
			labirint[i][j] = value;
		}
		else if (labirint[i][j+1] == 1) {
			j++;
			value++;
			labirint[i][j] = value;
		}
		else if (labirint[i-1][j] == 1) {
			i--;
			value++;
			labirint[i][j] = value;
		}
		else if (labirint[i][j - 1] == 1) {
			j--;
			value++;
			labirint[i][j] = value;
		}									//можно сделать ход

		else if (labirint[i + 1][j] == value-1) {
			labirint[i][j] = 0;
			i++;
			value--;
		}
		else if (labirint[i][j + 1] == value - 1) {
			labirint[i][j] = 0;
			j++;
			value--;
		}
		else if (labirint[i - 1][j] == value - 1) {
			labirint[i][j] = 0;
			i--;
			value--;
		}
		else if (labirint[i][j - 1] == value - 1) {
			labirint[i][j] = 0;
			j--;
			value--;
		}								//нельзя сделать ход
		cout << "(" << i - 1 << ";" << j - 1 << ")" << "  "<<endl;
		labcout(labirint);
		output << "(" << i - 1 << ";" << j - 1 << ")" << ", ";
		if (!labirint[i][j - 1] && !labirint[i][j + 1] && !labirint[i + 1][j] && !labirint[i - 1][j]) {
			output.close();
			fstream clear("A2.txt", ios::out|ios::trunc);
			clear.close();
			output.open("A2.txt");
			output << "There is no way out of the maze ";
			flag = 0;
			cout << "No exit";
		}
		if (i == labirint.size() - 2 && j == labirint[0].size() - 2) flag = 0;
	}
	output.close();
}