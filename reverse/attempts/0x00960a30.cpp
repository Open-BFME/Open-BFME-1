// ?Render@SegLineRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@ABVSphereClass@@PAVVector4@@@Z
// partial score=0.994673674 date=2026-09-11
// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
// RVA 0x00960A30: scratch-free bank; TU-local VB ABI declarations included.
#include "../attempt_support/0x00960a30.inc"
#include "seglinerenderer.h"
#include "ww3d.h"
class CameraClass;
#include "rinfo.h"
#include "dx8wrapper.h"
#include "sortingrenderer.h"
#include "vp.h"
#include "vector3i.h"
#define BFME_RANDOM3CLASS_CTOR_NOINLINE
#include "random.h"
#include "v3_rnd.h"
#include "meshgeometry.h"
#ifndef W3D_ELINE_TILED_TEXTURE_MAP
#define W3D_ELINE_MERGE_INTERSECTIONS 				0x00000001
#define W3D_ELINE_FREEZE_RANDOM						0x00000002
#define W3D_ELINE_DISABLE_SORTING					0x00000004
#define W3D_ELINE_END_CAPS 							0x00000008
#define W3D_ELINE_TEXTURE_MAP_MODE_MASK 			0xFF000000
#define W3D_ELINE_TEXTURE_MAP_MODE_OFFSET 		24
#define W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP		0x00000000
#define W3D_ELINE_UNIFORM_LENGTH_TEXTURE_MAP 	0x00000001
#define W3D_ELINE_TILED_TEXTURE_MAP					0x00000002
#define W3D_ELINE_DEFAULT_BITS	(W3D_ELINE_MERGE_INTERSECTIONS | (W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP << W3D_ELINE_TEXTURE_MAP_MODE_OFFSET))
struct W3dEmitterLinePropertiesStruct
{
uint32			Flags;
uint32			SubdivisionLevel;
float32			NoiseAmplitude;
float32			MergeAbortFactor;
float32			TextureTileFactor;
float32			UPerSec;
float32			VPerSec;
uint32			Reserved[9];
};
#endif
#if MAX_SEGLINE_SUBDIV_LEVELS > 7
#define SEGLINE_CHUNK_SIZE (1 << MAX_SEGLINE_SUBDIV_LEVELS)
#else
#define SEGLINE_CHUNK_SIZE (128)
#endif
#ifdef _INTERNAL
#endif
#define MAX_SEGLINE_POINT_BUFFER_SIZE (1 + SEGLINE_CHUNK_SIZE)
#define MAX_SEGLINE_POLY_BUFFER_SIZE (SEGLINE_CHUNK_SIZE * 2)
void BoxSetTexture(unsigned,TextureBaseClass *&);

// Existing canonical members retained in the renderer translation unit.
SegLineRendererClass::SegLineRendererClass(void) :
		Texture(NULL),
		Shader(ShaderClass::_PresetAdditiveSpriteShader),
		Width(0.0f),
		Color(Vector3(1,1,1)),
		Opacity(1.0f),
		_BFME_Unknown_Member(0.0f),
		SubdivisionLevel(0),
		NoiseAmplitude(0.0f),
		MergeAbortFactor(1.5f),
		TextureTileFactor(1.0f),
		LastUsedSyncTime(WW3D::Get_Sync_Time()),
		CurrentUVOffset(0.0f,0.0f),
		UVOffsetDeltaPerMS(0.0f, 0.0f),
		Bits(DEFAULT_BITS),
		m_vertexBufferSize(0),
		m_vertexBuffer(NULL)
{
	// EMPTY
}


SegLineRendererClass::~SegLineRendererClass(void)
{
	// BFME reorders these vs GeneralsMD: the vertex buffer is freed before the
	// texture reference (verified against the dtor at 0x960030). The texture
	// release is a bare conditional call (no NULL-out), so it tail-jmps.
	delete [] m_vertexBuffer;
	if (Texture) Texture->Release_Ref();
}

void SegLineRendererClass::Init(const W3dEmitterLinePropertiesStruct & props)
{
	// translate the flags
	Set_Merge_Intersections(props.Flags & W3D_ELINE_MERGE_INTERSECTIONS);
	Set_Freeze_Random(props.Flags & W3D_ELINE_FREEZE_RANDOM);
	Set_Disable_Sorting(props.Flags & W3D_ELINE_DISABLE_SORTING);
	Set_End_Caps(props.Flags & W3D_ELINE_END_CAPS);

	int texture_mode = ((props.Flags & W3D_ELINE_TEXTURE_MAP_MODE_MASK) >> W3D_ELINE_TEXTURE_MAP_MODE_OFFSET);
	switch (texture_mode) 
	{
	case W3D_ELINE_UNIFORM_WIDTH_TEXTURE_MAP:
		Set_Texture_Mapping_Mode(UNIFORM_WIDTH_TEXTURE_MAP);
		break;
	case W3D_ELINE_UNIFORM_LENGTH_TEXTURE_MAP:
		Set_Texture_Mapping_Mode(UNIFORM_LENGTH_TEXTURE_MAP);		
		break;
	case W3D_ELINE_TILED_TEXTURE_MAP:
		Set_Texture_Mapping_Mode(TILED_TEXTURE_MAP);		
		break;
	};

	// install all other settings
	Set_Current_Subdivision_Level(props.SubdivisionLevel);
	Set_Noise_Amplitude(props.NoiseAmplitude);
	Set_Merge_Abort_Factor(props.MergeAbortFactor);
	Set_Texture_Tile_Factor(props.TextureTileFactor);
	Set_UV_Offset_Rate(Vector2(props.UPerSec,props.VPerSec));
}



void SegLineRendererClass::Set_Current_UV_Offset(const Vector2 & offset)
{
	CurrentUVOffset = offset;
}

void SegLineRendererClass::Set_Texture_Tile_Factor(float factor)
{
	// Care should be taken to avoid tiling a texture too many times over a single polygon;
	// otherwise performance may be adversely affected.
	///@todo: I raised this number and didn't see much difference on our min-spec. -MW
	const static float MAX_LINE_TILING_FACTOR = 50.0f;
	if (factor > MAX_LINE_TILING_FACTOR) {
		WWDEBUG_SAY(("Texture (%s) Tile Factor (%.2f) too large in SegLineRendererClass!\r\n", Get_Texture()->Get_Texture_Name(), TextureTileFactor));
		factor = MAX_LINE_TILING_FACTOR;
	} else {
		factor = MAX(factor, 0.0f);
	}
	TextureTileFactor = factor;
}

void SegLineRendererClass::Reset_Line(void)
{
	LastUsedSyncTime = WW3D::Get_Sync_Time();
	CurrentUVOffset.Set(0.0f,0.0f);
}




