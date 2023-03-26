#pragma once
struct Field {
	const void* class;
	void* field[8][8];
};

void check(void* _self);

extern const void* Field;