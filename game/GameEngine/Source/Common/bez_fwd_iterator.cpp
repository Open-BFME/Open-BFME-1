// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define D3DXMATRIX _D3DXMATRIX
#include <vector>
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

#include "prerts.h"
#include "coord.h"
#include "bez_fwd_iterator.h"

//-------------------------------------------------------------------------------------------------
BezFwdIterator::BezFwdIterator(): mStep(0), mStepsDesired(0)
{ 
	// Added by Sadullah Nader
	mCurrPoint.zero();
	mDDDq.zero();
	mDDq.zero();
	mDq.zero();
} 

// Retail BezFwdIterator::BezFwdIterator (0x000B65C0) is implemented in BezFwdIterator.cpp.

// start, done and next are owned by Common/Bezier/BezFwdIterator.cpp.

const Coord3D& BezFwdIterator::getCurrent(void) const
{
	return mCurrPoint;
}

