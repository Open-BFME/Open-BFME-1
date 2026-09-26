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
// BFME normal reader: RVA 0x009274C0, complete 203 bytes.
// MeshModelClass::read_chunks dispatches normal chunks 0x03 and 0xC01 here,
// passing the buffer selector and testing the Boolean result in AL. The
// GeneralsMD read_vertex_normals loop survives; BFME additionally refreshes
// the skinning normal buffer as separate X, Y and Z arrays. VertexCount is
// +0x28; those ShareBuffer<float> pointers are +0x48 and +0x4C. SKIN is the
// original 0x400 flag. get_vert_normals(bool) selects +0x40/+0x44 buffers.
// Both RET 8 paths are included; the final RET at +0xC8 ends before INT3
// padding at RVA 0x0092758B. No literal or global relocation is required.
#include "always.h"
#include "chunkio.h"
#include "sharebuf.h"
#include "vector3.h"
#include "w3d_file.h"

class MeshGeometryClass
{
	protected:
	char _prefix[0x18];
	enum { SKIN = 0x400 };
	int Flags;
	char _between_flags_and_count[0x0c];
	int VertexCount;
	char _between_count_and_buffers[0x1c];
	ShareBufferClass<float> *SkinNormalBuffers[2];

	bool read_vertex_normals(ChunkLoadClass &cload, bool alternate_format);
	Vector3 *get_vert_normals(bool alternate_format);
};

// ?read_vertex_normals@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@_N@Z
bool MeshGeometryClass::read_vertex_normals(ChunkLoadClass &cload, bool alternate_format)
{
	W3dVectorStruct norm;
	Vector3 *mdlnorms = get_vert_normals(alternate_format);
	int buffer_index = 0;
	if (alternate_format) {
		buffer_index = 1;
	}

	for (int i = 0; i < VertexCount; i++) {
		if (cload.Read(&norm, sizeof(W3dVectorStruct)) != sizeof(W3dVectorStruct)) {
			return false;
		}
		mdlnorms[i].Set(norm.X, norm.Y, norm.Z);
	}

	if ((Flags & SKIN) && SkinNormalBuffers[buffer_index] != NULL) {
		float *skin_normals = SkinNormalBuffers[buffer_index]->Get_Array();
		int vertex_count = VertexCount;
		int vidx = 0;
		int z_offset = vertex_count + vertex_count;
		if (vertex_count > 0) {
			do {
				skin_normals[vidx] = mdlnorms[vidx].X;
				skin_normals[VertexCount + vidx] = mdlnorms[vidx].Y;
				skin_normals[z_offset + vidx] = mdlnorms[vidx].Z;
				vidx++;
			} while (vidx < VertexCount);
		}
	}

	return true;
}
