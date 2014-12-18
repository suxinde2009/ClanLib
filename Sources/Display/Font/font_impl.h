/*
**  ClanLib SDK
**  Copyright (c) 1997-2015 The ClanLib Team
**
**  This software is provided 'as-is', without any express or implied
**  warranty.  In no event will the authors be held liable for any damages
**  arising from the use of this software.
**
**  Permission is granted to anyone to use this software for any purpose,
**  including commercial applications, and to alter it and redistribute it
**  freely, subject to the following restrictions:
**
**  1. The origin of this software must not be misrepresented; you must not
**     claim that you wrote the original software. If you use this software
**     in a product, an acknowledgment in the product documentation would be
**     appreciated but is not required.
**  2. Altered source versions must be plainly marked as such, and must not be
**     misrepresented as being the original software.
**  3. This notice may not be removed or altered from any source distribution.
**
**  Note: Some of the libraries ClanLib may link to may have additional
**  requirements or restrictions.
**
**  File Author(s):
**
**    Harry Storbacka
**    Magnus Norddahl
**    Mark Page
*/

#pragma once

#include "API/Display/Font/font_metrics.h"
#include "API/Display/Font/glyph_metrics.h"
#include "API/Display/Font/font.h"
#include "API/Display/Font/font_face.h"
#include "API/Display/Render/texture_2d.h"
#include <list>
#include <map>
#include "glyph_cache.h"
#include "font_face_impl.h"

namespace clan
{

class FontEngine;

class Font_Impl
{
public:
	Font_Impl();
	~Font_Impl();

	const FontMetrics &get_font_metrics();

	void set_font_face(FontFace &new_font_face);

	int get_character_index(Canvas &canvas, const std::string &text, const Point &point);

	GlyphMetrics get_metrics(Canvas &canvas, unsigned int glyph);

	GlyphMetrics measure_text(Canvas &canvas, const std::string &string);

	void draw_text(Canvas &canvas, const Pointf &position, const std::string &text, const Colorf &color);

	void get_glyph_path(unsigned int glyph_index, Path &out_path, GlyphMetrics &out_metrics);

	static Font load(Canvas &canvas, const FontDescription &reference_desc, const std::string &id, const XMLResourceDocument &doc, std::function<Resource<Sprite>(Canvas &, const std::string &)> cb_get_sprite);

	void set_typeface_name(const std::string &name);
	void set_height(float value);
	void set_weight(FontWeight value);
	void set_line_height(float height);
	void set_style(FontStyle setting);

private:
	void select_font_face();

	Font_Selected selected_description;
	float selected_line_height = 0.0f;
	float scaled_height = 1.0f;	// Currently not implemented
	FontMetrics selected_metrics;

	GlyphCache *glyph_cache = nullptr;
	FontEngine *font_engine = nullptr;	// If null, use select_font_face() to update
	FontFace font_face;
};

}
