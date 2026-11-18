// Thing::isSignificantlyAboveTerrain, retail 0x00131B20 (58 bytes, ILT 0x00019FF1).
//
// Identity: the ILT oracle confirms ?isSignificantlyAboveTerrain@Thing@@QBE_NXZ
// at ILT 0x00019FF1 (and contradicts the earlier placeholder), and the body is
// Zero Hour's Thing::isSignificantlyAboveTerrain with getHeightAboveTerrain()
// inlined: the cached altitude at +0x54 is refreshed through the slot-0
// virtual calculateHeightAboveTerrain under m_cacheFlags bit 2, then compared
// against the scaled gravity. Zero Hour's Thing.cpp copy keeps ZH offsets, so
// it cannot be retail's.

// View of retail's global at 0x012ED5C8, Common/GlobalData.cpp's
// GlobalData *TheWritableGlobalData; this view is cast in at the one use.
struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadRW[0x1ac];
	float m_gravity;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// Retail's operand at 0x01090DDC is the class-static scale constant defined in
// game/GameEngine/Source/Common/S3CachedThresholdTest.cpp.
class BfmeCachedThresholdScaleHolder
{
public:
	static const float value;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Thing.h
class Thing
{
public:
	bool isSignificantlyAboveTerrain() const;

protected:
	virtual float calculateHeightAboveTerrain() const;	// slot 0

private:
	unsigned char m_bfmeHead[0x54 - 4];
	mutable float m_cachedAltitudeAboveTerrain;			// +0x54
	unsigned char m_bfmeGap58[4];
	mutable int m_cacheFlags;							// +0x5C
};

bool Thing::isSignificantlyAboveTerrain() const
{
	if ((m_cacheFlags & 2) == 0)
	{
		m_cachedAltitudeAboveTerrain = calculateHeightAboveTerrain();
		m_cacheFlags |= 2;
	}

	return *(volatile float *)&((Rva006C9270GlobalData *)TheWritableGlobalData)->m_gravity * BfmeCachedThresholdScaleHolder::value < m_cachedAltitudeAboveTerrain;
}
