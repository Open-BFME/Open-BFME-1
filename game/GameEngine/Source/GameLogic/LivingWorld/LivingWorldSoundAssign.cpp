// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class Xfer;

extern void j_00002c2a(void);
extern void j_0003afe4(void);

class LivingWorldSoundThunkCall
{
};

template <class Function>
__forceinline Function livingWorldSoundThunk(void (*raw)())
{
	union { void (*raw)(); Function member; } fn;
	fn.raw = raw;
	return fn.member;
}

#define LIVING_WORLD_SOUND_THUNK_CALL(object, Function, raw) \
	(reinterpret_cast<LivingWorldSoundThunkCall *>(object)->*livingWorldSoundThunk<Function>(raw))

class Rva00087750Counted;

// Retail ILT0x0002C6D8 reaches the verified ref-count assignment at0x00087750.
class Rva00087750Ref
{
public:
	Rva00087750Ref &operator=(const Rva00087750Ref &other);

	Rva00087750Counted *m_ptr;
};

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

struct Region2DBase
{
	float xMin;
	float yMin;
	float xMax;
	float yMax;
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void LoadPostProcess() = 0;
	virtual const char *GetSnapshotName() = 0;
	virtual void DoXfer( Xfer &xfer ) = 0;
};

class LivingWorldSound : public Snapshot
{
public:
	LivingWorldSound &operator=( const LivingWorldSound &that );
	virtual ~LivingWorldSound();
	virtual void LoadPostProcess();
	virtual const char *GetSnapshotName();
	virtual void DoXfer( Xfer &xfer );

	void Rva0061C060();

private:
	AsciiString m_name;
	Coord3DBase m_position;
	Rva00087750Ref m_sound;
	unsigned int m_flags;
	Region2DBase m_zoomRegion;
	int m_playState;
	bool m_shouldFade;
	bool m_isPlaying;
	bool m_hasPlayed;
};

LivingWorldSound &LivingWorldSound::operator=( const LivingWorldSound &that )
{
	if ( this != &that )
	{
		typedef void (LivingWorldSoundThunkCall::*BfmeTwoNA)(void);
		LIVING_WORLD_SOUND_THUNK_CALL(this, BfmeTwoNA, j_0003afe4)();

		m_name = that.m_name;

		m_position = that.m_position;

		m_sound = that.m_sound;
		m_flags = that.m_flags;

		m_zoomRegion = that.m_zoomRegion;

		m_shouldFade = that.m_shouldFade;
		m_isPlaying = that.m_isPlaying;
		m_hasPlayed = that.m_hasPlayed;

		if ( static_cast<unsigned int>( that.m_playState ) >= 5 && m_sound.m_ptr != 0 )
		{
			typedef void (LivingWorldSoundThunkCall::*BfmeOneNA)(void);
			LIVING_WORLD_SOUND_THUNK_CALL(this, BfmeOneNA, j_00002c2a)();
		}
	}

	return *this;
}
