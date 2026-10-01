// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail RVA 0x000BABF0 (283 bytes, cdecl). An INI field parser with the
// standard (ini, instance, store, userData) shape. It reads one token. The
// token NoSound drops the counted reference at store and clears it. Any other
// token becomes a name that a virtual call on TheAudio (slot 0x118)
// resolves to a counted reference, which is assigned into store. The parser
// throws INIException 3 "Invalid Sound '%s'" when store is still empty. The
// name and the reference are expression temporaries, which is what keeps the
// exception object out of their frame slots. The owning table is not named by
// any caller, so the method keeps its address.

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile *lpAddend );
extern "C" __declspec(dllimport) int __cdecl _stricmp( const char *a, const char *b );

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	StringBase( const StringBase<T> &other );
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	AsciiString( const AsciiString &other ) : StringBase<char>( other ) {}
	~AsciiString() {}
};

class INIException
{
public:
	INIException( int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	int m_code;
	const char *m_msg;
};

class Rva00087750Counted
{
public:
	virtual ~Rva00087750Counted();

	void Release_Ref()
	{
		if( InterlockedDecrement( &m_refCount ) <= 0 )
			delete this;
	}

	long m_refCount;
};

class Rva00087750Ref
{
public:
	Rva00087750Ref() : m_ptr( 0 ) {}
	~Rva00087750Ref()
	{
		if( m_ptr )
			m_ptr->Release_Ref();
	}
	Rva00087750Ref &operator=( const Rva00087750Ref &rhs );

	Rva00087750Counted *m_ptr;
};

class Rva005A00B0AudioClient
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void slot90();
	virtual void slot94();
	virtual void slot98();
	virtual void slot9C();
	virtual void slotA0();
	virtual void slotA4();
	virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0();
	virtual void slotB4();
	virtual void slotB8();
	virtual void slotBC();
	virtual void slotC0();
	virtual void slotC4();
	virtual void slotC8();
	virtual void slotCC();
	virtual void slotD0();
	virtual void slotD4();
	virtual void slotD8();
	virtual void slotDC();
	virtual void slotE0();
	virtual void slotE4();
	virtual void slotE8();
	virtual void slotEC();
	virtual void slotF0();
	virtual void slotF4();
	virtual void slotF8();
	virtual void slotFC();
	virtual void slot100();
	virtual void slot104();
	virtual void slot108();
	virtual void slot10C();
	virtual void slot110();
	virtual void slot114();
	virtual Rva00087750Ref findSound( const AsciiString &name );
};

class INI
{
public:
	const char *getNextToken( const char *seps = 0 );

	static void rva000BABF0( INI *ini, void *instance, void *store, const void *userData );
};

// Retail's global at 0x012ED668 is EA's `AudioManager *TheAudio`, defined once in
// Common/Audio/GameAudio.cpp. Rva005A00B0AudioClient above is this TU's vslot view
// of it, so the canonical global takes an opaque forward declaration and the cast at
// the use is the whole translation.
class AudioManager;

extern AudioManager *TheAudio;

static inline Rva005A00B0AudioClient *localTheAudio()
{
	return (Rva005A00B0AudioClient *)TheAudio;
}

void INI::rva000BABF0( INI *ini, void *, void *store, const void * )
{
	const char *token = ini->getNextToken();
	Rva00087750Ref *handle = (Rva00087750Ref *)store;
	if( _stricmp( token, "NoSound" ) == 0 )
	{
		if( handle->m_ptr )
		{
			handle->m_ptr->Release_Ref();
			handle->m_ptr = 0;
		}
		return;
	}

	*handle = localTheAudio()->findSound( AsciiString( token ) );

	if( handle->m_ptr == 0 )
		throw INIException( 3, "Invalid Sound '%s'", token );
}
