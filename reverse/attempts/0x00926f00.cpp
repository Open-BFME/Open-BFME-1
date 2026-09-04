// ?Compute_Vertex_Normals@MeshGeometryClass@@MAEXPAVVector3@@_N@Z
// partial score=0.98 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Open-BFME: BFME ABI-slice for MeshGeometryClass::Compute_Vertex_Normals.
// The retail MeshGeometry layout is four bytes earlier than the vendored ZH
// header from PolyCount through the geometry buffers; keep those accesses
// explicit while leaving the shared header untouched.

#include "always.h"
#include "refcount.h"
#include "bittype.h"
#include "sharebuf.h"
#include "vector3.h"
#include "vector3i.h"
#include "vector4.h"
#include "multilist.h"
#include "vp.h"

typedef Vector3i16 TriIndex;

class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	virtual void Delete_This(void);
	virtual ~MeshGeometryClass(void);
	virtual void Retail_Vtable_Slot_2(void);

protected:
	virtual void Compute_Plane_Equations(Vector4 *array);
	virtual void Compute_Vertex_Normals(Vector3 *array, bool unused);
	virtual void Compute_Bounds(Vector3 *array);

	Vector4 *get_planes(bool create);
	uint32 *get_shade_indices(bool create);

	public:
	void *UserText;
	void *MeshName;
	int Flags;
	char SortLevel;
	uint32 W3dAttributes;
	int PolyCount;
	int VertexCount;
	void *Poly;
	void *Vertex;
	void *Slot34;
	void *Slot38;
	void *Slot3c;
	void *Slot40;
	void *Slot44;
	ShareBufferClass<float> *Slot48;
	void *Slot4c;
	void *Slot50;
	void *Slot54;
	void *Slot58;
	void *Slot5c;
	void *Slot60;
	void *Slot64;
};

void MeshGeometryClass::Compute_Vertex_Normals(Vector3 *vnorm, bool)
{
	if ((*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x24) == 0) ||
		(*reinterpret_cast<int *>(reinterpret_cast<char *>(this) + 0x28) == 0)) {
		return;
	}

	char * const retail_this = reinterpret_cast<char *>(this);
	const Vector4 *peq = get_planes(true);
	if (peq != NULL && (*reinterpret_cast<unsigned char *>(retail_this + 0x18) & 2) != 0) {
		Compute_Plane_Equations(const_cast<Vector4 *>(peq));
	}

	TriIndex *poly = (*reinterpret_cast<ShareBufferClass<TriIndex> **>(retail_this + 0x2c))->Get_Array();
	const uint32 *shadeIx = get_shade_indices(false);

	if (!shadeIx) {
		VectorProcessorClass::Clear(vnorm, *reinterpret_cast<int *>(retail_this + 0x28));

		for (int pidx = 0; pidx < *reinterpret_cast<int *>(retail_this + 0x24); pidx++) {
			vnorm[poly[pidx].I].X += peq[pidx].X;
			vnorm[poly[pidx].I].Y += peq[pidx].Y;
			vnorm[poly[pidx].I].Z += peq[pidx].Z;

			vnorm[poly[pidx].J].X += peq[pidx].X;
			vnorm[poly[pidx].J].Y += peq[pidx].Y;
			vnorm[poly[pidx].J].Z += peq[pidx].Z;

			vnorm[poly[pidx].K].X += peq[pidx].X;
			vnorm[poly[pidx].K].Y += peq[pidx].Y;
			vnorm[poly[pidx].K].Z += peq[pidx].Z;
		}
	} else {
		VectorProcessorClass::Clear(vnorm, *reinterpret_cast<int *>(retail_this + 0x28));

		for (int pidx = 0; pidx < *reinterpret_cast<int *>(retail_this + 0x24); pidx++) {
			vnorm[shadeIx[poly[pidx].I]].X += peq[pidx].X;
			vnorm[shadeIx[poly[pidx].I]].Y += peq[pidx].Y;
			vnorm[shadeIx[poly[pidx].I]].Z += peq[pidx].Z;

			vnorm[shadeIx[poly[pidx].J]].X += peq[pidx].X;
			vnorm[shadeIx[poly[pidx].J]].Y += peq[pidx].Y;
			vnorm[shadeIx[poly[pidx].J]].Z += peq[pidx].Z;

			vnorm[shadeIx[poly[pidx].K]].X += peq[pidx].X;
			vnorm[shadeIx[poly[pidx].K]].Y += peq[pidx].Y;
			vnorm[shadeIx[poly[pidx].K]].Z += peq[pidx].Z;
		}

		for (unsigned vidx = 0; vidx < (unsigned)*reinterpret_cast<int *>(retail_this + 0x28); vidx++) {
			if (shadeIx[vidx] == vidx) {
				vnorm[vidx].Normalize();
			} else {
				vnorm[vidx] = vnorm[shadeIx[vidx]];
			}
		}
	}

	VectorProcessorClass::Normalize(vnorm, *reinterpret_cast<int *>(retail_this + 0x28));
	if ((*reinterpret_cast<int *>(retail_this + 0x18) & 0x400) != 0 &&
		*reinterpret_cast<ShareBufferClass<float> **>(retail_this + 0x48) != NULL) {
		float *skin_normals = Slot48->Get_Array();
		int vertex_count = VertexCount;
		int vidx = 0;
		if (vertex_count > 0) {
			int z_offset = vertex_count + vertex_count;
			float *skin_normals_z = skin_normals + z_offset;
			do {
				skin_normals[vidx] = vnorm[vidx].X;
				skin_normals[VertexCount + vidx] = vnorm[vidx].Y;
				*skin_normals_z = vnorm[vidx].Z;
				vidx++;
				skin_normals_z++;
			} while (vidx < VertexCount);
		}
	}
	*reinterpret_cast<int *>(retail_this + 0x18) &= ~4;
}
