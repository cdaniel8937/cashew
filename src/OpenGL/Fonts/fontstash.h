//
// Copyright (c) 2011 Andreas Krinke andreas.krinke@gmx.de
// Copyright (c) 2009 Mikko Mononen memon@inside.org
//
// This software is provided 'as-is', without any express or implied
// warranty.  In no event will the authors be held liable for any damages
// arising from the use of this software.
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.
//

#ifndef FONTSTASH_H
#define FONTSTASH_H

#define STH_ESUCCESS 0
// error opening file
#define STH_EFILEIO -1
// error initializing truetype font
#define STH_ETTFINIT -2
// invalid argument
#define STH_EINVAL -3
// not enough memory
#define STH_ENOMEM -4

#define HASH_LUT_SIZE 256
#define MAX_ROWS 128
#define VERT_COUNT (6*128)
#define VERT_STRIDE (sizeof(float)*4)

#define TTFONT_FILE 1
#define TTFONT_MEM  2
#define BMFONT      3

/* @rlyeh: removed STB_TRUETYPE_IMPLENTATION. We link it externally */
#include "stb_truetype.h"


struct sth_quad
{
    float x0,y0,s0,t0;
    float x1,y1,s1,t1;
};

struct sth_row
{
    short x,y,h;
};

struct sth_glyph
{
    unsigned int codepoint;
    short size;
    struct sth_texture* texture;
    int x0,y0,x1,y1;
    float xadv,xoff,yoff;
    int next;
};

struct sth_font
{
    int idx;
    int type;
    stbtt_fontinfo font;
    unsigned char* data;
    struct sth_glyph* glyphs;
    int lut[HASH_LUT_SIZE];
    int nglyphs;
    float ascender;
    float descender;
    float lineh;
    struct sth_font* next;
};

struct sth_texture
{
    GLuint id;
    // TODO: replace rows with pointer
    struct sth_row rows[MAX_ROWS];
    int nrows;
    float verts[4*VERT_COUNT];
    int nverts;
    struct sth_texture* next;
};

struct sth_stash
{
    int tw,th;
    float itw,ith;
    GLubyte *empty_data;
    struct sth_texture* tt_textures;
    struct sth_texture* bm_textures;
    struct sth_font* fonts;
    int drawing;
};


struct sth_stash* sth_create(int cachew, int cacheh);

int sth_add_font(struct sth_stash* stash, const char* path);
int sth_add_font_from_memory(struct sth_stash* stash, unsigned char* buffer);

int sth_add_bitmap_font(struct sth_stash* stash, int ascent, int descent, int line_gap);
int sth_add_glyph_for_codepoint(struct sth_stash* stash, int idx, GLuint id, unsigned int codepoint,
                                short size, short base, int x, int y, int w, int h,
                                float xoffset, float yoffset, float xadvance);
int sth_add_glyph_for_char(struct sth_stash* stash, int idx, GLuint id, const char* s,
                           short size, short base, int x, int y, int w, int h,
                           float xoffset, float yoffset, float xadvance);

void sth_begin_draw(struct sth_stash* stash);
void sth_end_draw(struct sth_stash* stash);

void sth_draw_text(struct sth_stash* stash,
				   int idx, float size,
				   float x, float y, const char* string, float* dx);

void sth_dim_text(struct sth_stash* stash, int idx, float size, const char* string,
				  float* minx, float* miny, float* maxx, float* maxy);

void sth_vmetrics(struct sth_stash* stash,
				  int idx, float size,
				  float* ascender, float* descender, float * lineh);

void sth_delete(struct sth_stash* stash);

#endif // FONTSTASH_H