static WWINLINE float SegLineNearestDot(const Vector3 &direction, const Vector3 &point)
{
return *(const volatile float *)&direction.X * point.X
     + *(const volatile float *)&direction.Y * point.Y
     + direction.Z * point.Z;
}
static WWINLINE float SegLineEndpointDot(float px, float py, float pz, float nx, float ny, float nz)
{
return nz*pz + py*ny + px*nx;
}
static __forceinline void NormalizeSegLineLocal(Vector3 &v) {
float z = v.Z;
float y = v.Y;
float x = v.X;
float len2 = x*x + y*y + z*z;
if (len2 != 0.0f) {
float oolen = WWMath::Inv_Sqrt(len2);
v.X *= oolen;
v.Y *= oolen;
v.Z *= oolen;
}
}
static __forceinline void NormalizeSegLineDouble(Vector3 &v) {
float len2 = (float)((double)v.X * v.X + (double)v.Y * v.Y + (double)v.Z * v.Z);
if (len2 != 0.0f) {
float oolen = WWMath::Inv_Sqrt(len2);
v.X *= oolen;
v.Y *= oolen;
v.Z *= oolen;
}
}
static __forceinline Vector3 &ScaleSegLineExpansion(Vector3 &value, float factor)
{
value.X = *(volatile float *)&factor * value.X;
value.Y = *(volatile float *)&factor * value.Y;
value.Z = *(volatile float *)&factor * value.Z;
return value;
}
static WWINLINE void CrossSegLineMerge(const Vector3 &a,const Vector3 &b,Vector3 * set_result)
{
assert(set_result != &a);
set_result->X = (*(const volatile float *)&a.Y * b.Z - a.Z * *(const volatile float *)&b.Y);
set_result->Y = (a.Z * *(const volatile float *)&b.X - *(const volatile float *)&a.X * b.Z);
const volatile float &next_y = b.Y;
const volatile float &prev_y = a.Y;
set_result->Z = (a.X * next_y - prev_y * b.X);
}
static WWINLINE void CrossSegLineStartPlane(const Vector3 &a,const Vector3 &b,Vector3 * set_result)
{
assert(set_result != &a);
set_result->X = (*(const volatile float *)&a.Y * b.Z - a.Z * *(const volatile float *)&b.Y);
set_result->Y = (*(const volatile float *)&a.Z * b.X - *(const volatile float *)&a.X * b.Z);
set_result->Z = (a.X * *(const volatile float *)&b.Y - *(const volatile float *)&a.Y * b.X);
}
static WWINLINE float DotSegLineLastTopSequential(const Vector3 &plane, const Vector3 &point)
{
float zy = *(const volatile float *)&point.Z * plane.Z;
zy += *(const volatile float *)&point.Y * plane.Y;
zy += *(const volatile float *)&plane.X * point.X;
return zy;
}
static WWINLINE float SegLineMergeNextEdgeDot(const Vector3 &direction,const Vector3 &plane)
{
float zy = direction.Z * plane.Z + direction.Y * plane.Y;
zy += direction.X * *(const volatile float *)&plane.X;
return zy;
}
static WWINLINE float SegLineMergeStartDot(const Vector3 &direction,const Vector3 &plane)
{
float zy = direction.Z * plane.Z + direction.Y * plane.Y;
zy += *(const volatile float *)&direction.X * plane.X;
return zy;
}
static WWINLINE void ScaleSegLineFirstTop(const Vector3 &plane, float factor, Vector3 &scaled, float &scaled_y)
{
scaled.Z = factor * plane.Z;
scaled_y = factor * plane.Y;
factor *= plane.X;
scaled.X = factor;
}
static WWINLINE Vector3 SubtractSegLineFirstTop(const Vector3 &point, const Vector3 &projected, const float &projected_y)
{
return Vector3(
point.X - projected.X,
point.Y - projected_y,
point.Z - projected.Z
);
}

