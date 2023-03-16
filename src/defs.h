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

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define STRNCPY(dest, src, n) strncpy(dest, src, n); dest[n - 1] = '\0'

#define PLATFORM_SPEED 4
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  720

#define MAX_TILES    7

#define TILE_SIZE    64

#define MAP_WIDTH    40
#define MAP_HEIGHT   20

#define MAP_RENDER_WIDTH    20
#define MAP_RENDER_HEIGHT   12

#define PLAYER_MOVE_SPEED 6

#define MAX_NAME_LENGTH        32
#define MAX_LINE_LENGTH        1024
#define MAX_FILENAME_LENGTH    1024

#define MAX_KEYBOARD_KEYS 350

#define MAX_SND_CHANNELS 16

#define EF_NONE       0
#define EF_WEIGHTLESS (2 << 0)
#define EF_SOLID      (2 << 1)
#define EF_PUSH       (2 << 2)

#define GLYPH_WIDTH  18
#define GLYPH_HEIGHT 29

enum
{
	TEXT_LEFT,
	TEXT_CENTER,
	TEXT_RIGHT
};

enum
{
	SND_JUMP,
	SND_PIZZA,
	SND_PIZZA_DONE,
	SND_MAX
};

enum
{
	CH_PLAYER,
	CH_PIZZA
};
