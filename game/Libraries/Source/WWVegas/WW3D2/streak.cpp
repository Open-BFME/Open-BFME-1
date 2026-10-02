// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
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
 *                 Project Name : G                                                            *
 *                                                                                             *
 *                     $Archive:: /VSS_Sync/ww3d2/segline.cpp                                 $*
 *                                                                                             *
 *                      $Author:: Vss_sync                                                    $*
 *                                                                                             *
 *                     $Modtime:: 8/29/01 7:29p                                               $*
 *                                                                                             *
 *                    $Revision:: 23                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * Functions:                                                                                  *
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "streak.h"
#include "ww3d.h"
#include "rinfo.h"
#include "predlod.h"
#include "v3_rnd.h"
#include "texture.h"
#include "coltest.h"
#include "w3d_file.h"
#include "texture.h"
#include "dx8wrapper.h"
#include "vp.h"
#include "vector3i.h"
#include "sortingrenderer.h"

static SegLineRendererClass _LineRenderer;

// BFME's second renderer setter is the ICF twin at 0x0095C7A0, not the
// canonical SegLineRendererClass body at 0x00960050.  Keep that call target
// explicit while retaining a typed __thiscall so the emitted ABI stays the
// same as the retail member call.
class Rva0095C7A0SegLineRendererClass
{
public:
	void Set_Texture(TextureClass *texture);
};


/*
** StreakLineClass implementation:
*/

// ??0StreakLineClass@@ present-unmatched
StreakLineClass::StreakLineClass(void) :
		MaxSubdivisionLevels(0),
		NormalizedScreenArea(0.0f)
{
		Personalities = NULL;

}

// ??0StreakLineClass@@ present-unmatched
StreakLineClass::StreakLineClass(const StreakLineClass & src) :
		MaxSubdivisionLevels(src.MaxSubdivisionLevels),
		NormalizedScreenArea(src.NormalizedScreenArea),
		PointLocations(src.PointLocations),
		PointColors(src.PointColors),
		PointWidths(src.PointWidths),
		LineRenderer(src.LineRenderer),
		StreakRenderer(src.StreakRenderer),
		Personalities(src.Personalities)
{
}

// ??4StreakLineClass@@ present-unmatched
StreakLineClass & StreakLineClass::operator = (const StreakLineClass &that)
{
	RenderObjClass::operator = (that);

	if (this != &that) {

		MaxSubdivisionLevels = that.MaxSubdivisionLevels;
		NormalizedScreenArea = that.NormalizedScreenArea;
		PointLocations = that.PointLocations;
		PointColors = that.PointColors;
		PointWidths = that.PointWidths;
		LineRenderer = that.LineRenderer;
		StreakRenderer = that.StreakRenderer;
		Personalities = that.Personalities;
	}

	return * this;
}

//StreakLineClass::~StreakLineClass(void)
//{
//}





// ?Reset_Line@StreakLineClass@@ present-unmatched
void StreakLineClass::Reset_Line(void)
{
	LineRenderer.Reset_Line();
	StreakRenderer.Reset_Line();
}





////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
// These are segment points, and include the start and end point of the
// entire line. Therefore there must be at least two.
void StreakLineClass::Set_Locs( unsigned int num_points, Vector3 *locs )
{
	if (num_points < 2 || !locs) {
		WWASSERT(0);
		return;
	}

	SimpleDynVecClass<Vector3> &point_locations =
		*reinterpret_cast<SimpleDynVecClass<Vector3> *>(reinterpret_cast<char *>(this) + 0xD4);
	point_locations.Delete_All();
	for (unsigned int i=0; i<num_points; i++) {
		point_locations.Add(locs[i],num_points);
	}

	// BFME keeps RenderObjClass::Bits at +0x10 and uses bit 17 for the
	// cached bounding volumes validity flag (the shared header is ZH-shaped).
	*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(this) + 0x10) &= 0xFFFDFFFF;
}

