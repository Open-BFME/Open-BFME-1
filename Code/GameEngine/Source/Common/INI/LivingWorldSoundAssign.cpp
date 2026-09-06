// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/campaignmanagerascii /ICode/Libraries/Source/WWVegas/WWLib

#include "Common/AsciiString.h"

class Xfer;

// Existing pinned helper identity is address-derived; its implementation is
// the LivingWorldSound stop-current-sound path at 0x0061BB50.
class BfmeThingNA
{
public:
	void bfmeTwoNA();
};

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
		reinterpret_cast<BfmeThingNA *>( this )->bfmeTwoNA();

		m_name = that.m_name;

		m_position = that.m_position;

		m_sound = that.m_sound;
		m_flags = that.m_flags;

		m_zoomRegion = that.m_zoomRegion;

		m_shouldFade = that.m_shouldFade;
		m_isPlaying = that.m_isPlaying;
		m_hasPlayed = that.m_hasPlayed;

		if ( static_cast<unsigned int>( that.m_playState ) >= 5 && m_sound.m_ptr != 0 )
			Rva0061C060();
	}

	return *this;
}
