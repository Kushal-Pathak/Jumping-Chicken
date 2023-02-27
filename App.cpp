#include <iostream>
#include <conio.h>
#include <windows.h>
#define h 15
#define w 100
using namespace std;

char buffer[h][w];
string chicken_body = "...\\\\....(o>\\\\_//).\\_/_).../\\.";
char chicken[5][6];
int score;
int x_off = 10, y_off = 9;
void init_buffer();
void render();
void parse_chicken();

int main() {
	init_buffer();
	parse_chicken();
	render();
	return 0;
}
void render() {
	system("cls");
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			cout << buffer[i][j];
		}
		cout << endl;
	}
	cout << "\t  Score: " << score;
}
void init_buffer() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			buffer[i][j] = ' ';
			buffer[h - 1][j] = '_';
		}
	}
	cout << endl;
}

void parse_chicken() {
	int index = 0;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			index = j + 6 * i;
			if (chicken_body[index] == '.')chicken[i][j] = ' ';
			else chicken[i][j] = chicken_body[index];
			buffer[i + y_off][j + x_off] = chicken[i][j];
		}
	}

}