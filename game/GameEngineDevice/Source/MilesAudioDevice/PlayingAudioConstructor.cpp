// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
//
// Retail's MilesAudioManager::allocatePlayingAudio body at 0x0069AAA0
// allocates 0x40 bytes, constructs this type, and then changes m_status at
// +0x10 from PS_Stopped to PS_Playing.  MilesAudioManager::stopAudio fixes the
// handle/type/status/event fields at +0x08..+0x14.  The deleting destructor at
// 0x006BA0E0 and its sole vtable slot prove that the object is ref-counted and
// that PlayingAudio has one real virtual destructor, rather than padding slots.

enum PlayingAudioType
{
	PAT_Sample,
	PAT_3DSample,
	PAT_Stream,
	PAT_Bink,
	PAT_Invalid
};

enum PlayingStatus
{
	PS_Playing,
	PS_Stopped,
	PS_Paused
};

class RefCountClass
{
public:
	RefCountClass() : m_refCount(0) {}
	virtual ~RefCountClass();

private:
	volatile long m_refCount;
};

// The one-pointer reference handle is independently present at 0x00690FE0
// (default construction), 0x00690FF0 (construction from a pointee), and
// 0x00691030 (release on destruction).  Its pointee identity is not needed by
// this constructor, so retain the address-qualified family name already used
// by the matched 0x006911A0 handle-return body.
class Rva00690FF0Handle
{
public:
	Rva00690FF0Handle();
	~Rva00690FF0Handle();

private:
	void *m_pointer;
};

class AudioEventRTS;

// Retail unwind funclet 0x00C493A8 destroys the +0x14 member through
// 0x00008A99 -> 0x00691200.  That destructor releases AudioEventRTS through
// its ref-counted secondary base at +0x70, proving this is an owning handle
// rather than the raw pointer used by the older Zero Hour layout.
class Rva00691200Holder
{
public:
	Rva00691200Holder() : m_pointer(0) {}
	~Rva00691200Holder();

private:
	AudioEventRTS *m_pointer;
};

class PlayingAudio : public RefCountClass
{
public:
	PlayingAudio();
	virtual ~PlayingAudio();

private:
	void *m_milesHandle;                 // +0x08, assigned by the play path
	PlayingAudioType m_type;             // +0x0c
	volatile PlayingStatus m_status;     // +0x10, written by the audio thread
	Rva00691200Holder m_audioEventRTS;   // +0x14, owning event handle
	Rva00690FF0Handle m_file;            // +0x18, owning one-pointer handle
	unsigned int m_value1c;              // +0x1c
	unsigned int m_value20;              // +0x20
	unsigned int m_value24;              // +0x24
	unsigned int m_value28;              // +0x28
	float m_volume;                      // +0x2c
	int m_playingAudioIndex;             // +0x30
	bool m_flag34;                       // +0x34
	bool m_flag35;
	bool m_flag36;
	bool m_flag37;
	bool m_flag38;
	bool m_flag39;
	bool m_flag3a;
	bool m_flag3b;
	bool m_flag3c;
	bool m_flag3d;
	bool m_flag3e;
};

typedef char PlayingAudio_must_be_0x40_bytes[
	(sizeof(PlayingAudio) == 0x40) ? 1 : -1];

PlayingAudio::PlayingAudio() :
	RefCountClass(),
	m_type(PAT_Invalid),
	m_status(PS_Stopped),
	m_audioEventRTS(),
	m_file(),
	m_value1c(0),
	m_value20(0),
	m_value24(0),
	m_value28(0),
	m_volume(1.0f),
	m_playingAudioIndex(-1),
	m_flag34(false),
	m_flag35(false),
	m_flag36(false),
	m_flag37(false),
	m_flag38(false),
	m_flag39(false),
	m_flag3a(false),
	m_flag3b(false),
	m_flag3c(false),
	m_flag3d(false),
	m_flag3e(false)
{
}
