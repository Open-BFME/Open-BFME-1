// ?bfmeApplyYH@BfmeHostYH@@QAEHXZ
// partial score=0.98 date=2026-09-08
extern "C" void *__cdecl memset(void *d, int c, unsigned int n);

template <int N>
class BitFlags
{
public:
	unsigned int m_bfmeBitsYG[10];
};

class ModelConditionFlags
{
public:
	unsigned int m_bfmeBitsYH[3];
};

struct Rva00367E30Logic
{
	unsigned char m_bfmeHeadYH[0x3c];
	unsigned int m_bfme3CYH;
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class Object
{
public:
	void applyRva1C7370(const ModelConditionFlags &flags, bool on);
	void clearAndSetModelConditionFlags(const BitFlags<320> &clr, const BitFlags<320> &set);
	void bfmeClearYG(const BitFlags<320> &set);
};

void Object::bfmeClearYG(const BitFlags<320> &set)
{
	BitFlags<320> zero;

	memset(&zero, 0, 40);
	clearAndSetModelConditionFlags(zero, set);
}

class BfmeOwnerYH
{
public:
	unsigned char m_bfmeHeadYH[0x10];
	Object *m_bfme10YH;
};

class BfmeHostYH
{
public:
	int bfmeApplyYH();

	unsigned char m_bfmeHeadYH[0x1c];
	BfmeOwnerYH *m_bfme1CYH;
	unsigned char m_bfmeGapYH[4];
	unsigned int m_bfme24YH;
};

int BfmeHostYH::bfmeApplyYH()
{
	if (m_bfme24YH < TheBfmeGameLogic->m_bfme3CYH)
		return -1;

	ModelConditionFlags flags;

	memset(flags.m_bfmeBitsYH, 0, 12);
	flags.m_bfmeBitsYH[0] |= 0x400000;

	Object *obj = m_bfme1CYH->m_bfme10YH;

	obj->applyRva1C7370(flags, false);

	return 0;
}
