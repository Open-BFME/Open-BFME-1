// cl: /DNDEBUG /MD /EHsc
// Real-C++ reconstruction of GameState::missionSave at 0x00110600.

typedef int Int;
typedef bool Bool;
typedef char Char;
typedef unsigned short WideChar;

template <typename T>
class StringBase
{
	friend class AsciiString;
	friend class UnicodeString;

private:
	StringBase() : m_data(0) {}
	StringBase(const StringBase<T> &other);
	StringBase(const T *text);
	~StringBase();

	struct Header
	{
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString(const UnicodeString &other) : StringBase<WideChar>(other) {}
	~UnicodeString() {}

	const WideChar *str() const
	{
		return m_data ? &m_data->data[0] : (const WideChar *)0x0107388C;
	}

	void format(UnicodeString format, ...);
};

// The retail interface has nine entries before the two fetch overloads.  The
// two overloads are ordered AsciiString, const Char* in its BFME vtable.
class GameTextInterface
{
public:
	virtual void gameTextSlot0() = 0;
	virtual void gameTextSlot1() = 0;
	virtual void gameTextSlot2() = 0;
	virtual void gameTextSlot3() = 0;
	virtual void gameTextSlot4() = 0;
	virtual void gameTextSlot5() = 0;
	virtual void gameTextSlot6() = 0;
	virtual void gameTextSlot7() = 0;
	virtual void gameTextSlot8() = 0;
	virtual UnicodeString fetch(const Char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};

class Campaign
{
	char m_base[0x0C];

public:
	AsciiString m_campaignNameLabel;
};

class CampaignManager
{
public:
	Campaign *getCurrentCampaign();
	Int getCurrentMissionNumber();
};

enum SaveFileType
{
	SAVE_FILE_TYPE_NORMAL,
	SAVE_FILE_TYPE_MISSION
};

enum SnapshotType
{
	SNAPSHOT_SAVELOAD
};

enum SaveCode
{
	SC_INVALID = -1,
	SC_OK
};

class GameState
{
public:
	SaveCode missionSave();
};

// BFME's saveGame body consumes a fifth message-enable byte at [ebp+0x18]
// even though its inherited ledger name stops at SnapshotType.  The call site
// reaches the proven incremental-link thunk at 0x00020CD4.
extern void j_00020cd4();
// A pointer-to-member cast preserves the retail thiscall (ECX) without
// adding fastcall's otherwise-unused EDX setup.  The thunk's five stack
// parameters are the two string objects, the two enums, and the BFME message
// flag consumed at [ebp+0x18].
struct SaveGameCallTarget
{
	SaveCode saveGame(AsciiString filename, UnicodeString desc,
		SaveFileType saveType, SnapshotType which, Bool showMessage);
};
typedef SaveCode (SaveGameCallTarget::*SaveGameCall)(AsciiString,
	UnicodeString, SaveFileType, SnapshotType, Bool);

extern CampaignManager *TheCampaignManager;
extern GameTextInterface *TheGameText;
extern GameState *TheGameState;

// ?missionSave@GameState@@QAE?AW4SaveCode@@XZ
SaveCode GameState::missionSave()
{
	Campaign *campaign = TheCampaignManager->getCurrentCampaign();
	Int missionNumber = TheCampaignManager->getCurrentMissionNumber() + 1;
	UnicodeString format = TheGameText->fetch("GUI:MissionSave");
	UnicodeString desc;
	desc.format(format, TheGameText->fetch(campaign->m_campaignNameLabel).str(), missionNumber);
	union
	{
		void (*asFunction)();
		SaveGameCall asMember;
	} saveGameCast;
	saveGameCast.asFunction = j_00020cd4;
	return (reinterpret_cast<SaveGameCallTarget *>(TheGameState)->*saveGameCast.asMember)(
		AsciiString(""), desc, SAVE_FILE_TYPE_MISSION, SNAPSHOT_SAVELOAD, true);
}
