// Retail RVA 0x00617B20 is reached by the named BfmeHostAAY::bfmeStep3AAY
// thunk at 0x00030BF2.  The method drains the BfmeItemAM map at +0x210,
// removes each item from the BfmeHostCA name map, and then clears the table.

// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

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
	return text != 0 ? text + 8 : "";
}

// Neither callee is a member of BfmeItemAM in retail: 0x0060AA10 is the shared
// 32-byte name getter body (?dup_0060aa10@@YAXXZ) and 0x0061E3E0 the destructor
// body (?d_0061e3e0@@YAXXZ).  Both run thiscall on the item, so the calls are
// routed through a member-pointer typedef over the plain externs instead of
// being given BfmeItemAM member names that do not exist.
extern void dup_0060aa10();
extern void d_0061e3e0();

class BfmeItemAM
{
};

typedef BFMERetailAsciiString (BfmeItemAM::*BfmeItemGetNameFn)();
typedef void (BfmeItemAM::*BfmeItemDtorFn)();

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

class GameLogic;
// 0x012F0898 is retail's `GameLogic *TheGameLogic`; Rva00367E30Logic is this
// TU's local view of the same global, so cast at the use.
extern GameLogic *TheGameLogic;

class Gen_00609320
{
public:
	virtual void bfmeSlot0AAY();
	virtual void bfmeSlot1AAY();
	virtual void bfmeSlot2AAY();
	virtual void bfmeFinishAAY();
};

// The client LivingWorld singleton cell at VA 0x012F7048, defined once by
// game/GameEngine/Source/GameClient/LivingWorld.cpp.  Gen_00609320 above is
// this TU's local view of the same pointee, so cast at the use.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;

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
	union GetNameRoute
	{
		void (*fn)();
		BfmeItemGetNameFn call;
	};
	union DtorRoute
	{
		void (*fn)();
		BfmeItemDtorFn call;
	};

	const GetNameRoute getName = { dup_0060aa10 };
	const DtorRoute dtor = { d_0061e3e0 };

	for (BfmeItemMapAAY::iterator it = m_bfmeItemsAAY.begin();
		it != m_bfmeItemsAAY.end(); ++it)
	{
		BfmeItemAM *item = it->second;
		if (item != 0)
		{
			reinterpret_cast<BfmeHostCA *>(this)->bfmeRemoveCA(
				bfmeNameText((item->*getName.call)()));
			(item->*dtor.call)();
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

	if (TheGameLogic != 0)
		((Rva00367E30Logic *)TheGameLogic)->bfmeResetAAY();

	if (g_rva012F7048LivingWorld != 0)
		((Gen_00609320 *)g_rva012F7048LivingWorld)->bfmeFinishAAY();

	m_bfme288AAY = 0;
}
