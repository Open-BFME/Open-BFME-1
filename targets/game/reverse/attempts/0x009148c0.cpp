// ?rva009148C0@PointGroupClass@@QAEXPAVVector3@@PAMPAEH@Z
// partial score=0.9965 date=2026-11-07
// ?rva009148C0@PointGroupClass@@QAEXPAVVector3@@PAMPAEH@Z
// cl: /O2 /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Ported from Open-BFME-2 Code/Libraries/Source/WWVegas/WW3D2/PointGroupClassRva0017A890.cpp
// (commit d1720ae604, matched there for the BFME2 binary) with BFME1 include paths and
// without /arch:SSE /G7, and BFME1's full DX8Wrapper::Get_Transform body (D3DMATRIX
// local, device default branch). 9232/9232 bytes; every case exact except case 7,
// where the view-transform row sums differ in operand order (42 bytes).
// PointGroupClass vertex-location fill, retail RVA 0x0017A890 (VA 0x009148C0),
// PointGroupClass vertex-location fill, retail RVA 0x0017A890 (VA 0x009148C0),
// 12000 bytes including its 12-entry dispatch table. Called by the matched
// array-update helper 0x0017F3A0 (PointGroupClassUpdateArrays00917B10.cpp),
// which proves the receiver and the (point_loc, point_size, point_orientation,
// active_points) ABI; the existing neutral pin keeps the address-named method.
// Semantic lead (donor source, not a target fact): the location subsection of
// ZH/BFME1 pointgr.cpp PointGroupClass::Update_Arrays (the WorldBuilder twin
// names it Update_Location_Array), split out of Update_Arrays in BFME 2.
// Target findings: view matrix read transposed from the DX8 render state
// (offset 0x22C) into a 48-byte Matrix3D, billboard flag bit 1, scaled_offset[3]
// built by the vector constructor iterator, per-case loops in the ZH shape.
// Retail codegen only reproduces with VertexLoc at internal linkage: an extern
// or non-static definition changes the prologue load and the induction
// variables of the varying-size and ground cases. BFME 2's pointgr.cpp
// therefore keeps VertexLoc file-static (ZH/BFME1 define it globally); this TU
// carries its own static copy until the remaining VertexLoc users rejoin one
// unit. History: reverse/attempt_support/rva17a890-2026-10-20.md.
#include "sharebuf.h"
#include "vector.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"
#include "matrix4.h"
#include "matrix3d.h"
struct RenderStateStruct { unsigned char opaque[0x1EC]; Matrix4 world; Matrix4 view; };
class DX8Wrapper { public:
 struct Rva009148C0Device { virtual long GetTransform(int transform, void *matrix); };
 static Rva009148C0Device *_Get_D3D_Device8();
 static unsigned number_of_DX8_calls;
 static __forceinline void Get_Transform(int transform,Matrix4& m) {
  struct { float e[16]; } mat;
  switch (transform) {
	case 0x100:
		if (render_state_changed&(1<<18)) m.Make_Identity();
		else m=render_state.world.Transpose();
		break;
	case 2:
		if (render_state_changed&(1<<19)) m.Make_Identity();
		else m=render_state.view.Transpose();
		break;
	default:
		_Get_D3D_Device8()->GetTransform(transform,&mat); number_of_DX8_calls++;
		m=*(Matrix4*)&mat;
		m=m.Transpose();
		break;
  }
 }
 static __forceinline void Get_Transform(int,Matrix3D& matrix3D) {
  if(render_state_changed&(1<<19)) matrix3D.Make_Identity();
  else {matrix3D[0][0]=render_state.view[0][0];matrix3D[0][1]=render_state.view[1][0];matrix3D[0][2]=render_state.view[2][0];matrix3D[0][3]=render_state.view[3][0];matrix3D[1][0]=render_state.view[0][1];matrix3D[1][1]=render_state.view[1][1];matrix3D[1][2]=render_state.view[2][1];matrix3D[1][3]=render_state.view[3][1];matrix3D[2][0]=render_state.view[0][2];matrix3D[2][1]=render_state.view[1][2];matrix3D[2][2]=render_state.view[2][2];matrix3D[2][3]=render_state.view[3][2];}
 }
protected: static Matrix4 ProjectionMatrix; static RenderStateStruct render_state; static unsigned render_state_changed;
};
#include "ww3d.h"
#include <d3dx8.h>
static __forceinline Vector3 operator * (const Matrix3D &A,const Vector3 &a)
{
	return Vector3
	(
		(A[0][0]*a[0] + A[0][1]*a[1] + A[0][2]*a[2] + A[0][3]),
		(A[1][0]*a[0] + A[1][1]*a[1] + A[1][2]*a[2] + A[1][3]),
		(A[2][0]*a[0] + A[2][1]*a[1] + A[2][2]*a[2] + A[2][3])
	);
}
static Vector3 GroundMultiplierX(1,0,0),GroundMultiplierY(0,1,0);
// The static VertexLoc instantiates VectorClass<Vector3>; its /O2 copies of
// the constructor and Resize are not retail's, so bind both to the rowed
// 0x000F0D2F and 0x000F0BF1 bodies (vector_class_vector3_ctor/_resize.cpp).
template <> VectorClass<Vector3>::VectorClass(int, Vector3 const *);
template <> bool VectorClass<Vector3>::Resize(int, Vector3 const *);
static VectorClass<Vector3> VertexLoc;
extern VectorClass<Vector2> VertexUV;

