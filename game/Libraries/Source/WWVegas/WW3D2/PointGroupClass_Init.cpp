// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWDebug
#define BFME_DYNAMIC_IB_UINT_CTOR_ABI
#define Matrix4x4 Matrix4
#define private public

#include "pointgr.h"
#include "vertmaterial.h"
#include "ww3d.h"
#include "simplevec.h"
#include "wwmath.h"
#include "dx8indexbuffer.h"
#include "always.h"

extern DX8IndexBufferClass *Tris;
extern DX8IndexBufferClass *Quads;
extern SortingIndexBufferClass *SortingTris;
extern SortingIndexBufferClass *SortingQuads;

#define MAX_VB_SIZE 2048
#define MAX_TRI_POINTS (MAX_VB_SIZE / 3)
#define MAX_TRI_IB_SIZE MAX_VB_SIZE
#define MAX_QUAD_POINTS (MAX_VB_SIZE / 4)
#define MAX_QUAD_IB_SIZE (6 * MAX_QUAD_POINTS)

void Rva00917280Init(void)
{
	int i, j;

	Vector3 tri_locs[3] = {
		Vector3(0.0f, -2.0f, 0.0f),
		Vector3(-1.732f, 1.0f, 0.0f),
		Vector3(1.732f, 1.0f, 0.0f)
	};
	Vector3 quad_locs[4] = {
		Vector3(-0.5f, 0.5f, 0.0f),
		Vector3(-0.5f, -0.5f, 0.0f),
		Vector3(0.5f, -0.5f, 0.0f),
		Vector3(0.5f, 0.5f, 0.0f)
	};

	float angle = 0.0f;
	float angle_step = (WWMATH_PI * 2.0f) / 256.0f;
	for (i = 0; i < 256; i++) {
		float c = WWMath::Fast_Cos(angle);
		float s = WWMath::Fast_Sin(angle);
		for (j = 0; j < 3; j++) {
			PointGroupClass::_TriVertexLocationOrientationTable[i][j].X = tri_locs[j].X * c - tri_locs[j].Y * s;
			PointGroupClass::_TriVertexLocationOrientationTable[i][j].Y = tri_locs[j].X * s + tri_locs[j].Y * c;
			PointGroupClass::_TriVertexLocationOrientationTable[i][j].Z = tri_locs[j].Z;
		}
		for (j = 0; j < 4; j++) {
			PointGroupClass::_QuadVertexLocationOrientationTable[i][j].X = quad_locs[j].X * c - quad_locs[j].Y * s;
			PointGroupClass::_QuadVertexLocationOrientationTable[i][j].Y = quad_locs[j].X * s + quad_locs[j].Y * c;
			PointGroupClass::_QuadVertexLocationOrientationTable[i][j].Z = quad_locs[j].Z;
		}
		angle += angle_step;
	}

	Vector2 tri_uvs[3] = {
		Vector2(0.5f, 0.0f),
		Vector2(0.0f, 0.866f),
		Vector2(1.0f, 0.866f)
	};
	Vector2 quad_uvs[4] = {
		Vector2(0.0f, 0.0f),
		Vector2(0.0f, 1.0f),
		Vector2(1.0f, 1.0f),
		Vector2(1.0f, 0.0f)
	};

	for (i = 0; i < 5; i++) {
		unsigned int rows = 1 << i;
		unsigned int count = rows * rows;
		Vector2 *tri_table = PointGroupClass::_TriVertexUVFrameTable[i] = W3DNEWARRAY Vector2[count * 3];
		Vector2 *quad_table = PointGroupClass::_QuadVertexUVFrameTable[i] = W3DNEWARRAY Vector2[count * 4];
		Vector2 corner(0.0f, 0.0f);
		float scale = 1.0f / (float)rows;
		int tri_idx = 0;
		int quad_idx = 0;

		for (unsigned int v = 0; v < rows; v++) {
			for (unsigned int u = 0; u < rows; u++) {
				tri_table[tri_idx++] = corner + (tri_uvs[0] * scale);
				tri_table[tri_idx++] = corner + (tri_uvs[1] * scale);
				tri_table[tri_idx++] = corner + (tri_uvs[2] * scale);
				quad_table[quad_idx++] = corner + (quad_uvs[0] * scale);
				quad_table[quad_idx++] = corner + (quad_uvs[1] * scale);
				quad_table[quad_idx++] = corner + (quad_uvs[2] * scale);
				quad_table[quad_idx++] = corner + (quad_uvs[3] * scale);
				corner.X += scale;
			}
			corner.Y += scale;
			corner.X = 0.0f;
		}
	}

	Tris = NEW_REF(DX8IndexBufferClass, (MAX_TRI_IB_SIZE));
	Quads = NEW_REF(DX8IndexBufferClass, (MAX_QUAD_IB_SIZE));
	SortingTris = NEW_REF(SortingIndexBufferClass, (MAX_TRI_IB_SIZE));
	SortingQuads = NEW_REF(SortingIndexBufferClass, (MAX_QUAD_IB_SIZE));

	{
		IndexBufferClass::WriteLockClass locktris(Tris);
		unsigned short *ib = locktris.Get_Index_Array();
		for (i = 0; i < MAX_TRI_IB_SIZE; i++)
			ib[i] = (unsigned short)i;
	}

	{
		unsigned short vert = 0;
		IndexBufferClass::WriteLockClass lockquads(Quads);
		unsigned short *ib = lockquads.Get_Index_Array();
		vert = 0;
		for (i = 0; i < MAX_QUAD_IB_SIZE; i += 6) {
			ib[i] = vert;
			ib[i + 1] = vert + 1;
			ib[i + 2] = vert + 2;
			ib[i + 3] = vert + 2;
			ib[i + 4] = vert + 3;
			ib[i + 5] = vert;
			vert += 4;
		}
	}

	{
		IndexBufferClass::WriteLockClass locktris(SortingTris);
		unsigned short *ib = locktris.Get_Index_Array();
		for (i = 0; i < MAX_TRI_IB_SIZE; i++)
			ib[i] = (unsigned short)i;
	}

	{
		unsigned short vert = 0;
		IndexBufferClass::WriteLockClass lockquads(SortingQuads);
		unsigned short *ib = lockquads.Get_Index_Array();
		for (i = 0; i < MAX_QUAD_IB_SIZE; i += 6) {
			ib[i] = vert;
			ib[i + 1] = vert + 1;
			ib[i + 2] = vert + 2;
			ib[i + 3] = vert + 2;
			ib[i + 4] = vert + 3;
			ib[i + 5] = vert;
			vert += 4;
		}
	}

	PointGroupClass::PointMaterial =
		VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
}

#undef MAX_TRI_POINTS
#undef MAX_TRI_IB_SIZE
#undef MAX_QUAD_POINTS
#undef MAX_QUAD_IB_SIZE
#undef MAX_VB_SIZE
#undef private
