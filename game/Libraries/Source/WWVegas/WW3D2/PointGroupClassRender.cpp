// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// BFME renamed GeneralsMD Matrix4x4 -> Matrix4 (see pointgr.cpp).
#define Matrix4x4 Matrix4

// PointGroupClass::Render(RenderInfoClass &, int) at retail 0x00917B70 and the
// APT compression helper it calls at 0x00917920.
//
// BFME split the Zero Hour Render/Update_Arrays pair into helpers: shader prep
// (0x00912E60), APT compression (0x00917920), the vertex location, UV and
// diffuse fills (0x009148C0, 0x00916CD0, 0x00912880) and the vertex-buffer
// submit (0x00913AF0). The view transform loop and the Update_Arrays sizing
// prologue (out of line at 0x00914860) stay inline in Render.
//
// The helper at 0x00917920 is defined here, before Render, as it was in the
// retail pointgr.cpp: VC7.1 sees that it does not keep the addresses of
// Render's five out pointers, so Render loads them lazily, keeps the location
// base in a register through the transform loop and reads the diffuse pointer
// once. With only a declaration every one of those loads is repeated
// (docs/shape_levers.md, "Compiler-private ABI: compile the static helper with
// its caller"). The other helpers are not visible here, so Render copies
// PointCount into a local that retail kept live across those calls.

#include "sharebuf.h"
#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "dx8wrapper.h"
#include "vp.h"

class RenderInfoClass;

extern VectorClass<Vector3> VertexLoc;
extern VectorClass<Vector4> VertexDiffuse;
extern VectorClass<Vector2> VertexUV;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/pointgr.h
// pointgr.h does not declare the BFME helpers, so this TU carries a shim.
// +0x24 and +0x28 are not read here and have no layout witness.
class PointGroupClass
{
public:
	enum PointModeEnum {
		TRIS,
		QUADS,
		SCREENSPACE
	};
	enum FlagsType {
		TRANSFORM,
		BILLBOARD,
	};

	// Same body as the matched out-of-line Get_Flag at 0x009120D0.
	int Get_Flag(FlagsType flag) { return (Flags >> flag) & 0x1; }

	void Render(RenderInfoClass &rinfo, int unknown);

	void prepare_shader(void);
	void rva00917920(Vector3 **point_loc, Vector4 **point_diffuse, float **point_size,
		unsigned char **point_orientation, unsigned char **point_frame);
	void rva009148C0(Vector3 *point_loc, float *point_size, unsigned char *point_orientation,
		int active_points);
	void rva00916CD0(unsigned char *point_frame, int active_points, int unknown);
	void rva00912880(Vector4 *point_diffuse, int active_points);
	void rva00913AF0(int vnum, bool no_diffuse);

	// Update_Arrays sizing prologue; retail keeps an out-of-line copy at
	// 0x00914860 and inlines this one.
	void rva00914860(int active_points, int total_points, int *vnum)
	{
		int verts_per_point = (PointMode == QUADS) ? 4 : 3;
		int total_vnum = verts_per_point * total_points;
		*vnum = verts_per_point * active_points;
		if (VertexLoc.Length() < total_vnum) {
			VertexLoc.Resize(total_vnum * 2, false);
			VertexUV.Resize(total_vnum * 2, false);
			VertexDiffuse.Resize(total_vnum * 2, false);
		}
	}

private:
	virtual void abstract_dtor(void);
	ShareBufferClass<Vector3> *PointLoc;
	ShareBufferClass<Vector4> *PointDiffuse;
	ShareBufferClass<unsigned int> *APT;
	ShareBufferClass<float> *PointSize;
	ShareBufferClass<unsigned char> *PointOrientation;
	ShareBufferClass<unsigned char> *PointFrame;
	int PointCount;
	unsigned char FrameRowColumnCountLog2;
	void *dword_24;
	unsigned int dword_28;
	PointModeEnum PointMode;
	unsigned int Flags;

	static VectorClass<Vector3> compressed_loc;
	static VectorClass<Vector4> compressed_diffuse;
	static VectorClass<float> compressed_size;
	static VectorClass<unsigned char> compressed_orient;
	static VectorClass<unsigned char> compressed_frame;
};

// One APT compression step of 0x00917920. The buffer is a reference, so the
// Resize call stays virtual as in retail.
template <class T, class S>
inline T *rva00917920_compress(VectorClass<T> &buffer, S *source, unsigned int *apt, int count)
{
	if (source) {
		if (buffer.Length() < count) {
			buffer.Resize(count * 2);
		}
		VectorProcessorClass::CopyIndexed(&buffer[0], source->Get_Array(), apt, count);
		return &buffer[0];
	}
	return NULL;
}

void PointGroupClass::rva00917920(Vector3 **point_loc, Vector4 **point_diffuse, float **point_size,
	unsigned char **point_orientation, unsigned char **point_frame)
{
	if (APT) {
		unsigned int *apt = APT->Get_Array();
		*point_loc = rva00917920_compress(compressed_loc, PointLoc, apt, PointCount);
		*point_diffuse = rva00917920_compress(compressed_diffuse, PointDiffuse, apt, PointCount);
		*point_size = rva00917920_compress(compressed_size, PointSize, apt, PointCount);
		*point_orientation = rva00917920_compress(compressed_orient, PointOrientation, apt, PointCount);
		*point_frame = rva00917920_compress(compressed_frame, PointFrame, apt, PointCount);
	} else {
		*point_loc = PointLoc->Get_Array();
		if (PointDiffuse) {
			*point_diffuse = PointDiffuse->Get_Array();
		}
		if (PointSize) {
			*point_size = PointSize->Get_Array();
		}
		if (PointOrientation) {
			*point_orientation = PointOrientation->Get_Array();
		}
		if (PointFrame) {
			*point_frame = PointFrame->Get_Array();
		}
	}
}

void PointGroupClass::Render(RenderInfoClass &rinfo, int unknown)
{
	if (PointCount == 0) return;

	prepare_shader();

	Vector3 *current_loc = NULL;
	Vector4 *current_diffuse = NULL;
	float *current_size = NULL;
	unsigned char *current_orient = NULL;
	unsigned char *current_frame = NULL;
	rva00917920(&current_loc, &current_diffuse, &current_size, &current_orient, &current_frame);

	Matrix4x4 view;
	DX8Wrapper::Get_Transform(D3DTS_VIEW, view);

	if (Get_Flag(TRANSFORM) && Get_Flag(BILLBOARD)) {
		if (compressed_loc.Length() < PointCount) {
			compressed_loc.Resize(PointCount * 2);
		}
		Vector4 result;
		for (int i = 0; i < PointCount; i++) {
			result = view * current_loc[i];
			compressed_loc[i][0] = result[0];
			compressed_loc[i][1] = result[1];
			compressed_loc[i][2] = result[2];
		}
		current_loc = &compressed_loc[0];
	}

	int count = PointCount;
	int vnum;
	rva00914860(count, PointLoc->Get_Count(), &vnum);
	rva009148C0(current_loc, current_size, current_orient, count);
	rva00916CD0(current_frame, count, unknown);
	rva00912880(current_diffuse, count);
	rva00913AF0(vnum, current_diffuse == NULL);
}
