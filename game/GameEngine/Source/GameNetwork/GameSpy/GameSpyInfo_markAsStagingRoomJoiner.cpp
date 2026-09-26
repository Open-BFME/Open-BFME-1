// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/asciistring_copyctor_outofline /Iinputs/reference/shims/psplayerstats /Iinputs/reference/shims/peerdefs /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWSaveLoad /Igame/Libraries/Source/WWVegas/WWLib
// stlport

#define Matrix4x4 Matrix4
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#define _BFME_RETAIL_PLAYER_INFO_LAYOUT
#define __PLACEMENT_VEC_NEW_INLINE
#include <map>

// This TU needs the BFME by-value string ABI: the concrete string objects
// forward their copy construction and destruction to StringBase, while those
// forwarders remain inline so the argument-slot lifetime matches retail.
// Keep this local because the surrounding ZH headers expose a different
// string layout and the body only needs the one-pointer representation.
#define ASCIISTRING_H
#define UNICODESTRING_H
template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
	AsciiString &operator=(const AsciiString &other);
	const char *str(void) const { return m_data ? m_data->m_text : ""; }
	int getLength(void) const;
	int compareNoCase(const AsciiString &other) const;
	void toLower(void);
	static AsciiString TheEmptyString;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString() : StringBase<unsigned short>() {}
	UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
	UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
	~UnicodeString() {}
	UnicodeString &operator=(const UnicodeString &other);
	const unsigned short *str(void) const;
	int getLength(void) const;
	int compareNoCase(const UnicodeString &other) const;
	static UnicodeString TheEmptyString;
};

int operator==(const AsciiString &left, const AsciiString &right);
bool operator<(const AsciiString &left, const AsciiString &right);

#include "PreRTS.h"
#include <set>

#include "Common/GameState.h"
#include "Common/RandomValue.h"
#include "Common/IgnorePreferences.h"
#include "Common/CustomMatchPreferences.h"
#include "Common/GameSpyMiscPreferences.h"
#include "Common/Recorder.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/PlayerTemplate.h"
#include "GameClient/MapUtil.h"
#include "GameClient/ShellHooks.h"
#include "GameClient/GameText.h"
#include "GameNetwork/GameSpy/LadderDefs.h"
#define GameSpyStagingRoom BfmeHeaderStagingRoom
#include "GameNetwork/GameSpy/PeerDefsImplementation.h"
#undef GameSpyStagingRoom
#include "GameNetwork/GameSpy/BuddyThread.h"
#include "GameNetwork/GameSpy/PeerThread.h"
#include "GameNetwork/GameSpy/PingThread.h"
#include "GameNetwork/GameSpy/PersistentStorageThread.h"
#include "GameNetwork/GameSpy/GSConfig.h"
#include "GameNetwork/GameSpyOverlay.h"
#include "GameNetwork/RankPointValue.h"
#include "GameLogic/GameLogic.h"
#include "GameNetwork/NetworkDefs.h"

extern AsciiString GameInfoToAsciiString(const GameInfo *game, Bool includeSlots);
extern Bool ParseAsciiStringToGameInfo(GameInfo *game, AsciiString options, Bool includeSlots);

// Keep the official GameSpyStagingRoom method symbols while the included ZH
// layout is renamed above.  The object is still the same BFME room; these are
// declarations only, and their routes are independently pinned to the matched
// BFME setter/getter bodies.
class GameSpyStagingRoom : public GameInfo
{
public:
	void cleanUpSlotPointers();
	void setLocalName(AsciiString name);
	UnicodeString getGameName();
	void setGameName(UnicodeString name);
};

class BfmeStagingRoomResetView
{
public:
	virtual void unused0() = 0;
	virtual void unused1() = 0;
	virtual void reset() = 0;
};

// The BFME copy constructor and destructor place these members at +0x418
// through +0x438; the ZH inline accessors address the old +0x390 tail.
class BfmeStagingRoomFieldsView
{
public:
	// These are the observed retail copies at the BFME tail offsets; their
	// semantic field identities are not established by this body.
	void setTailDword430(UnsignedInt value) { m_tailDword430 = value; }
	void setTailDword434(UnsignedInt value) { m_tailDword434 = value; }
	void setTailDword438(UnsignedInt value) { m_tailDword438 = value; }
	void setTailByte428(Bool value) { m_tailByte428 = value; }
	void setTailByte429(Bool value) { m_tailByte429 = value; }
	UnsignedInt getTailDword430() const { return m_tailDword430; }
	UnsignedInt getTailDword434() const { return m_tailDword434; }
	UnsignedInt getTailDword438() const { return m_tailDword438; }
	Bool getTailByte428() const { return m_tailByte428; }
	Bool getTailByte429() const { return m_tailByte429; }

private:
	char m_pad0[0x418];
	UnicodeString m_gameName;
	Int m_id;
	void *m_transport;
	AsciiString m_localName;
	Bool m_tailByte428;
	Bool m_tailByte429;
	char m_pad42A[6];
	UnsignedInt m_tailDword430;
	UnsignedInt m_tailDword434;
	UnsignedInt m_tailDword438;
};

// ?markAsStagingRoomJoiner@GameSpyInfo@@UAEXH@Z
void GameSpyInfo::markAsStagingRoomJoiner(Int game)
{
	m_localStagingRoomID = game;
	m_joinedStagingRoom = TRUE;
	m_isHosting = FALSE;
	reinterpret_cast<BfmeStagingRoomResetView *>(&m_localStagingRoom)->reset();
	m_localStagingRoom.enterGame();
	typedef std::map<Int, GameSpyStagingRoom *> OfficialStagingRoomMap;
	OfficialStagingRoomMap *stagingRooms = reinterpret_cast<OfficialStagingRoomMap *>(&m_stagingRooms);
	OfficialStagingRoomMap::iterator it = stagingRooms->find(game);
	if (it != stagingRooms->end())
	{
		GameSpyStagingRoom *info = it->second;
		info->cleanUpSlotPointers();
		AsciiString options = GameInfoToAsciiString(info, TRUE);
		ParseAsciiStringToGameInfo(&m_localStagingRoom, options, TRUE);
		m_localStagingRoom.setInGame();
		reinterpret_cast<GameSpyStagingRoom *>(&m_localStagingRoom)->setLocalName(m_localName);
		reinterpret_cast<BfmeStagingRoomFieldsView *>(&m_localStagingRoom)->setTailDword430(
			reinterpret_cast<const BfmeStagingRoomFieldsView *>(info)->getTailDword430());
		reinterpret_cast<BfmeStagingRoomFieldsView *>(&m_localStagingRoom)->setTailDword434(
			reinterpret_cast<const BfmeStagingRoomFieldsView *>(info)->getTailDword434());
		reinterpret_cast<BfmeStagingRoomFieldsView *>(&m_localStagingRoom)->setTailDword438(
			reinterpret_cast<const BfmeStagingRoomFieldsView *>(info)->getTailDword438());
		reinterpret_cast<BfmeStagingRoomFieldsView *>(&m_localStagingRoom)->setTailByte429(
			reinterpret_cast<const BfmeStagingRoomFieldsView *>(info)->getTailByte429());
		reinterpret_cast<BfmeStagingRoomFieldsView *>(&m_localStagingRoom)->setTailByte428(
			reinterpret_cast<const BfmeStagingRoomFieldsView *>(info)->getTailByte428());
		reinterpret_cast<GameSpyStagingRoom *>(&m_localStagingRoom)->setGameName(
		reinterpret_cast<GameSpyStagingRoom *>(info)->getGameName());
	}
}
