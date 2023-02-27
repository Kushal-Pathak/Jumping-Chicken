#include <iostream>
#include <conio.h>
#include <windows.h>
#define block (char)254
#define h 30
#define w 130
using namespace std;

char buffer[h][w];
string chicken_body = "...\\\\....(o>\\\\_//).\\_/_).../\\.";
char chicken[5][6];
int score;
float x_off = 20.0f, y_off = h - 6, vy = 0.0f, g = 0.5f;
void init_buffer();
void render();
void parse_chicken();
void control();
void update();
void bind_objects();
void unbind_objects();
void move_legs();

int main() {
	init_buffer();
	parse_chicken();
	bind_objects();
	while (1) {
		render();
		control();
		move_legs();
		update();
		Sleep(100);
	}
	return 0;
}

void move_legs() {
	int tx = 4, ty = 4;
	if (y_off == h - 6) {
		if (chicken[ty][tx] == '\\') chicken[ty][tx] = '>';
		else chicken[ty][tx] = '\\';
		if (chicken[ty][tx - 1] == '/') chicken[ty][tx - 1] = '|';
		else chicken[ty][tx - 1] = '/';
	}
}

void control() {
	if (y_off == h - 6) vy = 0.0f;
	if (_kbhit()) {
		char c = _getch();
		if (c == 'w') vy = -1.0f;
	}
}

void update() {
	unbind_objects();
	if (y_off == h - 9) vy = 1.0f;
	y_off += vy;
	cout << "\ny_off: " << y_off << " vy: " << vy;
	bind_objects();
}

void bind_objects() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			int tx = j + (int)x_off, ty = i + (int)y_off;
			if (tx > -1 && tx<w && ty>-1 && ty < h) {
				buffer[ty][tx] = chicken[i][j];
			}
		}
	}
}

void unbind_objects() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			int tx = j + (int)x_off, ty = i + (int)y_off;
			if (tx > -1 && tx<w && ty>-1 && ty < h) {
				buffer[ty][tx] = ' ';
			}
		}
	}
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
			if (chicken_body[index] == '.') chicken[i][j] = ' ';
			else chicken[i][j] = chicken_body[index];
		}
	}
}