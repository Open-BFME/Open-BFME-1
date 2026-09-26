// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Real-C++ reconstruction of the anonymous GameState auto-save helper at
// retail RVA 0x003BDB80. The GUI:AutoSaveName string and TheGameState call
// identify this body, but the original semantic method name remains unknown.

typedef bool Bool;
typedef unsigned short WideChar;

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString(const WideChar *text) : StringBase<WideChar>(text) {}
	UnicodeString(const UnicodeString &other)
		: StringBase<WideChar>(other) {}
	~UnicodeString() {}
};

class GameTextInterface
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual UnicodeString fetch(const char *label, Bool *exists = 0);
	virtual UnicodeString fetch(AsciiString label, Bool *exists = 0);
};

class InGameUI
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void message(UnicodeString format, ...);
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
	SC_OK = 0
};

class GameState
{
public:
	SaveCode saveGame(AsciiString filename, UnicodeString desc,
		SaveFileType saveType, SnapshotType which, Bool showMessage);
};

extern void j_00020cd4();

struct SaveGameCallTarget
{
	SaveCode saveGame(AsciiString filename, UnicodeString desc,
		SaveFileType saveType, SnapshotType which, Bool showMessage);
};
typedef SaveCode (SaveGameCallTarget::*SaveGameCall)(AsciiString,
	UnicodeString, SaveFileType, SnapshotType, Bool);

#define TheGameState (*(GameState **)0x012EF190)
#define TheGameText (*(GameTextInterface **)0x012F147C)
#define TheInGameUI (*(InGameUI **)0x012F148C)

class Rva003BDB80GameState
{
public:
	void autoSave();
};

// ?autoSave@Rva003BDB80GameState@@QAEXXZ
void Rva003BDB80GameState::autoSave()
{
	union
	{
		void (*asFunction)();
		SaveGameCall asMember;
	} saveGameCast;
	saveGameCast.asFunction = j_00020cd4;
	SaveCode result = (reinterpret_cast<SaveGameCallTarget *>(TheGameState)->*
		saveGameCast.asMember)(
		AsciiString("00000000.sav"),
		UnicodeString(L"__AUTO#SAVE__"),
		SAVE_FILE_TYPE_MISSION, SNAPSHOT_SAVELOAD, false);
	if (result == SC_OK)
		TheInGameUI->message(TheGameText->fetch("GUI:AutoSaveName"), "ON");
}
