#include <stdio.h>
#include <string.h>
#include "Queen.h"
#include "new.h"
#include "piece.h"
#include "Desk.h"

static void* Queen_ctor(void* _self, Desk* desk, va_list* app) {
	struct Queen* self = ((const struct Class*)Piece)->ctor(_self, desk, app);
	if (self == NULL)
		return NULL;
	strcpy_s(name(self), sizeof(name(self)), "Queen");
	desk->cells[x(self)][y(self)].ch = 'Q';
	return (void*)self;
}

//static void* Queen_dtor(void* _self) { (void)self; return NULL; }

static void Queen_attack(const void* _self, Desk* desk) {
	if (!_self || !desk) return;
	const struct Queen* self = _self;
	printf("%s at %d, %d attacks:\n", name(self), x(self), y(self));
	attack_diagonal_cross(self, desk);
	attack_vertical_cross(self, desk);
}

static const struct Class _Queen = {
	sizeof(struct Queen),
	Queen_ctor,
	NULL,//Queen_dtor,
	Queen_attack
};

const void* Queen = &_Queen;