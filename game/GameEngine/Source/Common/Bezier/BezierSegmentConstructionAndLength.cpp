// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
// readable body of ?getApproximateLength@BezierSegment@@: game/GameEngine/Source/Common/Bezier/BezierSegment.cpp
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

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D();
	~Coord3D();

	Real x, y, z;

	void zero( void ) { x = 0.0f; y = 0.0f; z = 0.0f; }
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/BezierSegment.h
class BezierSegment
{
	protected:
		Coord3D m_controlPoints[4];

	public:
		BezierSegment();
		BezierSegment(Coord3D controlPoints[4]);

		Real getApproximateLength(Real withinTolerance) const;
		void splitSegmentAtT(Real tValue, BezierSegment &outSeg1, BezierSegment &outSeg2) const;
};

// BFME has a second copy of the scalar constructor in this translation unit's
// constructor family.  The canonical ZH spelling is already claimed at a
// different retail address, so keep this independently evidenced body under
// an address-derived class name while preserving the proven layout.
class Rva000B6D50BezierSegment
{
		Coord3D m_controlPoints[4];

	public:
		Rva000B6D50BezierSegment(Real x0, Real y0, Real z0,
											 Real x1, Real y1, Real z1,
											 Real x2, Real y2, Real z2,
											 Real x3, Real y3, Real z3);
		Rva000B6D50BezierSegment(Real controlPointCoordinates[12]);
		Rva000B6D50BezierSegment(const Coord3D& cp0, const Coord3D& cp1,
											 const Coord3D& cp2, const Coord3D& cp3);
};

// The difference vectors retail spills are NOT contiguous on the stack, so the
// locals are a plain aggregate whose fields the optimiser scalarises -- not the
// ctor/dtor-bearing element type m_controlPoints is made of.
struct BezierDifferenceVector
{
	Real x, y, z;

	BezierDifferenceVector( Real _x, Real _y, Real _z ) { x = _x; y = _y; z = _z; }

	Real length( void ) const { return (Real)sqrt( x*x + y*y + z*z ); }
};

//-------------------------------------------------------------------------------------------------
BezierSegment::BezierSegment()
{ 
	for(int controlPointIndex=0; controlPointIndex < 4; controlPointIndex++)
		m_controlPoints[controlPointIndex].zero();
}

//-------------------------------------------------------------------------------------------------
BezierSegment::BezierSegment(Coord3D controlPoints[4])
{
	m_controlPoints[0] = controlPoints[0];
	m_controlPoints[1] = controlPoints[1];
	m_controlPoints[2] = controlPoints[2];
	m_controlPoints[3] = controlPoints[3];
}

Rva000B6D50BezierSegment::Rva000B6D50BezierSegment(Real x0, Real y0, Real z0,
																					 Real x1, Real y1, Real z1,
																					 Real x2, Real y2, Real z2,
																					 Real x3, Real y3, Real z3)
{
		m_controlPoints[0].x = x0;
		m_controlPoints[0].y = y0;
		m_controlPoints[0].z = z0;

		m_controlPoints[1].x = x1;
		m_controlPoints[1].y = y1;
		m_controlPoints[1].z = z1;

		m_controlPoints[2].x = x2;
		m_controlPoints[2].y = y2;
		m_controlPoints[2].z = z2;

		m_controlPoints[3].x = x3;
		m_controlPoints[3].y = y3;
		m_controlPoints[3].z = z3;
}

Rva000B6D50BezierSegment::Rva000B6D50BezierSegment(Real controlPointCoordinates[12])
{
		m_controlPoints[0].x = controlPointCoordinates[0];
		m_controlPoints[0].y = controlPointCoordinates[1];
		m_controlPoints[0].z = controlPointCoordinates[2];

		m_controlPoints[1].x = controlPointCoordinates[3];
		m_controlPoints[1].y = controlPointCoordinates[4];
		m_controlPoints[1].z = controlPointCoordinates[5];

		m_controlPoints[2].x = controlPointCoordinates[6];
		m_controlPoints[2].y = controlPointCoordinates[7];
		m_controlPoints[2].z = controlPointCoordinates[8];

		m_controlPoints[3].x = controlPointCoordinates[9];
		m_controlPoints[3].y = controlPointCoordinates[10];
		m_controlPoints[3].z = controlPointCoordinates[11];
}

Rva000B6D50BezierSegment::Rva000B6D50BezierSegment(const Coord3D& cp0,
																			 const Coord3D& cp1,
																			 const Coord3D& cp2,
																			 const Coord3D& cp3)
{
		m_controlPoints[0] = cp0;
		m_controlPoints[1] = cp1;
		m_controlPoints[2] = cp2;
		m_controlPoints[3] = cp3;
}

//-------------------------------------------------------------------------------------------------
Real BezierSegment::getApproximateLength(Real withinTolerance) const
{
	BezierDifferenceVector p0p1( m_controlPoints[1].x - m_controlPoints[0].x, m_controlPoints[1].y - m_controlPoints[0].y, m_controlPoints[1].z - m_controlPoints[0].z );

	BezierDifferenceVector p1p2( m_controlPoints[2].x - m_controlPoints[1].x, m_controlPoints[2].y - m_controlPoints[1].y, m_controlPoints[2].z - m_controlPoints[1].z );

	BezierDifferenceVector p2p3( m_controlPoints[3].x - m_controlPoints[2].x, m_controlPoints[3].y - m_controlPoints[2].y, m_controlPoints[3].z - m_controlPoints[2].z );

	BezierDifferenceVector p0p3( m_controlPoints[3].x - m_controlPoints[0].x, m_controlPoints[3].y - m_controlPoints[0].y, m_controlPoints[3].z - m_controlPoints[0].z );

	Real chordLength = p0p3.length();
	Real controlPolygonLength = p0p1.length() + p1p2.length() + p2p3.length();

	if ((controlPolygonLength - chordLength) > withinTolerance) {
		BezierSegment firstHalf, secondHalf;
		splitSegmentAtT(0.5f, firstHalf, secondHalf);
		return (firstHalf.getApproximateLength(withinTolerance) + secondHalf.getApproximateLength(withinTolerance));
	}

	return ((chordLength + controlPolygonLength) / 2.0f);
}
