// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Save action of the save/load screen object (Rva56E070StateDispatch.cpp layout),
// reached from the 0x0056FD90 dispatch through ILT 0x0002D6B9; method name address-derived.
#include "ascii_string.h"
#include "unicode_string.h"

inline UnicodeString::UnicodeString()
{
	m_text = 0;
}
inline UnicodeString::UnicodeString(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)
		->StringBase<unsigned short>::StringBase(*(const StringBase<unsigned short> *)&s);
}
inline UnicodeString::~UnicodeString()
{
	((StringBase<unsigned short> *)this)->releaseBuffer();
}
inline UnicodeString &UnicodeString::operator=(const UnicodeString &s)
{
	((StringBase<unsigned short> *)this)->set(*(const StringBase<unsigned short> *)&s);
	return *this;
}

typedef int Int;
typedef bool Bool;

class GameWindow;
class WindowLayout;

UnicodeString GadgetTextEntryGetText(GameWindow *window);
void ReleaseWindowLayout(WindowLayout *layout);

// Slot order as in the matched SkirmishScreenStateRva005294F0.cpp.
class GameTextInterface
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

// InGameUI's variadic message() sits at +0x34 (caller-cleaned, `this` pushed).
class InGameUI
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void __cdecl message(UnicodeString format, ...) = 0;
};
extern InGameUI *TheInGameUI;

class RecorderClass
{
public:
	AsciiString getLastReplayFileName();
	static AsciiString getReplayExtention();
};
extern RecorderClass *TheRecorder;

// The recorder member at 0x00099A40 (RecorderCopyReplayRva00099A40.cpp) and the
// free copy at 0x00099E10 (RecorderCopyReplayFile.cpp), under their ledger names.
class Rva00099A40Owner
{
public:
	bool dup_00099A40(AsciiString *name, UnicodeString *description);
};
bool dup_00099E10(AsciiString *source, AsciiString *name, UnicodeString *description);

enum SaveCode { SC_INVALID = -1 };
enum SaveFileType { SAVE_FILE_TYPE_NORMAL };
enum SnapshotType { SNAPSHOT_SAVELOAD };

class GameState
{
public:
	SaveCode saveGame(AsciiString filename, UnicodeString desc, SaveFileType fileType,
		SnapshotType which, Bool silent);
};
extern GameState *TheGameState;

// APT message box at 0x00522110 (ILT 0x00047307): cdecl, returns a bool in al,
// stores mode into the box state and reads both strings by reference.
Bool rva00522110(Int mode, const UnicodeString &title, const UnicodeString &body);

struct Rva56E070SelectedItem
{
	AsciiString filename;
};

class BfmeThingME
{
public:
	int bfmeTestME();
};

// resolveMode (0x0056AD10) reads the same object's +0x270.
class Rva0056AD10
{
public:
	int resolveMode() const;
};

// Ledger row ?getSelectedItemData@Rva0056AB50Owner@@QAEPAXXZ (0x0056AB50).
class Rva0056AB50Owner
{
public:
	void *getSelectedItemData();
};

class Rva56E070StateOwner : public BfmeThingME
{
public:
	char m_pad0[0x258];
	int m_state;
	int m_direction;
	char m_pad260[4];
	void *m_arg264;
	void *m_arg268;
	void *m_context26c;
	int m_mode270;
	int m_value274;
	bool m_flag278;
	char m_pad279[3];
	int m_auxiliaryState;

	void rva0056D070();
};

void Rva56E070StateOwner::rva0056D070()
{
	if (m_context26c == 0 || m_arg264 == 0)
		return;

	UnicodeString description = GadgetTextEntryGetText((GameWindow *)m_context26c);
	Rva56E070SelectedItem *selected = (Rva56E070SelectedItem *)((Rva0056AB50Owner *)this)->getSelectedItemData();
	AsciiString filename;
	if (selected != 0)
		filename = selected->filename;

	if (m_auxiliaryState == 4)
	{
		if (m_flag278)
		{
			Bool saved = ((Rva00099A40Owner *)TheRecorder)->dup_00099A40(&filename, &description);
			ReleaseWindowLayout(0);
			UnicodeString text;
			if (saved)
				text = TheGameText->fetch("GUI:ReplaySaveComplete");
			else
				text = TheGameText->fetch("GUI:ReplaySaveError");
			TheInGameUI->message(text);
		}
		else
		{
			Bool saved = dup_00099E10(&(TheRecorder->getLastReplayFileName() + RecorderClass::getReplayExtention()),
				&filename, &description);
			UnicodeString text;
			if (saved)
				text = TheGameText->fetch("APT:ReplaySaveCompleteMessageBox");
			else
				text = TheGameText->fetch("APT:ReplaySaveErrorMessageBox");
			rva00522110(0, TheGameText->fetch("APT:SaveGameProgress"), text);
		}
		m_state = 8;
	}
	else
	{
		SaveFileType fileType = (SaveFileType)((const Rva0056AD10 *)this)->resolveMode();
		TheGameState->saveGame(filename, description, fileType, SNAPSHOT_SAVELOAD, true);
		rva00522110(0, TheGameText->fetch("APT:SaveGameProgress"), TheGameText->fetch("GUI:GameSaved"));
		m_state = 8;
	}
}
