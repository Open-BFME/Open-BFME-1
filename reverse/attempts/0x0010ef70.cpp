// ?findHighFileNumber@@YAXVAsciiString@@PAX@Z
// partial score=0.85 date=2026-09-05
// cl: /DNDEBUG /MD /EHsc
// readable body of ?findHighFileNumber@@YAXVAsciiString@@PAX@Z: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp
// Open-BFME: static findHighFileNumber(AsciiString, void *), the
// IterateSaveFileCallback used by GameState::findNextSaveFilename's disk
// scan, retail 0x0010EF70, 318 bytes.
//
// Sanity-checks the extension, strips it off a copy, atoi's what remains,
// and keeps the running high-water mark in *userData.

typedef int Int;

// The original translation unit linked the dynamic CRT, so CRT calls that are
// not compiler intrinsics (e.g. atoi) go through the import table. Defining
// _DLL before the CRT headers reproduces that dllimport linkage.
#define _DLL
#include <stdlib.h>

extern "C" unsigned int __cdecl strlen(const char *str);
#pragma intrinsic(strlen)

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:
	AsciiString(const AsciiString &src);			// 0x00887B60
	~AsciiString();						// 0x00887940

	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	const char *str() const { return m_data ? &m_data->data[0] : ""; }

	bool endsWithNoCase(const char *p, Int len) const;	// 0x00887680
	bool endsWithNoCase(const char *p) const { return endsWithNoCase(p, p ? (Int)strlen(p) : 0); }

	void removeLastChar();					// 0x00887F80

	int compare(const char *p) const;			// 0x0004B01A (ILT of StringBase<char>::compare(const char*))

private:
	struct Header {
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	Header *m_data;
};

static const char *SAVE_GAME_EXTENSION = ".sav";
static const char *ZERO_NAME_ONLY      = "00000000";

void findHighFileNumber(AsciiString filename, void *userData)
{
	if (filename.isEmpty())
		return;

	if (filename.endsWithNoCase(SAVE_GAME_EXTENSION) == false)
		return;

	AsciiString nameOnly = filename;
	for (Int count = 0; count < (Int)strlen(SAVE_GAME_EXTENSION); count++)
		nameOnly.removeLastChar();

	Int fileNumber;
	fileNumber = atoi(nameOnly.str());

	if (fileNumber == 0 && nameOnly.compare(ZERO_NAME_ONLY) != 0)
		return;

	Int *highFileNumber = (Int *)userData;
	if (fileNumber >= *highFileNumber)
		*highFileNumber = fileNumber;
}
