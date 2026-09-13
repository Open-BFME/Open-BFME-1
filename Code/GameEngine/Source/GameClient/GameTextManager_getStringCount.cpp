// cl: /DNDEBUG /MD /EHsc /Ob1
// BFME's map-string count helper, called by initMapStringFile at 0x00438D50.
// The caller opens the File and passes it through; this is not the ZH
// filename-opening getStringCount implementation in GameText.cpp.

#include <string.h>

typedef int Int;
typedef bool Bool;
typedef char Char;

enum
{
	MAX_UITEXT_LENGTH = 10 * 1024
};

class File
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual Int read(void *buffer, Int bytes) = 0;
};

// The first eight bytes are SubsystemInterface's vptr and data word.  The
// retail GameTextManager keeps its first character buffer at +0x0c.
class GameTextManager
{
	protected:
	Bool readLine(Char *buffer, Int max, File *file)
	{
		Int ok = 0;
		while (max && file->read(buffer, 1) == 1)
		{
			ok = 1;
			if (*buffer == '\n')
				break;
			++buffer;
			--max;
		}
		*buffer = 0;
		return ok;
	}

	void removeLeadingAndTrailing(Char *buffer);
	void readToEndOfQuote(File *file, Char *in, Char *out, Char *wavefile,
		Int maxBufLen);

	Bool getStringCount(File *file, Int &textCount);

	void *m_vtable;
	unsigned m_subsystemData;
	Int m_textCount;
	Char m_buffer[MAX_UITEXT_LENGTH];
	Char m_buffer2[MAX_UITEXT_LENGTH];
	Char m_buffer3[MAX_UITEXT_LENGTH];
};

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *, const char *);

// ?getStringCount@GameTextManager@@IAE_NPAVFile@@AAH@Z
Bool GameTextManager::getStringCount(File *file, Int &textCount)
{
	Char quoteBuffer[MAX_UITEXT_LENGTH];
	Char waveBuffer[MAX_UITEXT_LENGTH];
	textCount = 0;

	if (file == NULL)
		return 0;

	while (1)
	{
		if (!readLine(m_buffer, sizeof(m_buffer) - 1, file))
			break;

		removeLeadingAndTrailing(m_buffer);

		if (m_buffer[0] == '"')
		{
			Int len = strlen(m_buffer);
			m_buffer[len] = '\n';
			m_buffer[len + 1] = 0;
			readToEndOfQuote(file, &m_buffer[1], quoteBuffer, waveBuffer,
				MAX_UITEXT_LENGTH);
		}
		else if (_strcmpi(m_buffer, "END") == 0)
		{
			++textCount;
		}
	}

	textCount += 500;
	return 1;
}
