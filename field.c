#include <stdio.h>
#include "new.h"
#include "field.h"

static void* Field_ctor(void*_self,va_list*app){
	struct Field* self = _self;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			self->field[i][j] = NULL;
		}
	}
	return self;
}

static void Field_draw(const void* _self) {
	const struct Field* self = _self;
	printf("##########");
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (self->field[i][j] == NULL)
				printf(" ");
			else
				self->field[i][j]->draw(self->field[i][j]);//field не класс
		}
	}
	printf("##########");
}

void check(void* _self) {
	const struct Field* self = _self;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			self->field[i][j]->attack(self->field[i][j]);
		}
	}
}

void* Field_dtor(void*_self){}

static const struct Class _Field = {
	sizeof(struct Field),
	Field_ctor,
	Field_dtor,
	Field_draw,
	NULL
};

const void* Field = &_Field;