static WWINLINE Vector3 SubtractSegLineTopPlane(const Vector3 &a,const Vector3 &b)
{
return Vector3(
    a.X-b.X,
    a.Y-b.Y,
    *(const volatile float *)&a.Z-b.Z
);
}
static WWINLINE float DotSegLineFirstTopSequenced(const Vector3 &plane, const Vector3 &point)
{
float zy = *(const volatile float *)&plane.Z * point.Z;
zy += *(const volatile float *)&point.Y * plane.Y;
zy += *(const volatile float *)&point.X * plane.X;
return zy;
}
static __forceinline void NormalizeMerge(Vector3 &v)
{
float len2 = (*(const volatile float *)&v.Z*v.Z + v.Y*v.Y) + v.X*v.X;
if (len2 != 0.0f) {
float oolen = WWMath::Inv_Sqrt(len2);
v.X *= oolen;
v.Y *= oolen;
v.Z *= oolen;
}
}
static WWINLINE Vector3 AddSegLineMergePlaneNextX(const Vector3 &a, const Vector3 &b)
{
return Vector3(
a.X+*(const volatile float *)&b.X,
a.Y+b.Y,
a.Z+b.Z
);
}
static WWINLINE float DotSegLineTopPlaneYXZ(const Vector3 &plane, const Vector3 &point)
{
float yx = *(const volatile float *)&plane.Y*point.Y;
yx += *(const volatile float *)&plane.X*point.X;
yx += plane.Z*point.Z;
return yx;
}
static WWINLINE Vector3 AddSegLineTopPlane(const Vector3 &a,const Vector3 &b)
{
return Vector3(*(const volatile float *)&a.X+b.X, *(const volatile float *)&a.Y+b.Y, *(const volatile float *)&b.Z+a.Z);
}
static WWINLINE float SegLineTopSignSequential(const Vector3 &direction, const Vector3 &midpoint)
{
float xz = *(const volatile float *)&direction.X * midpoint.X;
xz += *(const volatile float *)&midpoint.Z * direction.Z;
xz += *(const volatile float *)&direction.Y * midpoint.Y;
return xz;
}
static WWINLINE float SegLineBottomSignDot(const Vector3 &direction,const Vector3 &midpoint)
{
float yz = *(const volatile float *)&direction.Y * midpoint.Y;
yz += *(const volatile float *)&midpoint.Z * direction.Z;
yz += *(const volatile float *)&midpoint.X * direction.X;
return yz;
}
static WWINLINE void NormalizeSegLineBottomPlane(Vector3 &plane)
{
float len2 = (*(const volatile float *)&plane.X * plane.X + plane.Z*plane.Z) + plane.Y*plane.Y;
if (len2 != 0.0f) {
float inverse = WWMath::Inv_Sqrt(len2);
plane.X *= inverse;
plane.Y *= inverse;
plane.Z *= inverse;
}
}
static WWINLINE float SegLineStartSignXZ(const Vector3 &plane, const Vector3 &direction)
{
return (*(const volatile float *)&plane.X * direction.X + plane.Z * direction.Z) + *(const volatile float *)&plane.Y * direction.Y;
}
static WWINLINE float SegLineBottomPlaneClassification(const Vector3 &prev, const Vector3 &next)
{
float yz = *(const volatile float *)&prev.Y * next.Y;
yz += *(const volatile float *)&prev.Z * next.Z;
yz += *(const volatile float *)&prev.X * next.X;
return yz;
}
static WWINLINE void SegLinePreviousPlaneCross(const Vector3 &a, const Vector3 &b, Vector3 *out)
{
assert(out != &a);
out->X = a.Y * *(const volatile float *)&b.Z - a.Z * *(const volatile float *)&b.Y;
out->Y = *(const volatile float *)&a.Z * b.X - a.X * *(const volatile float *)&b.Z;
out->Z = a.X * *(const volatile float *)&b.Y - *(const volatile float *)&a.Y * b.X;
}
static WWINLINE void SegLineCurrentPlaneCross(const Vector3 &a, const Vector3 &b, Vector3 *out)
{
assert(out != &a);
out->X = *(const volatile float *)&a.Y * b.Z - *(const volatile float *)&a.Z * b.Y;
out->Y = *(const volatile float *)&a.Z * b.X - a.X * *(const volatile float *)&b.Z;
out->Z = a.X * *(const volatile float *)&b.Y - *(const volatile float *)&a.Y * b.X;
}
static WWINLINE float SegLineEarlyNearestDot(const Vector3 &direction, const Vector3 &point)
{
float dot = *(const volatile float *)&direction.X * point.X;
dot += *(const volatile float *)&direction.Y * point.Y;
return dot + *(const volatile float *)&point.Z * direction.Z;
}
static WWINLINE float DotSegLineLastBottomSequential(const Vector3 &plane, const Vector3 &point)
{
float zy = *(const volatile float *)&plane.Z * point.Z;
zy += *(const volatile float *)&plane.Y * point.Y;
zy += *(const volatile float *)&plane.X * point.X;
return zy;
}
static WWINLINE void CrossSegLineBottomDirection(const Vector3 &a, const Vector3 &b, Vector3 *set_result)
{
assert(set_result != &a);
set_result->X = (a.Y * *(const volatile float *)&b.Z - *(const volatile float *)&a.Z * b.Y);
set_result->Y = (*(const volatile float *)&a.Z * b.X - a.X * *(const volatile float *)&b.Z);
set_result->Z = (*(const volatile float *)&a.X * b.Y - *(const volatile float *)&a.Y * b.X);
}
static WWINLINE void SegLineTopDirectionCross(const Vector3 &a, const Vector3 &b, Vector3 *out)
{
assert(out != &a);
out->X = a.Y * *(const volatile float *)&b.Z - *(const volatile float *)&a.Z * b.Y;
out->Y = a.Z * *(const volatile float *)&b.X - a.X * *(const volatile float *)&b.Z;
out->Z = *(const volatile float *)&a.X * b.Y - a.Y * *(const volatile float *)&b.X;
}
static WWINLINE Vector3 AddSegLineBottomPlane(const Vector3 &a, const Vector3 &b)
{
return Vector3(*(const volatile float *)&a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}
static WWINLINE Vector3 SubtractSegLineBottomPlane(const Vector3 &a, const Vector3 &b)
{
return Vector3(*(const volatile float *)&a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}
void SegLineRendererClass::Render
(	
RenderInfoClass & rinfo,
const Matrix3D & transform,
unsigned int num_points,
Vector3 * points,
const SphereClass & obj_sphere,
Vector4 * rgbas
)
{
Matrix4x4 view;
DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
Matrix4x4 identity(true);
DX8Wrapper::Set_Transform(D3DTS_WORLD,identity);	
DX8Wrapper::Set_Transform(D3DTS_VIEW,identity);	
unsigned int delta = WW3D::Get_Sync_Time() - LastUsedSyncTime;
float del = (float)delta;
Vector2 uv_offset = CurrentUVOffset + UVOffsetDeltaPerMS * del;
uv_offset.X = uv_offset.X - floorf(uv_offset.X);
uv_offset.Y = uv_offset.Y - floorf(uv_offset.Y);
CurrentUVOffset = uv_offset;
LastUsedSyncTime = WW3D::Get_Sync_Time();
TextureMapMode map_mode = Get_Texture_Mapping_Mode();
const float parallel_factor = 0.9f;
const unsigned int chunk_capacity = (SEGLINE_CHUNK_SIZE >> SubdivisionLevel) + 1;
unsigned int chunk_size = chunk_capacity;
if (chunk_size > num_points) chunk_size = num_points;
for (unsigned int chidx = 0; chidx < num_points - 1; chidx += (chunk_size - 1)) {
unsigned int point_cnt = num_points - chidx;
point_cnt = MIN(point_cnt, chunk_size);
unsigned int pidx;	
unsigned int sidx;	
unsigned int iidx;	
Vector3 xformed_pts[MAX_SEGLINE_POINT_BUFFER_SIZE];
Matrix3D view2(	view[0].X,view[0].Y,view[0].Z,view[0].W,
view[1].X,view[1].Y,view[1].Z,view[1].W,
view[2].X,view[2].Y,view[2].Z,view[2].W);
#ifdef ALLOW_TEMPORARIES
Matrix3D modelview=view2*transform;
#else
Matrix3D modelview;
modelview.mul(view2, transform);
#endif
VectorProcessorClass::Transform(&xformed_pts[0],
&points[chidx], modelview, point_cnt);
float base_tex_v[MAX_SEGLINE_POINT_BUFFER_SIZE];
float u_values[2];
switch (map_mode) {
case UNIFORM_WIDTH_TEXTURE_MAP:
for (pidx = 0; pidx < point_cnt; pidx++) {
base_tex_v[pidx] = 0.0f;
}
u_values[0] = 0.0f;
u_values[1] = 1.0f;
break;
case UNIFORM_LENGTH_TEXTURE_MAP:
for (pidx = 0; pidx < point_cnt; pidx++) {
base_tex_v[pidx] = (float)(pidx + chidx) * TextureTileFactor;
}
u_values[0] = 0.0f;
u_values[1] = 0.0f;
break;
case TILED_TEXTURE_MAP: ;
default:
for (pidx = 0; pidx < point_cnt; pidx++) {
base_tex_v[pidx] = (float)(pidx + chidx) * TextureTileFactor;
}
u_values[0] = 0.0f;
u_values[1] = 1.0f;
break;
}
Vector3 xformed_subdiv_pts[MAX_SEGLINE_POINT_BUFFER_SIZE];
float subdiv_tex_v[MAX_SEGLINE_POINT_BUFFER_SIZE];
Vector4 subdiv_rgbas[MAX_SEGLINE_POINT_BUFFER_SIZE];
unsigned int sub_point_cnt;
Vector4 *rgbasPointer = rgbas ? &rgbas[ chidx ] : NULL;
subdivision_util(point_cnt, xformed_pts, base_tex_v, &sub_point_cnt, xformed_subdiv_pts, subdiv_tex_v, rgbasPointer, subdiv_rgbas);
Vector3 *points = xformed_subdiv_pts;
float *tex_v = subdiv_tex_v;
Vector4 *diffuse = subdiv_rgbas;
point_cnt = sub_point_cnt;
enum SegmentEdge {
FIRST_EDGE     = 0,	
TOP_EDGE			= 0,	
BOTTOM_EDGE		= 1,	
MAX_EDGE			= 1,	
NUM_EDGES		= 2	
};
bool switch_edges = false;
struct LineSegment {
Vector3	StartPlane;
Vector3	EdgePlane[NUM_EDGES];
};
LineSegment segment[MAX_SEGLINE_POINT_BUFFER_SIZE + 1];
struct LineSegmentIntersection  {
unsigned int	PointCount;			
unsigned int	NextSegmentID;		
Vector3			Direction;			
Vector3			Point;				
float				TexV;					
Vector4			RGBA;					
bool				Fold;					
bool				Parallel;			
};
float radius = Width * 0.5f;
LineSegmentIntersection intersection[MAX_SEGLINE_POINT_BUFFER_SIZE + 1][NUM_EDGES];
for (sidx = 1; sidx < point_cnt; sidx++) {	
Vector3 &curr_point = points[sidx - 1];
Vector3 &next_point = points[sidx];
if (Equal_Within_Epsilon(curr_point, next_point, 0.0001f))
{
next_point.X += 0.001f;
}
Vector3 &segdir = segment[sidx].StartPlane;
segdir = next_point - curr_point;
segdir.Normalize();
Vector3 nearest = curr_point + segdir * -SegLineEarlyNearestDot(segdir, curr_point);
Vector3 offset;
Vector3::Cross_Product(segdir, nearest, &offset);
offset.Normalize();
Vector3 top = curr_point + offset * radius;
Vector3 bottom = curr_point + offset * -radius;
Vector3 top_normal;
Vector3::Cross_Product(top, segdir, &top_normal);
top_normal.Normalize();
segment[sidx].EdgePlane[TOP_EDGE] = top_normal;
Vector3 bottom_normal;
Vector3::Cross_Product(segdir, bottom, &bottom_normal);
bottom_normal.Normalize();
segment[sidx].EdgePlane[BOTTOM_EDGE] = bottom_normal;
if (sidx > 1) {
Vector3 prev_plane;
SegLinePreviousPlaneCross(points[sidx - 2], curr_point, &prev_plane);
prev_plane.Normalize();
Vector3 curr_plane;
SegLineCurrentPlaneCross(curr_point, next_point, &curr_plane);
curr_plane.Normalize();
if (Vector3::Dot_Product(prev_plane, curr_plane) < 0.0f) {
switch_edges = !switch_edges;
intersection[sidx][TOP_EDGE].Fold = true;
intersection[sidx][BOTTOM_EDGE].Fold = true;
} else {
intersection[sidx][TOP_EDGE].Fold = false;
intersection[sidx][BOTTOM_EDGE].Fold = false;
}
}
if (switch_edges) {
segment[sidx].EdgePlane[TOP_EDGE] = -bottom_normal;
segment[sidx].EdgePlane[BOTTOM_EDGE] = -top_normal;
}
}
unsigned int numsegs = point_cnt - 1;	
unsigned int num_intersections[NUM_EDGES];
num_intersections[TOP_EDGE] = point_cnt;
num_intersections[BOTTOM_EDGE] = point_cnt;
intersection[0][TOP_EDGE].PointCount = 0;				
intersection[0][TOP_EDGE].NextSegmentID = 0;			
intersection[0][TOP_EDGE].Direction.Set(1,0,0);		
intersection[0][TOP_EDGE].Point.Set(0,0,0);			
intersection[0][TOP_EDGE].TexV = 0.0f;					
intersection[0][TOP_EDGE].RGBA.Set(0, 0, 0, 0);		
intersection[0][TOP_EDGE].Fold = true;					
intersection[0][TOP_EDGE].Parallel = false;			
intersection[0][BOTTOM_EDGE].PointCount = 0;			
intersection[0][BOTTOM_EDGE].NextSegmentID = 0;		
intersection[0][BOTTOM_EDGE].Point.Set(0,0,0);		
intersection[0][BOTTOM_EDGE].TexV = 0.0f;				
intersection[0][BOTTOM_EDGE].RGBA.Set(0, 0, 0, 0); 
intersection[0][BOTTOM_EDGE].Direction.Set(1,0,0);	
intersection[0][BOTTOM_EDGE].Fold = true;				
intersection[0][BOTTOM_EDGE].Parallel = false;		
intersection[1][TOP_EDGE].PointCount = 1;
intersection[1][TOP_EDGE].NextSegmentID = 1;
intersection[1][TOP_EDGE].Point = points[0];
intersection[1][TOP_EDGE].TexV = tex_v[0];
intersection[1][TOP_EDGE].RGBA = diffuse[0];
intersection[1][TOP_EDGE].Fold = true;
intersection[1][TOP_EDGE].Parallel = false;
intersection[1][BOTTOM_EDGE].PointCount = 1;
intersection[1][BOTTOM_EDGE].NextSegmentID = 1;
intersection[1][BOTTOM_EDGE].Point = points[0];
intersection[1][BOTTOM_EDGE].TexV = tex_v[0];
intersection[1][BOTTOM_EDGE].RGBA = diffuse[0];
intersection[1][BOTTOM_EDGE].Fold = true;
intersection[1][BOTTOM_EDGE].Parallel = false;
Vector3 top;
Vector3 bottom;
Vector3 &first_point = points[0];
Vector3 *first_plane = &(segment[1].EdgePlane[0]);
{
Vector3 projected_plane;
float projected_y;
ScaleSegLineFirstTop(first_plane[TOP_EDGE], DotSegLineFirstTopSequenced(first_plane[TOP_EDGE], first_point), projected_plane, projected_y);
top = SubtractSegLineFirstTop(first_point, projected_plane, projected_y);
}
top.Normalize();
intersection[1][TOP_EDGE].Direction = top;
bottom = first_point - first_plane[BOTTOM_EDGE] * DotSegLineFirstTopSequenced(first_plane[BOTTOM_EDGE], first_point);
bottom.Normalize();
intersection[1][BOTTOM_EDGE].Direction = bottom;
Vector3 segdir = points[1] - points[0];
segdir.Normalize();	
Vector3 start_pl;
Vector3::Cross_Product(top, bottom, &start_pl);
NormalizeSegLineBottomPlane(start_pl);
float dp = SegLineStartSignXZ(start_pl, segdir);
if (dp > 0.0f) {
segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = start_pl;
} else {
segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = -start_pl;
}
segment[1].StartPlane = segment[0].StartPlane;
unsigned int last_isec = num_intersections[TOP_EDGE]; 
intersection[last_isec][TOP_EDGE].PointCount = 1;
intersection[last_isec][TOP_EDGE].NextSegmentID = numsegs + 1; 
intersection[last_isec][TOP_EDGE].Point = points[point_cnt - 1];
intersection[last_isec][TOP_EDGE].TexV = tex_v[point_cnt - 1];
intersection[last_isec][TOP_EDGE].RGBA = diffuse[point_cnt - 1];
intersection[last_isec][TOP_EDGE].Fold = true;
intersection[last_isec][TOP_EDGE].Parallel = false;
intersection[last_isec][BOTTOM_EDGE].PointCount = 1;
intersection[last_isec][BOTTOM_EDGE].NextSegmentID = numsegs + 1;
intersection[last_isec][BOTTOM_EDGE].Point = points[point_cnt - 1];
intersection[last_isec][BOTTOM_EDGE].TexV = tex_v[point_cnt - 1];
intersection[last_isec][BOTTOM_EDGE].RGBA = diffuse[point_cnt - 1];
intersection[last_isec][BOTTOM_EDGE].Fold = true;
intersection[last_isec][BOTTOM_EDGE].Parallel = false;
Vector3 &last_point = points[point_cnt - 1];
Vector3 *last_plane = &(segment[numsegs].EdgePlane[0]);
top = last_point - last_plane[TOP_EDGE] * DotSegLineLastTopSequential(last_plane[TOP_EDGE], last_point);
top.Normalize();
intersection[last_isec][TOP_EDGE].Direction = top;
bottom = last_point - last_plane[BOTTOM_EDGE] * DotSegLineLastBottomSequential(last_plane[BOTTOM_EDGE], last_point);
bottom.Normalize();
intersection[last_isec][BOTTOM_EDGE].Direction = bottom;
segdir = points[point_cnt - 1] - points[point_cnt - 2];
segdir.Normalize();	
Vector3::Cross_Product(top, bottom, &start_pl);
NormalizeSegLineBottomPlane(start_pl);
dp = SegLineStartSignXZ(start_pl, segdir);
if (dp > 0.0f) {
segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = start_pl;
} else {
segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = -start_pl;
}
float vdp;
for (iidx = 2; iidx < num_intersections[TOP_EDGE]; iidx++) {
Vector3 &midpoint = points[iidx - 1];
float mid_tex_v = tex_v[iidx - 1];
Vector4 mid_diffuse = diffuse[iidx - 1];
intersection[iidx][TOP_EDGE].PointCount = 1;
intersection[iidx][TOP_EDGE].NextSegmentID = iidx;
intersection[iidx][TOP_EDGE].Point = midpoint;
intersection[iidx][TOP_EDGE].TexV = mid_tex_v;
intersection[iidx][TOP_EDGE].RGBA = mid_diffuse;
intersection[iidx][BOTTOM_EDGE].PointCount = 1;
intersection[iidx][BOTTOM_EDGE].NextSegmentID = iidx;
intersection[iidx][BOTTOM_EDGE].Point = midpoint;
intersection[iidx][BOTTOM_EDGE].TexV = mid_tex_v;
intersection[iidx][BOTTOM_EDGE].RGBA = mid_diffuse;
vdp = SegLineTopSignSequential(segment[iidx - 1].EdgePlane[TOP_EDGE], segment[iidx].EdgePlane[TOP_EDGE]);
if (fabs(vdp) < parallel_factor) {
SegLineTopDirectionCross(segment[iidx - 1].EdgePlane[TOP_EDGE], segment[iidx].EdgePlane[TOP_EDGE],
&(intersection[iidx][TOP_EDGE].Direction));
NormalizeSegLineLocal(intersection[iidx][TOP_EDGE].Direction);
if (SegLineTopSignSequential(intersection[iidx][TOP_EDGE].Direction, midpoint) < 0.0f) {
intersection[iidx][TOP_EDGE].Direction = -intersection[iidx][TOP_EDGE].Direction;
}
intersection[iidx][TOP_EDGE].Parallel = false;
} else {
Vector3 pl;
if (vdp > 0.0f) {
pl = AddSegLineTopPlane(segment[iidx - 1].EdgePlane[TOP_EDGE], segment[iidx].EdgePlane[TOP_EDGE]);
} else {
pl = SubtractSegLineTopPlane(segment[iidx - 1].EdgePlane[TOP_EDGE], segment[iidx].EdgePlane[TOP_EDGE]);
}
pl.Normalize();
intersection[iidx][TOP_EDGE].Direction = midpoint - pl * DotSegLineTopPlaneYXZ(pl, midpoint);
NormalizeSegLineLocal(intersection[iidx][TOP_EDGE].Direction);
intersection[iidx][TOP_EDGE].Parallel = true;
}
vdp = SegLineBottomPlaneClassification(segment[iidx - 1].EdgePlane[BOTTOM_EDGE], segment[iidx].EdgePlane[BOTTOM_EDGE]);
if (fabs(vdp) < parallel_factor) {
CrossSegLineBottomDirection(segment[iidx - 1].EdgePlane[BOTTOM_EDGE], segment[iidx].EdgePlane[BOTTOM_EDGE],
&(intersection[iidx][BOTTOM_EDGE].Direction));
NormalizeSegLineLocal(intersection[iidx][BOTTOM_EDGE].Direction);
if (SegLineBottomSignDot(intersection[iidx][BOTTOM_EDGE].Direction, midpoint) < 0.0f) {
intersection[iidx][BOTTOM_EDGE].Direction = -intersection[iidx][BOTTOM_EDGE].Direction;
}
intersection[iidx][BOTTOM_EDGE].Parallel = false;
} else {
Vector3 pl;
if (vdp > 0.0f) {
pl = AddSegLineBottomPlane(segment[iidx - 1].EdgePlane[BOTTOM_EDGE], segment[iidx].EdgePlane[BOTTOM_EDGE]);
} else {
pl = SubtractSegLineBottomPlane(segment[iidx - 1].EdgePlane[BOTTOM_EDGE], segment[iidx].EdgePlane[BOTTOM_EDGE]);
}
NormalizeSegLineBottomPlane(pl);
intersection[iidx][BOTTOM_EDGE].Direction = midpoint - pl * DotSegLineTopPlaneYXZ(pl, midpoint);
NormalizeSegLineDouble(intersection[iidx][BOTTOM_EDGE].Direction);
intersection[iidx][BOTTOM_EDGE].Parallel = true;
}
CrossSegLineStartPlane(intersection[iidx][TOP_EDGE].Direction, intersection[iidx][BOTTOM_EDGE].Direction, &start_pl);
NormalizeSegLineBottomPlane(start_pl);
dp = SegLineStartSignXZ(start_pl, segment[iidx].StartPlane);
if (dp > 0.0f) {
segment[iidx].StartPlane = start_pl;
} else {
segment[iidx].StartPlane = -start_pl;
}
}	
if (Is_Merge_Intersections()) {
unsigned int iidx_r;
unsigned int iidx_w;
bool merged = true;
while (merged) {
merged = false;
SegmentEdge edge;
for (edge = FIRST_EDGE; edge <= MAX_EDGE; edge = (SegmentEdge)((int)edge + 1)) {
unsigned int num_isects = num_intersections[edge];	
for (iidx_r = 1, iidx_w = 1; iidx_r < num_isects; iidx_r++, iidx_w++) {
LineSegmentIntersection *curr_int = &(intersection[iidx_r][edge]);
LineSegmentIntersection *next_int = &(intersection[iidx_r + 1][edge]);
LineSegmentIntersection *write_int = &(intersection[iidx_w][edge]);
LineSegmentIntersection *prev_int = &(intersection[iidx_w - 1][edge]);
LineSegment *next_seg = &(segment[next_int->NextSegmentID]);
LineSegment *curr_seg = &(segment[curr_int->NextSegmentID]);
LineSegment *prev_seg = &(segment[prev_int->NextSegmentID]);
while	(	(!next_int->Fold &&
(SegLineMergeStartDot(curr_int->Direction, next_seg->StartPlane) > 0.0f) &&
(SegLineMergeNextEdgeDot(curr_int->Direction, next_seg->EdgePlane[edge]) > 0.0f )) ||
(!curr_int->Fold &&
(Vector3::Dot_Product(next_int->Direction, -curr_seg->StartPlane) > 0.0f) &&
(SegLineMergeStartDot(next_int->Direction, prev_seg->EdgePlane[edge]) > 0.0f )) ) {
unsigned int new_count = curr_int->PointCount + next_int->PointCount;
float oo_new_count = 1.0f / (float)new_count;
float curr_factor = oo_new_count * (float)curr_int->PointCount;
float next_factor = oo_new_count * (float)curr_int->PointCount;
Vector3 new_point = curr_int->Point * curr_factor + next_int->Point * next_factor;
float new_tex_v = curr_int->TexV * curr_factor + next_int->TexV * next_factor;
Vector4 new_diffuse = curr_int->RGBA * curr_factor + next_int->RGBA * next_factor;
bool new_parallel;
Vector3 new_direction;
vdp = Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);
if (fabs(vdp) < parallel_factor) {
CrossSegLineMerge(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge], &new_direction);
new_direction.Normalize();
if (Vector3::Dot_Product(new_direction, new_point) < 0.0f) {
new_direction = -new_direction;
}
new_parallel = false;
} else {
Vector3 pl;
if (vdp > 0.0f) {
pl = AddSegLineMergePlaneNextX(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);
} else {
pl = prev_seg->EdgePlane[edge] - next_seg->EdgePlane[edge];
}
NormalizeMerge(pl);
if (curr_int->Parallel) {
new_direction = new_direction - pl * Vector3::Dot_Product(pl, new_direction);
new_direction.Normalize();
} else {
Vector3::Cross_Product(curr_seg->EdgePlane[edge], pl, &new_direction);
new_direction.Normalize();
}
new_parallel = true;
}
if (MergeAbortFactor > 0.0f) {
float abort_dist = radius * MergeAbortFactor;
float abort_dist2 = abort_dist * abort_dist;
Vector3 diff_curr = curr_int->Point -
new_direction * Vector3::Dot_Product(curr_int->Point, new_direction);
if (diff_curr.Length2() > abort_dist2) break;
Vector3 next_curr = next_int->Point -
new_direction * Vector3::Dot_Product(next_int->Point, new_direction);
if (next_curr.Length2() > abort_dist2) break;
}
merged = true;
curr_int->Direction = new_direction;
curr_int->Parallel = new_parallel;
curr_int->Point = new_point;
curr_int->TexV = new_tex_v;
curr_int->RGBA = new_diffuse;
curr_int->PointCount = new_count;
curr_int->NextSegmentID = next_int->NextSegmentID;
curr_int->Fold = curr_int->Fold || next_int->Fold;
num_intersections[edge]--;
iidx_r++;
if (iidx_r == num_isects) {
break;
}
next_int = &(intersection[iidx_r + 1][edge]);
next_seg = &(segment[next_int->NextSegmentID]);
}	
write_int->PointCount		= curr_int->PointCount;
write_int->NextSegmentID	= curr_int->NextSegmentID;
write_int->Point				= curr_int->Point;
write_int->TexV				= curr_int->TexV;
write_int->RGBA				= curr_int->RGBA;
write_int->Direction			= curr_int->Direction;
write_int->Fold				= curr_int->Fold;
}	
if (iidx_r == num_isects) {
LineSegmentIntersection *write_int = &(intersection[iidx_w][edge]);
LineSegmentIntersection *curr_int = &(intersection[iidx_r][edge]);
write_int->PointCount		= curr_int->PointCount;
write_int->NextSegmentID	= curr_int->NextSegmentID;
write_int->Point				= curr_int->Point;
write_int->TexV				= curr_int->TexV;
write_int->RGBA				= curr_int->RGBA;
write_int->Direction			= curr_int->Direction;
write_int->Fold				= curr_int->Fold;
}
#ifdef ENABLE_WWDEBUGGING
unsigned int total_cnt = 0;
for (unsigned int nidx = 0; nidx <= num_intersections[edge]; nidx++) {
total_cnt += intersection[nidx][edge].PointCount;
}
assert(total_cnt == point_cnt);
#endif
}	
}	
}	
unsigned int vnum = num_intersections[TOP_EDGE] + num_intersections[BOTTOM_EDGE];		
VertexFormatXYZDUV1 *vArray = getVertexBuffer(vnum);
TriIndex v_index_array[MAX_SEGLINE_POLY_BUFFER_SIZE];
unsigned int vidx = 0;
unsigned int tidx = 0;
Vector3 &top_dir = intersection[1][TOP_EDGE].Direction;
top = top_dir * SegLineNearestDot(points[0], top_dir);
Vector3 &bottom_dir = intersection[1][BOTTOM_EDGE].Direction;
bottom = bottom_dir * SegLineNearestDot(points[0], bottom_dir);
vArray[vidx].x = top.X;
vArray[vidx].y = top.Y;
vArray[vidx].z = top.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[1][TOP_EDGE].RGBA);
vArray[vidx].u1 = u_values[0] + uv_offset.X;
vArray[vidx].v1 = intersection[1][TOP_EDGE].TexV + uv_offset.Y;
vidx++;
vArray[vidx].x = bottom.X;
vArray[vidx].y = bottom.Y;
vArray[vidx].z = bottom.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[1][BOTTOM_EDGE].RGBA);
vArray[vidx].u1 = u_values[1] + uv_offset.X;
vArray[vidx].v1 = intersection[1][BOTTOM_EDGE].TexV + uv_offset.Y;
vidx++;
unsigned int last_top_vidx = 0;
unsigned int last_bottom_vidx = 1;
unsigned int top_int_idx = 1;		
unsigned int bottom_int_idx = 1;	
pidx = 0;
unsigned int residual_top_points = intersection[1][TOP_EDGE].PointCount;
unsigned int residual_bottom_points = intersection[1][BOTTOM_EDGE].PointCount;
unsigned int delta = MIN(residual_top_points, residual_bottom_points) - 1;
residual_top_points -= delta;
residual_bottom_points -= delta;
pidx += delta;
for (; ; ) {
if (residual_top_points == 1 && residual_bottom_points == 1) {
v_index_array[tidx].I = last_top_vidx;
v_index_array[tidx].J = last_bottom_vidx;
v_index_array[tidx].K = vidx;
tidx++;
v_index_array[tidx].I = last_bottom_vidx;
v_index_array[tidx].J = vidx + 1;
v_index_array[tidx].K = vidx;
tidx++;
last_top_vidx = vidx;
last_bottom_vidx = vidx + 1;
top_int_idx++;
bottom_int_idx++;
residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;
pidx++;
Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
top = top_dir * DotSegLineLastTopSequential(top_dir, points[pidx]);
Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
bottom = bottom_dir * DotSegLineLastTopSequential(bottom_dir, points[pidx]);
if (_BFME_Unknown_Member > 0.0f) { Vector3 delta = top - bottom; ScaleSegLineExpansion(delta, _BFME_Unknown_Member); top += delta; bottom -= delta; }
vArray[vidx].x = top.X;
vArray[vidx].y = top.Y;
vArray[vidx].z = top.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[top_int_idx][TOP_EDGE].RGBA);
vArray[vidx].u1 = u_values[0] + uv_offset.X;
vArray[vidx].v1 = intersection[top_int_idx][TOP_EDGE].TexV + uv_offset.Y;
vidx++;
vArray[vidx].x = bottom.X;
vArray[vidx].y = bottom.Y;
vArray[vidx].z = bottom.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[bottom_int_idx][BOTTOM_EDGE].RGBA);
vArray[vidx].u1 = u_values[1] + uv_offset.X;
vArray[vidx].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV + uv_offset.Y;
vidx++;
} else {
if (residual_top_points > 1) {
v_index_array[tidx].I = last_top_vidx;
v_index_array[tidx].J = last_bottom_vidx;
v_index_array[tidx].K = vidx;
tidx++;
last_bottom_vidx = vidx;
residual_top_points--;
bottom_int_idx++;
residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;
pidx++;
Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
bottom = bottom_dir * Vector3::Dot_Product(points[pidx], bottom_dir);
vArray[vidx].x = bottom.X;
vArray[vidx].y = bottom.Y;
vArray[vidx].z = bottom.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[bottom_int_idx][BOTTOM_EDGE].RGBA);
vArray[vidx].u1 = u_values[1] + uv_offset.X;
vArray[vidx].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV + uv_offset.Y;					
vidx++;
} else {
v_index_array[tidx].I = last_top_vidx;
v_index_array[tidx].J = last_bottom_vidx;
v_index_array[tidx].K = vidx;
tidx++;
last_top_vidx = vidx;
residual_bottom_points--;
top_int_idx++;
residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
pidx++;
Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
top = top_dir * Vector3::Dot_Product(points[pidx], top_dir);
vArray[vidx].x = top.X;
vArray[vidx].y = top.Y;
vArray[vidx].z = top.Z;
vArray[vidx].diffuse = DX8Wrapper::Convert_Color(intersection[top_int_idx][TOP_EDGE].RGBA);
vArray[vidx].u1 = u_values[0] + uv_offset.X;
vArray[vidx].v1 = intersection[top_int_idx][TOP_EDGE].TexV + uv_offset.Y;
vidx++;
}
}
delta = MIN(residual_top_points, residual_bottom_points) - 1;
residual_top_points -= delta;
residual_bottom_points -= delta;
pidx += delta;
if (	(top_int_idx >= num_intersections[TOP_EDGE] && residual_top_points == 1) ||
(bottom_int_idx >= num_intersections[BOTTOM_EDGE] && residual_bottom_points == 1)) {
assert(top_int_idx == num_intersections[TOP_EDGE]);
assert(bottom_int_idx == num_intersections[BOTTOM_EDGE]);
assert(pidx == point_cnt - 1);
break;
}
}		
unsigned int rgba;
rgba=DX8Wrapper::Convert_Color(Color,Opacity);
bool rgba_all=(rgba==0xFFFFFFFF);
bool sorting = (!Is_Sorting_Disabled()) && (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO && Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE);
ShaderClass shader = Shader;
// Retail BFME cull bit, confirmed by matched PointGroupClass::prepare_shader.
reinterpret_cast<unsigned int &>(shader) &= ~0x100000u;
VertexMaterialClass *mat;		
if (!rgba_all || (rgba != 0) ) {
// Retail BFME primary gradient modulate value is 6 rather than the ZH value 1.
reinterpret_cast<unsigned int &>(shader) &= ~0x1c00u;
reinterpret_cast<unsigned int &>(shader) |= 0x1800u;			
mat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
} else {
shader.Set_Primary_Gradient(ShaderClass::GRADIENT_DISABLE);
mat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_NODIFFUSE);
}
if (Texture) {
shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);			
} else {
shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
}
BoxDynamicVBAccessClass Verts((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),5,vnum,0);
{
BoxDynamicVBAccessClass::WriteLockClass Lock(&Verts);
unsigned int i;
unsigned char *vb=(unsigned char*)Lock.Get_Formatted_Vertex_Array();			
const FVFInfoClass& fvfinfo=Verts.FVF_Info();			
const unsigned int verticesOffset = fvfinfo.Get_Location_Offset();
const unsigned diffuseOffset = fvfinfo.Get_Diffuse_Offset();
const unsigned textureOffset = fvfinfo.Get_Tex_Offset(0);
const unsigned vbSize = fvfinfo.Get_FVF_Size();
for (i=0; i<vnum; i++)
{
Vector3 *vertex = reinterpret_cast<Vector3 *>(vb + verticesOffset);
vertex->X = vArray[i].x;
vertex->Y = vArray[i].y;
vertex->Z = vArray[i].z;
*reinterpret_cast<unsigned int *>(vb + diffuseOffset) = vArray[i].diffuse;
Vector2 *texture = reinterpret_cast<Vector2 *>(vb + textureOffset);
texture->U = vArray[i].u1;
texture->V = vArray[i].v1;
vb += vbSize;
}			
} 
DynamicIBAccessClass ib_access((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),tidx*3);
{
unsigned int i;
DynamicIBAccessClass::WriteLockClass lock(&ib_access);
unsigned short* inds=lock.Get_Index_Array();
{
for (i=0; i<tidx; i++)
{
*inds++=v_index_array[i].I;
*inds++=v_index_array[i].J;
*inds++=v_index_array[i].K;
}
}
}
DX8Wrapper::Set_Index_Buffer(ib_access,0);
DX8Wrapper::Set_Vertex_Buffer(*reinterpret_cast<const DynamicVBAccessClass *>(&Verts));				
DX8Wrapper::Set_Material(mat);		
BoxSetTexture(0,(TextureBaseClass *&)Texture);
DX8Wrapper::Set_Shader(shader);
if (sorting) {	
SortingRendererClass::Insert_Triangles(obj_sphere,0,tidx,0,vnum);
} else {
DX8Wrapper::Draw_Triangles(0,tidx,0,vnum);
}
REF_PTR_RELEASE(mat);
}	
DX8Wrapper::Set_Transform(D3DTS_VIEW,view);
}
void SegLineRendererClass::subdivision_util(unsigned int point_cnt, const Vector3 *xformed_pts,
const float *base_tex_v, unsigned int *p_sub_point_cnt, Vector3 *xformed_subdiv_pts,
float *subdiv_tex_v, Vector4 *base_diffuse, Vector4 *subdiv_diffuse)
{
int freeze_random = Is_Freeze_Random();
Random3Class randomize;
const float oo_int_max = 1.0f / (float)INT_MAX;
Vector3SolidBoxRandomizer randomizer(Vector3(1,1,1));
Vector3 randvec(0,0,0);
unsigned int sub_pidx = 0;
struct SegLineSubdivision {
Vector3			StartPos;
Vector3			EndPos;
float				StartTexV;	
float				EndTexV;		
Vector4			StartDiffuse;
Vector4			EndDiffuse;
float				Rand;
unsigned int	Level;		
};
SegLineSubdivision stack[2 * MAX_SEGLINE_SUBDIV_LEVELS];	
int tos = 0;
for (unsigned int pidx = 0; pidx < point_cnt - 1; pidx++) {
tos = 0;
stack[0].StartPos = xformed_pts[pidx];
stack[0].EndPos = xformed_pts[pidx + 1];
stack[0].StartTexV = base_tex_v[pidx];
stack[0].EndTexV = base_tex_v[pidx + 1];
if (base_diffuse) {
stack[0].StartDiffuse = base_diffuse[pidx];
stack[0].EndDiffuse = base_diffuse[pidx+1];
} else {
stack[0].StartDiffuse.Set(Color.X, Color.Y, Color.Z, Opacity);
stack[0].EndDiffuse = stack[0].StartDiffuse;
}
stack[0].Rand = NoiseAmplitude;
stack[0].Level = 0;
for (; tos >= 0;) {
if (stack[tos].Level == SubdivisionLevel) {
xformed_subdiv_pts[sub_pidx] = stack[tos].StartPos;
subdiv_tex_v[sub_pidx] = stack[tos].StartTexV;
subdiv_diffuse[sub_pidx] = stack[tos].StartDiffuse;
sub_pidx = sub_pidx + 1;
tos--;
} else {
if (freeze_random) {
randvec.Set(randomize * oo_int_max, randomize * oo_int_max, randomize * oo_int_max);
} else {
randomizer.Get_Vector(randvec);
}
stack[tos + 1].StartPos = stack[tos].StartPos;
stack[tos + 1].EndPos = (stack[tos].StartPos + stack[tos].EndPos) * 0.5f + randvec * stack[tos].Rand;
stack[tos + 1].StartTexV = stack[tos].StartTexV;
stack[tos + 1].EndTexV = (stack[tos].StartTexV + stack[tos].EndTexV) * 0.5f;
stack[tos + 1].StartDiffuse = stack[tos].StartDiffuse;
stack[tos + 1].EndDiffuse = (stack[tos].StartDiffuse + stack[tos].EndDiffuse) * 0.5f;
stack[tos + 1].Rand = stack[tos].Rand * 0.5f;
stack[tos + 1].Level = stack[tos].Level + 1;
stack[tos].StartPos = stack[tos + 1].EndPos;
stack[tos].StartTexV = stack[tos + 1].EndTexV;
stack[tos].Rand = stack[tos + 1].Rand;
stack[tos].Level = stack[tos + 1].Level;
tos++;
}
}
}
xformed_subdiv_pts[sub_pidx] = xformed_pts[point_cnt - 1];
subdiv_tex_v[sub_pidx] = base_tex_v[point_cnt - 1];
if (base_diffuse) {
subdiv_diffuse[sub_pidx] = base_diffuse[point_cnt - 1];
} else {
subdiv_diffuse[sub_pidx].Set(Color.X, Color.Y, Color.Z, Opacity);
}
sub_pidx = sub_pidx + 1;
*p_sub_point_cnt = sub_pidx;
}
void SegLineRendererClass::Scale(float scale)
{
Width *= scale;
NoiseAmplitude *= scale;
_BFME_Unknown_Member *= scale;
}
VertexFormatXYZDUV1 *SegLineRendererClass::getVertexBuffer(unsigned int number)
{
if (number > m_vertexBufferSize)
{
unsigned int numberToAlloc = number + (number >> 1);
delete [] m_vertexBuffer;
m_vertexBuffer = W3DNEWARRAY VertexFormatXYZDUV1[numberToAlloc];
m_vertexBufferSize = numberToAlloc;
}
return m_vertexBuffer;
}
