#include <stdio.h>
#include <string.h>
#include "Rook.h"
#include "new.h"
#include "piece.h"
#include "Desk.h"

static void* Rook_ctor(void* _self, Desk* desk, va_list* app) {
	struct Rook* self = ((const struct Class*)Piece)->ctor(_self, desk, app);
	if (self == NULL)
		return NULL;
	strcpy_s(name(self), sizeof(name(self)), "Rook");
	desk->cells[x(self)][y(self)].ch = 'R';
	return (void*)self;
}

//static void* Rook_dtor(void* _self) { (void)self; return NULL; }

static void Rook_attack(const void* _self, Desk* desk) {
	if (!_self || !desk) return;
	const struct Rook* self = _self;
	printf("%s at %d, %d attacks:\n", name(self), x(self), y(self));
	attack_vertical_cross(self, desk);
}

static const struct Class _Rook = {
	sizeof(struct Rook),
	Rook_ctor,
	NULL,//Rook_dtor,
	Rook_attack
};

const void* Rook = &_Rook;