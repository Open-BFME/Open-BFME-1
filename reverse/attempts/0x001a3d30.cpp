// ?sample@Rva001A3D30TerrainSample@@QAE_NPBUCoord3D@@PAURGBColor@@@Z
// partial score=0.0540915 date=2026-09-25
// cl: /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/scriptenginelayout /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
#include "Lib/BaseType.h"

extern "C" __declspec(dllimport) double __cdecl floor(double);

class Rva001A3D30TerrainSample
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual Real sampleOrigin();

	Bool sample(const Coord3D *position, RGBColor *color);
 char m_pad04[0xC];
 Int m_worldWidth, m_worldHeight;
 unsigned char *m_samples;
 UnsignedInt m_sampleWidth, m_sampleHeight;
};

Bool Rva001A3D30TerrainSample::sample(const Coord3D *position, RGBColor *color)
{
	if (!m_samples ||
		m_worldWidth < 1 || m_worldHeight < 1)
		return FALSE;

	Real origin = sampleOrigin();
	Real worldX = position->x + origin;
	Real worldY = position->y + origin;
	Real zero = *(const Real *)0x01075350;
	Real cellScale = *(const Real *)0x01075c74;
	if (worldX < zero)
		worldX = zero;
	else if (worldX > (Real)m_worldWidth * cellScale)
		worldX = (Real)m_worldWidth * cellScale;
	if (worldY < zero)
		worldY = zero;
	else if (worldY > (Real)m_worldHeight * cellScale)
		worldY = (Real)m_worldHeight * cellScale;

	UnsignedInt sampleWidth = m_sampleWidth;
	UnsignedInt sampleHeight = m_sampleHeight;
	Real sampleX = (Real)sampleWidth /
		((Real)m_worldWidth * cellScale) * worldX;
	Real sampleY = (Real)sampleHeight /
		((Real)m_worldHeight * cellScale) * worldY;
	Int x = fast_float2long_round((Real)floor((double)sampleX));
	Int y = fast_float2long_round((Real)floor((double)sampleY));

	if ((UnsignedInt)x >= sampleWidth - 1)
		x = (Int)(sampleWidth - 2);
	if ((UnsignedInt)y >= sampleHeight - 1)
		y = (Int)(sampleHeight - 2);
	Real fractionX = sampleX - (Real)x;
	Real fractionY = sampleY - (Real)y;
	Real one = *(const Real *)0x01075334;
	if (fractionX > one)
		fractionX = one;
	if (fractionY > one)
		fractionY = one;
	Real inverseX = one - fractionX;
	Real inverseY = one - fractionY;

	Int top = (y * (Int)sampleWidth + x) * 3;
	Int bottom = top + (Int)sampleWidth * 3;
	unsigned char *samples = m_samples;
	Real scale = *(const Real *)0x0107c64c;

	// The source bytes are B,G,R. Preserve each channel's retail pair order.
	Real blueTop = (Real)samples[top + 3] * fractionX +
		(Real)samples[top] * inverseX;
	Real blueBottom = (Real)samples[bottom + 3] * fractionX +
		(Real)samples[bottom] * inverseX;
	color->blue = (blueTop * inverseY + blueBottom * fractionY) * scale;

	Real greenBottom = (Real)samples[bottom + 4] * fractionX +
		(Real)samples[bottom + 1] * inverseX;
	Real greenTop = (Real)samples[top + 4] * fractionX +
		(Real)samples[top + 1] * inverseX;
	color->green = (greenTop * inverseY + greenBottom * fractionY) * scale;

	Real redBottom = (Real)samples[bottom + 5] * fractionX +
		(Real)samples[bottom + 2] * inverseX;
	Real redTop = (Real)samples[top + 5] * fractionX +
		(Real)samples[top + 2] * inverseX;
	color->red = (redTop * inverseY + redBottom * fractionY) * scale;
	return TRUE;
}
