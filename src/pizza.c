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

static void tick(void);
static void touch(Entity *other);

void initPizza(char *line)
{
	Entity *e;

	e = malloc(sizeof(Entity));
	memset(e, 0, sizeof(Entity));
	stage.entityTail->next = e;
	stage.entityTail = e;

	sscanf(line, "%*s %f %f", &e->x, &e->y);

	e->health = 1;

	e->texture = loadTexture("gfx/pizza.png");
	SDL_QueryTexture(e->texture, NULL, NULL, &e->w, &e->h);
	e->flags = EF_WEIGHTLESS;
	e->tick = tick;
	e->touch = touch;

	stage.pizzaTotal++;
}

static void tick(void)
{
	self->value += 0.1;

	self->y += sin(self->value);
}

static void touch(Entity *other)
{
	if (self->health > 0 && other == player)
	{
		self->health = 0;

		stage.pizzaFound++;

		if (stage.pizzaFound == stage.pizzaTotal)
		{
			playSound(SND_PIZZA_DONE, CH_PIZZA);
			exit(1);
		}
		else
		{
			playSound(SND_PIZZA, CH_PIZZA);
		}
	}
}
