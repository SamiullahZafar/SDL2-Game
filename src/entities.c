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

#include "common.h"

static void move(Entity *e);
static void push(Entity *e, float dx, float dy);
static void moveToWorld(Entity *e, float dx, float dy);
static void moveToEntities(Entity *e, float dx, float dy);
static void loadEnts(const char *filename);
static void addEntFromLine(char *line);

void initEntities(void)
{
	loadEnts("data/ents01.dat");
}

void doEntities(void)
{
	Entity *e, *prev;

	prev = &stage.entityHead;

	for (e = stage.entityHead.next ; e != NULL ; e = e->next)
	{
		self = e;

		if (e->tick)
		{
			e->tick();
		}

		move(e);

		if (e->health <= 0)
		{
			if (e == stage.entityTail)
			{
				stage.entityTail = prev;
			}

			prev->next = e->next;
			free(e);
			e = prev;
		}

		prev = e;
	}

	for (e = stage.entityHead.next ; e != NULL ; e = e->next)
	{
		if (e->riding != NULL)
		{
			e->x += e->riding->dx;

			push(e, e->riding->dx, 0);
		}

		e->x = MIN(MAX(e->x, 0), MAP_WIDTH * TILE_SIZE);
		e->y = MIN(MAX(e->y, 0), MAP_HEIGHT * TILE_SIZE);
	}
}

static void move(Entity *e)
{
	if (!(e->flags & EF_WEIGHTLESS))
	{
		e->dy += 1.5;
		e->dy = MAX(MIN(e->dy, 18), -999);
	}

	if (e->riding != NULL && e->riding->dy > 0)
	{
		e->dy = e->riding->dy + 1;
	}

	e->riding = NULL;

	e->isOnGround = 0;

	e->x += e->dx;
	push(e, e->dx, 0);

	e->y += e->dy;
	push(e, 0, e->dy);
}

static void push(Entity *e, float dx, float dy)
{
	moveToWorld(e, dx, dy);

	moveToEntities(e, dx, dy);
}

static void moveToWorld(Entity *e, float dx, float dy)
{
	int mx, my, hit, adj;

	if (dx != 0)
	{
		mx = dx > 0 ? (e->x + e->w) : e->x;
		mx /= TILE_SIZE;

		my = (e->y / TILE_SIZE);

		hit = 0;

		if (!isInsideMap(mx, my) || stage.map[mx][my] != 0)
		{
			hit = 1;
		}

		my = (e->y + e->h - 1) / TILE_SIZE;

		if (!isInsideMap(mx, my) || stage.map[mx][my] != 0)
		{
			hit = 1;
		}

		if (hit)
		{
			adj = dx > 0 ? -e->w : TILE_SIZE;

			e->x = (mx * TILE_SIZE) + adj;

			e->dx = 0;
		}
	}

	if (dy != 0)
	{
		my = dy > 0 ? (e->y + e->h) : e->y;
		my /= TILE_SIZE;

		mx = e->x / TILE_SIZE;

		hit = 0;

		if (!isInsideMap(mx, my) || stage.map[mx][my] != 0)
		{
			hit = 1;
		}

		mx = (e->x + e->w - 1) / TILE_SIZE;

		if (!isInsideMap(mx, my) || stage.map[mx][my] != 0)
		{
			hit = 1;
		}

		if (hit)
		{
			adj = dy > 0 ? -e->h : TILE_SIZE;

			e->y = (my * TILE_SIZE) + adj;

			e->dy = 0;

			e->isOnGround = dy > 0;
		}
	}
}

static void moveToEntities(Entity *e, float dx, float dy)
{
	Entity *other;
	int adj;

	for (other = stage.entityHead.next ; other != NULL ; other = other->next)
	{
		if (other != e && collision(e->x, e->y, e->w, e->h, other->x, other->y, other->w, other->h))
		{
			if (other->flags & EF_SOLID)
			{
				if (dy != 0)
				{
					adj = dy > 0 ? -e->h : other->h;

					e->y = other->y + adj;

					e->dy = 0;

					if (dy > 0)
					{
						e->isOnGround = 1;

						e->riding = other;
					}
				}

				if (dx != 0)
				{
					adj = dx > 0 ? -e->w : other->w;

					e->x = other->x + adj;

					e->dx = 0;
				}
			}
			else if (e->flags & EF_PUSH)
			{
				other->x += e->dx;
				push(other, e->dx, 0);

				other->y += e->dy;
				push(other, 0, e->dy);
			}

			if (e->touch)
			{
				e->touch(other);
			}
		}
	}
}

void drawEntities(void)
{
	Entity *e;

	for (e = stage.entityHead.next ; e != NULL ; e = e->next)
	{
		blit(e->texture, e->x - stage.camera.x, e->y - stage.camera.y, 0);
	}
}

static void loadEnts(const char *filename)
{
	char line[MAX_LINE_LENGTH];
	char *data, *p;
	int n;

	data = readFile(filename);

	p = data;

	n = 0;

	memset(line, '\0', MAX_LINE_LENGTH);

	while (*p)
	{
		if (*p == '\n')
		{
			addEntFromLine(line);
			memset(line, '\0', MAX_LINE_LENGTH);
			n = 0;
		}
		else
		{
			line[n++] = *p;
		}

		p++;
	}

	free(data);
}

static void addEntFromLine(char *line)
{
	char name[MAX_NAME_LENGTH];

	sscanf(line, "%s", name);

	if (strcmp(name, "BLOCK") == 0)
	{
		initBlock(line);
	}
	else if (strcmp(name, "PLATFORM") == 0)
	{
		initPlatform(line);
	}
	else if (strcmp(name, "PIZZA") == 0)
	{
		initPizza(line);
	}
	else
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_WARN, "Unknown entity '%s'", line);
	}
}
