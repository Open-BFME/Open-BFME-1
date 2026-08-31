// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// FILE: INILargeGroupAudioUnusedKnownKeys.cpp ////////////////////////////////
//
// The LargeGroupAudioUnusedKnownKeys block, retail 0x003CF010. BFME-only; the
// INI block table in .data names it.
//
// The subsystem at 0x012F1044 is TheLargeGroupAudio: the code at 0x0038A476
// stores into that same address and then builds the literal "TheLargeGroupAudio"
// into the AsciiString it hands the name setter. This block creates it on
// demand if it is still null, which is why nothing here tests it afterwards.
//
// The record is Zero Hour's Overridable protocol with BFME's field offsets: the
// next-override pointer at +0x04 and the override flag at +0x08, behind a vtable
// at +0x00. Both writes are inline here - retail stores the flag byte and the
// chain pointer directly - so only friend_getFinalOverride is a call, and the
// image already names that one.
//
// The final-override walk shows one level of its own recursion inlined: retail
// tests the chain pointer, and only calls when it is set. That is
// friend_getFinalOverride's own body, not a guard the caller wrote.
//
///////////////////////////////////////////////////////////////////////////////

struct FieldParse;

enum { INI_LOAD_CREATE_OVERRIDES = 2 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	int getLoadType() const { return m_loadType; }

	void initFromINI( void *what, const FieldParse *parseTable );

private:
	unsigned char m_unmodelled_00[ 8 ];
	int m_loadType;										// +0x08
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	Overridable *friend_getFinalOverride();
};

class LargeGroupAudioUnusedKnownKeys;

class LargeGroupAudioUnusedKnownKeysBase
{
public:
	virtual ~LargeGroupAudioUnusedKnownKeysBase();
	virtual void bfmeSlot0();

	LargeGroupAudioUnusedKnownKeys *m_nextOverride;
	bool m_isOverride;
	unsigned char m_unmodelled_09[ 3 ];
};

class LargeGroupAudioUnusedKnownKeys : public LargeGroupAudioUnusedKnownKeysBase
{
public:
	LargeGroupAudioUnusedKnownKeys();
	LargeGroupAudioUnusedKnownKeys( const LargeGroupAudioUnusedKnownKeys &original );

	static const FieldParse m_fieldParseTable[];		// 0x010EE0C4

	unsigned char m_unmodelled_0C[ 0x0C ];
};

class AsciiString
{
public:
	AsciiString() : m_data( 0 ) {}
	~AsciiString() {}

	void *m_data;
};

class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();

	virtual void bfmeSubsystemSlot();
	AsciiString m_name;
};

class __declspec(novtable) HordeContainModuleDataBase
{
public:
	virtual ~HordeContainModuleDataBase();
	virtual void bfmeSlot0();
};

class AudioVectorInit
{
public:
	AudioVectorInit()
	{
		*reinterpret_cast<volatile int *>( reinterpret_cast<unsigned char *>( this ) - 0x04 ) = 0x01073744;
		*reinterpret_cast<volatile int *>( reinterpret_cast<unsigned char *>( this ) - 0x0C ) = 0x010EE13C;
		*reinterpret_cast<volatile int *>( reinterpret_cast<unsigned char *>( this ) - 0x04 ) = 0x010EE128;
		m_begin = 0;
		m_end = 0;
		m_capacity = 0;
	}
	~AudioVectorInit();

	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class AudioVector
{
public:
	AudioVector() : m_begin( 0 ), m_end( 0 ), m_capacity( 0 ) {}
	~AudioVector();

	void *m_begin;
	void *m_end;
	void *m_capacity;
};

class __declspec(novtable) LargeGroupAudio : public SubsystemInterface, public HordeContainModuleDataBase
{
public:
	LargeGroupAudio();
	virtual ~LargeGroupAudio() {}
	virtual void bfmeSubsystemSlot();

	AudioVectorInit m_0C;
	AudioVector m_18;
	AudioVector m_24;
	LargeGroupAudioUnusedKnownKeys *m_unusedKnownKeys;
	volatile unsigned char m_34;
	unsigned char m_35[ 3 ];
};

extern LargeGroupAudio *TheLargeGroupAudio;				// 0x012F1044

LargeGroupAudio::LargeGroupAudio() : SubsystemInterface()
{
	m_unusedKnownKeys = 0;
	m_34 = 1;
	m_unusedKnownKeys = new LargeGroupAudioUnusedKnownKeys();
}

// ?parseLargeGroupAudioUnusedKnownKeys@@YAXPAVINI@@@Z
void parseLargeGroupAudioUnusedKnownKeys( INI *ini )
{
	if( !TheLargeGroupAudio )
		TheLargeGroupAudio = new LargeGroupAudio();

	LargeGroupAudioUnusedKnownKeys *keys;

	if( ini->getLoadType() == INI_LOAD_CREATE_OVERRIDES )
	{
		LargeGroupAudioUnusedKnownKeys *override =
			new LargeGroupAudioUnusedKnownKeys( *TheLargeGroupAudio->m_unusedKnownKeys );

		override->m_isOverride = true;

		TheLargeGroupAudio->m_unusedKnownKeys->m_nextOverride = override;

		keys = override;
	}
	else
	{
		keys = TheLargeGroupAudio->m_unusedKnownKeys;

		if( keys->m_nextOverride )
			keys = (LargeGroupAudioUnusedKnownKeys *)
				((Overridable *)keys->m_nextOverride)->friend_getFinalOverride();
	}

	ini->initFromINI( keys, LargeGroupAudioUnusedKnownKeys::m_fieldParseTable );
}
