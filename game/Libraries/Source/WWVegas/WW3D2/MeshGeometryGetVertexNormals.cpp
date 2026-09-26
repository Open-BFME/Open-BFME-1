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
// BFME MeshGeometryClass::get_vert_normals(bool), RVA 0x00927230, 171 bytes.
// The verified normal reader at 0x009274C0 calls this selector. Alternate
// buffers return at +0x8F; normal buffers return at +0xA8, both RET 4.
// INT3 padding begins at +0xAB. The VertexNorm literal and constructor route
// 0x00049832 -> 0x005F3BE0 were checked against the retail image.
// The BFME helper keeps the normal buffers at this+0x40/+0x44 and lazily
// creates the alternate Vector3 buffer when requested.

#include "always.h"
#include <string.h>
#include "sharebuf.h"
#include "vector3.h"

class MeshGeometryClass
{
protected:
	char _prefix[0x18];
	int Flags;
	char _between_flags_and_count[0x0c];
	int VertexCount;
	char _between_count_and_buffers[0x14];
	ShareBufferClass<Vector3> *VertexNorm;
	ShareBufferClass<Vector3> *AlternateVertexNorm;

	Vector3 *get_vert_normals(bool alternate_format);
};

// ?get_vert_normals@MeshGeometryClass@@IAEPAVVector3@@_N@Z
Vector3 *MeshGeometryClass::get_vert_normals(bool alternate_format)
{
	if (alternate_format) {
		if (!AlternateVertexNorm) {
			AlternateVertexNorm = NEW_REF(ShareBufferClass<Vector3>,
				(VertexCount, "MeshGeometryClass::VertexNorm", 0));
			AlternateVertexNorm->Clear();
		}
		return AlternateVertexNorm->Get_Array();
	}
	return VertexNorm->Get_Array();
}
