// ?d_00917e10@@YAXXZ
// partial score=0.9874 date=2026-09-27
// cl: /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// BFME renamed GeneralsMD Matrix4x4 -> Matrix4 (see pointgr.cpp).
#define Matrix4x4 Matrix4

// Native bank for 0x00917E10, complete 952-byte entry (ret 12 at +0x393
// and fallback tail ret 12 at +0x3B5). The address-derived method keeps its
// semantic identity open. Its volume rendering algorithm follows the official
// PointGroup twin; the already-matched compression helper remains visible
// because its nonescaping output arguments affect this caller's codegen.
// Residue: twelve x87 operand bytes in the transformed Y/Z dot products.

#include "sharebuf.h"
#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "dx8wrapper.h"
#include "vp.h"
#include "rinfo.h"
#include "camera.h"

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
 void rva00917E10(RenderInfoClass &rinfo,unsigned depth,int unknown);

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


void PointGroupClass::rva00917E10(RenderInfoClass &rinfo,unsigned depth,int unknown)
{
 if(depth<=1 || !Get_Flag(TRANSFORM) || !Get_Flag(BILLBOARD)) { Render(rinfo,unknown);return; }
 if(depth>16)depth=16;
 if(PointCount==0)return;
 prepare_shader();
 Vector3 *current_loc=NULL;
 Vector4 *current_diffuse=NULL;
 float *current_size=NULL;
 unsigned char *current_orient=NULL,*current_frame=NULL;
 rva00917920(&current_loc,&current_diffuse,&current_size,&current_orient,&current_frame);
 Vector3 *original_loc=current_loc;
 int vnum;
 rva00914860(PointCount,PointLoc->Get_Count(),&vnum);
 rva00912880(current_diffuse,PointCount);
 rva00916CD0(current_frame,PointCount,unknown);
 Matrix4 view;
 DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
 if(compressed_loc.Length()<PointCount)compressed_loc.Resize(PointCount*2);
 for(int t=0;t<(int)depth;t++){
  float shift=(t*0.1f)/(float)depth;
  Vector3 cameraPosition=rinfo.Camera.Get_Position();
  for(int i=0;i<PointCount;i++){
   Vector3 cameraToPointDelta;
   Vector3::Subtract(cameraPosition,original_loc[i],&cameraToPointDelta);
   float dist=cameraToPointDelta.Length();
   float offset=(shift*current_size[i])/dist;
   cameraToPointDelta.X*=offset;
   cameraToPointDelta.Y*=offset;
   cameraToPointDelta.Z*=offset;
   Vector3 temp;
   temp.X=original_loc[i].X+cameraToPointDelta.X;
   temp.Y=original_loc[i].Y+cameraToPointDelta.Y;
   temp.Z=original_loc[i].Z+cameraToPointDelta.Z;
   Vector4 result=view*temp;
   compressed_loc[i].X=result.X;
   compressed_loc[i].Y=result.Y;
   compressed_loc[i].Z=result.Z;
  }
  current_loc=&compressed_loc[0];
  rva009148C0(current_loc,current_size,current_orient,PointCount);
  rva00913AF0(vnum,current_diffuse==NULL);
 }
}
