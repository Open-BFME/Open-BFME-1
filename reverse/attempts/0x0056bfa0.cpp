// ?showAptSaveLoad@@YAXPAXHD@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// ?showAptSaveLoad@@YAXPAXHD@Z
// Retail 0x0056BFA0 188B. Inline-forwarder AsciiString over StringBase<char>
// fixes the EH-temp order (mov [esp+8],esp then mov ecx,esp). Prefix through
// the +0x274 store matches. Remaining miss is the flag-tail registers:
// extra in cl/dl instead of al, reload in edx instead of ecx, 186 vs 188.

#include "StringInline.h"

class Shell
{
public:
	void showAptScreen( AsciiString name, int unused );
};

class AptSaveLoad
{
public:
	char m_unmodelled[ 0x270 ];
	void *m_270;
	int m_274;
	volatile char m_278;
	char m_pad279[ 3 ];
	int m_27c;
};

extern AptSaveLoad *TheAptSaveLoad;
extern Shell *TheShell;

void showAptSaveLoad( void *arg0, int flags, const volatile char extra )
{
	if ( TheAptSaveLoad != 0 )
		return;
	char value;
	AptSaveLoad *p;
	AptSaveLoad *q;
	void *argument = arg0;
	int flagBits = flags;
	TheShell->showAptScreen( AsciiString( "SaveLoad.apt" ), 0 );
	TheAptSaveLoad->m_270 = argument;
	TheAptSaveLoad->m_274 = flagBits;
		if ( flagBits & 1 )
		{
			TheAptSaveLoad->m_27c = 1;
			value = extra;
			TheAptSaveLoad->m_278 = value;
			return;
		}
		if ( flagBits & 2 )
		{
			TheAptSaveLoad->m_27c = 2;
			TheAptSaveLoad->m_278 = extra;
			return;
		}
	if ( flagBits & 4 )
	{
		TheAptSaveLoad->m_27c = 4;
	}
	TheAptSaveLoad->m_278 = extra;
}
