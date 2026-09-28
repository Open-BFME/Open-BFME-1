// ?rva00763AC0@Rva00763AC0@@QAEPAVGen00375590EntryStorage@@PAVRenderObjClass@@PAM@Z
// partial score=0.57 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug

// Retail body 0x00763AC0 spans 1,500 bytes and ends at ret 8 at +0x5D9.
// The W3DModelDraw slot-32 caller at 0x00767B30 calls through ILT 0x0002E7B7.
// The caller passes a RenderObjClass pointer and a float output pointer.
// This body sets the render object's transform.
// It joins mesh edges used by one triangle into an outline.
// It writes the final transformed point's z through the output pointer.
// The caller does not prove the owner's class or this method's name.
// The source keeps both names address-derived.

#define Matrix4x4 Matrix4
#include "WW3D2/rendobj.h"

typedef unsigned short UnsignedShort;

// The helper at 0x0075C690 stays in this source because VC7.1 uses a private
// register convention for its three calls.
struct Rva0075C690PackedEntry
{
	UnsignedShort m_000[3];
};

static __declspec(noinline) int Rva0075C690CountSharedEdges(
	int entryCount, const Rva0075C690PackedEntry *entries,
	const int *vertexRemap, int firstVertex, int secondVertex)
{
	int sharedCount = 0;
	for (int i = 0; i < entryCount; ++i)
	{
		bool hasFirst =
			firstVertex == vertexRemap[entries[i].m_000[0]] ||
			firstVertex == vertexRemap[entries[i].m_000[1]] ||
			firstVertex == vertexRemap[entries[i].m_000[2]];
		bool hasSecond =
			secondVertex == vertexRemap[entries[i].m_000[0]] ||
			secondVertex == vertexRemap[entries[i].m_000[1]] ||
			secondVertex == vertexRemap[entries[i].m_000[2]];
		if (hasFirst && hasSecond)
			++sharedCount;
	}
	return sharedCount;
}

struct Rva00763AC0Buffer
{
	char m_pad00[0xc];
	void *m_00C;
};

struct Rva00763AC0MeshModel
{
	char m_pad00[0x24];
	int m_024;
	int m_028;
	Rva00763AC0Buffer *m_02C;
	Rva00763AC0Buffer *m_030;
};

struct Rva00763AC0MeshView
{
	char m_pad00[0xc8];
	Rva00763AC0MeshModel *m_0C8;
};

struct Rva00763AC0MeshScratch
{
	char m_008[0x30];
	const Vector3 *m_030;
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
};

struct Rva00763AC0TransformView
{
	char m_pad00[8];
	Matrix3D m_008;
};

struct Rva00763AC0Offset008View
{
	char m_pad00[0xfc];
	Rva00763AC0TransformView *m_unwitnessed_0FC;
};

struct Rva00763AC0Offset004View
{
	char m_pad00[0x69];
	bool m_unwitnessed_069;
};

struct BfmeVector3BG
{
	int m_000;
	int m_004;
	int m_008;
};

class Gen00375590EntryStorage
{
public:
	Gen00375590EntryStorage(int count);

private:
	char m_data[0x88];
};

class Gen_0018F210
{
public:
	void bfmeAppendVector3(const BfmeVector3BG *point);
};

class Rva0077B3F0
{
public:
	void rva007629F0(Matrix3D &transform);
};

class Rva00763AC0
{
public:
	virtual void slot00();

	Gen00375590EntryStorage *rva00763AC0(RenderObjClass *mesh, float *height);

	Rva00763AC0Offset004View *m_field_004;
	Rva00763AC0Offset008View *m_field_008;
	char m_pad00c[0x34 - 0xc];
	RenderObjClass *m_renderObject;
};