void StreakLineClass::Set_Widths( unsigned int num_points, float *widths )
{
	if (num_points < 2 || !widths) {
		WWASSERT(0);
		return;
	}

	// BFME's StreakLine layout places PointWidths at +0xF4; the shared
	// Zero Hour declaration is four bytes earlier, so use the retail view here.
	SimpleDynVecClass<float> &point_widths =
		*reinterpret_cast<SimpleDynVecClass<float> *>(reinterpret_cast<char *>(this) + 0xF4);
	point_widths.Delete_All();
	for (unsigned int i=0; i<num_points; i++) {
		point_widths.Add(widths[i],num_points);
	}

}

void StreakLineClass::Set_Colors( unsigned int num_points, Vector4 *colors )
{
	if (num_points < 2 || !colors) {
		WWASSERT(0);
		return;
	}

	SimpleDynVecClass<Vector4> &point_colors =
		*reinterpret_cast<SimpleDynVecClass<Vector4> *>(reinterpret_cast<char *>(this) + 0xE4);
	point_colors.Delete_All();
	for (unsigned int i=0; i<num_points; i++) {
		point_colors.Add(colors[i],num_points);
	}

}

// ?Set_LocsWidthsColors@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_LocsWidthsColors( unsigned int num_points, 
																					 Vector3 *locs, 
																					 float *widths, 
																					 Vector4 *colors,
																					 unsigned int *personalities)
{

	Personalities = personalities;

	Set_Locs( num_points, locs );

	if (widths)
	{
		Set_Widths( num_points, widths );

		//sanity check
		int locCount = PointLocations.Count();
		int widCount = PointWidths.Count();
		WWASSERT(locCount == widCount);

	}

	if (colors)
	{
		Set_Colors( num_points, colors );

		//sanity check
		int locCount = PointLocations.Count();
		int colCount = PointColors.Count();
		WWASSERT(locCount == colCount);

	}


	Invalidate_Cached_Bounding_Volumes();
}



////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////







// These are segment points, and include the start and end point of the
// entire line. Therefore there must be at least two.
// ?Get_Num_Points@StreakLineClass@@ present-unmatched
int StreakLineClass::Get_Num_Points(void)
{
	int locCount = PointLocations.Count();
	return locCount;
}

// Set object-space location for a given point.
// NOTE: If given position beyond end of point list, do nothing.
void StreakLineClass::Set_Point_Location(unsigned int point_idx, const Vector3 &location)
{
	SimpleDynVecClass<Vector3> &point_locations =
		*reinterpret_cast<SimpleDynVecClass<Vector3> *>(reinterpret_cast<char *>(this) + 0xD4);
	if (point_idx < (unsigned int)point_locations.Count()) {
		point_locations[point_idx] = location;
	}
	*reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(this) + 0x10) &= 0xFFFDFFFF;
}

// Get object-space location of a given point (if position beyond end of
// point list, will return 0,0,0).
// ?Get_Point_Location@StreakLineClass@@ present-unmatched
void StreakLineClass::Get_Point_Location(unsigned int point_idx, Vector3 &loc)
{
	if (point_idx < (unsigned int)PointLocations.Count()) {
		loc.Set(PointLocations[point_idx]);
	} else {
		loc.Set(0, 0, 0);
	}
}

// ?Add_Point@StreakLineClass@@ present-unmatched
void StreakLineClass::Add_Point(const Vector3 & location)
{
	PointLocations.Add(location);
}

void StreakLineClass::Delete_Point(unsigned int point_idx)
{
	if (point_idx < *reinterpret_cast<unsigned int *>(reinterpret_cast<char *>(this) + 0xE0)) {
		SimpleDynVecClass<Vector3> &point_locations =
			*reinterpret_cast<SimpleDynVecClass<Vector3> *>(reinterpret_cast<char *>(this) + 0xD4);
		point_locations.Delete(point_idx);
	}
}


// ?Get_Texture@StreakLineClass@@ present-unmatched
TextureClass * StreakLineClass::Get_Texture(void)
{
	return LineRenderer.Get_Texture();
}

// ?Get_Shader@StreakLineClass@@ present-unmatched
ShaderClass StreakLineClass::Get_Shader(void)
{
	return LineRenderer.Get_Shader();
}

// ?Get_Color@StreakLineClass@@ present-unmatched
void StreakLineClass::Get_Color(Vector3 &color)
{
	color.Set(LineRenderer.Get_Color());
}

