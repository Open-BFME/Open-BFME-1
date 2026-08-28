// cl: /DNDEBUG /MD /EHsc /ICode/GameEngine/Include/Precompiled /ICode/GameEngine/Source/Common/System /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
// readable body of ?getApproximateLength@BezierSegment@@: Code/GameEngine/Source/Common/Bezier/BezierSegment.cpp
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

// BFME's BezierSegment holds an ARRAY of a 12-byte point type that has an
// out-of-line (empty) default ctor and dtor: retail's ctor/dtor bodies drive
// the elements through `eh vector constructor iterator' / `eh vector destructor
// iterator' with size 0xc and count 4, and the two element hooks are the
// out-of-line ??0Coord3D@@QAE@XZ / ??1Coord3D@@QAE@XZ. The shared coord.h shim
// carries a POD Coord3D instead, so the declaration is kept source-local here
// rather than editing that header.

#include <math.h>

typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D();
	~Coord3D();

	Real x, y, z;

	void zero( void ) { x = 0.0f; y = 0.0f; z = 0.0f; }
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BezierSegment.h
class BezierSegment
{
	protected:
		Coord3D m_controlPoints[4];

	public:
		BezierSegment();
		BezierSegment(Coord3D cp[4]);

		Real getApproximateLength(Real withinTolerance) const;
		void splitSegmentAtT(Real tValue, BezierSegment &outSeg1, BezierSegment &outSeg2) const;
};

// The difference vectors retail spills are NOT contiguous on the stack, so the
// locals are a plain aggregate whose fields the optimiser scalarises -- not the
// ctor/dtor-bearing element type m_controlPoints is made of.
struct W4Vec
{
	Real x, y, z;

	W4Vec( Real _x, Real _y, Real _z ) { x = _x; y = _y; z = _z; }

	Real length( void ) const { return (Real)sqrt( x*x + y*y + z*z ); }
};

//-------------------------------------------------------------------------------------------------
BezierSegment::BezierSegment()
{ 
	for(int i=0; i < 4; i++)
		m_controlPoints[i].zero();
}

//-------------------------------------------------------------------------------------------------
BezierSegment::BezierSegment(Coord3D cp[4])
{
	m_controlPoints[0] = cp[0];
	m_controlPoints[1] = cp[1];
	m_controlPoints[2] = cp[2];
	m_controlPoints[3] = cp[3];
}

//-------------------------------------------------------------------------------------------------
Real BezierSegment::getApproximateLength(Real withinTolerance) const
{
	W4Vec p0p1( m_controlPoints[1].x - m_controlPoints[0].x, m_controlPoints[1].y - m_controlPoints[0].y, m_controlPoints[1].z - m_controlPoints[0].z );

	W4Vec p1p2( m_controlPoints[2].x - m_controlPoints[1].x, m_controlPoints[2].y - m_controlPoints[1].y, m_controlPoints[2].z - m_controlPoints[1].z );

	W4Vec p2p3( m_controlPoints[3].x - m_controlPoints[2].x, m_controlPoints[3].y - m_controlPoints[2].y, m_controlPoints[3].z - m_controlPoints[2].z );

	W4Vec p0p3( m_controlPoints[3].x - m_controlPoints[0].x, m_controlPoints[3].y - m_controlPoints[0].y, m_controlPoints[3].z - m_controlPoints[0].z );

	Real length0 = p0p3.length();
	Real length1 = p0p1.length() + p1p2.length() + p2p3.length();

	if ((length1 - length0) > withinTolerance) {
		BezierSegment seg1, seg2;
		splitSegmentAtT(0.5f, seg1, seg2);
		return (seg1.getApproximateLength(withinTolerance) + seg2.getApproximateLength(withinTolerance));
	}

	return ((length0 + length1) / 2.0f);
}
