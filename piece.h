#pragma once

#define x(p) (((struct Piece*)(p))->x)
#define y(p) (((struct Piece*)(p))->y)
#define name(p) (((struct Piece*)(p))->name)

#include "Desk.h"

struct Piece {
	const void* class;
	int x, y;
	char name[7];
};

//void* attack(void* _self, const void* field); //виртуальная

extern const void* Piece;
void attack_diagonal_cross(const void* _self, Desk* desk);
void attack_vertical_cross(const void* _self, Desk* desk);