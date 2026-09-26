// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

#include "PreRTS.h"
#include "Common/BezFwdIterator.h"

//-------------------------------------------------------------------------------------------------
BezFwdIterator::BezFwdIterator(): mStep(0), mStepsDesired(0)
{ 
	// Added by Sadullah Nader
	mCurrPoint.zero();
	mDDDq.zero();
	mDDq.zero();
	mDq.zero();
} 

//-------------------------------------------------------------------------------------------------
BezFwdIterator::BezFwdIterator(Int stepsDesired, const BezierSegment *bezSeg)
	: mStep(0)
{
	// Added by Sadullah Nader
	mCurrPoint.zero();
	mDDDq.zero();
	mDDq.zero();
	mDq.zero();
	//

	mStepsDesired = stepsDesired;
	mBezSeg = (*bezSeg);
}

//-------------------------------------------------------------------------------------------------
void BezFwdIterator::start(void)
{
	mStep = 0;

	if (mStepsDesired <= 1)
		return;

	float parameterStep	 = 1.0f / (mStepsDesired - 1);
	float parameterStepSquared = parameterStep * parameterStep;
	float parameterStepCubed = parameterStep * parameterStepSquared;

	D3DXVECTOR4 xControlPoints(mBezSeg.m_controlPoints[0].x, mBezSeg.m_controlPoints[1].x, mBezSeg.m_controlPoints[2].x, mBezSeg.m_controlPoints[3].x);
	D3DXVECTOR4 yControlPoints(mBezSeg.m_controlPoints[0].y, mBezSeg.m_controlPoints[1].y, mBezSeg.m_controlPoints[2].y, mBezSeg.m_controlPoints[3].y);
	D3DXVECTOR4 zControlPoints(mBezSeg.m_controlPoints[0].z, mBezSeg.m_controlPoints[1].z, mBezSeg.m_controlPoints[2].z, mBezSeg.m_controlPoints[3].z);

	D3DXVECTOR4 polynomialCoefficients[3];
	D3DXVec4Transform(&polynomialCoefficients[0], &xControlPoints, &BezierSegment::s_bezBasisMatrix);
	D3DXVec4Transform(&polynomialCoefficients[1], &yControlPoints, &BezierSegment::s_bezBasisMatrix);
	D3DXVec4Transform(&polynomialCoefficients[2], &zControlPoints, &BezierSegment::s_bezBasisMatrix);

	mCurrPoint = mBezSeg.m_controlPoints[0];

	int axisIndex = 3;
	while (axisIndex--) {
		float cubicCoefficient = polynomialCoefficients[axisIndex].x;
		float quadraticCoefficient = polynomialCoefficients[axisIndex].y;
		float linearCoefficient = polynomialCoefficients[axisIndex].z;

		float *firstDifference, *secondDifference, *thirdDifference;

		if (axisIndex == 2) {
			firstDifference = &mDq.z;
			secondDifference = &mDDq.z;
			thirdDifference = &mDDDq.z;
		} else if (axisIndex == 1) {
			firstDifference = &mDq.y;
			secondDifference = &mDDq.y;
			thirdDifference = &mDDDq.y;
		} else if (axisIndex == 0) {
			firstDifference = &mDq.x;
			secondDifference = &mDDq.x;
			thirdDifference = &mDDDq.x;
		}

		(*firstDifference) = cubicCoefficient * parameterStepCubed + quadraticCoefficient * parameterStepSquared + linearCoefficient * parameterStep;
		(*secondDifference) = 6 * cubicCoefficient * parameterStepCubed + 2 * quadraticCoefficient * parameterStepSquared;
		(*thirdDifference) = 6 * cubicCoefficient * parameterStepCubed;
	}
}

//-------------------------------------------------------------------------------------------------
Bool BezFwdIterator::done(void)
{
	return (mStep >= mStepsDesired);
}

//-------------------------------------------------------------------------------------------------
// ?getCurrent@BezFwdIterator@@QBEABUCoord3D@@XZ present-unmatched
const Coord3D& BezFwdIterator::getCurrent(void) const
{
	return mCurrPoint;
}

//-------------------------------------------------------------------------------------------------
void BezFwdIterator::next(void)
{
	mCurrPoint.add(&mDq);
	mDq.add(&mDDq);
	mDDq.add(&mDDDq);

	++mStep;
}

