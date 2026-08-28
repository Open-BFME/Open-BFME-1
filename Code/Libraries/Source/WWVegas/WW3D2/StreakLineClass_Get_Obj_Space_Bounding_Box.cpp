// cl: /DNDEBUG /MD /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// readable body of ?Get_Obj_Space_Bounding_Box@StreakLineClass@@: Code/Libraries/Source/WWVegas/WW3D2/streak.cpp
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

// StreakLineClass::Get_Obj_Space_Bounding_Box -- Zero Hour's streak.cpp body,
// compiled against the BFME object layout instead of the ZH one.
//
// The body itself never drifted: compiling the stock ZH source reproduces all
// 2279 retail bytes instruction for instruction. Only seven displacements come
// out wrong, and every one of them is a member offset:
//
//     MaxSubdivisionLevels   ZH 0x94  retail 0xC8
//     PointLocations.Vector  ZH 0xA4  retail 0xD8
//     PointLocations.Count   ZH 0xAC  retail 0xE0
//     LineRenderer.Width     ZH 0xD8  retail 0x10C
//     LineRenderer.NoiseAmp  ZH 0xF0  retail 0x128
//
// Two independent drifts add up to that. RenderObjClass is 0xC8 bytes in BFME
// rather than ZH's 0x94 (reference/shims/sweep/rendobj.h carries the members
// that grew it), which shifts the whole StreakLineClass tail by 0x34; and
// SegLineRendererClass carries one extra unidentified dword at +0x1C
// (seglinerenderer.h here), which shifts NoiseAmplitude by a further 4 so the
// last displacement moves 0x38 instead of 0x34.
//
// streak.cpp cannot pick either correction up: it reaches RenderObjClass and
// SegLineRendererClass through the vendored ZH streak.h, whose own directory
// wins the quoted-include search, so the sweep shim and the WW3D2 header in
// this tree are both bypassed. This translation unit is the same lift that
// StreakLineClass_Set_Widths_Thunk.cpp already does for Set_Widths: spell the
// class locally at the retail offsets and let the stock body compile against
// it. The base is opaque here -- only its size matters -- so it is a pad, and
// PointWidths at 0xF4 agrees with the offset that thunk proved.
//
// The function is a leaf: every helper it uses (Vector3::Update_Min/Update_Max,
// the arithmetic operators, AABoxClass::Init and Init_Min_Max) is WWINLINE, and
// retail emits no calls at all between the prologue and either `ret 4`.

#include "always.h"
#include "aabox.h"
#include "simplevec.h"
#include "vector3.h"
#include "vector4.h"
#include "seglinerenderer.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/streak.h
class StreakLineClass
{
public:

	virtual void					Get_Obj_Space_Bounding_Box(AABoxClass & box) const;

private:

	// vtable pointer at +0x00, RenderObjClass base out to sizeof() == 0xC8.
	unsigned char					m_unreconstructed_04[0xC4];

	// Subdivision properties
	unsigned int					MaxSubdivisionLevels;		///< retail this+0x0C8

	// per-particle seeds
	unsigned int					*Personalities;				///< retail this+0x0CC

	// Normalized screen area - used for LOD purposes
	float								NormalizedScreenArea;	///< retail this+0x0D0

	SimpleDynVecClass<Vector3>	PointLocations;				///< retail this+0x0D4
	SimpleDynVecClass<Vector4>	PointColors;					///< retail this+0x0E4
	SimpleDynVecClass<float>	PointWidths;					///< retail this+0x0F4

	SegLineRendererClass			LineRenderer;				///< retail this+0x104
};

// ?Get_Obj_Space_Bounding_Box@StreakLineClass@@UBEXAAVAABoxClass@@@Z
void StreakLineClass::Get_Obj_Space_Bounding_Box(AABoxClass & box) const
{
	unsigned int num_points = PointLocations.Count();

	// Line must have at least two points to be valid

	if (num_points >= 2) {

		// Find object-space axis-aligned bounding box
		Vector3 max_coords;
		Vector3 min_coords;
		unsigned int i;

		// We create two bounding boxes; one from the points, and if we have random noise
		// subdivision we create another one from the midpoints and factor the noise amplitude
		// into the second box, and then combine the two.

		// First bounding box:
		max_coords = PointLocations[0];
		min_coords = PointLocations[0];
		for (i = 1; i < num_points; i++) {
			max_coords.Update_Max(PointLocations[i]);
			min_coords.Update_Min(PointLocations[i]);
		}
		// Enlarge bounding box by half the width
		float enlarge_factor = LineRenderer.Get_Width() * 0.5f;
		Vector3 enlarge_offset;
		enlarge_offset.Set(enlarge_factor, enlarge_factor, enlarge_factor);
		max_coords += enlarge_offset;
		min_coords -= enlarge_offset;

		if (MaxSubdivisionLevels > 0) {
			// Second bounding box:
			Vector3 max_coords2;
			Vector3 min_coords2;
			Vector3 midpoint = (PointLocations[0] + PointLocations[1]) * 0.5f;
			max_coords2 = midpoint;
			min_coords2 = midpoint;
			for (i = 1; i < num_points - 1; i++) {
				midpoint = (PointLocations[i] + PointLocations[i + 1]) * 0.5f;
				max_coords2.Update_Max(midpoint);
				min_coords2.Update_Min(midpoint);
			}

			// We ignore the actual number of subdivision levels: we multiply the random noise
			// amplitude by 2, which is the limit as the number of subdivision levels goes to
			// infinity.
			enlarge_factor += (2 * LineRenderer.Get_Noise_Amplitude());
			enlarge_offset.Set(enlarge_factor, enlarge_factor, enlarge_factor);
			max_coords2 += enlarge_offset;
			min_coords2 -= enlarge_offset;

			// Combine the two:
			max_coords.Update_Max(max_coords2);
			min_coords.Update_Min(min_coords2);
		}

		box.Init_Min_Max(min_coords, max_coords);

	} else {
		// Invalid line - return something
		box.Init(Vector3(0,0,0),Vector3(1,1,1));
	}
}
