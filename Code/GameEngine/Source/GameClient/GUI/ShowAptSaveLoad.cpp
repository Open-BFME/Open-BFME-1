// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Retail 0056BFA0: launch SaveLoad.apt once, then configure its singleton.
// Volatile by-value byte preserves the retail argument reloads; reconstruction
// shaping, not evidence that the original source used volatile.

#include "StringInline.h"

class Shell
{
public:
	void push(AsciiString name, bool shutdownImmediate);
};

class AptSaveLoad
{
public:
	char m_unmodelled[ 0x270 ];
	void *m_270;
	int m_274;
	char m_278;
	char m_pad279[ 3 ];
	int m_27c;
};

extern AptSaveLoad *TheAptSaveLoad;
extern Shell *TheShell;

// ?showAptSaveLoad@@YAXPAXHD@Z
void showAptSaveLoad( void *arg0, int flags, const volatile char extra )
{
	if ( TheAptSaveLoad != 0 )
		return;
	void *argument = arg0;
	int flagBits = flags;
	TheShell->push( AsciiString( "SaveLoad.apt" ), false );
	TheAptSaveLoad->m_270 = argument;
	TheAptSaveLoad->m_274 = flagBits;
	if (flagBits & 1) TheAptSaveLoad->m_27c=1;
	else if (flagBits & 2) TheAptSaveLoad->m_27c=2;
	else if (flagBits & 4) TheAptSaveLoad->m_27c=4;
	TheAptSaveLoad->m_278=extra;
}
