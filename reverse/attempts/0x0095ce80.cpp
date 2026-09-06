// ?RenderStreak@StreakRendererClass@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@PAVVector4@@PAMABVSphereClass@@PAI@Z
// partial score=0.6 date=2026-09-06
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main  
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
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
/***********************************************************************************************
 ***              EA PACIFIC CONFIDENTIAL              ***
 ***********************************************************************************************
 *                                                                                             *
 *              Original Author:: Mark Lorenzen                                                *
 *                                                                                             *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
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
/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : ww3d                                                         *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/ww3d2/Streakrender.h                      $*
 *                                                                                             *
 *              Original Author:: Greg Hjelstrom                                               *
 *                                                                                             *
 *                      $Author:: Greg_h                                                      $*
 *                                                                                             *
 *                     $Modtime:: 6/08/01 5:23p                                               $*
 *                                                                                             *
 *                    $Revision:: 1                                                           $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */
#ifndef STREAKRENDER_H
#define STREAKRENDER_H
#include "always.h"
#include "shader.h"
#include "texture.h"
#include "matrix3d.h"
#include "vector2.h"
class RenderInfoClass;
class SphereClass;
struct W3dEmitterLinePropertiesStruct;
struct VertexFormatXYZUV1;
#define MAX_STREAK_SUBDIV_LEVELS 7
/**
** StreakRendererClass
** This class implements the low-level line rendering functionality used by both SegmentedLineClass
** and ParticleBufferClass
*/
class StreakRendererClass
{
public:
	StreakRendererClass(void);
	StreakRendererClass(const StreakRendererClass & that);
	StreakRendererClass & operator = (const StreakRendererClass & that);
	~StreakRendererClass(void);
	enum TextureMapMode {
		UNIFORM_WIDTH_TEXTURE_MAP =	0x00000000,	// Entire line uses one row of texture (constant V)
		UNIFORM_LENGTH_TEXTURE_MAP =	0x00000001, // Entire line uses one row of texture stretched length-wise
		TILED_TEXTURE_MAP =				0x00000002	// Tiled continuously over line
	};
	void					Init(const W3dEmitterLinePropertiesStruct & props);
	TextureClass *		Get_Texture(void) const;
	TextureClass *		Peek_Texture(void) const								{ return Texture; }
	ShaderClass			Get_Shader(void) const									{ return Shader; }
	float					Get_Width(void) const									{ return Width; }
	const Vector3 &	Get_Color(void) const 									{ return Color; }
	float					Get_Opacity(void) const									{ return Opacity; }
	float					Get_Noise_Amplitude(void) const						{ return NoiseAmplitude; }
	float					Get_Merge_Abort_Factor(void) const					{ return MergeAbortFactor; }
	unsigned int		Get_Current_Subdivision_Level(void)	const			{ return SubdivisionLevel; }
	TextureMapMode		Get_Texture_Mapping_Mode(void) const;
	float					Get_Texture_Tile_Factor(void) const					{ return TextureTileFactor; }
	int					Is_Merge_Intersections(void) const					{ return Bits & MERGE_INTERSECTIONS; }
	int					Is_Freeze_Random(void) const							{ return Bits & FREEZE_RANDOM; }
	int					Is_Sorting_Disabled(void) const						{ return Bits & DISABLE_SORTING; }
	int					Are_End_Caps_Enabled(void)	const						{ return Bits & END_CAPS; }
	void					Set_Texture(TextureClass *texture);
	void					Set_Shader(ShaderClass shader)						{ Shader = shader; }
	void					Set_Width(float width)									{ Width = width; }
	void					Set_Color(const Vector3 &color)						{ Color = color; }
	void					Set_Opacity(float opacity)								{ Opacity = opacity; }
	void					Set_Noise_Amplitude(float amplitude)				{ NoiseAmplitude = amplitude; }
	void					Set_Merge_Abort_Factor(float factor)				{ MergeAbortFactor = factor; }
	void					Set_Current_Subdivision_Level(unsigned int lv)	{
		DEBUG_ASSERTCRASH(lv == 0, ("Streak renderer does not work for non-zero subdivisions"));
		SubdivisionLevel = lv; SubdivisionLevel = 0;
	}
	void					Set_Texture_Mapping_Mode(TextureMapMode mode);
	void					Set_Merge_Intersections(int onoff)					{ if (onoff) { Bits |= MERGE_INTERSECTIONS; } else { Bits &= ~MERGE_INTERSECTIONS; }; }
	void					Set_Freeze_Random(int onoff)							{ if (onoff) { Bits |= FREEZE_RANDOM; } else { Bits &= ~FREEZE_RANDOM; }; }
	void					Set_Disable_Sorting(int onoff)						{ if (onoff) { Bits |= DISABLE_SORTING; } else { Bits &= ~DISABLE_SORTING; }; }
	void					Set_End_Caps(int onoff)									{ if (onoff) { Bits |= END_CAPS; } else { Bits &= ~END_CAPS; }; }
	void					Reset_Line(void);
	void	Render(	RenderInfoClass & rinfo,
								const Matrix3D & transform,
								unsigned int point_count,
								Vector3 * points,
								const SphereClass & obj_sphere);
	void	RenderStreak(	RenderInfoClass & rinfo,
								const Matrix3D & transform,
								unsigned int point_count,
								Vector3 * points,
								Vector4 * colors,
								float * widths,
								const SphereClass & obj_sphere,
								unsigned int *personalities);
private:
	void								subdivision_util(unsigned int point_cnt, const Vector3 *xformed_pts,
											const float *base_tex_v, unsigned int *p_sub_point_cnt,
											Vector3 *xformed_subdiv_pts, float *subdiv_tex_v);
	TextureClass *					Texture;
	ShaderClass						Shader;
	float								Width;
	Vector3							Color;
	float								Opacity;
	unsigned int					SubdivisionLevel;	
	float								NoiseAmplitude;
	float								MergeAbortFactor;
	float								TextureTileFactor;
	unsigned int					LastUsedSyncTime;		// Last sync time used	
	Vector2							CurrentUVOffset;		// Current UV offset
	Vector2							UVOffsetDeltaPerMS;	// Amount to increase offset each millisec
	enum BitShiftOffsets {
		TEXTURE_MAP_MODE_OFFSET = 24	// By how many bits do I need to shift the texture mapping mode?
	};
	enum {
		MERGE_INTERSECTIONS =	0x00000001,	// Merge intersections
		FREEZE_RANDOM =			0x00000002,	// Freeze random (note: offsets are in camera space)
		DISABLE_SORTING =			0x00000004,	// Disable sorting (even if shader has alpha-blending)
		END_CAPS =					0x00000008,	// Draw end caps on the line
		TEXTURE_MAP_MODE_MASK =	0xFF000000,	// Must cover all possible TextureMapMode values
		DEFAULT_BITS = MERGE_INTERSECTIONS | (UNIFORM_WIDTH_TEXTURE_MAP << TEXTURE_MAP_MODE_OFFSET)
	};
	unsigned int					Bits;
	friend class SegmentedLineClass;
	VertexFormatXYZUV1 *getVertexBuffer(unsigned int number);
  unsigned int m_vertexBufferSize;
  VertexFormatXYZUV1 *m_vertexBuffer;
};
inline StreakRendererClass::TextureMapMode StreakRendererClass::Get_Texture_Mapping_Mode(void) const
{ 
	return (TextureMapMode)((Bits & TEXTURE_MAP_MODE_MASK) >> TEXTURE_MAP_MODE_OFFSET); 
}
inline void StreakRendererClass::Set_Texture_Mapping_Mode(StreakRendererClass::TextureMapMode mode)
{
	Bits &= ~TEXTURE_MAP_MODE_MASK;
	Bits |= ((mode << TEXTURE_MAP_MODE_OFFSET) & TEXTURE_MAP_MODE_MASK);
}
inline void StreakRendererClass::Reset_Line(void)
{
}
#endif //STREAKRENDER_H
#include "ww3d.h"
#include "rinfo.h"
#include "dx8wrapper.h"
#include "sortingrenderer.h"
#include "vp.h"
#include "vector3i.h"
#include "random.h"
#include "v3_rnd.h"
#ifdef _INTERNAL
#endif
/* We have chunking logic which handles N segments at a time. To simplify the subdivision logic,
** we will ensure that N is a power of two and that N >= 2^MAX_STREAK_SUBDIV_LEVELS, so that the
** subdivision logic can be inside the chunking loop.
*/
#if MAX_STREAK_SUBDIV_LEVELS > 7
#define STREAK_CHUNK_SIZE (1 << MAX_STREAK_SUBDIV_LEVELS)
#else
#define STREAK_CHUNK_SIZE (128)
#endif
#define MAX_STREAK_POINT_BUFFER_SIZE (1 + STREAK_CHUNK_SIZE)
#define MAX_STREAK_POLY_BUFFER_SIZE (STREAK_CHUNK_SIZE * 2)
StreakRendererClass & StreakRendererClass::operator = (const StreakRendererClass & that)
{
	if (this != &that) {
		REF_PTR_SET(Texture,that.Texture);
		Shader = that.Shader;
		Width = that.Width;
		Color = that.Color;
		Opacity = that.Opacity;
		SubdivisionLevel = that.SubdivisionLevel;
		NoiseAmplitude = that.NoiseAmplitude;
		MergeAbortFactor = that.MergeAbortFactor;
		Bits = that.Bits;
	}
	return *this;
}
StreakRendererClass::~StreakRendererClass(void)
{
	REF_PTR_RELEASE(Texture);
	delete [] m_vertexBuffer;
}
void StreakRendererClass::Init(const W3dEmitterLinePropertiesStruct & props)
{
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
	Set_Current_Subdivision_Level(props.SubdivisionLevel);
	Set_Noise_Amplitude(props.NoiseAmplitude);
	Set_Merge_Abort_Factor(props.MergeAbortFactor);
}
void StreakRendererClass::Set_Texture(TextureClass *texture)
{ 
	REF_PTR_SET(Texture,texture); 
}
TextureClass * StreakRendererClass::Get_Texture(void) const
{
	if (Texture != NULL) {
		Texture->Add_Ref();
	}
	return Texture;
}
void StreakRendererClass::Render
(	
	RenderInfoClass & rinfo,
	const Matrix3D & transform,
	unsigned int num_points,
	Vector3 * points,
	const SphereClass & obj_sphere
)
{
	return;
}
void StreakRendererClass::subdivision_util(unsigned int point_cnt, const Vector3 *xformed_pts,
	const float *base_tex_v, unsigned int *p_sub_point_cnt, Vector3 *xformed_subdiv_pts,
	float *subdiv_tex_v)
{
	struct StreakRendererRetailLayout {
		TextureClass *Texture;
		ShaderClass Shader;
		float Width;
		Vector3 Color;
		float Opacity;
		unsigned int SubdivisionLevel;
		float NoiseAmplitude;
		float MergeAbortFactor;
		float TextureTileFactor;
		unsigned int LastUsedSyncTime;
		Vector2 CurrentUVOffset;
		Vector2 UVOffsetDeltaPerMS;
		unsigned int Bits;
	};
	const StreakRendererRetailLayout *retail_this =
		reinterpret_cast<const StreakRendererRetailLayout *>(this);
	int freeze_random = retail_this->Bits & FREEZE_RANDOM;
	Random3Class randomize;
	const float oo_int_max = 1.0f / (float)INT_MAX;
	Vector3SolidBoxRandomizer randomizer(Vector3(1,1,1));
	Vector3 randvec(0,0,0);
	unsigned int sub_pointIndex = 0;
	struct StreakSubdivision {
		Vector3			StartPos;
		Vector3			EndPos;
		float				StartTexV;	// V texture coordinate of start point
		float				EndTexV;		// V texture coordinate of end point
		float				Rand;
		unsigned int	Level;		// Subdivision level
	};
	StreakSubdivision stack[2 * MAX_STREAK_SUBDIV_LEVELS];	// Maximum number needed
	int tos = 0;
	for (unsigned int pointIndex = 0; pointIndex < point_cnt - 1; pointIndex++) {
		tos = 0;
		stack[0].StartPos = xformed_pts[pointIndex];
		stack[0].EndPos = xformed_pts[pointIndex + 1];
		stack[0].StartTexV = base_tex_v[pointIndex];
		stack[0].EndTexV = base_tex_v[pointIndex + 1];
		stack[0].Rand = NoiseAmplitude;
		stack[0].Level = 0;
		for (; tos >= 0;) {
			if (stack[tos].Level == SubdivisionLevel) {
				xformed_subdiv_pts[sub_pointIndex] = stack[tos].StartPos;
				subdiv_tex_v[sub_pointIndex++] = stack[tos].StartTexV;
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
	xformed_subdiv_pts[sub_pointIndex] = xformed_pts[point_cnt - 1];
	subdiv_tex_v[sub_pointIndex++] = base_tex_v[point_cnt - 1];
	*p_sub_point_cnt = sub_pointIndex;
}
void StreakRendererClass::RenderStreak
(	
	RenderInfoClass & rinfo,
	const Matrix3D & transform,
	unsigned int num_points,
	Vector3 * points,
	Vector4 * colors,								/////////////// DIFFERENT FROM RENDER( )
	float * widths,									/////////////// DIFFERENT FROM RENDER( )
	const SphereClass & obj_sphere,
	unsigned int *personalities			/////////////// DIFFERENT FROM RENDER( )
)
{
	Matrix4x4 view;
	DX8Wrapper::Get_Transform(D3DTS_VIEW,view);
	Matrix4x4 identity(true);
	DX8Wrapper::Set_Transform(D3DTS_WORLD,identity);	
	DX8Wrapper::Set_Transform(D3DTS_VIEW,identity);	
	/* 
	** Handle texture UV offset animation (done once for entire line).
	*/
	unsigned int delta = WW3D::Get_Sync_Time() - LastUsedSyncTime;
	float del = (float)delta;
	Vector2 uv_offset = CurrentUVOffset + UVOffsetDeltaPerMS * del;
	uv_offset.X = uv_offset.X - floorf(uv_offset.X);
	uv_offset.Y = uv_offset.Y - floorf(uv_offset.Y);
	CurrentUVOffset = uv_offset;
	LastUsedSyncTime = WW3D::Get_Sync_Time();
	TextureMapMode map_mode = Get_Texture_Mapping_Mode();
	/*
	** Process line geometry:
	*/
	const float parallel_factor = 0.9f;
	unsigned int chunk_size = (STREAK_CHUNK_SIZE >> SubdivisionLevel) + 1;
	if (chunk_size > num_points) chunk_size = num_points;
	for (unsigned int chunkIndex = 0; chunkIndex < num_points - 1; chunkIndex += (chunk_size - 1)) 
	{
		unsigned int point_cnt = num_points - chunkIndex;
		point_cnt = MIN(point_cnt, chunk_size);
		unsigned int pointIndex;	// Point index
		unsigned int segmentIndex;	// Segment index
		unsigned int intersectionIndex;	// Intersection index
		/*
		** Transform points in chunk from objectspace to eyespace:
		*/
		Vector3 xformed_pts[MAX_STREAK_POINT_BUFFER_SIZE];
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
			&points[chunkIndex], modelview, point_cnt);
		/*
		** Prepare v parameter per point - used for texture mapping (esp. tiled mapping mode)
		*/
		float base_tex_v[MAX_STREAK_POINT_BUFFER_SIZE];
		float u_values[2];
		switch (map_mode) 
		{
			case UNIFORM_WIDTH_TEXTURE_MAP:// only non-dead case
				for (pointIndex = 0; pointIndex < point_cnt; pointIndex++) 
				{
					base_tex_v[pointIndex] = 0.0f;
				}
				u_values[0] = 0.0f;
				u_values[1] = 1.0f;
				break;
			case UNIFORM_LENGTH_TEXTURE_MAP:
				for (pointIndex = 0; pointIndex < point_cnt; pointIndex++) 
				{
					base_tex_v[pointIndex] = (float)(pointIndex + chunkIndex) * TextureTileFactor;
				}
				u_values[0] = 0.0f;
				u_values[1] = 0.0f;
				break;
			case TILED_TEXTURE_MAP:
				for (pointIndex = 0; pointIndex < point_cnt; pointIndex++) 
				{
					base_tex_v[pointIndex] = (float)(pointIndex + chunkIndex) * TextureTileFactor;
				}
				u_values[0] = 0.0f;
				u_values[1] = 1.0f;
				break;
		}
		/*
		** Fractal noise recursive subdivision:
		** We find the midpoint for each section, apply a random offset, and recurse. We also find
		** the average V coordinate of the endpoints which is the midpoint V (for tiled texture
		** mapping).
		*/
		Vector3 xformed_subdiv_pts[MAX_STREAK_POINT_BUFFER_SIZE];
		float subdiv_tex_v[MAX_STREAK_POINT_BUFFER_SIZE];
		unsigned int sub_point_cnt;
		subdivision_util(point_cnt, xformed_pts, base_tex_v, &sub_point_cnt, xformed_subdiv_pts, subdiv_tex_v);
		Vector3 *points = xformed_subdiv_pts;
		float *tex_v = subdiv_tex_v;
		point_cnt = sub_point_cnt;
		/*
		** Calculate line segment edge planes:
		*/
		enum SegmentEdge 
		{
			FIRST_EDGE     = 0,	// For loop conditions
			TOP_EDGE			= 0,	// Top Edge
			BOTTOM_EDGE		= 1,	// Bottom Edge
			MAX_EDGE			= 1,	// For loop conditions
			NUM_EDGES		= 2	// For array allocations
		};
		bool switch_edges = false;
		struct LineSegment 
		{
			Vector3	StartPlane;
			Vector3	EdgePlane[NUM_EDGES];
		};
		LineSegment segment[MAX_STREAK_POINT_BUFFER_SIZE + 1];
		struct LineSegmentIntersection  
		{
			unsigned int	PointCount;			// How many points does this intersection represent
			unsigned int	NextSegmentID;		// ID of segment after this intersection
			Vector3			Direction;			// Calculated intersection direction line
			Vector3			Point;				// Averaged 3D point on the line which this represents
			float				TexV;					// Averaged texture V coordinate of points
			bool				Fold;					// Does the line fold over at this intersection?
			bool				Parallel;			// Edges at this intersection are parallel (or almost-)
		};
		float radius = Width * 0.5f; 
		LineSegmentIntersection intersection[MAX_STREAK_POINT_BUFFER_SIZE + 1][NUM_EDGES];
		for (segmentIndex = 1; segmentIndex < point_cnt; segmentIndex++) 
		{	// #segments = #points - 1 (+ 2 dummy segments)
			radius = widths[segmentIndex]; /// NEW ///// // TODO: Does not work correctly when subdivision are not 0
			Vector3 &curr_point = points[segmentIndex - 1];
			Vector3 &next_point = points[segmentIndex];
			if (Equal_Within_Epsilon(curr_point, next_point, 0.0001f))
			{
				next_point.X += 0.001f;
			}
			Vector3 &segdir = segment[segmentIndex].StartPlane;
			segdir = next_point - curr_point;
			segdir.Normalize();
			Vector3 nearest = curr_point + segdir * -Vector3::Dot_Product(segdir, curr_point);
			Vector3 offset;
			Vector3::Cross_Product(segdir, nearest, &offset);
			offset.Normalize();
			Vector3 top = curr_point + offset * radius;
			Vector3 bottom = curr_point + offset * -radius;
			Vector3 top_normal;
			Vector3::Cross_Product(top, segdir, &top_normal);
			top_normal.Normalize();
			segment[segmentIndex].EdgePlane[TOP_EDGE] = top_normal;
			Vector3 bottom_normal;
			Vector3::Cross_Product(segdir, bottom, &bottom_normal);
			bottom_normal.Normalize();
			segment[segmentIndex].EdgePlane[BOTTOM_EDGE] = bottom_normal;
			if (segmentIndex > 1) 
			{
				Vector3 prev_plane;
				Vector3::Cross_Product(points[segmentIndex - 2], curr_point, &prev_plane);
				prev_plane.Normalize();
				Vector3 curr_plane;
				Vector3::Cross_Product(curr_point, next_point, &curr_plane);
				curr_plane.Normalize();
				if (Vector3::Dot_Product(prev_plane, curr_plane) < 0.0f) 
				{
					switch_edges = !switch_edges;
					intersection[segmentIndex][TOP_EDGE].Fold = true;
					intersection[segmentIndex][BOTTOM_EDGE].Fold = true;
				} 
				else 
				{
					intersection[segmentIndex][TOP_EDGE].Fold = false;
					intersection[segmentIndex][BOTTOM_EDGE].Fold = false;
				}
			}
			if (switch_edges) 
			{
				segment[segmentIndex].EdgePlane[TOP_EDGE] = -bottom_normal;
				segment[segmentIndex].EdgePlane[BOTTOM_EDGE] = -top_normal;
			}
		}
		/*
		** Calculate segment edge intersections:
		*/
		unsigned int numsegs = point_cnt - 1;	// Doesn't include the two dummy segments
		unsigned int num_intersections[NUM_EDGES];
		num_intersections[TOP_EDGE] = point_cnt;
		num_intersections[BOTTOM_EDGE] = point_cnt;
		intersection[0][TOP_EDGE].PointCount = 0;				// Should never be used
		intersection[0][TOP_EDGE].NextSegmentID = 0;			// Points to first dummy segment
		intersection[0][TOP_EDGE].Direction.Set(1,0,0);		// Should never be used
		intersection[0][TOP_EDGE].Point.Set(0,0,0);			// Should never be used
		intersection[0][TOP_EDGE].TexV = 0.0f;					// Should never be used
		intersection[0][TOP_EDGE].Fold = true;					// Should never be used
		intersection[0][TOP_EDGE].Parallel = false;			// Should never be used
		intersection[0][BOTTOM_EDGE].PointCount = 0;			// Should never be used
		intersection[0][BOTTOM_EDGE].NextSegmentID = 0;		// Points to first dummy segment
		intersection[0][BOTTOM_EDGE].Point.Set(0,0,0);		// Should never be used
		intersection[0][BOTTOM_EDGE].TexV = 0.0f;				// Should never be used
		intersection[0][BOTTOM_EDGE].Direction.Set(1,0,0);	// Should never be used
		intersection[0][BOTTOM_EDGE].Fold = true;				// Should never be used
		intersection[0][BOTTOM_EDGE].Parallel = false;		// Should never be used
		intersection[1][TOP_EDGE].PointCount = 1;
		intersection[1][TOP_EDGE].NextSegmentID = 1;
		intersection[1][TOP_EDGE].Point = points[0];
		intersection[1][TOP_EDGE].TexV = tex_v[0];
		intersection[1][TOP_EDGE].Fold = true;
		intersection[1][TOP_EDGE].Parallel = false;
		intersection[1][BOTTOM_EDGE].PointCount = 1;
		intersection[1][BOTTOM_EDGE].NextSegmentID = 1;
		intersection[1][BOTTOM_EDGE].Point = points[0];
		intersection[1][BOTTOM_EDGE].TexV = tex_v[0];
		intersection[1][BOTTOM_EDGE].Fold = true;
		intersection[1][BOTTOM_EDGE].Parallel = false;
		Vector3 top;
		Vector3 bottom;
		Vector3 &first_point = points[0];
		Vector3 *first_plane = &(segment[1].EdgePlane[0]);
		top = first_point - first_plane[TOP_EDGE] * Vector3::Dot_Product(first_plane[TOP_EDGE], first_point);
		top.Normalize();
		intersection[1][TOP_EDGE].Direction = top;
		bottom = first_point - first_plane[BOTTOM_EDGE] * Vector3::Dot_Product(first_plane[BOTTOM_EDGE], first_point);
		bottom.Normalize();
		intersection[1][BOTTOM_EDGE].Direction = bottom;
		Vector3 segdir = points[1] - points[0];
		segdir.Normalize();	// Is this needed? Probably not - remove later when all works
		Vector3 start_pl;
		Vector3::Cross_Product(top, bottom, &start_pl);
		start_pl.Normalize();
		float dp = Vector3::Dot_Product(segdir, start_pl);
		if (dp > 0.0f) 
		{
			segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = start_pl;
		} 
		else
		{
			segment[0].StartPlane = segment[0].EdgePlane[TOP_EDGE] = segment[0].EdgePlane[BOTTOM_EDGE] = -start_pl;
		}
		segment[1].StartPlane = segment[0].StartPlane;
		unsigned int last_isec = num_intersections[TOP_EDGE]; // Same # top, bottom intersections
		intersection[last_isec][TOP_EDGE].PointCount = 1;
		intersection[last_isec][TOP_EDGE].NextSegmentID = numsegs + 1; // Last dummy segment
		intersection[last_isec][TOP_EDGE].Point = points[point_cnt - 1];
		intersection[last_isec][TOP_EDGE].TexV = tex_v[point_cnt - 1];
		intersection[last_isec][TOP_EDGE].Fold = true;
		intersection[last_isec][TOP_EDGE].Parallel = false;
		intersection[last_isec][BOTTOM_EDGE].PointCount = 1;
		intersection[last_isec][BOTTOM_EDGE].NextSegmentID = numsegs + 1;// Last dummy segment
		intersection[last_isec][BOTTOM_EDGE].Point = points[point_cnt - 1];
		intersection[last_isec][BOTTOM_EDGE].TexV = tex_v[point_cnt - 1];
		intersection[last_isec][BOTTOM_EDGE].Fold = true;
		intersection[last_isec][BOTTOM_EDGE].Parallel = false;
		Vector3 &last_point = points[point_cnt - 1];
		Vector3 *last_plane = &(segment[numsegs].EdgePlane[0]);
		top = last_point - last_plane[TOP_EDGE] * Vector3::Dot_Product(last_plane[TOP_EDGE], last_point);
		top.Normalize();
		intersection[last_isec][TOP_EDGE].Direction = top;
		bottom = last_point - last_plane[BOTTOM_EDGE] * Vector3::Dot_Product(last_plane[BOTTOM_EDGE], last_point);
		bottom.Normalize();
		intersection[last_isec][BOTTOM_EDGE].Direction = bottom;
		segdir = points[point_cnt - 1] - points[point_cnt - 2];
		segdir.Normalize();	// Is this needed? Probably not - remove later when all works
		Vector3::Cross_Product(top, bottom, &start_pl);
		start_pl.Normalize();
		dp = Vector3::Dot_Product(segdir, start_pl);
		if (dp > 0.0f) 
		{
			segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
				segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = start_pl;
		} 
		else 
		{
			segment[numsegs + 1].StartPlane = segment[numsegs + 1].EdgePlane[TOP_EDGE] =
				segment[numsegs + 1].EdgePlane[BOTTOM_EDGE] = -start_pl;
		}
		float vdp;
		for (intersectionIndex = 2; intersectionIndex < num_intersections[TOP_EDGE]; intersectionIndex++) 
		{
			Vector3 &midpoint = points[intersectionIndex - 1];
			float mid_tex_v = tex_v[intersectionIndex - 1];
			intersection[intersectionIndex][TOP_EDGE].PointCount = 1;
			intersection[intersectionIndex][TOP_EDGE].NextSegmentID = intersectionIndex;
			intersection[intersectionIndex][TOP_EDGE].Point = midpoint;
			intersection[intersectionIndex][TOP_EDGE].TexV = personalities[intersectionIndex]&1;//LORENZEN LORENZEN 
			intersection[intersectionIndex][BOTTOM_EDGE].PointCount = 1;
			intersection[intersectionIndex][BOTTOM_EDGE].NextSegmentID = intersectionIndex;
			intersection[intersectionIndex][BOTTOM_EDGE].Point = midpoint;
			intersection[intersectionIndex][BOTTOM_EDGE].TexV = personalities[intersectionIndex]&1;//LORENZEN LORENZEN 
			vdp = Vector3::Dot_Product(segment[intersectionIndex - 1].EdgePlane[TOP_EDGE], segment[intersectionIndex].EdgePlane[TOP_EDGE]);
			if (fabs(vdp) < parallel_factor) 
			{
				Vector3::Cross_Product(segment[intersectionIndex - 1].EdgePlane[TOP_EDGE], segment[intersectionIndex].EdgePlane[TOP_EDGE],
					&(intersection[intersectionIndex][TOP_EDGE].Direction));
				intersection[intersectionIndex][TOP_EDGE].Direction.Normalize();
				if (Vector3::Dot_Product(intersection[intersectionIndex][TOP_EDGE].Direction, midpoint) < 0.0f) 
				{
					intersection[intersectionIndex][TOP_EDGE].Direction = -intersection[intersectionIndex][TOP_EDGE].Direction;
				}
				intersection[intersectionIndex][TOP_EDGE].Parallel = false;
			} 
			else 
			{
				Vector3 pl;
				if (vdp > 0.0f) 
				{
					pl = segment[intersectionIndex - 1].EdgePlane[TOP_EDGE] + segment[intersectionIndex].EdgePlane[TOP_EDGE];
				} 
				else 
				{
					pl = segment[intersectionIndex - 1].EdgePlane[TOP_EDGE] - segment[intersectionIndex].EdgePlane[TOP_EDGE];
				}
				pl.Normalize();
				intersection[intersectionIndex][TOP_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
				intersection[intersectionIndex][TOP_EDGE].Direction.Normalize();
				intersection[intersectionIndex][TOP_EDGE].Parallel = true;
			}
			vdp = Vector3::Dot_Product(segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE], segment[intersectionIndex].EdgePlane[BOTTOM_EDGE]);
			if (fabs(vdp) < parallel_factor) 
			{
				Vector3::Cross_Product(segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE], segment[intersectionIndex].EdgePlane[BOTTOM_EDGE],
					&(intersection[intersectionIndex][BOTTOM_EDGE].Direction));
				intersection[intersectionIndex][BOTTOM_EDGE].Direction.Normalize();
				if (Vector3::Dot_Product(intersection[intersectionIndex][BOTTOM_EDGE].Direction, midpoint) < 0.0f) 
				{
					intersection[intersectionIndex][BOTTOM_EDGE].Direction = -intersection[intersectionIndex][BOTTOM_EDGE].Direction;
				}
				intersection[intersectionIndex][BOTTOM_EDGE].Parallel = false;
			} 
			else 
			{
				Vector3 pl;
				if (vdp > 0.0f) 
				{
					pl = segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE] + segment[intersectionIndex].EdgePlane[BOTTOM_EDGE];
				} 
				else 
				{
					pl = segment[intersectionIndex - 1].EdgePlane[BOTTOM_EDGE] - segment[intersectionIndex].EdgePlane[BOTTOM_EDGE];
				}
				pl.Normalize();
				intersection[intersectionIndex][BOTTOM_EDGE].Direction = midpoint - pl * Vector3::Dot_Product(pl, midpoint);
				intersection[intersectionIndex][BOTTOM_EDGE].Direction.Normalize();
				intersection[intersectionIndex][BOTTOM_EDGE].Parallel = true;
			}
			Vector3::Cross_Product(intersection[intersectionIndex][TOP_EDGE].Direction, intersection[intersectionIndex][BOTTOM_EDGE].Direction, &start_pl);
			start_pl.Normalize();
			dp = Vector3::Dot_Product(segment[intersectionIndex].StartPlane, start_pl);
			if (dp > 0.0f) 
			{
				segment[intersectionIndex].StartPlane = start_pl;
			} 
			else 
			{
				segment[intersectionIndex].StartPlane = -start_pl;
			}
		}	// for intersectionIndex
		/*
		** Intersection merging: when an intersection is inside an adjacent segment and certain
		** other conditions hold true, we need to merge intersections to avoid visual glitches
		** caused by the polys folding over on themselves.
		*/
		if (Is_Merge_Intersections()) 
		{
			unsigned int intersectionIndex_r;
			unsigned int intersectionIndex_w;
			bool merged = true;
			while (merged) 
			{
				merged = false;
				SegmentEdge edge;
				for (edge = FIRST_EDGE; edge <= MAX_EDGE; edge = (SegmentEdge)((int)edge + 1)) 
				{
					unsigned int num_isects = num_intersections[edge];	// Capture here because will change inside loop
					for (intersectionIndex_r = 1, intersectionIndex_w = 1; intersectionIndex_r < num_isects; intersectionIndex_r++, intersectionIndex_w++) {
						LineSegmentIntersection *curr_int = &(intersection[intersectionIndex_r][edge]);
						LineSegmentIntersection *next_int = &(intersection[intersectionIndex_r + 1][edge]);
						LineSegmentIntersection *write_int = &(intersection[intersectionIndex_w][edge]);
						LineSegmentIntersection *prev_int = &(intersection[intersectionIndex_w - 1][edge]);
						LineSegment *next_seg = &(segment[next_int->NextSegmentID]);
						LineSegment *curr_seg = &(segment[curr_int->NextSegmentID]);
						LineSegment *prev_seg = &(segment[prev_int->NextSegmentID]);
						while	(	(!next_int->Fold &&
										(Vector3::Dot_Product(curr_int->Direction, next_seg->StartPlane) > 0.0f) &&
										(Vector3::Dot_Product(curr_int->Direction, next_seg->EdgePlane[edge]) > 0.0f )) ||
									(!curr_int->Fold &&
										(Vector3::Dot_Product(next_int->Direction, -curr_seg->StartPlane) > 0.0f) &&
										(Vector3::Dot_Product(next_int->Direction, prev_seg->EdgePlane[edge]) > 0.0f )) ) 
						{
							unsigned int new_count = curr_int->PointCount + next_int->PointCount;
							float oo_new_count = 1.0f / (float)new_count;
							float curr_factor = oo_new_count * (float)curr_int->PointCount;
							float next_factor = oo_new_count * (float)curr_int->PointCount;
							Vector3 new_point = curr_int->Point * curr_factor + next_int->Point * next_factor;
							float new_tex_v = curr_int->TexV * curr_factor + next_int->TexV * next_factor;
							bool new_parallel;
							Vector3 new_direction;
							vdp = Vector3::Dot_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge]);
							if (fabs(vdp) < parallel_factor) 
							{
								Vector3::Cross_Product(prev_seg->EdgePlane[edge], next_seg->EdgePlane[edge], &new_direction);
								new_direction.Normalize();
								if (Vector3::Dot_Product(new_direction, new_point) < 0.0f) 
								{
									new_direction = -new_direction;
								}
								new_parallel = false;
							} 
							else 
							{
								Vector3 pl;
								if (vdp > 0.0f) 
								{
									pl = prev_seg->EdgePlane[edge] + next_seg->EdgePlane[edge];
								} 
								else 
								{
									pl = prev_seg->EdgePlane[edge] - next_seg->EdgePlane[edge];
								}
								pl.Normalize();
								if (curr_int->Parallel) 
								{
									new_direction = new_direction - pl * Vector3::Dot_Product(pl, new_direction);
									new_direction.Normalize();
								} 
								else
								{
									Vector3::Cross_Product(curr_seg->EdgePlane[edge], pl, &new_direction);
									new_direction.Normalize();
								}
								new_parallel = true;
							}
							if (MergeAbortFactor > 0.0f) 
							{
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
							curr_int->PointCount = new_count;
							curr_int->NextSegmentID = next_int->NextSegmentID;
							curr_int->Fold = curr_int->Fold || next_int->Fold;
							num_intersections[edge]--;
							intersectionIndex_r++;
							if (intersectionIndex_r == num_isects) 
							{
								break;
							}
							next_int = &(intersection[intersectionIndex_r + 1][edge]);
							next_seg = &(segment[next_int->NextSegmentID]);
						}	// while <merging needed>
						write_int->PointCount		= curr_int->PointCount;
						write_int->NextSegmentID	= curr_int->NextSegmentID;
						write_int->Point				= curr_int->Point;
						write_int->TexV				= curr_int->TexV;
						write_int->Direction			= curr_int->Direction;
						write_int->Fold				= curr_int->Fold;
					}	// for intersectionIndex
					if (intersectionIndex_r == num_isects) 
					{
						LineSegmentIntersection *write_int = &(intersection[intersectionIndex_w][edge]);
						LineSegmentIntersection *curr_int = &(intersection[intersectionIndex_r][edge]);
						write_int->PointCount		= curr_int->PointCount;
						write_int->NextSegmentID	= curr_int->NextSegmentID;
						write_int->Point				= curr_int->Point;
						write_int->TexV				= curr_int->TexV;
						write_int->Direction			= curr_int->Direction;
						write_int->Fold				= curr_int->Fold;
					}
#ifdef ENABLE_WWDEBUGGING
					unsigned int total_cnt = 0;
					for (unsigned int nidx = 0; nidx <= num_intersections[edge]; nidx++) 
					{
						total_cnt += intersection[nidx][edge].PointCount;
					}
					assert(total_cnt == point_cnt);
#endif
				}	// for edge
			}	// while (merged)
		}	// if (Is_Merge_Intersections())
		/*
		** Find vertex positions, generate vertices and triangles:
		** Since we can have top/bottom intersections merged, we need to skip points if both the top
		** and bottom intersections are merged, generate triangle fans if one of the sides is merged
		** and the other isnt, and generate triangle strips otherwise.
		*/
		unsigned int vnum = num_intersections[TOP_EDGE] + num_intersections[BOTTOM_EDGE];		
		VertexFormatXYZUV1 *vertexArray = getVertexBuffer(vnum);
		Vector3i v_index_array[MAX_STREAK_POLY_BUFFER_SIZE];
		unsigned int vertexIndex = 0;
		unsigned int triangleIndex = 0;
		Vector3 &top_dir = intersection[1][TOP_EDGE].Direction;
		top = top_dir * Vector3::Dot_Product(points[0], top_dir);
		Vector3 &bottom_dir = intersection[1][BOTTOM_EDGE].Direction;
		bottom = bottom_dir * Vector3::Dot_Product(points[0], bottom_dir);
		vertexArray[vertexIndex].x = top.X;
		vertexArray[vertexIndex].y = top.Y;
		vertexArray[vertexIndex].z = top.Z;
		vertexArray[vertexIndex].u1 = u_values[0] + uv_offset.X;
		vertexArray[vertexIndex].v1 = intersection[1][TOP_EDGE].TexV  + uv_offset.Y;
		vertexIndex++;
		vertexArray[vertexIndex].x = bottom.X;
		vertexArray[vertexIndex].y = bottom.Y;
		vertexArray[vertexIndex].z = bottom.Z;
		vertexArray[vertexIndex].u1 = u_values[1] + uv_offset.X;
		vertexArray[vertexIndex].v1 = intersection[1][BOTTOM_EDGE].TexV  + uv_offset.Y;
		vertexIndex++;
		unsigned int last_top_vertexIndex = 0;
		unsigned int last_bottom_vertexIndex = 1;
		unsigned int top_int_idx = 1;		// Skip "pre-first-point" dummy intersection
		unsigned int bottom_int_idx = 1;	// Skip "pre-first-point" dummy intersection
		pointIndex = 0;
		unsigned int residual_top_points = intersection[1][TOP_EDGE].PointCount;
		unsigned int residual_bottom_points = intersection[1][BOTTOM_EDGE].PointCount;
		unsigned int delta = MIN(residual_top_points, residual_bottom_points) - 1;
		residual_top_points -= delta;
		residual_bottom_points -= delta;
		pointIndex += delta;
		for (; ; ) 
		{
			if (residual_top_points == 1 && residual_bottom_points == 1) 
			{
				v_index_array[triangleIndex].I = last_top_vertexIndex;
				v_index_array[triangleIndex].J = last_bottom_vertexIndex;
				v_index_array[triangleIndex].K = vertexIndex;
				triangleIndex++;
				v_index_array[triangleIndex].I = last_bottom_vertexIndex;
				v_index_array[triangleIndex].J = vertexIndex + 1;
				v_index_array[triangleIndex].K = vertexIndex;
				triangleIndex++;
				last_top_vertexIndex = vertexIndex;
				last_bottom_vertexIndex = vertexIndex + 1;
				top_int_idx++;
				bottom_int_idx++;
				residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
				residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;
				pointIndex++;
				Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
				top = top_dir * Vector3::Dot_Product(points[pointIndex], top_dir);
				Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
				bottom = bottom_dir * Vector3::Dot_Product(points[pointIndex], bottom_dir);
				vertexArray[vertexIndex].x = top.X;
				vertexArray[vertexIndex].y = top.Y;
				vertexArray[vertexIndex].z = top.Z;
				vertexArray[vertexIndex].u1 = u_values[0] + uv_offset.X;
				vertexArray[vertexIndex].v1 = intersection[top_int_idx][TOP_EDGE].TexV  + uv_offset.Y;
				vertexIndex++;
				vertexArray[vertexIndex].x = bottom.X;
				vertexArray[vertexIndex].y = bottom.Y;
				vertexArray[vertexIndex].z = bottom.Z;
				vertexArray[vertexIndex].u1 = u_values[1] + uv_offset.X;
				vertexArray[vertexIndex].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV  + uv_offset.Y;
				vertexIndex++;
			}
			else 
			{
				if (residual_top_points > 1) 
				{
					v_index_array[triangleIndex].I = last_top_vertexIndex;
					v_index_array[triangleIndex].J = last_bottom_vertexIndex;
					v_index_array[triangleIndex].K = vertexIndex;
					triangleIndex++;
					last_bottom_vertexIndex = vertexIndex;
					residual_top_points--;
					bottom_int_idx++;
					residual_bottom_points = intersection[bottom_int_idx][BOTTOM_EDGE].PointCount;
					pointIndex++;
					Vector3 &bottom_dir = intersection[bottom_int_idx][BOTTOM_EDGE].Direction;
					bottom = bottom_dir * Vector3::Dot_Product(points[pointIndex], bottom_dir);
					vertexArray[vertexIndex].x = bottom.X;
					vertexArray[vertexIndex].y = bottom.Y;
					vertexArray[vertexIndex].z = bottom.Z;
					vertexArray[vertexIndex].u1 = u_values[1] + uv_offset.X;
					vertexArray[vertexIndex].v1 = intersection[bottom_int_idx][BOTTOM_EDGE].TexV  + uv_offset.Y;					
					vertexIndex++;
				}
				else 
				{
					v_index_array[triangleIndex].I = last_top_vertexIndex;
					v_index_array[triangleIndex].J = last_bottom_vertexIndex;
					v_index_array[triangleIndex].K = vertexIndex;
					triangleIndex++;
					last_top_vertexIndex = vertexIndex;
					residual_bottom_points--;
					top_int_idx++;
					residual_top_points = intersection[top_int_idx][TOP_EDGE].PointCount;
					pointIndex++;
					Vector3 &top_dir = intersection[top_int_idx][TOP_EDGE].Direction;
					top = top_dir * Vector3::Dot_Product(points[pointIndex], top_dir);
					vertexArray[vertexIndex].x = top.X;
					vertexArray[vertexIndex].y = top.Y;
					vertexArray[vertexIndex].z = top.Z;
					vertexArray[vertexIndex].u1 = u_values[0] + uv_offset.X;
					vertexArray[vertexIndex].v1 = intersection[top_int_idx][TOP_EDGE].TexV  + uv_offset.Y;
					vertexIndex++;
				}
			}
			delta = MIN(residual_top_points, residual_bottom_points) - 1;
			residual_top_points -= delta;
			residual_bottom_points -= delta;
			pointIndex += delta;
			if (	(top_int_idx >= num_intersections[TOP_EDGE] && residual_top_points == 1) ||
					(bottom_int_idx >= num_intersections[BOTTOM_EDGE] && residual_bottom_points == 1)) 
			{
				assert(top_int_idx == num_intersections[TOP_EDGE]);
				assert(bottom_int_idx == num_intersections[BOTTOM_EDGE]);
				assert(pointIndex == point_cnt - 1);
				break;
			}
		}		
		/*
		** Set color, opacity, vertex flags:
		*/
		bool sorting = (!Is_Sorting_Disabled()) && (Shader.Get_Dst_Blend_Func() != ShaderClass::DSTBLEND_ZERO && Shader.Get_Alpha_Test() == ShaderClass::ALPHATEST_DISABLE);
		ShaderClass shader = Shader;
		shader.Set_Cull_Mode(ShaderClass::CULL_MODE_DISABLE);
		shader.Set_Primary_Gradient(ShaderClass::GRADIENT_MODULATE);			
		VertexMaterialClass *mat;		
		mat=VertexMaterialClass::Get_Preset(VertexMaterialClass::PRELIT_DIFFUSE);
		DX8Wrapper::Set_Material(mat);
		REF_PTR_RELEASE(mat);
		if (Texture) 
		{
			shader.Set_Texturing(ShaderClass::TEXTURING_ENABLE);			
		} 
		else 
		{
			shader.Set_Texturing(ShaderClass::TEXTURING_DISABLE);
		}
		/*
		** Render
		*/		
		DynamicVBAccessClass Verts((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),dynamic_fvf_type,vnum);
		{
			DynamicVBAccessClass::WriteLockClass Lock(&Verts);
			unsigned int i;
			unsigned char *vb=(unsigned char*)Lock.Get_Formatted_Vertex_Array();			
			const FVFInfoClass& fvfinfo=Verts.FVF_Info();			
			int segIdx = 0;
			unsigned int argb = 0x00000000;
			unsigned int oddEven = 0;
			const unsigned verticesOffset = fvfinfo.Get_Location_Offset();
			const unsigned diffuseOffset = fvfinfo.Get_Diffuse_Offset();
			const unsigned textureOffset = fvfinfo.Get_Tex_Offset(0);
			const unsigned vbSize = fvfinfo.Get_FVF_Size();
			for (i=0; i<vnum; i++)
			{
				DEBUG_ASSERTCRASH(vertexArray[i].x != (float)0xdeadbeef && vertexArray[i].y != (float)0xdeadbeef && vertexArray[i].z != (float)0xdeadbeef && vertexArray[i].u1 != (float)0xdeadbeeef && vertexArray[i].v1 != (float)0xdeadbeef, ("Uninitialized vertexArray[%d]", i));
				DEBUG_ASSERTCRASH((! _isnan(vertexArray[i].x) && _finite(vertexArray[i].x) && ! _isnan(vertexArray[i].y) && _finite(vertexArray[i].y) && ! _isnan(vertexArray[i].z) && _finite(vertexArray[i].z)) , ("Bad vertexArray[%d]", i));
				Vector3 *vertex = reinterpret_cast<Vector3 *>(vb + verticesOffset);
				vertex->X = vertexArray[i].x;
				vertex->Y = vertexArray[i].y;
				vertex->Z = vertexArray[i].z;
				*reinterpret_cast<unsigned int *>(vb + diffuseOffset) = DX8Wrapper::Convert_Color_Clamp(colors[MIN((i/2), point_cnt)]); // TODO: Does not work correctly when subdivision are not 0
				Vector2 *texture = reinterpret_cast<Vector2 *>(vb + textureOffset);
				texture->U = vertexArray[i].u1;
				texture->V = vertexArray[i].v1;
				vb += vbSize;				
			}			
		} // copy
		DynamicIBAccessClass ib_access((sorting?BUFFER_TYPE_DYNAMIC_SORTING:BUFFER_TYPE_DYNAMIC_DX8),triangleIndex*3);
		{
			unsigned int i;
			DynamicIBAccessClass::WriteLockClass lock(&ib_access);
			unsigned short* inds=lock.Get_Index_Array();
			for (i=0; i<triangleIndex; i++)
			{
				*inds++=v_index_array[i].I;
				*inds++=v_index_array[i].J;
				*inds++=v_index_array[i].K;
			}
		}
		DX8Wrapper::Set_Index_Buffer(ib_access,0);
		DX8Wrapper::Set_Vertex_Buffer(Verts);				
		DX8Wrapper::Set_Texture(0,Texture);
		DX8Wrapper::Set_Shader(shader);
		if (sorting) 
		{	
			SortingRendererClass::Insert_Triangles(obj_sphere,0,triangleIndex,0,vnum);
		} 
		else 
		{
			DX8Wrapper::Draw_Triangles(0,triangleIndex,0,vnum);
		}
	}	// Chunking loop
	DX8Wrapper::Set_Transform(D3DTS_VIEW,view);
}
#define BFME_STREAK_VBSIZE(s) (*(unsigned int *)((char *)(s) + 0x44))
#define BFME_STREAK_VB(s)     (*(VertexFormatXYZUV1 **)((char *)(s) + 0x48))
VertexFormatXYZUV1 *StreakRendererClass::getVertexBuffer(unsigned int number)
{
	if (number > BFME_STREAK_VBSIZE(this))
	{
		unsigned int numberToAlloc = number + (number >> 1);
	  delete [] BFME_STREAK_VB(this);
		BFME_STREAK_VB(this) = W3DNEWARRAY VertexFormatXYZUV1[numberToAlloc];		
		BFME_STREAK_VBSIZE(this) = numberToAlloc;
	}
#ifdef _INTERNAL
	for (unsigned i = 0; i < number; ++i)
	{
	  m_vertexBuffer[i].x = m_vertexBuffer[i].y = m_vertexBuffer[i].z = m_vertexBuffer[i].u1 = m_vertexBuffer[i].v1 = (float)0xdeadbeef + uv_offset.Y;
	}
#endif
	return BFME_STREAK_VB(this);
}