// ?rva00763AC0@Rva00763AC0@@QAEPAVGen00375590EntryStorage@@PAVRenderObjClass@@PAM@Z
Gen00375590EntryStorage *Rva00763AC0::rva00763AC0(RenderObjClass *mesh, float *height)
{
	int edgeCount = 0;
	int verts3[3][100];
	verts3[2][0] = 0;
	verts3[1][0] = 0;

	Rva00763AC0TransformView *obj = m_field_008->m_unwitnessed_0FC;
	if (!obj)
	{
		if (mesh)
			mesh->Release_Ref();
		return 0;
	}

	Matrix3D transform(true);
	if (m_field_004->m_unwitnessed_069)
	{
		const Matrix3D *drawTransform = ((Drawable *)m_field_008)->getTransformMatrix();
		transform.Set_Translation(drawTransform->Get_Translation());
	}
	else
	{
		transform = obj->m_008;
	}

	((Rva0077B3F0 *)this)->rva007629F0(transform);
	m_renderObject->Set_Transform(transform);

	if (mesh && mesh->Class_ID() == RenderObjClass::CLASSID_MESH)
	{
		Rva00763AC0MeshScratch scratch;
		Matrix3D &meshTransform = *(Matrix3D *)scratch.m_008;
		meshTransform = mesh->Get_Transform();
		Rva00763AC0MeshModel *model = ((Rva00763AC0MeshView *)mesh)->m_0C8;
		int vertexCount = model->m_028;
		scratch.m_030 = (const Vector3 *)model->m_030->m_00C;
		int polyCount = model->m_024;
		const Rva0075C690PackedEntry *polys = (const Rva0075C690PackedEntry *)model->m_02C->m_00C;

		if (vertexCount >= 100 || polyCount >= 100)
		{
			mesh->Release_Ref();
			return 0;
		}

		int i;
		for (i = 0; i < vertexCount; i++)
			verts3[0][i] = i;

		for (i = 0; i < vertexCount - 1; i++)
		{
			for (int j = i + 1; j < vertexCount; j++)
			{
				if (scratch.m_030[i].X == scratch.m_030[j].X &&
					scratch.m_030[i].Y == scratch.m_030[j].Y &&
					scratch.m_030[i].Z == scratch.m_030[j].Z)
					verts3[0][j] = verts3[0][i];
			}
		}

		for (i = 0; i < polyCount; i++)
		{
			int a = verts3[0][polys[i].m_000[0]];
			int b = verts3[0][polys[i].m_000[1]];
			if (Rva0075C690CountSharedEdges(polyCount, polys, verts3[0], a, b) == 1)
			{
				verts3[2][edgeCount] = a;
				verts3[1][edgeCount] = b;
				edgeCount++;
			}
			int c = verts3[0][polys[i].m_000[2]];
			if (Rva0075C690CountSharedEdges(polyCount, polys, verts3[0], b, c) == 1)
			{
				verts3[2][edgeCount] = b;
				verts3[1][edgeCount] = c;
				edgeCount++;
			}
			if (Rva0075C690CountSharedEdges(polyCount, polys, verts3[0], c, a) == 1)
			{
				verts3[2][edgeCount] = c;
				verts3[1][edgeCount] = a;
				edgeCount++;
			}
		}

		if (edgeCount > 0)
		{
			verts3[0][0] = verts3[2][0];
			verts3[0][1] = verts3[1][0];
			int current = verts3[1][0];
			verts3[2][0] = -1;
			verts3[1][0] = -1;
			int count = 2;
			while (count < 100)
			{
				if (current == verts3[0][0])
					break;
				int e;
				for (e = 0; e < edgeCount; e++)
				{
					if (verts3[2][e] == current)
					{
						current = verts3[1][e];
						break;
					}
					if (verts3[1][e] == current)
					{
						current = verts3[2][e];
						break;
					}
				}
				if (e >= edgeCount)
					break;
				verts3[2][e] = -1;
				verts3[1][e] = -1;
				if (current != verts3[0][0])
					verts3[0][count++] = current;
			}

			if (count > 2)
			{
				Gen00375590EntryStorage *outline = new Gen00375590EntryStorage(count + 1);
				for (i = 0; i < count; i++)
				{
					Vector3 point;
					Matrix3D::Transform_Vector(meshTransform, scratch.m_030[verts3[0][i]], &point);
					BfmeVector3BG ipoint;
					ipoint.m_000 = (int)point.X;
					ipoint.m_004 = (int)point.Y;
					ipoint.m_008 = (int)point.Z;
					((Gen_0018F210 *)outline)->bfmeAppendVector3(&ipoint);
					*height = (float)ipoint.m_008;
				}
				mesh->Release_Ref();
				return outline;
			}
		}
	}

	if (mesh)
		mesh->Release_Ref();
	return 0;
}
