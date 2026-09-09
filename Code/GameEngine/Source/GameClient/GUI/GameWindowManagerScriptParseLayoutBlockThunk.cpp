// cl: /DNDEBUG /MD /EHsc
// Open-BFME: typed C++ reconstruction of the named parseLayoutBlock parser.
//
// The namespace gives this TU a distinct symbol; reverse/functions.csv
// names the retail body from the reference implementation
// and its named caller.  File deliberately mirrors the target-era vtable: the
// target has one MemoryPoolObject destructor followed by open through
// scanString, without the later getObjectMemoryPool virtual in the full header.

#include <string.h>

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)
extern "C" unsigned int __cdecl strlen(const char *);
#pragma intrinsic(strlen)

typedef unsigned int UnsignedInt;
typedef bool Bool;

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString() { releaseBuffer(); }

	// The cold first-token call is the proven out-of-line AsciiString compare.
	int compare(const char *text) const;

	// These two comparisons are inlined by the retail compiler.  Keeping the
	// StringBase-compatible eight-byte header local lets the compiler reproduce
	// the target's length-aware compare without inventing a linked wrapper.
	__forceinline int compareHot(const char *text) const
	{
		int textLength = text ? strlen(text) : 0;
		int stringLength = m_data ? m_data->length : 0;
		const char *stringData = m_data ? m_data->data : "";
		int count = stringLength < textLength ? stringLength : textLength;
		int result = memcmp(stringData, text, count);
		if (result != 0)
			return result;
		return stringLength - textLength;
	}

	const char *str() const
	{
		return m_data ? reinterpret_cast<const char *>(m_data) + 8 : "";
	}

private:
	struct Data
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		char data[1];
	};

	void releaseBuffer();
	Data *m_data;
};

class MemoryPoolObject
{
public:
	virtual ~MemoryPoolObject();
};

// This is the target-era File ABI observed in parseLayoutBlock and
// readUntilSemicolon.  The current full File header has an additional virtual
// getObjectMemoryPool, which would move scanString from slot +0x24 to +0x28.
class File : public MemoryPoolObject
{
public:
	virtual Bool open(const char *, int = 0) = 0;
	virtual void close() = 0;
	virtual int read(void *, int) = 0;
	virtual int write(const void *, int) = 0;
	virtual int seek(int, int = 0) = 0;
	virtual void nextLine(char * = 0, int = 0) = 0;
	virtual Bool scanInt(int &) = 0;
	virtual Bool scanReal(float &) = 0;
	virtual Bool scanString(AsciiString &string) = 0;
};

class WindowLayoutInfo;

typedef Bool (*LayoutParse)(char *, char *, UnsignedInt, WindowLayoutInfo *);

struct LayoutScriptParse
{
	char *name;
	LayoutParse parse;
};

// The three entries are the named registrations in GameWindowManagerScript's
// layoutScriptTable; each callback is already matched at its own retail RVA.
extern Bool parseInit(char *, char *, UnsignedInt, WindowLayoutInfo *);
extern Bool parseUpdate(char *, char *, UnsignedInt, WindowLayoutInfo *);
extern Bool parseShutdown(char *, char *, UnsignedInt, WindowLayoutInfo *);
extern void __cdecl readUntilSemicolon(File *, char *, int);
extern __declspec(dllimport) char *__cdecl strtok(char *, const char *);

static LayoutScriptParse layoutScriptTable[] =
{
	{ (char *)"LAYOUTINIT", parseInit },
	{ (char *)"LAYOUTUPDATE", parseUpdate },
	{ (char *)"LAYOUTSHUTDOWN", parseShutdown },
	{ 0, 0 }
};

// The row's object-symbol note maps this link-isolated definition to the
// proven ?parseLayoutBlock@@... retail identity and named caller.  A namespace
// gives the standalone TU a unique C++ symbol without changing its code shape.
namespace BfmeParseLayout
{
Bool __cdecl parseLayoutBlock(
	File *inFile, char *buffer, UnsignedInt version, WindowLayoutInfo *info)
{
	AsciiString asciitoken;
	char token[256];
	if (inFile->scanString(asciitoken) == false)
		return false;

	if (asciitoken.compare("STARTLAYOUTBLOCK") != 0)
		return false;

	while (true)
	{
		inFile->scanString(asciitoken);

		if (asciitoken.compareHot("ENDLAYOUTBLOCK") == 0)
			break;

		for (LayoutScriptParse *parse = layoutScriptTable;
			parse && parse->name; parse++)
		{
			int match = asciitoken.compareHot(parse->name);
			if (match != 0)
				continue;
			{
				char *c;
				readUntilSemicolon(inFile, buffer, 2048);
				c = strtok(buffer, " =");
				strcpy(token, asciitoken.str());
				if (parse->parse(token, c, version, info) == false)
					return false;
				break;
			}
		}
	}

	return true;
}
}
