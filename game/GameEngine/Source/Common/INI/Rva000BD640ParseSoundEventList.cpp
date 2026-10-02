// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// Retail 0x000BD640: INI list parser that appends one AudioEventRTS per sound token to a vector.
// NoSound appends an event with an empty info ref; an unknown name throws INIException 3.
// The owning field table is not named by any caller, so the method keeps its address.

#define _STLP_NO_EXCEPTIONS 1
#include <vector>

#include "ascii_string.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement( long volatile *lpAddend );
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement( long volatile *lpAddend );
extern "C" __declspec(dllimport) int __cdecl _strcmpi( const char *a, const char *b );

class INIException
{
public:
	INIException( int code, const char *msg, ... );
	INIException( const INIException &other );

private:
	int m_code;
	const char *m_msg;
};

class AudioEventInfo
{
public:
	virtual ~AudioEventInfo();

	// ?Add_Ref@AudioEventInfo@@QAEXXZ absent-from-retail
	void Add_Ref() { InterlockedIncrement( &m_refCount ); }
	// ?Release_Ref@AudioEventInfo@@QAEXXZ absent-from-retail
	void Release_Ref()
	{
		long refs = InterlockedDecrement( &m_refCount );
		if( refs <= 0 )
			delete this;
	}

	long m_refCount;
};

class AudioEventInfoRef
{
public:
	// ??0AudioEventInfoRef@@QAE@XZ absent-from-retail
	AudioEventInfoRef() : m_ptr( 0 ) {}
	// Out of line at 0x000877B0 (ILT 0x000362FF), where the unwind funclets jump.
	~AudioEventInfoRef()
	{
		if( m_ptr )
			m_ptr->Release_Ref();
	}
	// ??4AudioEventInfoRef@@QAEAAV0@ABV0@@Z absent-from-retail
	AudioEventInfoRef &operator=( const AudioEventInfoRef &rhs )
	{
		if( this != &rhs )
		{
			if( rhs.m_ptr )
				rhs.m_ptr->Add_Ref();
			if( m_ptr )
				m_ptr->Release_Ref();
			m_ptr = rhs.m_ptr;
		}
		return *this;
	}

	AudioEventInfo *m_ptr;
};

class Rva005A00B0AudioClient
{
public:
#define AUDIO_SLOT(n) virtual void slot##n();
	AUDIO_SLOT(0)  AUDIO_SLOT(1)  AUDIO_SLOT(2)  AUDIO_SLOT(3)
	AUDIO_SLOT(4)  AUDIO_SLOT(5)  AUDIO_SLOT(6)  AUDIO_SLOT(7)
	AUDIO_SLOT(8)  AUDIO_SLOT(9)  AUDIO_SLOT(10) AUDIO_SLOT(11)
	AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
	AUDIO_SLOT(16) AUDIO_SLOT(17) AUDIO_SLOT(18) AUDIO_SLOT(19)
	AUDIO_SLOT(20) AUDIO_SLOT(21) AUDIO_SLOT(22) AUDIO_SLOT(23)
	AUDIO_SLOT(24) AUDIO_SLOT(25) AUDIO_SLOT(26) AUDIO_SLOT(27)
	AUDIO_SLOT(28) AUDIO_SLOT(29) AUDIO_SLOT(30) AUDIO_SLOT(31)
	AUDIO_SLOT(32) AUDIO_SLOT(33) AUDIO_SLOT(34) AUDIO_SLOT(35)
	AUDIO_SLOT(36) AUDIO_SLOT(37) AUDIO_SLOT(38) AUDIO_SLOT(39)
	AUDIO_SLOT(40) AUDIO_SLOT(41) AUDIO_SLOT(42) AUDIO_SLOT(43)
	AUDIO_SLOT(44) AUDIO_SLOT(45) AUDIO_SLOT(46) AUDIO_SLOT(47)
	AUDIO_SLOT(48) AUDIO_SLOT(49) AUDIO_SLOT(50) AUDIO_SLOT(51)
	AUDIO_SLOT(52) AUDIO_SLOT(53) AUDIO_SLOT(54) AUDIO_SLOT(55)
	AUDIO_SLOT(56) AUDIO_SLOT(57) AUDIO_SLOT(58) AUDIO_SLOT(59)
	AUDIO_SLOT(60) AUDIO_SLOT(61) AUDIO_SLOT(62) AUDIO_SLOT(63)
	AUDIO_SLOT(64) AUDIO_SLOT(65) AUDIO_SLOT(66) AUDIO_SLOT(67)
	AUDIO_SLOT(68) AUDIO_SLOT(69)
#undef AUDIO_SLOT
	virtual AudioEventInfoRef findSound( const AsciiString &name );
};

// The linked build has one mangled name for the global at 0x012ED668: the
// canonical `AudioManager *TheAudio`, defined in GameAudio.cpp. The local view
// above is what this body calls through.
class AudioManager;
extern AudioManager *TheAudio;

static inline Rva005A00B0AudioClient *theAudioClient()
{
	return (Rva005A00B0AudioClient *)TheAudio;
}

// 0x70-byte view: the thin extra ctor (ILT 0x0001EC13), copy ctor and destructor are all it needs.
class AudioEventRTS
{
public:
	AudioEventRTS( const AsciiString &eventName, int extra );
	AudioEventRTS( const AudioEventRTS &other );
	~AudioEventRTS();

private:
	char m_unreconstructed00[ 0x70 ];
};

// The ledger's element name for this vector, whose overflow insert is matched at 0x000BCA50.
struct P5Elem000BD360 : public AudioEventRTS
{
};

typedef _STL::vector<P5Elem000BD360> Rva000BD640SoundVector;

class INI
{
public:
	const char *getNextTokenOrNull( const char *seps = 0 );

	static void rva000BD640( INI *ini, void *instance, void *store, const void *userData );
};

void INI::rva000BD640( INI *ini, void *, void *store, const void * )
{
	const char *token = ini->getNextTokenOrNull();
	while( token )
	{
		AudioEventInfoRef info;
		if( _strcmpi( token, "NoSound" ) == 0 )
		{
			if( info.m_ptr )
			{
				info.m_ptr->Release_Ref();
				info.m_ptr = 0;
			}
		}
		else
		{
			info = theAudioClient()->findSound( AsciiString( token ) );
			if( info.m_ptr == 0 )
				throw INIException( 3, "Invalid Sound '%s'", token );
		}
		// The thin ctor takes the info ref under its pinned AsciiString spelling.
		( (Rva000BD640SoundVector *)store )->push_back(
			static_cast<const P5Elem000BD360 &>(
				AudioEventRTS( reinterpret_cast<const AsciiString &>( info ), 0 ) ) );
		token = ini->getNextTokenOrNull();
	}
}
