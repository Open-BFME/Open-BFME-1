// View of retail's global at 0x012ED5C8. That global is
// Common/GlobalData.cpp's GlobalData *TheWritableGlobalData, the game's only
// definition of it, so the reference here carries that canonical type and this
// view is cast in at the one use.
struct Rva006C9270GlobalData
{
	unsigned char m_bfmeHeadRW[0x1ac];
	float m_bfmeScaleRW;
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;

// Retail's operand at 0x01090DDC is the class-static scale constant defined
// (const, 0.5f) in game/GameEngine/Source/Common/S3CachedThresholdTest.cpp;
// dir32_addresses.csv places ?value@BfmeCachedThresholdScaleHolder@@2MB at the
// same address the placeholder g_bfmeKRW named, so the reference is respelled
// to the defining name. The declaration below only has to forward-declare it.
class BfmeCachedThresholdScaleHolder
{
public:
	static const float value;
};

class BfmeOwnerRW
{
public:
	virtual float bfmeComputeRW(void);

	int bfmeCheckRW(void);

	unsigned char m_bfmeHeadRW[0x50];
	float m_bfmeCachedRW;
	unsigned char m_bfmeGapRW[4];
	int m_bfmeFlagsRW;
};

int BfmeOwnerRW::bfmeCheckRW(void)
{
	if ((m_bfmeFlagsRW & 2) == 0)
	{
		m_bfmeCachedRW = bfmeComputeRW();
		m_bfmeFlagsRW |= 2;
	}

	return *(volatile float *)&( (Rva006C9270GlobalData *)TheWritableGlobalData )->m_bfmeScaleRW * BfmeCachedThresholdScaleHolder::value < m_bfmeCachedRW;
}
