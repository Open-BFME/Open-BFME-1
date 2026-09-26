// ?d_00694130@@YAXXZ
// partial score=0.64 date=2026-09-16
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/stringinline

#include "StringInline.h"

struct Rva00694130AudioEventInfo
{
	unsigned char m_pad00[0x84];
	unsigned int m_soundType;
};

class AudioEventRTS
{
public:
	AsciiString getFilenameForPlayPortion();

	void *m_vtable;
	AsciiString m_filenameToLoad;
	Rva00694130AudioEventInfo *m_eventInfo;
};

class Rva00694130Handle
{
public:
	Rva00694130Handle();
	~Rva00694130Handle();
	void *m_target;
};

class Rva00694130Owner
{
public:
	Rva00694130Handle build(AudioEventRTS **event, int value);
	Rva00694130Handle dispatch(AsciiString filename, int value);
};

#pragma comment(linker, "/alternatename:??0Rva00694130Handle@@QAE@XZ=?j_0002833f@@YAXXZ")
#pragma comment(linker, "/alternatename:??1Rva00694130Handle@@QAE@XZ=?j_000298e8@@YAXXZ")
#pragma comment(linker, "/alternatename:?dispatch@Rva00694130Owner@@QAE?AVRva00694130Handle@@VAsciiString@@H@Z=?j_0003214b@@YAXXZ")

Rva00694130Handle Rva00694130Owner::build(AudioEventRTS **event, int value)
{
	AudioEventRTS *audioEvent = *event;
	if (audioEvent == 0)
	{
		return Rva00694130Handle();
	}

	if (audioEvent->m_eventInfo == 0)
	{
		return Rva00694130Handle();
	}

	if (audioEvent->m_eventInfo->m_soundType != 2)
	{
		return Rva00694130Handle();
	}

	AsciiString filename = audioEvent->getFilenameForPlayPortion();
	return dispatch(filename, value);
}
