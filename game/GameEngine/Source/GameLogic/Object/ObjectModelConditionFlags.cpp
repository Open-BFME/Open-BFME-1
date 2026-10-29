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

// Retail 0x012F0898 is ?TheGameLogic@@3PAVGameLogic@@A (data_rows.csv,
// GameLogic.cpp); TheBfmeGameLogic was only a pin nothing defines.
class GameLogic;
extern GameLogic *TheGameLogic;
#define TheBfmeGameLogic ( reinterpret_cast<Rva00367E30Logic *>( TheGameLogic ) )

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