class PointGroupClass {
public:
  enum PointModeEnum { TRIS, QUADS, SCREENSPACE };
  void rva009148C0(Vector3*,float*,unsigned char*,int);
  enum FlagsType{TRANSFORM,BILLBOARD};
  int Get_Flag(FlagsType f){return (Flags>>f)&1;}

private:
  virtual void abstract_dtor();
  ShareBufferClass<Vector3> *PointLoc;
  ShareBufferClass<Vector4> *PointDiffuse;
  ShareBufferClass<unsigned int> *APT;
  ShareBufferClass<float> *PointSize;
  ShareBufferClass<unsigned char> *PointOrientation, *PointFrame;
  int PointCount;
  unsigned char FrameRowColumnCountLog2;
  void *dword_24;
  unsigned int dword_28;
  PointModeEnum PointMode;
  unsigned int Flags;
  float DefaultPointSize;
  Vector3 DefaultPointColor;
  float DefaultPointAlpha;
  unsigned char DefaultPointOrientation, DefaultPointFrame;
  float VPXMin, VPYMin, VPXMax, VPYMax;
  static Vector3 _TriVertexLocationOrientationTable[256][3];
  static Vector3 _QuadVertexLocationOrientationTable[256][4];
  static Vector3 _ScreenspaceVertexLocationSizeTable[2][3];
  static Vector2 *_TriVertexUVFrameTable[5];
  static Vector2 *_QuadVertexUVFrameTable[5];
};

