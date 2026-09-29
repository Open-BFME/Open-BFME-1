// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
/*
** Copyright 2025 Electronic Arts Inc.
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
** You should have received a copy of the GNU General Public License
** along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
// BFME vertex reader: RVA 0x00927360, complete 350 bytes.
// MeshGeometryClass::read_chunks dispatches vertex chunks 0x02 and 0xC00 here,
// passing the buffer selector and testing the Boolean result in AL. The
// GeneralsMD read_vertices loop survives; BFME additionally builds a
// ShareBuffer<Vector3> for the alternate format and de-interleaves the SKIN
// data into three float arrays. VertexCount is +0x28, Flags is +0x18, the
// alternate ShareBuffer<Vector3> is +0x34 and the ShareBuffer<float> whose
// array receives the de-interleave is +0x38. SKIN is the original 0x400 flag.
//
// Two source details are load-bearing for the byte match and are not
// cosmetic. The two skin pointers must be independent `skin_x + n` /
// `skin_x + 2n` leas from the array base, not `skin_x + n` followed by
// `skin_y + n`: the dependent spelling folds the second lea onto the first
// pointer and picks the wrong register pair. And the Z pointer must read
// Get_Vertex_Count() again rather than reuse the cached `vertex_count` local;
// that member reload is what keeps the two leas independent instead of
// letting MSVC reassociate `2 * n` back through the local, which shrinks the
// loop by two bytes and breaks every later branch displacement.
// Both RET 8 paths are included; the final RET at +0x15B ends before INT3
// padding. No literal or global relocation is required.
#include "always.h"
#include "chunkio.h"
#include "sharebuf.h"
#include "vector3.h"
#include "w3d_file.h"
#include <string.h>

class MeshGeometryClass
{
	protected:
	char _prefix[0x18];
	enum { SKIN = 0x400 };
	int Flags;
	char _between_flags_and_count[0x0c];
	int VertexCount;
	char _between_vertex_count_and_vertex[4];
	ShareBufferClass<Vector3> *Vertex;
	ShareBufferClass<Vector3> *Slot34;
	ShareBufferClass<float> *Slot38;

	int Get_Vertex_Count(void) const { return VertexCount; }
	bool read_vertices(ChunkLoadClass &cload, bool alternate_format);
};

// ?read_vertices@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@_N@Z
bool MeshGeometryClass::read_vertices(ChunkLoadClass &cload, bool alternate_format)
{
	W3dVectorStruct vert;
	Vector3 *loc;

	if (alternate_format) {
		if (Slot34 == NULL) {
			Slot34 = NEW_REF(ShareBufferClass<Vector3>,
				(VertexCount, "MeshGeometryClass::Vertex", 0));
			int buffer_count = Slot34->Get_Count();
			Vector3 *buffer_array = Slot34->Get_Array();
			memset(buffer_array, 0, buffer_count * sizeof(Vector3));
		}
		loc = Slot34->Get_Array();
	} else {
		loc = Vertex->Get_Array();
	}

	for (int i = 0; i < VertexCount; i++) {
		if (cload.Read(&vert, sizeof(W3dVectorStruct)) != sizeof(W3dVectorStruct)) {
			return false;
		}
		loc[i].X = vert.X;
		loc[i].Y = vert.Y;
		loc[i].Z = vert.Z;
	}

	if ((Flags & SKIN) && Slot38 != NULL) {
		int vertex_count = Get_Vertex_Count();
		float *skin_x = Slot38->Get_Array();
		int i = 0;
		if (vertex_count > 0) {
			float *source_z = &loc[0].Z;
			float *skin_z = skin_x + Get_Vertex_Count() * 2;
			float *skin_y = skin_x + vertex_count;
			do {
				skin_x[i] = source_z[-2];
				*skin_y = source_z[-1];
				*skin_z = *source_z;
				++i;
				++skin_y;
				++skin_z;
				source_z += 3;
			} while (i < Get_Vertex_Count());
		}
	}

	return true;
}
