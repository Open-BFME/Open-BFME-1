typedef int Int;

class Glo012F1024Item
{
public:
	void bfmeEnter(void);

	char m_bfmeBodyZU[0xDC];
};

class Glo012F1028Sub
{
public:
	void bfmeNotify(void);
};

class Glo012F1028Type
{
public:
	char m_bfmeHeadZU[0x28];
	Glo012F1028Sub *m_bfmeSub;
};

// 0x012F1028 is EA's `TheLivingWorldLogic` (build/report_0x012F1028.md,
// section "0x012F1028 -- TheLivingWorldLogic": the literal pushed at the
// GameEngine::init initSubsystem<LivingWorldLogic> site, RVA 0x00079DB3, and
// the "LivingWorldLogic" literal the class vtable's name() returns at
// 0x010EDC08). Its definition moved to the class's own TU,
// game/GameEngine/Source/GameLogic/LivingWorld/LivingWorldLogic.cpp, which
// owns the data row for that address; this file only reads it.
// Glo012F1028Type above is this TU's own view of that address, so both reads
// cast at the use.
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class BfmeRewindZU
{
public:
	void bfmeRewindZU(void);

private:
	char m_bfmeHeadAZU[0x08];
	Int m_bfmeIndexZU;
	Glo012F1024Item *m_bfmeItemsZU;
	char m_bfmeHeadBZU[0x18 - 0x10];
	Int m_bfmeLimitZU;
};

void BfmeRewindZU::bfmeRewindZU(void)
{
	Int index = 0;
	Int limit = m_bfmeLimitZU;

	m_bfmeIndexZU = index;

	if (index > limit)
	{
		m_bfmeIndexZU = limit;
		((Glo012F1028Type *)TheLivingWorldLogic)->m_bfmeSub->bfmeNotify();
	}
	else
	{
		m_bfmeItemsZU[index].bfmeEnter();
		((Glo012F1028Type *)TheLivingWorldLogic)->m_bfmeSub->bfmeNotify();
	}
}
