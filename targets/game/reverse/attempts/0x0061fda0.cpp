// ?xfer@SkirmishGameInfo@@MAEXPAVXfer@@@Z
// partial score=0.7203 date=2026-09-21
// ?xfer@SkirmishGameInfo@@MAEXPAVXfer@@@Z
// cl: /DNDEBUG /MD /EHsc /I.

// SkirmishGameInfo::xfer, retail0061FDA0, complete901B boundary.
// Updated from the739B bank: retain slot-array reloads across virtual calls,
// use canonical by-value StringInline and Xfer headers, pass the witnessed
// zeroed GameSlotConnectInfo to setState, and call the real xferMapName.
// The landed GameInfo copy constructor proves the map-name member at+3C;
// the old bank mislabeled it Money and hid the call behind a union cast.
// Snapshot is the secondary subobject at+58, proven by00619720.
// NOT MATCHED:899B;252 nonreloc differences. Frame40 now agrees; ESI/EDI
// roles and EH saved-ESP home differ. The+38 field's semantic identity and
// padded16-bit representation remain a hypothesis; its old bank name is
// retained, not re-proven. Do not promote this view on byte similarity alone.

#include "Code/GameEngine/Source/Common/System/xfer.h"
#include "reference/shims/stringinline/StringInline.h"

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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameInfo.h
enum SlotState { SLOT_DUMMY = 0 };
struct GameSlotConnectInfo { int m_nat; unsigned short m_port; };
class GameSlot
{
public:
	virtual void reset(void);
 UnicodeString getName() const;
 void setState(SlotState, UnicodeString, const GameSlotConnectInfo *);
 void saveOffOriginalInfo() { m_origPlayerTemplate=m_playerTemplate; m_origStartPos=m_startPos; m_origColor=m_color; }
 void setPlayerTemplate(int p) { m_playerTemplate=p; if(p<=-2)m_startPos=-1; }
	int m_state;                  // +0x04
	bool m_isAccepted;   // +0x08
	unsigned char m_hasMap;       // +0x09 (not xferred here)
	bool m_isMuted;      // +0x0A
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
// Retail reads16 bits at+38 but copies32 bits back through a temporary.
// This padded-field model is an explicit remaining layout hypothesis.
struct Rva0061FDA0ShortField
{
 unsigned short m_value;
 unsigned char m_padding[2];
 Rva0061FDA0ShortField(unsigned short value):m_value(value) {}
 operator unsigned short() const { return m_value; }
};
class GameInfo
{
public:
	virtual void _bfme_gi_slot0(void);
	virtual void _bfme_gi_slot1(void);

	int m_preorderMask;                     // +0x04
	int m_crcInterval;                      // +0x08
	bool m_inGame;                 // +0x0C
	bool m_inProgress;             // +0x0D
	bool m_surrendered;            // +0x0E
	unsigned char _pad0F;
	int m_gameID;                           // +0x10
	GameSlot *m_slot[8];                    // +0x14
	UnsignedInt m_localIP;                  // +0x34
	Rva0061FDA0ShortField m_superweaponRestriction; // +0x38
	
	AsciiString m_mapName;             // +0x3C, matched xferMapName callee and GameInfo copy ctor
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

extern void xferMapName(Xfer *, AsciiString *);

// ?xfer@SkirmishGameInfo@@MAEXPAVXfer@@@Z
void SkirmishGameInfo::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;

	{ XferVersionView version(1, 1);
	*xfer == version; }

	*xfer == m_preorderMask;
	*xfer == m_crcInterval;
	*xfer == m_inGame;
	*xfer == m_inProgress;
	*xfer == m_surrendered;
	*xfer == m_gameID;

	Int slotCount = 8;
	*xfer == slotCount;

	for (slotCount = 0; slotCount < 8; slotCount++)
	{


		Int state = m_slot[slotCount]->m_state;
		*xfer == state;

		UnicodeString name = m_slot[slotCount]->getName();
		*xfer == name;

		Bool isAccepted = m_slot[slotCount]->m_isAccepted;
		*xfer == isAccepted;

		Bool isMuted = m_slot[slotCount]->m_isMuted;
		*xfer == isMuted;
		m_slot[slotCount]->m_isMuted = isMuted;

		Int color = m_slot[slotCount]->m_color;
		*xfer == color;

		Int startPos = m_slot[slotCount]->m_startPos;
		*xfer == startPos;

		Int playerTemplate = m_slot[slotCount]->m_playerTemplate;
		*xfer == playerTemplate;

		Int teamNumber = m_slot[slotCount]->m_teamNumber;
		*xfer == teamNumber;

		Int origColor = m_slot[slotCount]->m_origColor;
		*xfer == origColor;

		Int origStartPos = m_slot[slotCount]->m_origStartPos;
		*xfer == origStartPos;

		Int origPlayerTemplate = m_slot[slotCount]->m_origPlayerTemplate;
		*xfer == origPlayerTemplate;

		if (xfer->IsLoading())
		{
			GameSlotConnectInfo info; info.m_nat=0; info.m_port=0;
			m_slot[slotCount]->setState((SlotState)state,name,&info);

			if (isAccepted)
				m_slot[slotCount]->m_isAccepted = true;

			m_slot[slotCount]->setPlayerTemplate(origPlayerTemplate);
			m_slot[slotCount]->m_startPos = origStartPos;
			m_slot[slotCount]->m_color = origColor;
			m_slot[slotCount]->saveOffOriginalInfo();

			m_slot[slotCount]->m_teamNumber = teamNumber;
			m_slot[slotCount]->m_color = color;
			m_slot[slotCount]->m_startPos = startPos;
			m_slot[slotCount]->setPlayerTemplate(playerTemplate);
		}
	}

	UnsignedInt localIP = m_localIP;
	*xfer == localIP;
	UnsignedInt restriction = m_superweaponRestriction;
	*xfer == *(UnsignedShort *)&restriction;
	m_localIP = localIP;
	m_superweaponRestriction = (UnsignedShort)restriction;

	xferMapName(xfer, &m_mapName);

	*xfer == m_bfmeUnknown40;
	*xfer == m_bfmeUnknown44;
	*xfer == m_bfmeUnknown48;
	*xfer == m_bfmeUnknown4C;
}
