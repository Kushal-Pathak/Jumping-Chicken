#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cmath>
#define block (char)254
#define cloud 'c'
#define h 15
#define w 35
#define chicken_height 5
#define chicken_width 6
using namespace std;

string chicken_body = "...\\\\....(o>\\\\_//).\\_/_).../\\.";
char buffer[h][w], play='y';
char chicken[chicken_height][chicken_width];

float x_off = 10.0f, y_off = h - 6, vy = 0.0f;
int step = 0, game_over = 0, score = 0;

void init_buffer();
void render();
void parse_chicken();
void control();
void update();
void bind_objects();
void unbind_objects();
void move_legs();
void generate_obstacle();
void shift_objects();
void count_score();
void detect_collision();
void game_over_message();
void reset_game();

int main() {
	srand((unsigned int)time(0));
	while (play == 'y') {
		reset_game();
		while (!game_over) {
			render();
			control();
			move_legs();
			detect_collision();
			update();
			Sleep(50);
		}
		game_over_message();
	}
	return 0;
}

void detect_collision() {
	int ty, tx;
	for (int i = 0; i < chicken_height; i++) {
		for (int j = 0; j < chicken_width; j++) {
			tx = (int)x_off + j; ty = (int)y_off + i;
			if (buffer[ty][tx] == block) {
				game_over = 1;
				Beep(300, 1000);
			}
		}
	}
}

void count_score() {
	if (buffer[h - 2][8] == block) {
		score++;
		Beep(500, 70);
	}
}

void generate_obstacle() {
	if (step % 35 == 0) {
		int size = 1 + rand() % 3;
		for (int i = 1; i <= size; i++) {
			buffer[h - 1 - i][w-1] = block;
		}
	}
}
void shift_objects() {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w - 2; j++) {
			if (buffer[i][j + 2] == block) {
				buffer[i][j + 2] = ' ';
				buffer[i][j] = block;
			}
			if (buffer[i][0] == block) buffer[i][0] = ' ';
		}
	}
}

void move_legs() {
	int tx = 4, ty = 4;
	// legs move only when in the ground
	if (y_off == h - 6) {
		if (chicken[ty][tx] == '\\') chicken[ty][tx] = '>';
		else chicken[ty][tx] = '\\';
		if (chicken[ty][tx - 1] == '/') chicken[ty][tx - 1] = '|';
		else chicken[ty][tx - 1] = '/';
	}
	else {
		chicken[ty][tx] = '>';
		chicken[ty][tx - 1] = '|';
	}
}

void control() {
	if (y_off == h - 6) vy = 0.0f;
	if (_kbhit()) {
		char c = _getch();
		if (c == 'w') vy = -1.0f;
	}
	if (y_off == h - 11) vy = 1.0f;
}

void update() {
	step++;
	count_score();
	unbind_objects();
	y_off += vy;
	bind_objects();
	shift_objects();
	generate_obstacle();
}

void bind_objects() {
	for (int i = 0; i < chicken_height; i++) {
		for (int j = 0; j < chicken_width; j++) {
			int tx = j + (int)x_off, ty = i + (int)y_off;
			if (tx > -1 && tx < w && ty > -1 && ty < h) {
				buffer[ty][tx] = chicken[i][j];
			}
		}
	}
}

void unbind_objects() {
	for (int i = 0; i < chicken_height; i++) {
		for (int j = 0; j < chicken_width; j++) {
			int tx = j + (int)x_off, ty = i + (int)y_off;
			if (tx > -1 && tx < w && ty > -1 && ty < h) {
				//if (buffer[ty][tx] == block) game_over = 1;
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
	cout << "\t\t\t\tScore: " << score << endl;
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
	for (int i = 0; i < chicken_height; i++) {
		for (int j = 0; j < chicken_width; j++) {
			index = j + 6 * i;
			if (chicken_body[index] == '.') chicken[i][j] = ' ';
			else chicken[i][j] = chicken_body[index];
		}
	}
}
void game_over_message() {
	play = 'n';
	cout << "Game Over!" << endl << "Play again (y): ";
	cin >> play;
}

void reset_game() {
	game_over = 0;
	score = 0;
	step = 0;
	play = 'y';
	y_off = h - 6;
	vy = 0;
	init_buffer();
	parse_chicken();
	bind_objects();
}