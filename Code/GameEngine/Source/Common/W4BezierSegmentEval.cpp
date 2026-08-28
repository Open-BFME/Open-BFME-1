// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/Precompiled /ICode/GameEngine/Source/Common/System /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// stlport
// readable body of ?evaluateBezSegmentAtT@BezierSegment@@: Code/GameEngine/Source/Common/Bezier/BezierSegment.cpp
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

// The retail call site is `call _D3DXVec4Transform@12` -- a __stdcall import
// from d3dx8.lib, not the __cdecl inline the local d3dx8math.h shim carries.
// Rename the shim's inline out of the way for this TU only (the shim is shared
// and must not be edited) and declare the real stdcall entry point.
#define D3DXVec4Transform D3DXVec4Transform_cdecl_shim_unused
#include "bezier_segment.h"
#undef D3DXVec4Transform

extern "C" D3DXVECTOR4* __stdcall D3DXVec4Transform(D3DXVECTOR4 *pOut,
																									 const D3DXVECTOR4 *pV,
																									 const D3DXMATRIX *pM);

//-------------------------------------------------------------------------------------------------
void BezierSegment::evaluateBezSegmentAtT(Real tValue, Coord3D *outResult) const

{
	if (!outResult)
		return;

	D3DXVECTOR4	tVec(tValue * tValue * tValue, tValue * tValue, tValue, 1);

	D3DXVECTOR4 xCoords(m_controlPoints[0].x, m_controlPoints[1].x, m_controlPoints[2].x, m_controlPoints[3].x);
	D3DXVECTOR4 yCoords(m_controlPoints[0].y, m_controlPoints[1].y, m_controlPoints[2].y, m_controlPoints[3].y);
	D3DXVECTOR4 zCoords(m_controlPoints[0].z, m_controlPoints[1].z, m_controlPoints[2].z, m_controlPoints[3].z);

	D3DXVECTOR4 tResult;
	D3DXVec4Transform(&tResult, &tVec, &BezierSegment::s_bezBasisMatrix);
	
	outResult->x = D3DXVec4Dot(&xCoords, &tResult);
	outResult->y = D3DXVec4Dot(&yCoords, &tResult);
	outResult->z = D3DXVec4Dot(&zCoords, &tResult);
}
