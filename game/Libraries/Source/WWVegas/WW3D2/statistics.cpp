// cl: /DNDEBUG
// readable body of ?Begin_Statistics@Debug_Statistics@@: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
// readable body of ?End_Statistics@Debug_Statistics@@: game/GameEngineDevice/Source/W3DDevice/GameClient/W3DDisplay.cpp
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

// Statistics snapshots use external linkage for the data ledger.
// Local declarations avoid the reference header's DirectX SDK dependencies.

int g_Va01346E48;

namespace Debug_Statistics
{
	void Begin_Statistics();
	void End_Statistics();
	void Record_Sorting_Polys_And_Vertices(int pcount, int vcount);
	class ShaderClass;
	void Record_DX8_Polys_And_Vertices(int pcount, int vcount, const ShaderClass &shader);
	extern int dx8_polygons;
	extern int dx8_vertices;
	int dx8_renders;
	extern int dx8_skin_polygons;
	extern int dx8_skin_vertices;
	extern int dx8_skin_renders;
	extern int last_frame_dx8_skin_polygons;
	int last_frame_dx8_skin_vertices;
	int last_frame_dx8_skin_renders;
	int last_frame_dx8_polygons;
	int last_frame_dx8_renders;
	int last_frame_dx8_vertices;
	int last_frame_sorting_polygons;
	int last_frame_sorting_vertices;
}

void Record_Texture_Begin();
void Record_Texture_End();

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class DX8Wrapper
{
	public:
	static void Begin_Statistics();
	static void End_Statistics();
};

extern int g_rva009371E0;
extern int g_bfmeBytesEA;
extern int g_bfmeBlocksEA;
extern unsigned char *BfmeCurrentCaps;
extern unsigned NPatchesLevel;

static int sorting_polygons;
static int sorting_vertices;
static int draw_calls;

void Debug_Statistics::Begin_Statistics()
{
	dx8_polygons = 0;
	dx8_vertices = 0;
	dx8_skin_polygons = 0;
	dx8_skin_vertices = 0;
	g_rva009371E0 = 0;
	dx8_skin_renders = 0;
	g_bfmeBytesEA = 0;
	g_bfmeBlocksEA = 0;
	dx8_renders = 0;
	::Record_Texture_Begin();
	DX8Wrapper::Begin_Statistics();
}

void Debug_Statistics::End_Statistics()
{
	static int end_rva01346E18;
	static int end_dx8_polygons;
	static int end_dx8_vertices;
	static int end_sorting_polygons;
	static int end_sorting_vertices;

	::Record_Texture_End();
	last_frame_dx8_skin_polygons = dx8_skin_polygons;
	last_frame_dx8_skin_vertices = dx8_skin_vertices;
	last_frame_dx8_skin_renders = dx8_skin_renders;
	g_Va01346E48 = end_rva01346E18;
	last_frame_dx8_polygons = end_dx8_polygons;
	last_frame_dx8_vertices = end_dx8_vertices;
	last_frame_sorting_polygons = end_sorting_polygons;
	last_frame_sorting_vertices = end_sorting_vertices;
	last_frame_dx8_renders = dx8_renders;
	DX8Wrapper::End_Statistics();
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
		&& BfmeCurrentCaps[0x13b]) {
		unsigned level = NPatchesLevel;
		level *= level;
		pcount *= level;
	}
	dx8_polygons += pcount;
	dx8_vertices += vcount;
	dx8_renders++;
}
