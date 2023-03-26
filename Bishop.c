#include <stdio.h>
#include <string.h>
#include "Bishop.h"
#include "new.h"
#include "piece.h"
#include "Desk.h"

static void* Bishop_ctor(void* _self, Desk* desk, va_list* app) {
	struct Bishop* self = ((const struct Class*)Piece)->ctor(_self, desk, app);
	if (self == NULL)
		return NULL;
	strcpy_s(name(self), sizeof(name(self)), "Bishop");
	desk->cells[x(self)][y(self)].ch = 'B';
	return (void*)self;
}

//static void* Bishop_dtor(void* _self) {(void)self;  return NULL; }

static void Bishop_attack(const void* _self, Desk* desk) {
	if (!_self || !desk) return;
	const struct Bishop* self = _self;
	printf("%s at %d, %d attacks:\n", name(self), x(self), y(self));
	attack_diagonal_cross(self, desk);
}

static const struct Class _Bishop = {
	sizeof(struct Bishop),
	Bishop_ctor,
	NULL,//Bishop_dtor,
	Bishop_attack
};

const void* Bishop = &_Bishop;