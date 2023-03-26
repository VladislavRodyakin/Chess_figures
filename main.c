#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "Desk.h"
#include "new.h"
#include "piece.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include <crtdbg.h>
#define FILE_PATH "test.txt"
//"D:\\!Прога\\4 сем\\прога\\Chess_figures\\test.txt"

void* CreateFigure(const char* line, Desk* desk) {
	char input_name[64] = { 0 };
	int x = 0;
	int y = 0;
	int dump = 0;
	int cnt = sscanf_s(line, "%s %d %d %d", input_name, 64, &x, &y, &dump);
	if (cnt != 3 || x < 0 || x > 7 || y < 0 || y > 7)
		return NULL;
	if (strcmp(input_name, "king") == 0)
		return new(King, desk, x, y);
	else if (strcmp(input_name, "queen") == 0)
		return new(Queen, desk, x, y);
	else if (strcmp(input_name, "rook") == 0)
		return new(Rook, desk, x, y);
	else if (strcmp(input_name, "bishop") == 0)
		return new(Bishop, desk, x, y);
	else if (strcmp(input_name, "knight") == 0)
		return new(Knight, desk, x, y);
	return NULL;
}

void desk_fill(const char* file_path, Desk* desk) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			desk->cells[i][j].figure = NULL;
			desk->cells[i][j].ch = ' ';
		}
	}
	_Post_ _Notnull_ FILE* input_file;
	errno_t err = fopen_s(&input_file, file_path, "r");
	if (err != 0) {
		printf("failed to open file: %s\n", file_path);
		return;
	}
	char input_line[128] = { 0 };
	void* catch_err = (void*)1;
	while (fgets(input_line, 128, input_file)) {
		catch_err = CreateFigure(input_line, desk);
		if (catch_err == NULL) {
			printf("invalid line: %s\n", input_line);
			catch_err = (void*)1;
		}
	}
	fclose(input_file);
}

void draw_desk(Desk* desk) {
	printf("##########\n");
	for (int i = 0; i < 8; i++) {
		printf("%c", '#');
		for (int j = 0; j < 8; j++)
			printf("%c", (desk->cells[i][j].ch));
		printf("%s", "#\n");
	}
	printf("##########\n");
}

void check(Desk* desk) {
	for (int x = 0; x < 8; x++) {
		for (int y = 0; y < 8; y++) {
			if (desk->cells[x][y].figure) // desk[x][y]!==NULL
				attack(desk->cells[x][y].figure, desk);
		}
	}
}

void destroy_all(Desk* desk) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete(desk->cells[i][j].figure);
		}
	}
}

int main() {
	{
		Desk desk;
		desk_fill(FILE_PATH, &desk);
		draw_desk(&desk);
		check(&desk);
		destroy_all(&desk);
	}
	_CrtDumpMemoryLeaks();
	return 0;
}

