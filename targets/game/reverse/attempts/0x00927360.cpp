// ?read_vertices@MeshGeometryClass@@IAE_NAAVChunkLoadClass@@_N@Z
// partial score=0.982 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
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
			float *skin_y = skin_x + vertex_count;
			float *skin_z = skin_y + vertex_count;
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
