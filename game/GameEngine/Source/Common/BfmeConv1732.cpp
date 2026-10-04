extern const float BfmeZeroRange;

class BfmeRoomZE
{
public:
	BfmeRoomZE(const BfmeRoomZE &other);
	~BfmeRoomZE();

	int m_bfmeHandleZE;
};

class BfmeAZE
{
public:
	unsigned char m_bfmeHeadZE[8];
	BfmeRoomZE m_bfmeRoomZE;
	unsigned char m_bfmeMidZE[4];
	float m_bfmeRangeZE;
};

class BfmeDZE
{
public:
	unsigned char m_bfmeHeadZE[0x344];
	unsigned char m_bfmeFlagsZE;
};

class BfmeBZE
{
public:
	unsigned char m_bfmeHeadZE[0xfc];
	BfmeDZE *m_bfmeDZE;
};

class BfmeA1087
{
public:
	void bfmeSendZE(BfmeBZE *target, BfmeRoomZE room, float range);
};

// 0x012F7FE0 is retail's terrain render object singleton, defined by
// game/GameEngineDevice/Source/W3DDevice/GameClient/BaseHeightMap.cpp
// (matched data row ?TheTerrainRenderObject@@3PAVBaseHeightMapRenderObjClass@@A).
// Only the global's spelling changes; the send call keeps the TU-local view.
class BaseHeightMapRenderObjClass;

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;

class BfmeOwnZE
{
public:
	void bfmeTickZE(void *unused);

	unsigned char m_bfmeHeadZE[4];
	BfmeAZE *m_bfmeAZE;
	BfmeBZE *m_bfmeBZE;
};

void BfmeOwnZE::bfmeTickZE(void *unused)
{
	BfmeAZE *source = m_bfmeAZE;
	BfmeBZE *target = m_bfmeBZE;

	if (source && target && source->m_bfmeRangeZE != BfmeZeroRange
		&& target->m_bfmeDZE && (target->m_bfmeDZE->m_bfmeFlagsZE & 1))
		reinterpret_cast<BfmeA1087 *>(TheTerrainRenderObject)->bfmeSendZE(target,
			source->m_bfmeRoomZE, source->m_bfmeRangeZE);
}