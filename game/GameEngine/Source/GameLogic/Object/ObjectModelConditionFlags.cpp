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

