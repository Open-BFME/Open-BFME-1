// ?get_deformed_vertices@MeshGeometryClass@@IAEXPAVVector3@@PBVHTreeClass@@@Z
// partial score=0.79 date=2026-09-28
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// ?get_deformed_vertices@MeshGeometryClass@@IAEXPAVVector3@@PBVHTreeClass@@@Z -- retail 0x00925860, 1199 B (ret 8 at +0x4AC).
// Land in game/Libraries/Source/WWVegas/WW3D2/meshgeometry.cpp in place of the ZH body.
#include "meshgeometry.h"
#pragma push_macro("W3DMPO_GLUE")
#define W3DMPO_GLUE(ARGCLASS)
#include "aabtree.h"
#pragma pop_macro("W3DMPO_GLUE")
#include "chunkio.h"
#include "aabox.h"
#include "obbox.h"
#include "sphere.h"
#include "plane.h"
#include "wwdebug.h"
#include "wwmemlog.h"
#include "w3d_file.h"
#include "vp.h"
#include "htree.h"
#include "matrix4.h"
#include "rinfo.h"
#include "camera.h"

// Destination pointers MUST point to arrays large enough to hold all vertices
// BFME skins with up to two bone influences per vertex: each influence has its
// own bone-space position array (this+0x30/+0x34, see Compute_Ram_Size), the
// bone-link buffer at this+0x58 holds four vertex-count-long uint16 planes
// (bone 0, bone 1, weight 0, weight 1 in percent) and the buffer at this+0x5C
// lists runs of vertices that share their bones (the count is the second
// uint16 of each pair).
struct MeshGeometryRetailSkinView
{
	char pad_00[0x28];
	int vertex_count;
	char pad_2c[4];
	ShareBufferClass<Vector3> *vertex[2];
	char pad_38[0x20];
	ShareBufferClass<uint16> *bone_link;
	ShareBufferClass<uint16> *bone_run;
};

void rva009371E0Inc();

void MeshGeometryClass::get_deformed_vertices(Vector3 *dst_vert,const HTreeClass * htree)
{
	MeshGeometryRetailSkinView * const geometry =
		reinterpret_cast<MeshGeometryRetailSkinView *>(this);
	if (geometry->bone_run == NULL || geometry->bone_link == NULL || dst_vert == NULL) {
		return;
	}

	int influences = 1;
	if (geometry->vertex[1] != NULL) {
		influences = 2;
	}
	Vector3 * src_vert[2];
	int i;
	for (i = 0; i < influences; i++) {
		src_vert[i] = geometry->vertex[i] ? geometry->vertex[i]->Get_Array() : NULL;
	}
	uint16 * bonelink = geometry->bone_link->Get_Array();
	uint16 * run = geometry->bone_run->Get_Array();
	rva009371E0Inc();

	int vertex_count = geometry->vertex_count;
	int remaining = vertex_count;
	run++;
	while (remaining > 0) {
		int count = *run;
		run += 2;
		remaining -= count;
		int bone0 = bonelink[0];
		int bone1 = bonelink[vertex_count];
		if (influences == 2 && bone1 != 0) {
			float weight0 = bonelink[vertex_count * 2] * 0.01f;
			float weight1 = bonelink[vertex_count * 3] * 0.01f;
			Matrix3D tm0 = htree->Get_Transform(bone0);
			Matrix3D tm1 = htree->Get_Transform(bone1);
			for (i = 0; i < 3; i++) {
				tm0[i] *= weight0;
				tm1[i] *= weight1;
			}
			Vector3 * s0 = src_vert[0];
			Vector3 * s1 = src_vert[1];
			Vector3 * d = dst_vert;
			int n = count;
			while (n--) {
				d->X = tm0[0][0] * s0->X + tm0[0][1] * s0->Y + tm0[0][2] * s0->Z + tm0[0][3] + tm1[0][0] * s1->X + tm1[0][1] * s1->Y + tm1[0][2] * s1->Z + tm1[0][3];
				d->Y = tm0[1][0] * s0->X + tm0[1][1] * s0->Y + tm0[1][2] * s0->Z + tm0[1][3] + tm1[1][0] * s1->X + tm1[1][1] * s1->Y + tm1[1][2] * s1->Z + tm1[1][3];
				d->Z = tm0[2][0] * s0->X + tm0[2][1] * s0->Y + tm0[2][2] * s0->Z + tm0[2][3] + tm1[2][0] * s1->X + tm1[2][1] * s1->Y + tm1[2][2] * s1->Z + tm1[2][3];
				s0++;
				s1++;
				d++;
			}
		} else {
			const Matrix3D & tm = htree->Get_Transform(bone0);
			Vector3 * s = src_vert[0];
			Vector3 * d = dst_vert;
			int n = count;
			while (n--) {
				d->X = tm[0][0] * s->X + tm[0][1] * s->Y + tm[0][2] * s->Z + tm[0][3];
				d->Y = tm[1][0] * s->X + tm[1][1] * s->Y + tm[1][2] * s->Z + tm[1][3];
				d->Z = tm[2][0] * s->X + tm[2][1] * s->Y + tm[2][2] * s->Z + tm[2][3];
				s++;
				d++;
			}
		}
		bonelink += count;
		for (i = 0; i < influences; i++) {
			src_vert[i] += count;
		}
		dst_vert += count;
	}
}