// ?Get_Opacity@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Opacity(void)
{
	return LineRenderer.Get_Opacity();
}

// ?Get_Noise_Amplitude@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Noise_Amplitude(void)
{
	return LineRenderer.Get_Noise_Amplitude();
}

// ?Get_Merge_Abort_Factor@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Merge_Abort_Factor(void)
{
	return LineRenderer.Get_Merge_Abort_Factor();
}

// ?Get_Subdivision_Levels@StreakLineClass@@ present-unmatched
unsigned int StreakLineClass::Get_Subdivision_Levels(void)
{
	return MaxSubdivisionLevels;
}

// ?Get_Texture_Mapping_Mode@StreakLineClass@@ present-unmatched
SegLineRendererClass::TextureMapMode StreakLineClass::Get_Texture_Mapping_Mode(void)
{
	return LineRenderer.Get_Texture_Mapping_Mode(); 
}

// ?Get_Texture_Tile_Factor@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Texture_Tile_Factor(void)
{
	return LineRenderer.Get_Texture_Tile_Factor();
}

// ?Get_UV_Offset_Rate@StreakLineClass@@ present-unmatched
Vector2 StreakLineClass::Get_UV_Offset_Rate(void)
{
	return LineRenderer.Get_UV_Offset_Rate();
}

// ?Is_Merge_Intersections@StreakLineClass@@ present-unmatched
int StreakLineClass::Is_Merge_Intersections(void)
{
	return LineRenderer.Is_Merge_Intersections();
}

// ?Is_Freeze_Random@StreakLineClass@@ present-unmatched
int StreakLineClass::Is_Freeze_Random(void)
{
	return LineRenderer.Is_Freeze_Random();
}

// ?Is_Sorting_Disabled@StreakLineClass@@ present-unmatched
int StreakLineClass::Is_Sorting_Disabled(void)
{
	return LineRenderer.Is_Sorting_Disabled();
}

// ?Are_End_Caps_Enabled@StreakLineClass@@ present-unmatched
int StreakLineClass::Are_End_Caps_Enabled(void)
{
	return LineRenderer.Are_End_Caps_Enabled();
}

void StreakLineClass::Set_Texture(TextureClass *texture)
{
	reinterpret_cast<SegLineRendererClass *>(reinterpret_cast<char *>(this) + 0x104)->Set_Texture(texture);
	reinterpret_cast<Rva0095C7A0SegLineRendererClass *>(reinterpret_cast<char *>(this) + 0x154)->Set_Texture(texture);
}

// ?Set_Shader@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Shader(ShaderClass shader)
{
	LineRenderer.Set_Shader(shader);
	StreakRenderer.Set_Shader(shader);
}

// ?Get_Width@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Width(void)
{
	return LineRenderer.Get_Width();
}

// ?Set_Width@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Width(float width)
{
	// Widths need to be clamped because they are not automatically clamped later (like colors and
	// alphas are).
	LineRenderer.Set_Width(MAX(width, 0.0f));
	StreakRenderer.Set_Width(MAX(width, 0.0f));

	Invalidate_Cached_Bounding_Volumes();
}

void StreakLineClass::Set_Color(const Vector3 &color)
{
	reinterpret_cast<SegLineRendererClass *>(reinterpret_cast<char *>(&LineRenderer) + 0x34)->Set_Color(color);
	reinterpret_cast<StreakRendererClass *>(reinterpret_cast<char *>(&StreakRenderer) + 0x38)->Set_Color(color);
}

// BFME embeds the renderers 0x34 and 0x38 bytes after their ZH offsets.
void StreakLineClass::Set_Opacity(float opacity)
{
	reinterpret_cast<SegLineRendererClass *>(reinterpret_cast<char *>(&LineRenderer) + 0x34)->Set_Opacity(opacity);
	reinterpret_cast<StreakRendererClass *>(reinterpret_cast<char *>(&StreakRenderer) + 0x38)->Set_Opacity(opacity);
}

