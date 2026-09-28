// ?rva00763AC0@Rva00763AC0ModelDraw@@QAEPAVGen00375590EntryStorage@@PAVRenderObjClass@@PAM@Z
// partial score=0.41 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWDebug
// Retail RVA 0x00763AC0 (1500 B, ret 8), W3DModelDraw neighbourhood.  The
// W3DModelDraw slot-32 body at 0x00767B30 (and the dump at 0x00767C70) call it
// through ILT 0x0002E7B7 with the render object returned by slot 5 (already
// referenced; every exit here releases it) and a float out pointer.  It
// places the model's render object at the owner transform, welds the mesh's
// duplicate vertices, keeps the triangle edges used by exactly one triangle,
// chains them into an outline loop and returns a new point list holding the
// transformed outline (the last point's height goes to the out pointer).
// No retail name is known, so the owner and method stay address-derived.

#define Matrix4x4 Matrix4
#include "WW3D2/rendobj.h"

typedef unsigned short UnsignedShort;

// Retail 0x0075C690: internal-linkage helper, compiled in this TU so VC7.1
// applies the same private register convention at the three call sites.
struct Rva0075C690PackedEntry
{
	UnsignedShort vertex[3];
};

static __declspec(noinline) int Rva0075C690CountSharedEdges(
	int entryCount, const Rva0075C690PackedEntry *entries,
	const int *vertexRemap, int firstVertex, int secondVertex)
{
	int sharedCount = 0;
	for (int i = 0; i < entryCount; ++i)
	{
		bool hasFirst =
			firstVertex == vertexRemap[entries[i].vertex[0]] ||
			firstVertex == vertexRemap[entries[i].vertex[1]] ||
			firstVertex == vertexRemap[entries[i].vertex[2]];
		bool hasSecond =
			secondVertex == vertexRemap[entries[i].vertex[0]] ||
			secondVertex == vertexRemap[entries[i].vertex[1]] ||
			secondVertex == vertexRemap[entries[i].vertex[2]];
		if (hasFirst && hasSecond)
			++sharedCount;
	}
	return sharedCount;
}

struct Rva00763AC0Buffer
{
	char m_pad00[0xc];
	void *m_array;
};

struct Rva00763AC0MeshModel
{
	char m_pad00[0x24];
	int m_polyCount;
	int m_vertexCount;
	Rva00763AC0Buffer *m_polys;
	Rva00763AC0Buffer *m_vertices;
};

struct Rva00763AC0MeshView
{
	char m_pad00[0xc8];
	Rva00763AC0MeshModel *m_model;
};

class Drawable
{
public:
	const Matrix3D *getTransformMatrix() const;
};

struct Rva00763AC0ObjectView
{
	char m_pad00[8];
	Matrix3D m_transform;
};

struct Rva00763AC0DrawableView
{
	char m_pad00[0xfc];
	Rva00763AC0ObjectView *m_object;
};

struct Rva00763AC0ModuleData
{
	char m_pad00[0x69];
	bool m_useDrawablePosition;
};

struct BfmeVector3BG
{
	int x;
	int y;
	int z;
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

class Rva00763AC0ModelDraw
{
public:
	virtual void slot00();

	Gen00375590EntryStorage *rva00763AC0(RenderObjClass *mesh, float *height);

	Rva00763AC0ModuleData *m_moduleData;
	Rva00763AC0DrawableView *m_drawable;
	char m_pad00c[0x34 - 0xc];
	RenderObjClass *m_renderObject;
};

// ?rva00763AC0@Rva00763AC0ModelDraw@@QAEPAVGen00375590EntryStorage@@PAVRenderObjClass@@PAM@Z
Gen00375590EntryStorage *Rva00763AC0ModelDraw::rva00763AC0(RenderObjClass *mesh, float *height)
{
	int edgeCount = 0;
	int verts3[3][100];
	verts3[2][0] = 0;
	verts3[1][0] = 0;

	Rva00763AC0ObjectView *obj = m_drawable->m_object;
	if (!obj)
	{
		if (mesh)
			mesh->Release_Ref();
		return 0;
	}

	Matrix3D transform(true);
	if (m_moduleData->m_useDrawablePosition)
	{
		const Matrix3D *drawTransform = ((Drawable *)m_drawable)->getTransformMatrix();
		transform.Set_Translation(drawTransform->Get_Translation());
	}
	else
	{
		transform = obj->m_transform;
	}

	((Rva0077B3F0 *)this)->rva007629F0(transform);
	m_renderObject->Set_Transform(transform);

	if (!mesh)
		return 0;

	if (mesh->Class_ID() == RenderObjClass::CLASSID_MESH)
	{
		Matrix3D meshTransform = mesh->Get_Transform();
		Rva00763AC0MeshModel *model = ((Rva00763AC0MeshView *)mesh)->m_model;
		int vertexCount = model->m_vertexCount;
		const Vector3 *vertices = (const Vector3 *)model->m_vertices->m_array;
		int polyCount = model->m_polyCount;
		const Rva0075C690PackedEntry *polys = (const Rva0075C690PackedEntry *)model->m_polys->m_array;

		if (vertexCount >= 100 || polyCount >= 100)
		{
			mesh->Release_Ref();
			return 0;
		}

		int i;
		for (i = 0; i < vertexCount; i++)
			verts3[0][i] = i;

		for (i = 0; i < vertexCount; i++)
		{
			for (int j = i + 1; j < vertexCount; j++)
			{
				if (vertices[i].X == vertices[j].X &&
					vertices[i].Y == vertices[j].Y &&
					vertices[i].Z == vertices[j].Z)
					verts3[0][j] = verts3[0][i];
			}
		}

		for (i = 0; i < polyCount; i++)
		{
			int a = verts3[0][polys[i].vertex[0]];
			int b = verts3[0][polys[i].vertex[1]];
			if (Rva0075C690CountSharedEdges(polyCount, polys, verts3[0], a, b) == 1)
			{
				verts3[2][edgeCount] = a;
				verts3[1][edgeCount] = b;
				edgeCount++;
			}
			int c = verts3[0][polys[i].vertex[2]];
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
					Matrix3D::Transform_Vector(meshTransform, vertices[verts3[0][i]], &point);
					BfmeVector3BG ipoint;
					ipoint.x = (int)point.X;
					ipoint.y = (int)point.Y;
					ipoint.z = (int)point.Z;
					((Gen_0018F210 *)outline)->bfmeAppendVector3(&ipoint);
					*height = (float)ipoint.z;
				}
				mesh->Release_Ref();
				return outline;
			}
		}
	}

	mesh->Release_Ref();
	return 0;
}
