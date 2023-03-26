#include <stdio.h>
#include <string.h>
#include "Knight.h"
#include "new.h"
#include "piece.h"
#include "Desk.h"

static void* Knight_ctor(void* _self, Desk* desk, va_list* app) {
	struct Knight* self = ((const struct Class*)Piece)->ctor(_self, desk, app);
	if (self == NULL)
		return NULL;
	strcpy_s(name(self), sizeof(name(self)), "Knight");
	desk->cells[x(self)][y(self)].ch = 'k';
	return (void*)self;
}

//static void* Knight_dtor(void* _self) { (void)self; return NULL; }

static void Knight_attack(const void* _self, Desk* desk) {
	if (!_self || !desk) return;
	const struct Knight* self = _self;
	printf("%s at %d, %d attacks:\n", name(self), x(self), y(self));
	int X[8] = { 2, 2, 1, 1,-1,-1,-2,-2 };
	int Y[8] = { 1,-1, 2,-2, 2,-2, 1,-1 };
	for (int i = 0; i < 8; i++) {
		if (x(self) + X[i] < 0 || x(self) + X[i] > 7 || y(self) + Y[i] < 0 || y(self) + Y[i] > 7)
			continue;
		if (desk->cells[x(self) + X[i]][y(self) + Y[i]].figure != NULL)
			printf("      %s at %d, %d\n", name(desk->cells[x(self) + X[i]][y(self) + Y[i]].figure),
				x(self) + X[i], y(self) + Y[i]);
	}
}

static const struct Class _Knight = {
	sizeof(struct Knight),
	Knight_ctor,
	NULL,//Knight_dtor,
	Knight_attack
};

const void* Knight = &_Knight;