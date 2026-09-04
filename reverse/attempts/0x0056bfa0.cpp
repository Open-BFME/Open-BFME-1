// ?showAptSaveLoad@@YAXPAXHD@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc
// ?showAptSaveLoad@@YAXPAXHD@Z
// Retail 0x0056BFA0 188B. Inline-forwarder AsciiString over StringBase<char>
// fixes the EH-temp order (mov [esp+8],esp then mov ecx,esp). Prefix through
// the +0x274 store matches. Remaining miss is the flag-tail registers:
// extra in cl/dl instead of al, reload in edx instead of ecx, 186 vs 188.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data( 0 ) {}
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &o ) : StringBase<char>( o ) {}
	~AsciiString() {}
};

class Shell
{
public:
	void showAptScreen( AsciiString name, int unused );
};

class FlagValue
{
public:
	volatile int m_value;
	void operator=( int value ) { m_value = value; }
};

class AptSaveLoad
{
public:
	char m_unmodelled[ 0x270 ];
	void *m_270;
	int m_274;
	volatile char m_278;
	char m_pad279[ 3 ];
	long m_27c;
};

extern AptSaveLoad *TheAptSaveLoad;
extern Shell *TheShell;

void showAptSaveLoad( void *arg0, int flags, volatile char extra )
{
	if ( TheAptSaveLoad != 0 )
		return;
	AptSaveLoad *q;
	AptSaveLoad *p;
	char value;
	void *argument = arg0;
	TheShell->showAptScreen( AsciiString( "SaveLoad.apt" ), 0 );
	TheAptSaveLoad->m_270 = argument;
	TheAptSaveLoad->m_274 = flags;
	int flagBits = flags;
		if ( flagBits & 1 )
		{
			TheAptSaveLoad->m_27c = 1;
			value = extra;
			TheAptSaveLoad->m_278 = value;
			return;
		}
		else if ( flagBits & 2 )
		{
			value = extra;
			*(long *)( (char *)TheAptSaveLoad + 0x27c ) = 2;
			TheAptSaveLoad->m_278 = value;
			return;
		}
		else if ( flagBits & 4 )
	{
		q = TheAptSaveLoad;
		q->m_27c = 4;
	}
	TheAptSaveLoad->m_278 = extra;
}