// ?Set_Noise_Amplitude@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Noise_Amplitude(float amplitude)
{
	LineRenderer.Set_Noise_Amplitude(WWMath::Fabs(amplitude));

	Invalidate_Cached_Bounding_Volumes();
}

void StreakLineClass::Set_Merge_Abort_Factor(float factor)
{
	LineRenderer.Set_Merge_Abort_Factor(factor);
}

// ?Set_Subdivision_Levels@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Subdivision_Levels(unsigned int levels)
{
	MaxSubdivisionLevels = MIN(levels, MAX_SEGLINE_SUBDIV_LEVELS);

	Invalidate_Cached_Bounding_Volumes();
}

void StreakLineClass::Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode mode)
{
	// BFME's renderer members sit later than the GeneralsMD layout supplied by the reference header.
	StreakLineClass *bfme_line_layout = reinterpret_cast<StreakLineClass *>(reinterpret_cast<char *>(this) + 0x38);
	StreakLineClass *bfme_streak_layout = reinterpret_cast<StreakLineClass *>(reinterpret_cast<char *>(this) + 0x50);
	bfme_line_layout->LineRenderer.Set_Texture_Mapping_Mode(mode);
	bfme_streak_layout->StreakRenderer.Set_Texture_Mapping_Mode(static_cast<StreakRendererClass::TextureMapMode>(mode));
}

// ?Set_Texture_Tile_Factor@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Texture_Tile_Factor(float factor)
{
	LineRenderer.Set_Texture_Tile_Factor(factor);
}

// ?Set_UV_Offset_Rate@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_UV_Offset_Rate(const Vector2 &rate)
{
	LineRenderer.Set_UV_Offset_Rate(rate);
}

// ?Set_Merge_Intersections@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Merge_Intersections(int onoff)
{
	LineRenderer.Set_Merge_Intersections(onoff);
}

// ?Set_Freeze_Random@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Freeze_Random(int onoff)
{
	LineRenderer.Set_Freeze_Random(onoff);
}


// ?Set_Disable_Sorting@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Disable_Sorting(int onoff)
{
	LineRenderer.Set_Disable_Sorting(onoff);
}

// ?Set_End_Caps@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_End_Caps(int onoff)
{
	LineRenderer.Set_End_Caps(onoff);
}

/*
** RenderObjClass interface:
*/

// ?Clone@StreakLineClass@@ present-unmatched
RenderObjClass * StreakLineClass::Clone(void) const
{
	return NEW_REF( StreakLineClass, (*this)); 
}

// ?Get_Num_Polys@StreakLineClass@@ present-unmatched
int StreakLineClass::Get_Num_Polys(void) const
{
	int subdivision_factor = 1 << LineRenderer.Get_Current_Subdivision_Level();
	return 2 * (PointLocations.Count() - 1) * subdivision_factor;
}

// The shared declaration places visibility eight bytes earlier. The native slot
// +0x180 routes through ILT 0x0000BF1E to the matched RenderObjClass
// Is_Not_Hidden_At_All body, 0x006CF6D0. Keep the correction local to this TU.
class Rva0091A600VisibilityView
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92(); virtual void slot93(); virtual void slot94(); virtual void slot95();
	virtual int Is_Not_Hidden_At_All();
};

void StreakLineClass::Render(RenderInfoClass & rinfo)
{
	if (reinterpret_cast<Rva0091A600VisibilityView *>(this)->Is_Not_Hidden_At_All() == false) {
		return ;
	}

	// Process texture reductions:
//	if (LineRenderer.Peek_Texture()) LineRenderer.Peek_Texture()->Process_Reduction();

	unsigned int sort_level = SORT_LEVEL_NONE;

	if (!WW3D::Is_Sorting_Enabled())	
		sort_level=reinterpret_cast<SegLineRendererClass *>(reinterpret_cast<char *>(this) + 0x104)->Get_Shader().Guess_Sort_Level();	

	if (WW3D::Are_Static_Sort_Lists_Enabled() && sort_level!=SORT_LEVEL_NONE) {		
		
		WW3D::Add_To_Static_Sort_List(this, sort_level);

	} 
	else
	{
		if ( !reinterpret_cast<SimpleDynVecClass<Vector4> *>(reinterpret_cast<char *>(this) + 0xE4)->Count() ||
			 !reinterpret_cast<SimpleDynVecClass<float> *>(reinterpret_cast<char *>(this) + 0xF4)->Count() )
		{
			Render_Seg_Line(rinfo);
		}
		else
		{
			Render_Streak_Line(rinfo);
		}
	}
}