void PointGroupClass::rva009148C0(Vector3 *point_loc, float *point_size, unsigned char *point_orientation, int active_points)
{
	enum LoopSelectionEnum {
		TRIS_NOSIZE_NOORIENT		= ((int)TRIS << 2) + 0,
		TRIS_SIZE_NOORIENT		= ((int)TRIS << 2) + 1,
		TRIS_NOSIZE_ORIENT		= ((int)TRIS << 2) + 2,
		TRIS_SIZE_ORIENT			= ((int)TRIS << 2) + 3,
		QUADS_NOSIZE_NOORIENT	= ((int)QUADS << 2) + 0,
		QUADS_SIZE_NOORIENT		= ((int)QUADS << 2) + 1,
		QUADS_NOSIZE_ORIENT		= ((int)QUADS << 2) + 2,
		QUADS_SIZE_ORIENT			= ((int)QUADS << 2) + 3,
		SCREEN_NOSIZE_NOORIENT	= ((int)SCREENSPACE << 2) + 0,
		SCREEN_SIZE_NOORIENT		= ((int)SCREENSPACE << 2) + 1,
		SCREEN_NOSIZE_ORIENT		= ((int)SCREENSPACE << 2) + 2,
		SCREEN_SIZE_ORIENT		= ((int)SCREENSPACE << 2) + 3,
	};
	LoopSelectionEnum loop_sel = (LoopSelectionEnum)(((int)PointMode << 2) +
		(point_orientation ? 2 : 0) + (point_size ? 1 : 0));
	Vector3 *vertex_loc = &VertexLoc[0];

	/// @todo lorenzen sez: this switch statement may be done more compactly another way... look into it

	switch (loop_sel) {

		case TRIS_NOSIZE_NOORIENT:
			{
				Vector3 scaled_offset[3];
				scaled_offset[0] = _TriVertexLocationOrientationTable[DefaultPointOrientation][0] * DefaultPointSize;
				scaled_offset[1] = _TriVertexLocationOrientationTable[DefaultPointOrientation][1] * DefaultPointSize;
				scaled_offset[2] = _TriVertexLocationOrientationTable[DefaultPointOrientation][2] * DefaultPointSize;
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = scaled_offset[0].X + point_loc->X;
					vertex_loc[0].Y = scaled_offset[0].Y + point_loc->Y;
					vertex_loc[0].Z = scaled_offset[0].Z + point_loc->Z;
					vertex_loc[1].X = scaled_offset[1].X + point_loc->X;
					vertex_loc[1].Y = scaled_offset[1].Y + point_loc->Y;
					vertex_loc[1].Z = scaled_offset[1].Z + point_loc->Z;
					vertex_loc[2].X = scaled_offset[2].X + point_loc->X;
					vertex_loc[2].Y = scaled_offset[2].Y + point_loc->Y;
					vertex_loc[2].Z = scaled_offset[2].Z + point_loc->Z;
					vertex_loc += 3;
					point_loc++;
				}
			}
			break;

		case TRIS_SIZE_NOORIENT:
			{
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = _TriVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[0] + point_loc->X;
					vertex_loc[0].Y = _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[0] + point_loc->Y;
					vertex_loc[0].Z = _TriVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[0] + point_loc->Z;
					vertex_loc[1].X = _TriVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[0] + point_loc->X;
					vertex_loc[1].Y = _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[0] + point_loc->Y;
					vertex_loc[1].Z = _TriVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[0] + point_loc->Z;
					vertex_loc[2].X = _TriVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[0] + point_loc->X;
					vertex_loc[2].Y = _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[0] + point_loc->Y;
					vertex_loc[2].Z = _TriVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[0] + point_loc->Z;
					vertex_loc += 3;
					point_loc++;
					point_size++;
				}
			}
			break;

		case TRIS_NOSIZE_ORIENT:
			{
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = _TriVertexLocationOrientationTable[point_orientation[0]][0].X * DefaultPointSize + point_loc->X;
					vertex_loc[0].Y = _TriVertexLocationOrientationTable[point_orientation[0]][0].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[0].Z = _TriVertexLocationOrientationTable[point_orientation[0]][0].Z * DefaultPointSize + point_loc->Z;
					vertex_loc[1].X = _TriVertexLocationOrientationTable[point_orientation[0]][1].X * DefaultPointSize + point_loc->X;
					vertex_loc[1].Y = _TriVertexLocationOrientationTable[point_orientation[0]][1].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[1].Z = _TriVertexLocationOrientationTable[point_orientation[0]][1].Z * DefaultPointSize + point_loc->Z;
					vertex_loc[2].X = _TriVertexLocationOrientationTable[point_orientation[0]][2].X * DefaultPointSize + point_loc->X;
					vertex_loc[2].Y = _TriVertexLocationOrientationTable[point_orientation[0]][2].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[2].Z = _TriVertexLocationOrientationTable[point_orientation[0]][2].Z * DefaultPointSize + point_loc->Z;
					vertex_loc += 3;
					point_loc++;
					point_orientation++;
				}
			}
			break;

		case TRIS_SIZE_ORIENT:
			{
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = _TriVertexLocationOrientationTable[point_orientation[0]][0].X * point_size[0] + point_loc->X;
					vertex_loc[0].Y = _TriVertexLocationOrientationTable[point_orientation[0]][0].Y * point_size[0] + point_loc->Y;
					vertex_loc[0].Z = _TriVertexLocationOrientationTable[point_orientation[0]][0].Z * point_size[0] + point_loc->Z;
					vertex_loc[1].X = _TriVertexLocationOrientationTable[point_orientation[0]][1].X * point_size[0] + point_loc->X;
					vertex_loc[1].Y = _TriVertexLocationOrientationTable[point_orientation[0]][1].Y * point_size[0] + point_loc->Y;
					vertex_loc[1].Z = _TriVertexLocationOrientationTable[point_orientation[0]][1].Z * point_size[0] + point_loc->Z;
					vertex_loc[2].X = _TriVertexLocationOrientationTable[point_orientation[0]][2].X * point_size[0] + point_loc->X;
					vertex_loc[2].Y = _TriVertexLocationOrientationTable[point_orientation[0]][2].Y * point_size[0] + point_loc->Y;
					vertex_loc[2].Z = _TriVertexLocationOrientationTable[point_orientation[0]][2].Z * point_size[0] + point_loc->Z;
					vertex_loc += 3;
					point_loc++;
					point_orientation++;
					point_size++;
				}
			}
			break;

		case QUADS_NOSIZE_NOORIENT:
			{
				Vector3 scaled_offset[4];
				scaled_offset[0] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][0] * DefaultPointSize;
				scaled_offset[1] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][1] * DefaultPointSize;
				scaled_offset[2] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][2] * DefaultPointSize;
				scaled_offset[3] = _QuadVertexLocationOrientationTable[DefaultPointOrientation][3] * DefaultPointSize;
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = scaled_offset[0].X + point_loc->X;
					vertex_loc[0].Y = scaled_offset[0].Y + point_loc->Y;
					vertex_loc[0].Z = scaled_offset[0].Z + point_loc->Z;
					vertex_loc[1].X = scaled_offset[1].X + point_loc->X;
					vertex_loc[1].Y = scaled_offset[1].Y + point_loc->Y;
					vertex_loc[1].Z = scaled_offset[1].Z + point_loc->Z;
					vertex_loc[2].X = scaled_offset[2].X + point_loc->X;
					vertex_loc[2].Y = scaled_offset[2].Y + point_loc->Y;
					vertex_loc[2].Z = scaled_offset[2].Z + point_loc->Z;
					vertex_loc[3].X = scaled_offset[3].X + point_loc->X;
					vertex_loc[3].Y = scaled_offset[3].Y + point_loc->Y;
					vertex_loc[3].Z = scaled_offset[3].Z + point_loc->Z;
					vertex_loc += 4;
					point_loc++;
				}
			}
			break;

		case QUADS_SIZE_NOORIENT:
			{
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].X * point_size[0] + point_loc->X;
					vertex_loc[0].Y = _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Y * point_size[0] + point_loc->Y;
					vertex_loc[0].Z = _QuadVertexLocationOrientationTable[DefaultPointOrientation][0].Z * point_size[0] + point_loc->Z;
					vertex_loc[1].X = _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].X * point_size[0] + point_loc->X;
					vertex_loc[1].Y = _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Y * point_size[0] + point_loc->Y;
					vertex_loc[1].Z = _QuadVertexLocationOrientationTable[DefaultPointOrientation][1].Z * point_size[0] + point_loc->Z;
					vertex_loc[2].X = _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].X * point_size[0] + point_loc->X;
					vertex_loc[2].Y = _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Y * point_size[0] + point_loc->Y;
					vertex_loc[2].Z = _QuadVertexLocationOrientationTable[DefaultPointOrientation][2].Z * point_size[0] + point_loc->Z;
					vertex_loc[3].X = _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].X * point_size[0] + point_loc->X;
					vertex_loc[3].Y = _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Y * point_size[0] + point_loc->Y;
					vertex_loc[3].Z = _QuadVertexLocationOrientationTable[DefaultPointOrientation][3].Z * point_size[0] + point_loc->Z;
					vertex_loc += 4;
					point_loc++;
					point_size++;
				}
			}
			break;

		case QUADS_NOSIZE_ORIENT:
			{
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = _QuadVertexLocationOrientationTable[point_orientation[0]][0].X * DefaultPointSize + point_loc->X;
					vertex_loc[0].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][0].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[0].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][0].Z * DefaultPointSize + point_loc->Z;
					vertex_loc[1].X = _QuadVertexLocationOrientationTable[point_orientation[0]][1].X * DefaultPointSize + point_loc->X;
					vertex_loc[1].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][1].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[1].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][1].Z * DefaultPointSize + point_loc->Z;
					vertex_loc[2].X = _QuadVertexLocationOrientationTable[point_orientation[0]][2].X * DefaultPointSize + point_loc->X;
					vertex_loc[2].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][2].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[2].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][2].Z * DefaultPointSize + point_loc->Z;
					vertex_loc[3].X = _QuadVertexLocationOrientationTable[point_orientation[0]][3].X * DefaultPointSize + point_loc->X;
					vertex_loc[3].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][3].Y * DefaultPointSize + point_loc->Y;
					vertex_loc[3].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][3].Z * DefaultPointSize + point_loc->Z;
					vertex_loc += 4;
					point_loc++;
					point_orientation++;
				}
			}
			break;

		case QUADS_SIZE_ORIENT:
			{
				if (!Get_Flag(BILLBOARD)) {
					Matrix4 rotMat;
					Matrix4 view;
					DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
					for (int i = 0; i < active_points; i++) {
						D3DXMatrixRotationZ(&(D3DXMATRIX&) rotMat, ((float)point_orientation[0] / 255.0f * 2 * D3DX_PI));
						Vector4 orientedVecX = rotMat * GroundMultiplierX;
						Vector4 orientedVecY = rotMat * GroundMultiplierY;
						float dx0 = (orientedVecX.X + orientedVecY.X) * point_size[0];
						float dy0 = (orientedVecX.Y + orientedVecY.Y) * point_size[0];
						float dx1 = (orientedVecX.X - orientedVecY.X) * point_size[0];
						float dy1 = (orientedVecX.Y - orientedVecY.Y) * point_size[0];
						vertex_loc[0].X = dx0 + point_loc->X;
						vertex_loc[0].Y = dy0 + point_loc->Y;
						vertex_loc[0].Z = point_loc->Z;
						vertex_loc[1].X = dx1 + point_loc->X;
						vertex_loc[1].Y = dy1 + point_loc->Y;
						vertex_loc[1].Z = point_loc->Z;
						vertex_loc[2].X = point_loc->X - dx0;
						vertex_loc[2].Y = point_loc->Y - dy0;
						vertex_loc[2].Z = point_loc->Z;
						vertex_loc[3].X = point_loc->X - dx1;
						vertex_loc[3].Y = point_loc->Y - dy1;
						vertex_loc[3].Z = point_loc->Z;
						Vector4 result;
						result = view * vertex_loc[0];
						vertex_loc[0].X = result.X;
						vertex_loc[0].Y = result.Y;
						vertex_loc[0].Z = result.Z;
						Vector4 result1 = view * vertex_loc[1];
						vertex_loc[1].X = result1.X;
						vertex_loc[1].Y = result1.Y;
						vertex_loc[1].Z = result1.Z;
						Vector4 result2 = view * vertex_loc[2];
						vertex_loc[2].X = result2.X;
						vertex_loc[2].Y = result2.Y;
						vertex_loc[2].Z = result2.Z;
						Vector4 result3 = view * vertex_loc[3];
						vertex_loc[3].X = result3.X;
						vertex_loc[3].Y = result3.Y;
						vertex_loc[3].Z = result3.Z;
						vertex_loc += 4;
						point_loc++;
						point_orientation++;
						point_size++;
					}
				} else {
					for (int i = 0; i < active_points; i++) {
						vertex_loc[0].X = _QuadVertexLocationOrientationTable[point_orientation[0]][0].X * point_size[0] + point_loc->X;
						vertex_loc[0].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][0].Y * point_size[0] + point_loc->Y;
						vertex_loc[0].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][0].Z * point_size[0] + point_loc->Z;
						vertex_loc[1].X = _QuadVertexLocationOrientationTable[point_orientation[0]][1].X * point_size[0] + point_loc->X;
						vertex_loc[1].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][1].Y * point_size[0] + point_loc->Y;
						vertex_loc[1].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][1].Z * point_size[0] + point_loc->Z;
						vertex_loc[2].X = _QuadVertexLocationOrientationTable[point_orientation[0]][2].X * point_size[0] + point_loc->X;
						vertex_loc[2].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][2].Y * point_size[0] + point_loc->Y;
						vertex_loc[2].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][2].Z * point_size[0] + point_loc->Z;
						vertex_loc[3].X = _QuadVertexLocationOrientationTable[point_orientation[0]][3].X * point_size[0] + point_loc->X;
						vertex_loc[3].Y = _QuadVertexLocationOrientationTable[point_orientation[0]][3].Y * point_size[0] + point_loc->Y;
						vertex_loc[3].Z = _QuadVertexLocationOrientationTable[point_orientation[0]][3].Z * point_size[0] + point_loc->Z;
						vertex_loc += 4;
						point_loc++;
						point_orientation++;
						point_size++;
					}
					}
			}
			break;

		// Orientations are ignored for screensize pointgroups
		case SCREEN_NOSIZE_NOORIENT:
		case SCREEN_NOSIZE_ORIENT:
			{
				int xres, yres, bitdepth;
				bool windowed;
				WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);
				float x_scale = (VPXMax - VPXMin) / xres;
				float y_scale = (VPYMax - VPYMin) / yres;
				int size_idx = (DefaultPointSize <= 1.0f) ? 0 : 1;
				Vector3 scaled_locs[3];
				scaled_locs[0].X = x_scale * _ScreenspaceVertexLocationSizeTable[size_idx][0].X;
				scaled_locs[0].Y = y_scale * _ScreenspaceVertexLocationSizeTable[size_idx][0].Y;
				scaled_locs[0].Z = _ScreenspaceVertexLocationSizeTable[size_idx][0].Z;
				scaled_locs[1].X = x_scale * _ScreenspaceVertexLocationSizeTable[size_idx][1].X;
				scaled_locs[1].Y = y_scale * _ScreenspaceVertexLocationSizeTable[size_idx][1].Y;
				scaled_locs[1].Z = _ScreenspaceVertexLocationSizeTable[size_idx][1].Z;
				scaled_locs[2].X = x_scale * _ScreenspaceVertexLocationSizeTable[size_idx][2].X;
				scaled_locs[2].Y = y_scale * _ScreenspaceVertexLocationSizeTable[size_idx][2].Y;
				scaled_locs[2].Z = _ScreenspaceVertexLocationSizeTable[size_idx][2].Z;
				for (int i = 0; i < active_points; i++) {
					vertex_loc[0].X = scaled_locs[0].X + point_loc->X;
					vertex_loc[0].Y = scaled_locs[0].Y + point_loc->Y;
					vertex_loc[0].Z = scaled_locs[0].Z + point_loc->Z;
					vertex_loc[1].X = scaled_locs[1].X + point_loc->X;
					vertex_loc[1].Y = scaled_locs[1].Y + point_loc->Y;
					vertex_loc[1].Z = scaled_locs[1].Z + point_loc->Z;
					vertex_loc[2].X = scaled_locs[2].X + point_loc->X;
					vertex_loc[2].Y = scaled_locs[2].Y + point_loc->Y;
					vertex_loc[2].Z = scaled_locs[2].Z + point_loc->Z;
					vertex_loc += 3;
					point_loc++;
				}
			}
			break;

		case SCREEN_SIZE_NOORIENT:
		case SCREEN_SIZE_ORIENT:
			{
				int xres, yres, bitdepth;
				bool windowed;
				WW3D::Get_Render_Target_Resolution(xres, yres, bitdepth, windowed);
				float x_scale = (VPXMax - VPXMin) / xres;
				float y_scale = (VPYMax - VPYMin) / yres;
				Vector3 scaled_locs[2][3];
				for (int i = 0; i < 2; i++) {
					scaled_locs[i][0].X = x_scale * _ScreenspaceVertexLocationSizeTable[i][0].X;
					scaled_locs[i][0].Y = y_scale * _ScreenspaceVertexLocationSizeTable[i][0].Y;
					scaled_locs[i][0].Z = _ScreenspaceVertexLocationSizeTable[i][0].Z;
					scaled_locs[i][1].X = x_scale * _ScreenspaceVertexLocationSizeTable[i][1].X;
					scaled_locs[i][1].Y = y_scale * _ScreenspaceVertexLocationSizeTable[i][1].Y;
					scaled_locs[i][1].Z = _ScreenspaceVertexLocationSizeTable[i][1].Z;
					scaled_locs[i][2].X = x_scale * _ScreenspaceVertexLocationSizeTable[i][2].X;
					scaled_locs[i][2].Y = y_scale * _ScreenspaceVertexLocationSizeTable[i][2].Y;
					scaled_locs[i][2].Z = _ScreenspaceVertexLocationSizeTable[i][2].Z;
				}
				for (i = 0; i < active_points; i++) {
					int size_idx = (point_size[0] <= 1.0f) ? 0 : 1;
					vertex_loc[0].X = point_loc->X + scaled_locs[size_idx][0].X;
					vertex_loc[0].Y = point_loc->Y + scaled_locs[size_idx][0].Y;
					vertex_loc[0].Z = point_loc->Z + scaled_locs[size_idx][0].Z;
					vertex_loc[1].X = point_loc->X + scaled_locs[size_idx][1].X;
					vertex_loc[1].Y = point_loc->Y + scaled_locs[size_idx][1].Y;
					vertex_loc[1].Z = point_loc->Z + scaled_locs[size_idx][1].Z;
					vertex_loc[2].X = point_loc->X + scaled_locs[size_idx][2].X;
					vertex_loc[2].Y = point_loc->Y + scaled_locs[size_idx][2].Y;
					vertex_loc[2].Z = point_loc->Z + scaled_locs[size_idx][2].Z;
					vertex_loc += 3;
					point_loc++;
					point_size++;
				}
			}
			break;

		default:
			WWASSERT(0);
			break;
	}
}
