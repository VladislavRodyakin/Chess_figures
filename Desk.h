#pragma once
typedef struct Cell {
	void* figure;
	char ch;
} Cell;

typedef struct Desk {
	Cell cells[8][8];
} Desk;

