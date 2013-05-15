/*
**  ClanLib SDK
**  Copyright (c) 1997-2013 The ClanLib Team
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
**    Mark Page
*/

#include "SWRender/precomp.h"
#include "API/Core/System/mutex.h"
#include "API/SWRender/setup_swrender.h"
#include "API/SWRender/swr_target.h"
#include "setup_swrender_impl.h"

namespace clan
{


/////////////////////////////////////////////////////////////////////////////
// SetupSWRender Construction:

Mutex SetupSWRender_Impl::cl_swrender_mutex;
int SetupSWRender_Impl::cl_swrender_refcount = 0;
SWRenderTarget *SetupSWRender_Impl::cl_swrender_target = 0;

SetupSWRender::SetupSWRender()
{
	const std::vector<std::string> args;
	SetupSWRender_Impl::init(args);
}

SetupSWRender::SetupSWRender(const std::vector<std::string> &args)
{
	SetupSWRender_Impl::init(args);
}

SetupSWRender::~SetupSWRender()
{
	SetupSWRender_Impl::deinit();
}

void SetupSWRender_Impl::init(const std::vector<std::string> &args)
{
	if (!System::detect_cpu_extension(System::sse2))
	{
		throw Exception("Sorry, clanSWRender requires a processor capable of SSE2 instructions. (Update your CPU)");
	}

	MutexSection mutex_lock(&cl_swrender_mutex);
	if (cl_swrender_refcount == 0)
		cl_swrender_target = new SWRenderTarget();
	cl_swrender_refcount++;
}

void SetupSWRender_Impl::deinit()
{
	MutexSection mutex_lock(&cl_swrender_mutex);
	cl_swrender_refcount--;
	if (cl_swrender_refcount == 0)
		delete cl_swrender_target;
}

}
