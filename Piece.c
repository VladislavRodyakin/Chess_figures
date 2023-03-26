#include <stdlib.h>// Äëÿ free
#include <stdio.h>
#include <string.h>
#include "new.h"
#include "piece.h"
#include "Desk.h"

static void* Piece_ctor(void* _self, Desk* desk, va_list* app) {
	struct Piece* self = _self;
	x(self) = va_arg(*app, int);
	y(self) = va_arg(*app, int);
	if (self->x < 0 || self->x >= 8 || self->y < 0 || self->y >= 8){
		free(self);
		return NULL;
	}
	memset(self->name, 0, sizeof(self->name));
	desk->cells[x(self)][y(self)].figure = self;
	return (void*)self;
}

static const struct Class _Piece = {
	sizeof(struct Piece),
	Piece_ctor,
	NULL,//King_dtor,
	NULL
};

const void* Piece = &_Piece;

void attack_diagonal_cross(const void* _self, Desk* desk) {
	const struct Piece* self = _self;
	for (int i = 1; x(self) - i >= 0 && y(self) - i >= 0; i++) {
		if (desk->cells[x(self) - i][y(self) - i].figure != NULL) {
			printf("          %s at %d, %d\n", name(desk->cells[x(self) - i][y(self) - i].figure),
				x(self) - i, y(self) - i);
			break;
		}
	}
	for (int i = 1; x(self) + i < 8 && y(self) - i >= 0; i++) {
		if (desk->cells[x(self) + i][y(self) - i].figure != NULL) {
			printf("      %s at %d, %d\n", name(desk->cells[x(self) + i][y(self) - i].figure), 
				x(self) + i, y(self) - i);
			break;
		}
	}
	for (int i = 1; x(self) - i >= 0 && y(self) + i < 8; i++) {
		if (desk->cells[x(self) - i][y(self) + i].figure != NULL) {
			printf("      %s at %d, %d\n", name(desk->cells[x(self) - i][y(self) + i].figure), 
				x(self) - i, y(self) + i);
			break;
		}
	}
	for (int i = 1; x(self) + i < 8 && y(self) + i < 8; i++) {
		if (desk->cells[x(self) + i][y(self) + i].figure != NULL) {
			printf("      %s at %d, %d\n", name(desk->cells[x(self) + i][y(self) + i].figure), 
				x(self) + i, y(self) + i);
			break;
		}
	}
}

void attack_vertical_cross(const void* _self, Desk* desk) {
	const struct Piece* self = _self;
	for (int i = 1; x(self) - i >= 0; i++) {
		if (desk->cells[x(self) - i][y(self)].figure != NULL) {
			printf("      %s at %d, %d\n", name(desk->cells[x(self) - i][y(self)].figure),
				x(self) - i, y(self));
			break;
		}
	}
	for (int i = 1; x(self) + i < 8; i++) {
		if (desk->cells[x(self) + i][y(self)].figure != NULL) {
			printf("      %s at %d, %d\n", name(desk->cells[x(self) + i][y(self)].figure),
				x(self) + i, y(self));
			break;
		}
	}
	for (int i = 1; y(self) - i >= 0; i++) {
		if (desk->cells[x(self)][y(self) - i].figure != NULL) {
			printf("      %s at %d, %d\n", name(desk->cells[x(self)][y(self) - i].figure),
				x(self), y(self) - i);
			break;
		}
	}
	for (int i = 1; y(self) + i < 8; i++) {
		if (desk->cells[x(self)][y(self) + i].figure != NULL) {
			printf("      %s at %d, %d\n", name(desk->cells[x(self)][y(self) + i].figure),
				x(self), y(self) + i);
			break;
		}
	}
}