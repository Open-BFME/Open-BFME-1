// ?rva0056D070@Rva56E070StateOwner@@QAEXXZ
// partial score=0.9735 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// LANDING NEEDS a plain pin (admissible: pin_consistency OK): ?rva00522110@@YA_NHABVUnicodeString@@0@Z,0x00047307,opaque ABI alias for the cdecl bool message-box helper 0x00522110. Residue: this in esi (retail) vs edi (ours).
// Retail 0x0056D070, 756 bytes through RET at +0x2F3: the save action of the
// save/load screen object modelled by Rva56E070StateDispatch.cpp (state at
// +0x258, listbox +0x264, text entry +0x26C, replay flag +0x278, mode +0x27C).
// The generated dispatch 0x0056FD90 calls it through ILT 0x0002D6B9. With a
// listbox and a text entry present it reads the typed description and the
// selected item's file name, then either copies a replay (mode 4: in place
// through the recorder at 0x00099A40 with an in-game message, or from the last
// replay file name plus extension through 0x00099E10 with a message box), or
// saves the game through GameState::saveGame and shows "GUI:GameSaved", and
// finally sets the state to 8. Method name address-derived.
#include "ascii_string.h"
#include "unicode_string.h"

template <> inline const unsigned short *StringBase<unsigned short>::str() const
{
	return m_data ? m_data->data : (const unsigned short *)L"";
}

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

// 0x00522110 (still a generated dump; ILT 0x00047307): cdecl, returns a bool,
// stores its first word into the APT message-box state and reads the two
// strings through pointers (title, then body).
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
	Rva56E070SelectedItem *selected = (Rva56E070SelectedItem *)(unsigned int)bfmeTestME();
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
	}
	else
	{
		SaveFileType fileType = (SaveFileType)((const Rva0056AD10 *)this)->resolveMode();
		TheGameState->saveGame(filename, description, fileType, SNAPSHOT_SAVELOAD, true);
		rva00522110(0, TheGameText->fetch("APT:SaveGameProgress"), TheGameText->fetch("GUI:GameSaved"));
	}
	m_state = 8;
}
