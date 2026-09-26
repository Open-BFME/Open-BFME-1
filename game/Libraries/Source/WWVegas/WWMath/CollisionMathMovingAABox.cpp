// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
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

// BFME RVA 0x008DA000, complete 237-byte moving-AABox collision test.
// The visible helper preserves the retail TU-local register calling convention.
#include "colmath.h"
#include "colmathinlines.h"
#include "aaplane.h"
#include "plane.h"
#include "lineseg.h"
#include "tri.h"
#include "sphere.h"
#include "aabox.h"
#include "obbox.h"
#include "wwdebug.h"

/*
** AABCollisionStruct
** Contains all of the intermediate and temporary values used by
** the set of functions used in detecting collisions for aab's
*/
struct AABCollisionStruct
{
	AABCollisionStruct(const AABoxClass &box0,const Vector3 &move0,const AABoxClass & box1,const Vector3 &move1) :
		StartBad(true),													// Startbad is true until one of the axes clears it
		AxisId(-1),															// AxisId will be the axis that allowed the longest move
		MaxFrac(0.0f),
		Side(0), // BFME initializes the collision side even before an axis wins.
		Box0(box0),															
		Box1(box1)
	{
		Vector3::Subtract(box1.Center,box0.Center,&C);			// vector from center of box0 to center of box1
		Vector3::Subtract(move1,move0,&M);							// move vector relative to stationary box0
	}

	bool						StartBad;			// Inital configuration is intersecting?
	float						MaxFrac;				// Longest move allowed so far
	int						AxisId;				// Last separating axis
	int						Side;					// which side of the interval

	Vector3					C;						// Vector from the center0 to center1
	Vector3					M;						// Move vector relative to stationary box0
	
	const AABoxClass &	Box0;
	const AABoxClass &	Box1;

private:

	//not implemented
	AABCollisionStruct(const AABCollisionStruct&);
	AABCollisionStruct & operator = (const AABCollisionStruct&);
};


/***********************************************************************************************
 * aab_separation_test -- tests two AAB's for separation on an axis                            *
 *                                                                                             *
 * This function is very similar to the obb_separation_test.  If a flaw is found in either,    *
 * we should update the other...                                                               *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   11/19/99   gth : Created.                                                                 *
 *=============================================================================================*/
static inline bool aab_separation_test
(
	AABCollisionStruct & context,
	int						axis
)
{
	// ra = box0 projection onto the axis
	// rb = box1 projection onto the axis
	// u0 = projected distance between the box centers at t0
	// u1 = projected distance between the box centers at t1
	float ra = context.Box0.Extent[axis];
	float rb = context.Box1.Extent[axis];
	float u0 = context.C[axis];
	float u1 = u0 + context.M[axis];

	float tmp;
	float rsum = ra+rb;

	if ( u0 + WWMATH_EPSILON > rsum ) { 
		context.StartBad = false; 
		if ( u1 > rsum ) { 
			context.MaxFrac = 1.0f; 
			return true;
		} else { 
			tmp = (rsum-u0)/(u1-u0);
			if ( tmp > context.MaxFrac ) {
				context.MaxFrac = tmp; 
				context.AxisId = axis;
				context.Side = +1;
			}
		}
	} else if ( u0 - WWMATH_EPSILON < -rsum ) {
		context.StartBad = false;
		if ( u1 < -rsum ) {
			context.MaxFrac = 1.0f; 
			return true;
		} else {
			tmp = (-rsum-u0)/(u1-u0);
			if ( tmp > context.MaxFrac ) {
				context.MaxFrac = tmp;
				context.AxisId = axis;
				context.Side = -1;
			} 
		} 
	} 
	return false;
}


/***********************************************************************************************
 * CollisionMath::Collide -- Collision test for two moving AABoxes                             *
 *                                                                                             *
 * this function sweeps two AABoxes and finds the first time of collision.                     *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 * currently there is no parateter for the movement of the second box.  the internal code      *
 * can handle it though.                                                                       *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   11/19/99   gth : Created.                                                                 *
 *=============================================================================================*/
bool CollisionMath::Collide(const AABoxClass & box,const Vector3 & move,const AABoxClass & box2,CastResultStruct * result)
{
	/*
	**	Test the X-axis
	** ra = box projection onto the axis
	** rb = box2 projection onto the axis
	** u0 = projected distance between the box centers at t0
	** u1 = projected distance between the box centers at t1
	*/
	AABCollisionStruct context(box,move,box2,Vector3(0,0,0));

	if (aab_separation_test(context,0)) {
		goto exit;
	}

	if (aab_separation_test(context,1)) {
		goto exit;
	}
	
	if (aab_separation_test(context,2)) {
		goto exit;
	}

exit:

	if (context.StartBad) {
		result->StartBad = true;
		result->Fraction = 0.0f;
		return true;
	}

	if (context.MaxFrac < result->Fraction) {

		result->Fraction = context.MaxFrac;
		result->Normal.Set(0,0,0);
		result->Normal[context.AxisId] = -context.Side;

		if (result->ComputeContactPoint) {
			//WWASSERT(0); // TODO
			WWDEBUG_SAY(("AABox-AABox collision does not currently support contact point computation\r\n"));
		}

		return true;
	}
	return false;
}
