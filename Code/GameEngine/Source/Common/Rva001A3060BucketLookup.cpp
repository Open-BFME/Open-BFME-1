// cl: /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /D_STLP_USE_STATIC_LIB /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/scriptenginelayout /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// RVA 0x001A3060; opaque owner, Region3D written through virtual slot +0x28.
// Retail scale at VA 0x0109C348 is 0x4247999A (49.9f), keeping the high
// boundary inside a 50-by-50 grid. The existing x87 conversion helper preserves
// retail's FISTP rounding after floor; an ordinary cast emits different code.
#include "Lib/BaseType.h"

class Rva001A3060
{
public:
	virtual void slot00() const = 0;
	virtual void slot04() const = 0;
	virtual void slot08() const = 0;
	virtual void slot0C() const = 0;
	virtual void slot10() const = 0;
	virtual void slot14() const = 0;
	virtual void slot18() const = 0;
	virtual void slot1C() const = 0;
	virtual void slot20() const = 0;
	virtual void slot24() const = 0;
	virtual void getBounds(Region3D &bounds) const = 0;
	int getBucket(const Coord3D &position) const;
};

extern "C" __declspec(dllimport) double __cdecl floor(double);

int Rva001A3060::getBucket(const Coord3D &position) const
{
	float x = position.x;
	float y = position.y;
	Region3D bounds;
	getBounds(bounds);
	if (x < bounds.lo.x) x = bounds.lo.x;
	if (y < bounds.lo.y) y = bounds.lo.y;
	if (x > bounds.hi.x) x = bounds.hi.x;
	if (y > bounds.hi.y) y = bounds.hi.y;
	float xRatio = ((x - bounds.lo.x) / (bounds.hi.x - bounds.lo.x)) * 49.9f;
	int xIndex = fast_float2long_round((float)floor((double)xRatio));
	float yRatio = ((y - bounds.lo.y) / (bounds.hi.y - bounds.lo.y)) * 49.9f;
	int yIndex = fast_float2long_round((float)floor((double)yRatio));
	return yIndex * 50 + xIndex;
}