// ?Get_Obj_Space_Bounding_Sphere@StreakLineClass@@ present-unmatched
void StreakLineClass::Get_Obj_Space_Bounding_Sphere(SphereClass & sphere) const
{
	// Get object-space bounding box and create bounding sphere from it
	AABoxClass box;
	Get_Obj_Space_Bounding_Box(box);

	// Create object-space bounding sphere from the bounding box:
	sphere.Center = box.Center;
	sphere.Radius = box.Extent.Length();
}

// Retail bounding-box implementation: StreakLineClass_Get_Obj_Space_Bounding_Box.cpp.

// ?Prepare_LOD@StreakLineClass@@ present-unmatched
void StreakLineClass::Prepare_LOD(CameraClass &camera)
{
	// Find the maximum screen dimension of the object in pixels
	NormalizedScreenArea = Get_Screen_Size(camera);

//	// Find and set texture reduction factor
//   Set_Texture_Reduction_Factor(Calculate_Texture_Reduction_Factor(NormalizedScreenArea));

	// Ensure subdivision level is legal
	unsigned int lvl = LineRenderer.Get_Current_Subdivision_Level();
	lvl = MIN(lvl, MaxSubdivisionLevels);
	LineRenderer.Set_Current_Subdivision_Level(lvl);

	// Prepare LOD processing if the line has subdivision enabled:
	if (MaxSubdivisionLevels > 0) {
		// Add myself to the LOD optimizer:
		PredictiveLODOptimizerClass::Add_Object(this);
	} else {
		// Not added to optimizer, need to add cost
		PredictiveLODOptimizerClass::Add_Cost(Get_Cost());
	}
}

// ?Increment_LOD@StreakLineClass@@ present-unmatched
void StreakLineClass::Increment_LOD(void)
{
	unsigned int lvl = LineRenderer.Get_Current_Subdivision_Level();
	
	lvl = MIN(lvl+1,MaxSubdivisionLevels);
	
	LineRenderer.Set_Current_Subdivision_Level(lvl);
}

// ?Decrement_LOD@StreakLineClass@@ present-unmatched
void StreakLineClass::Decrement_LOD(void)
{
	int lvl = LineRenderer.Get_Current_Subdivision_Level();
	if (lvl == 0) return;
	LineRenderer.Set_Current_Subdivision_Level(lvl-1);
}

// ?Get_Cost@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Cost(void) const
{
	return Get_Num_Polys();
}

// ?Get_Value@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Value(void) const
{
	// If we are at the minimum LOD, we must return AT_MIN_LOD.
	if (LineRenderer.Get_Current_Subdivision_Level() == 0) {
		return AT_MIN_LOD;
	} else {
		float polycount = (float)Get_Num_Polys();
		float benefit_factor = 1.0f - (0.5f / (polycount * polycount));
		return (benefit_factor * NormalizedScreenArea) / Get_Cost();
	}
}

// ?Get_Post_Increment_Value@StreakLineClass@@ present-unmatched
float StreakLineClass::Get_Post_Increment_Value(void) const
{
	// If we are at the maximum LOD, we must return AT_MIN_LOD.
	if (LineRenderer.Get_Current_Subdivision_Level() == MaxSubdivisionLevels) {
		return AT_MAX_LOD;
	} else {
		// Assumption: each subdivision level doubles polycount
		float polycount = 2.0f * (float)Get_Num_Polys();
		float benefit_factor = 1.0f - (0.5f / (polycount * polycount));
		// Assumption: Cost() == polycount
		return (benefit_factor * NormalizedScreenArea) / polycount;
	}
}

// ?Set_LOD_Level@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_LOD_Level(int lod)
{
	lod = MAX(0, lod);
	lod = MIN(lod, (int)MaxSubdivisionLevels);

	LineRenderer.Set_Current_Subdivision_Level((unsigned int)lod);
}

