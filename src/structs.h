/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

typedef struct Texture Texture;
typedef struct Entity Entity;

typedef struct {
	void (*logic)(void);
	void (*draw)(void);
} Delegate;

struct Texture {
	char name[MAX_NAME_LENGTH];
	SDL_Texture *texture;
	Texture *next;
};

typedef struct {
	SDL_Renderer *renderer;
	SDL_Window *window;
	Delegate delegate;
	int keyboard[MAX_KEYBOARD_KEYS];
	Texture textureHead, *textureTail;
} App;

struct Entity {
	float x;
	float y;
	int w;
	int h;
	float ex;
	float ey;
	float sx;
	float sy;
	float dx;
	float dy;
	int health;
	int isOnGround;
	float value;
	SDL_Texture *texture;
	void (*tick)(void);
	void (*touch)(Entity *other);
	long flags;
	Entity *riding;
	Entity *next;
};

typedef struct {
	SDL_Point camera;
	int map[MAP_WIDTH][MAP_HEIGHT];
	Entity entityHead, *entityTail;
	int pizzaTotal, pizzaFound;
} Stage;
