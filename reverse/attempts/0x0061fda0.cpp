// ?xfer@SkirmishGameInfo@@MAEXPAVXfer@@@Z
// partial score=0.35 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc

// SkirmishGameInfo::xfer, retail RVA 0x0061FDA0. The generic snapshot form of
// GameInfo.cpp's own xfer stub (present-unmatched, Zero Hour Xfer API), ported
// to the real BFME Xfer ABI (Xfer::operator==, IsLightCRC/IsLoading). Field
// layout matches reference/shims/gameinfo/GameNetwork/GameInfo.h and the
// already-landed GameSlot/GameInfo bodies in GameInfo.cpp; GameInfo's total
// size (0x58, one dword more than the header's own accounting once its
// vtable pointer is counted) is proven by the Snapshot vtable store at
// this+0x58 in ??0SkirmishGameInfo@@QAE@XZ (0x00619720).

#include "../Common/System/xfer.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;

struct XferVersionView : Xfer::Version
{
	XferVersionView(unsigned char first, unsigned char current)
	{
		data[0] = first;
		data[1] = current;
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Snapshot.h
class Snapshot
{
public:
	virtual ~Snapshot();
protected:
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess(void) = 0;
};

// Real identity is GameSlot::getName(), returning UnicodeString through a
// hidden pointer; the mangled name is already pinned as this placeholder.
class BfmeOtherDQG;
class BfmeItemDQG
{
public:
	void bfmeCallDQG(BfmeOtherDQG *out);
};

// INLINE forwarding ctor/dtor to a StringBase<T> base (reference/shims/stringinline/StringInline.h):
// declaring them out of line on the string class itself transposes the EH
// saved-esp store and the ctor `this` on every flag combination.
template <typename T> class StringBase
{
	friend class UnicodeString;
private:
	StringBase() : m_data(0) {}
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
	T *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	~UnicodeString() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
class GameSlot
{
public:
	virtual void reset(void);
	int m_state;                  // +0x04
	unsigned char m_isAccepted;   // +0x08
	unsigned char m_hasMap;       // +0x09 (not xferred here)
	unsigned char m_isMuted;      // +0x0A
	unsigned char _pad0B;
	int m_color;                  // +0x0C
	int m_startPos;               // +0x10
	int m_playerTemplate;         // +0x14
	int m_teamNumber;             // +0x18
	int m_origColor;              // +0x1C
	int m_origStartPos;           // +0x20
	int m_origPlayerTemplate;     // +0x24
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
// BFME drops the map-transport fields (m_mapName/m_mapCRC/m_mapSize/m_mapMask/
// m_seed/m_useStats) that Zero Hour carries between m_localIP and
// m_startingCash; the four trailing dwords after m_startingCash are BFME
// additions with no recovered identity.
class GameInfo
{
public:
	virtual void _bfme_gi_slot0(void);
	virtual void _bfme_gi_slot1(void);

	int m_preorderMask;                     // +0x04
	int m_crcInterval;                      // +0x08
	unsigned char m_inGame;                 // +0x0C
	unsigned char m_inProgress;             // +0x0D
	unsigned char m_surrendered;            // +0x0E
	unsigned char _pad0F;
	int m_gameID;                           // +0x10
	GameSlot *m_slot[8];                    // +0x14
	UnsignedInt m_localIP;                  // +0x34
	UnsignedShort m_superweaponRestriction; // +0x38
	unsigned short _pad3A;
	UnsignedInt m_startingCash;             // +0x3C (Money, one dword wide)
	UnsignedInt m_bfmeUnknown40;            // +0x40
	UnsignedInt m_bfmeUnknown44;            // +0x44
	Int m_bfmeUnknown48;                    // +0x48
	Int m_bfmeUnknown4C;                    // +0x4C
	unsigned char _padTail[8];              // pad to 0x58 (Snapshot subobject offset)
};

class SkirmishGameInfo : public GameInfo, public Snapshot
{
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess(void);
};

extern void j_0002ec9e(); // GameSlot::setState thunk, pinned 0x0002EC9E
extern void j_00009f7a(); // Money xfer helper thunk, pinned 0x00009F7A

// ?xfer@SkirmishGameInfo@@MAEXPAVXfer@@@Z
void SkirmishGameInfo::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	XferVersionView version(1, 1);
	*xfer == version;

	*xfer == m_preorderMask;
	*xfer == m_crcInterval;
	*xfer == m_inGame;
	*xfer == m_inProgress;
	*xfer == m_surrendered;
	*xfer == m_gameID;

	Int slotCount = 8;
	*xfer == slotCount;

	for (Int i = 0; i < 8; i++)
	{
		GameSlot *s = m_slot[i];

		Int state = s->m_state;
		*xfer == state;

		UnicodeString name;
		((BfmeItemDQG *)s)->bfmeCallDQG((BfmeOtherDQG *)&name);
		*xfer == name;

		Bool isAccepted = s->m_isAccepted;
		*xfer == isAccepted;

		Bool isMuted = s->m_isMuted;
		*xfer == isMuted;
		s->m_isMuted = isMuted;

		Int color = s->m_color;
		*xfer == color;

		Int startPos = s->m_startPos;
		*xfer == startPos;

		Int playerTemplate = s->m_playerTemplate;
		*xfer == playerTemplate;

		Int teamNumber = s->m_teamNumber;
		*xfer == teamNumber;

		Int origColor = s->m_origColor;
		*xfer == origColor;

		Int origStartPos = s->m_origStartPos;
		*xfer == origStartPos;

		Int origPlayerTemplate = s->m_origPlayerTemplate;
		*xfer == origPlayerTemplate;

		if (xfer->IsLoading())
		{
			typedef void (GameSlot::*SetStateFn)(Int, UnicodeString, const void *);
			union { void (*free_)(void); SetStateFn member_; } su;
			su.free_ = j_0002ec9e;
			(s->*su.member_)(state, name, 0);

			if (isAccepted)
				s->m_isAccepted = true;

			s->m_playerTemplate = origPlayerTemplate;
			if (origPlayerTemplate <= -2)
				s->m_startPos = -1;
			s->m_startPos = origStartPos;
			s->m_color = origColor;

			s->m_origPlayerTemplate = s->m_playerTemplate;
			s->m_origStartPos = s->m_startPos;
			s->m_origColor = s->m_color;

			s->m_teamNumber = teamNumber;
			s->m_color = color;
			s->m_startPos = startPos;
			s->m_playerTemplate = playerTemplate;
			if (playerTemplate <= -2)
				s->m_startPos = -1;
		}
	}

	UnsignedInt localIP = m_localIP;
	*xfer == localIP;
	UnsignedShort restriction = m_superweaponRestriction;
	*xfer == restriction;
	m_localIP = localIP;
	m_superweaponRestriction = restriction;

	typedef void (__cdecl *MoneyXferFn)(Xfer *, void *);
	union { void (*free_)(void); MoneyXferFn call_; } mu;
	mu.free_ = j_00009f7a;
	mu.call_(xfer, &m_startingCash);

	*xfer == m_bfmeUnknown40;
	*xfer == m_bfmeUnknown44;
	*xfer == m_bfmeUnknown48;
	*xfer == m_bfmeUnknown4C;
}
