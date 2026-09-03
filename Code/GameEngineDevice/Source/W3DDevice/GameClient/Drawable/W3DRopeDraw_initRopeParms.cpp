// cl: /DNDEBUG /MD /EHsc /DBFME_MODULE_NO_MPO /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// readable body of ?initRopeParms@W3DRopeDraw@@UAEXMMABURGBColor@@MMM@Z: Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/W3DRopeDraw.cpp
#define Matrix4x4 Matrix4

#include "Common/Thing.h"
#include "GameClient/Color.h"
#include "W3DDevice/GameClient/Module/W3DRopeDraw.h"

static const Real &bfmeMax(const Real &a, const Real &b)
{
	return a > b ? a : b;
}

static const Real &bfmeMin(const Real &a, const Real &b)
{
	return a < b ? a : b;
}

void W3DRopeDraw::initRopeParms(
	Real length,
	Real width,
	const RGBColor &color,
	Real wobbleLen,
	Real wobbleAmp,
	Real wobbleRate)
{
	const Real one = 1.0f;
	m_maxLen = bfmeMax(one, length);
	m_curLen = 0.0f;
	m_width = width;
	m_color = color;
	m_wobbleLen = bfmeMin(m_maxLen, wobbleLen);
	m_wobbleAmp = wobbleAmp;
	m_wobbleRate = wobbleRate;
	m_curZOffset = 0.0f;

	tossSegments();
	buildSegments();
}
