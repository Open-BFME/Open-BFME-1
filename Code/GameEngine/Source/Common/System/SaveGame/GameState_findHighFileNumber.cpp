// ?findHighFileNumber@@YAXVAsciiString@@PAX@Z
// cl: /DNDEBUG /MD /EHsc
// readable body of ?findHighFileNumber@@YAXVAsciiString@@PAX@Z: Code/GameEngine/Source/Common/System/SaveGame/GameState.cpp
// Open-BFME: static findHighFileNumber(AsciiString, void *), the
// IterateSaveFileCallback used by GameState::findNextSaveFilename's disk
// scan, retail 0x0010EF70, 318 bytes.

typedef int Int;

#define _DLL
#include <stdlib.h>

extern "C" unsigned int __cdecl strlen(const char *str);
#pragma intrinsic(strlen)

template <typename T> class StringBase;

class AsciiString;

template <typename T> class StringBase
{
    friend class AsciiString;

protected:
	struct Header {
		int ref_count;
		unsigned short length;
		unsigned short capacity;
		T data[1];
	};

	Header *m_data;

public:
	StringBase(const StringBase<T> &src);
	bool endsWithNoCase(const T *p, Int len) const;
	void removeLastChar();
	int compare(const T *p) const;
};

class AsciiString : private StringBase<char>
{
public:
	~AsciiString();

	bool isEmpty() const { return m_data == 0 || m_data->length == 0; }
	const char *str() const { return m_data ? &m_data->data[0] : ""; }

	bool endsWithNoCase(const char *p) const
	{
		return StringBase<char>::endsWithNoCase(p, p ? (Int)strlen(p) : 0);
	}

	void removeLastChar() { StringBase<char>::removeLastChar(); }
	int compare(const char *p) const;
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
	for (Int count = 0; count < strlen(SAVE_GAME_EXTENSION); count++)
		nameOnly.removeLastChar();

	Int fileNumber;
	fileNumber = atoi(nameOnly.str());

	if (fileNumber == 0 && nameOnly.compare(ZERO_NAME_ONLY) != 0)
		return;

	Int *highFileNumber = (Int *)userData;
	if (fileNumber >= *highFileNumber)
		*highFileNumber = fileNumber;
}
