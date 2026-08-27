// cl: /DNDEBUG
/*
**	Command & Conquer Generals(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Debug_Statistics counters from WW3D2/statistics.cpp, verbatim from the Zero
// Hour reference. Only the accumulators this function touches are declared: the
// real statistics.h drags in dx8wrapper.h and the DirectX 8 SDK headers, which
// the fleet toolchains do not have, and the counters are file-static either way
// so their addresses are relocated from retail, not from this TU.

namespace Debug_Statistics
{
	void Begin_Statistics();
	void Record_Sorting_Polys_And_Vertices(int pcount, int vcount);
	class ShaderClass;
	void Record_DX8_Polys_And_Vertices(int pcount, int vcount, const ShaderClass &shader);
	extern int dx8_polygons;
	extern int dx8_vertices;
	extern int dx8_renders;
}

void Record_Texture_Begin();

class DX8Wrapper
{
	public:
	static void Begin_Statistics();
};

static int sorting_polygons;
static int sorting_vertices;
static int draw_calls;

void Debug_Statistics::Begin_Statistics()
{
	*reinterpret_cast<int *>(0x01346e64) = 0;
	*reinterpret_cast<int *>(0x01346df0) = 0;
	*reinterpret_cast<int *>(0x01346e0c) = 0;
	*reinterpret_cast<int *>(0x01346e14) = 0;
	*reinterpret_cast<int *>(0x01346e18) = 0;
	*reinterpret_cast<int *>(0x01346e60) = 0;
	*reinterpret_cast<int *>(0x01346e58) = 0;
	*reinterpret_cast<int *>(0x01346e6c) = 0;
	*reinterpret_cast<int *>(0x01346e68) = 0;
	::Record_Texture_Begin();
	DX8Wrapper::Begin_Statistics();
}

void Debug_Statistics::Record_Sorting_Polys_And_Vertices(int pcount,int vcount)
{
	sorting_polygons+=pcount;
	sorting_vertices+=vcount;
	draw_calls++;
}

class Debug_Statistics::ShaderClass
{
public:
	unsigned bits;
};

// Retail BFME stores these counters and N-patch state in engine globals.
// ?Debug_Statistics::Record_DX8_Polys_And_Vertices present-unmatched
void Debug_Statistics::Record_DX8_Polys_And_Vertices(int pcount, int vcount, const ShaderClass &shader)
{
	if ((shader.bits & 0x20000) != 0
		&& *reinterpret_cast<bool *>(*reinterpret_cast<unsigned char **>(0x01340578) + 0x13b)) {
		unsigned level = *reinterpret_cast<unsigned *>(0x012d6d8c);
		level *= level;
		pcount *= level;
	}
	dx8_polygons += pcount;
	dx8_vertices += vcount;
	dx8_renders++;
}
