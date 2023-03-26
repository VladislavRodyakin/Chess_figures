#include <stdio.h>
#include <string.h>
#include "King.h"
#include "new.h"
#include "piece.h"
#include "Desk.h"

static void* King_ctor(void* _self, Desk* desk, va_list* app) {
	struct King* self = ((const struct Class*)Piece)->ctor(_self, desk, app);
	if (self == NULL)
		return NULL;
	strcpy_s(name(self), sizeof(name(self)), "King");
	desk->cells[x(self)][y(self)].ch = 'K';
	return (void*)self;
}

//static void* King_dtor(void* _self) { (void)self; return NULL; }

static void King_attack(const void* _self, Desk* desk) {
	if (!_self || !desk) return;
	const struct King* self = _self;
	printf("%s at %d, %d attacks:\n", name(self), x(self), y(self));
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (x(self) + i < 0 || x(self) + i > 7 || y(self) + j < 0 || y(self) + j > 7 || (i == 0 && j == 0))
				continue;
			if (desk->cells[x(self) + i][y(self) + j].figure != NULL) {
				printf("      %s at %d, %d\n", name(desk->cells[x(self) + i][y(self) + j].figure),
					x(self) + i, y(self) + j);
			}
		}
	}
}

static const struct Class _King = {
	sizeof(struct King),
	King_ctor,
	NULL,//King_dtor,
	King_attack
};

const void* King = &_King;