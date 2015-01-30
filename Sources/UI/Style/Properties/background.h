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
**    Magnus Norddahl
*/

#pragma once

#include "API/UI/Style/style_property_parser.h"

namespace clan
{
	class BackgroundPropertyParser : public StylePropertyParser
	{
	public:
		BackgroundPropertyParser() : StylePropertyParser({ "background" }) { }
		void parse(StylePropertySetter *setter, const std::string &name, const std::string &value, const std::initializer_list<StylePropertyInitializerValue> &args) override;
	};

	class BackgroundAttachmentPropertyParser : public StylePropertyParser
	{
	public:
		BackgroundAttachmentPropertyParser() : StylePropertyParser({ "background-attachment" }) { }
		void parse(StylePropertySetter *setter, const std::string &name, const std::string &value, const std::initializer_list<StylePropertyInitializerValue> &args) override;
	};

	class BackgroundClipPropertyParser : public StylePropertyParser
	{
	public:
		BackgroundClipPropertyParser() : StylePropertyParser({ "background-clip" }) { }
		void parse(StylePropertySetter *setter, const std::string &name, const std::string &value, const std::initializer_list<StylePropertyInitializerValue> &args) override;
	};

	class BackgroundColorPropertyParser : public StylePropertyParser
	{
	public:
		BackgroundColorPropertyParser() : StylePropertyParser({ "background-color" }) { }
		void parse(StylePropertySetter *setter, const std::string &name, const std::string &value, const std::initializer_list<StylePropertyInitializerValue> &args) override;
	};

	class BackgroundImagePropertyParser : public StylePropertyParser
	{
	public:
		BackgroundImagePropertyParser() : StylePropertyParser({ "background-image" }) { }
		void parse(StylePropertySetter *setter, const std::string &name, const std::string &value, const std::initializer_list<StylePropertyInitializerValue> &args) override;
	};

	class BackgroundOriginPropertyParser : public StylePropertyParser
	{
	public:
		BackgroundOriginPropertyParser() : StylePropertyParser({ "background-origin" }) { }
		void parse(StylePropertySetter *setter, const std::string &name, const std::string &value, const std::initializer_list<StylePropertyInitializerValue> &args) override;
	};

	class BackgroundPositionPropertyParser : public StylePropertyParser
	{
	public:
		BackgroundPositionPropertyParser() : StylePropertyParser({ "background-position" }) { }
		void parse(StylePropertySetter *setter, const std::string &name, const std::string &value, const std::initializer_list<StylePropertyInitializerValue> &args) override;
	};

	class BackgroundRepeatPropertyParser : public StylePropertyParser
	{
	public:
		BackgroundRepeatPropertyParser() : StylePropertyParser({ "background-repeat" }) { }
		void parse(StylePropertySetter *setter, const std::string &name, const std::string &value, const std::initializer_list<StylePropertyInitializerValue> &args) override;
	};

	class BackgroundSizePropertyParser : public StylePropertyParser
	{
	public:
		BackgroundSizePropertyParser() : StylePropertyParser({ "background-size" }) { }
		void parse(StylePropertySetter *setter, const std::string &name, const std::string &value, const std::initializer_list<StylePropertyInitializerValue> &args) override;
	};
}