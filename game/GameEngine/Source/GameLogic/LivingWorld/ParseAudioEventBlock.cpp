// cl: /DNDEBUG /DWIN32 /MD /EHsc
// Open-BFME7: ParseAudioEventBlock (retail 0x003B7780 204 B; a gap claimed
// through its own exception text).  With no INI or instance it throws
// INIException(3 "ParseAudioEventBlock::Invalid data passed in."); otherwise
// a 16-byte record of the Rva003B7740 class (Rva003B7740ReleaseDtor.cpp: a
// vtable a pad the ref-counted holder and a flag byte all zeroed by the
// inline constructor) is filled through INI::initFromINI with the table at
// VA 0x010ECDC8 and handed to the instance's add routine (0x00415DD4 thunk)
// before the inline destructor releases the held reference.

typedef int Int;

struct FieldParse;

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile *lpAddend );

class INIException
{
public:
	INIException( Int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	Int m_code;
	const char *m_msg;
};

class INI
{
public:
	void initFromINI( void *what, const FieldParse *parseTable );
};

class RefCountedThing
{
public:
	virtual ~RefCountedThing();
	void Release_Ref( void )
	{
		if( InterlockedDecrement( &m_refCount ) <= 0 )
			delete this;
	}
	long m_refCount;
};

class BfmeReleaseHolder
{
public:
	BfmeReleaseHolder() : m_ptr( 0 ) {}
	~BfmeReleaseHolder()
	{
		if( m_ptr )
			m_ptr->Release_Ref();
	}
	RefCountedThing *m_ptr;
};

class Rva003B7740
{
public:
	Rva003B7740() : m_pad( 0 ), m_flag0C( false ) {}
	virtual ~Rva003B7740() {}

private:
	void *m_pad;
	BfmeReleaseHolder m_hold;
	bool m_flag0C;
};

extern const FieldParse Rva003B7780FieldParseTable[];

class Rva003B7780Owner
{
public:
	void addAudioEvent( Rva003B7740 *record );
};

// ?ParseAudioEventBlock@@YAXPAVINI@@PAX1PBX@Z
void ParseAudioEventBlock( INI *ini, void *instance, void *, const void * )
{
	if( ini && instance )
	{
		Rva003B7740 record;
		ini->initFromINI( &record, Rva003B7780FieldParseTable );
		((Rva003B7780Owner *)instance)->addAudioEvent( &record );
	}
	else
		throw INIException( 3, "ParseAudioEventBlock::Invalid data passed in." );
}