int StreakLineClass::Get_LOD_Level(void) const
{
	return (int) LineRenderer.Get_Current_Subdivision_Level();
}

// ?Get_LOD_Count@StreakLineClass@@ present-unmatched
int StreakLineClass::Get_LOD_Count(void) const
{
	return (int)MaxSubdivisionLevels;
}
/*
// ?Set_Texture_Reduction_Factor@StreakLineClass@@ present-unmatched
void StreakLineClass::Set_Texture_Reduction_Factor(float trf)
{
	if (LineRenderer.Peek_Texture()) LineRenderer.Peek_Texture()->Set_Reduction_Factor(trf);
}*/

 

// ?Render_Streak_Line@StreakLineClass@@ present-unmatched
void StreakLineClass::Render_Streak_Line(RenderInfoClass & rinfo)
{

	WWASSERT(PointLocations.Count() == PointColors.Count());
	WWASSERT(PointLocations.Count() == PointWidths.Count());

	// Line must have at least two points to be valid
	if (PointLocations.Count() < 2) return;
	if (PointColors.Count() < 2) return;
	if (PointWidths.Count() < 2) return;

	if(PointLocations.Count() != PointColors.Count()) return;
	if(PointLocations.Count() != PointWidths.Count()) return;

	SphereClass bounding_sphere;
	Get_Obj_Space_Bounding_Sphere(bounding_sphere);			


//	StreakRenderer.Render(
//		rinfo,
//		Transform,
//		PointLocations.Count(),
//		&(PointLocations[0]),
//		bounding_sphere
//		);
	StreakRenderer.RenderStreak(
		rinfo,
		Transform,
		PointLocations.Count(),
		&(PointLocations[0]),
		&(PointColors[0]),
		&(PointWidths[0]),
		bounding_sphere,
		Personalities
		);
}


// BFME's collision-mask virtual is at +0x1dc (ZH declares +0x1b4).
// A single-inheritance member pointer describes the four-byte vtable entry.
struct BfmeStreakCollisionView
{
    typedef int (BfmeStreakCollisionView::*GetMask)();
    struct Vtable { void *slots[119]; GetMask getMask; };
    Vtable *vtable;
    int collisionMask() { return (this->*(vtable->getMask))(); }
};

bool StreakLineClass::Cast_Ray(RayCollisionTestClass & raytest)
{
	const Matrix3D &transform = *(const Matrix3D *)((const char *)this + 0x18);
	if ((((BfmeStreakCollisionView *)this)->collisionMask() & raytest.CollisionType) == 0) return false;

	bool retval = false;

	//
	//	Check each line segment against the ray
	//
	float fraction = 1.0F;
	for (uint32 index = 1; index < (unsigned int)*(const int *)((const char *)this + 0xe0); index ++) 
	{
#ifdef ALLOW_TEMPORARIES
		Vector3 curr_start	= Transform * PointLocations[index-1];
		Vector3 curr_end		= Transform * PointLocations[index];
		LineSegClass line_seg (curr_start, curr_end);
#else
		Vector3 curr[2];
		transform.mulVector3Array(&(*(Vector3 **)((char *)this + 0xd8))[index-1], curr, 2);
		LineSegClass line_seg(curr[0], curr[1]);
#endif
		
		Vector3 p0;
		Vector3 p1;
		if (raytest.Ray.Find_Intersection (line_seg, &p0, &fraction, &p1, NULL)) {
			
			//
			//	Determine if the ray was close enough to this line to be
			// considered intersecting
			//
			float dist = (p0 - p1).Length ();
			if (dist <= *(const float *)((const char *)this + 0x10c) && fraction >= 0 && fraction < raytest.Result->Fraction) {
			//if (dist <= Width && fraction < raytest.Result->Fraction) {
				retval = true;
				break;
			}
		}			
	}

	//
	//	Fill in the raytest structure if we were successfull
	//
	if (retval) {
		raytest.Result->Fraction		= fraction;
		raytest.Result->SurfaceType	= SURFACE_TYPE_DEFAULT;
		raytest.CollidedRenderObj		= this;
	}

	return retval;
}
