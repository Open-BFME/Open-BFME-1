// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

// Open-BFME5: AudioEventRTS::getFilename, retail 0x000B3B70.
// BFME lazily regenerates a dirty filename when event metadata is available.

class AudioEventRTS
{
public:
	AsciiString getFilename();
	void generateFilename();

private:
	void *m_vtable;
	AsciiString m_filenameToLoad;
	const void *m_eventInfo;
	char m_pad[0x3a];
	bool m_filenameDirty;
};

AsciiString AudioEventRTS::getFilename()
{
	if (m_filenameDirty && m_eventInfo != 0)
		generateFilename();
	return m_filenameToLoad;
}
