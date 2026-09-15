// Retail RVA 0x00617B20 is reached by the named BfmeHostAAY::bfmeStep3AAY
// thunk at 0x00030BF2.  The method drains the BfmeItemAM map at +0x210,
// removes each item from the BfmeHostCA name map, and then clears the table.

// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

extern const char Rva006A16B0Empty[];

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data(0) {}
	BFMERetailAsciiString(const BFMERetailAsciiString &other) : m_data(other.m_data) {}
	~BFMERetailAsciiString() { releaseBuffer(); }

	const char *str() const { return m_data; }

private:
	void releaseBuffer();

	char *m_data;
};

__forceinline const char *bfmeNameText(const BFMERetailAsciiString &name)
{
	const char *text = name.str();
	return text != 0 ? text + 8 : Rva006A16B0Empty;
}

class BfmeItemAM
{
public:
	BFMERetailAsciiString getName();
	~BfmeItemAM();
};

#pragma comment(linker, "/alternatename:?getName@BfmeItemAM@@QAE?AVBFMERetailAsciiString@@XZ=?dup_0060aa10@@YAXXZ")
#pragma comment(linker, "/alternatename:??1BfmeItemAM@@QAE@XZ=?d_0061e3e0@@YAXXZ")

class BfmeHostCA
{
public:
	void bfmeRemoveCA(const char *name);
};

typedef _STL::hash_map<int, BfmeItemAM *> BfmeItemMapAAY;

class BfmeSubAAY
{
public:
	void bfmeCloseAAY();
};

struct Rva00367E30Logic
{
	void bfmeResetAAY();
};

extern Rva00367E30Logic *TheBfmeGameLogic;

class Gen_00609320
{
public:
	virtual void bfmeSlot0AAY();
	virtual void bfmeSlot1AAY();
	virtual void bfmeSlot2AAY();
	virtual void bfmeFinishAAY();
};

extern Gen_00609320 *g_bfmeStateDF;

class BfmeHostAAY
{
public:
	void bfmeShutdownAAY();

	void bfmeStep1AAY();
	void bfmeStep2AAY();
	void bfmeStep3AAY();
	void bfmeStep4AAY();
	void bfmeStep5AAY();
	void bfmeStep6AAY();

	unsigned char m_bfmeHeadAAY[0x210];
	BfmeItemMapAAY m_bfmeItemsAAY;
	unsigned char m_bfmeHeadTailAAY[0x288 - 0x210 - sizeof(BfmeItemMapAAY)];
	unsigned char m_bfme288AAY;
	unsigned char m_bfmePadAAY[3];
	BfmeSubAAY *m_bfme28CAAY;
};

void BfmeHostAAY::bfmeStep3AAY()
{
	for (BfmeItemMapAAY::iterator it = m_bfmeItemsAAY.begin();
		it != m_bfmeItemsAAY.end(); ++it)
	{
		BfmeItemAM *item = it->second;
		if (item != 0)
		{
			reinterpret_cast<BfmeHostCA *>(this)->bfmeRemoveCA(
				bfmeNameText(item->getName()));
			delete item;
		}
	}
	m_bfmeItemsAAY.clear();
}

void BfmeHostAAY::bfmeShutdownAAY()
{
	bfmeStep1AAY();
	bfmeStep2AAY();
	bfmeStep3AAY();
	bfmeStep4AAY();

	BfmeSubAAY *s = m_bfme28CAAY;

	if (s != 0)
		s->bfmeCloseAAY();

	bfmeStep5AAY();
	bfmeStep6AAY();

	if (TheBfmeGameLogic != 0)
		TheBfmeGameLogic->bfmeResetAAY();

	if (g_bfmeStateDF != 0)
		g_bfmeStateDF->bfmeFinishAAY();

	m_bfme288AAY = 0;
}
