// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// readable body of ?init@AudioManager@@: game/GameEngine/Source/Common/Audio/GameAudio.cpp
// ?init@AudioManager@@QAEXXZ

// This TU exists for the same reason CampaignManager_init.cpp does.
// Common/GameAudio.h declares init() virtual, which mangles to UAEXXZ, while
// retail's body is the nonvirtual QAEXXZ reached through the
// initSubsystem<AudioManager> registration at RVA 0x000730D0. The INI local is
// likewise a 0x848-byte stack object rather than the header's larger INI.
//
// The BFME tail past the CD loop is not the Zero Hour source: BFME adds the two
// AmbientStream loads (12 INI loads, not 10), writes the preferred volumes to the
// five absolute Miles globals rather than to members, and ends with an owner
// array allocation, the AIL file callbacks and the LOD speaker clamp.
//
// identity evidence: targets/game/reverse/identity_evidence/0x006b8220-audiomanager-init.md

#include "Common/AsciiString.h"

class Xfer;

#define NULL 0
#define TRUE 1

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/INI.h
class INI
{
public:
	INI();
	~INI();

	void load(AsciiString filename, INILoadType loadType, Xfer *xfer);

private:
	char m_storage[0x848];
};

// The only AudioSettings fields this body reads: a count at +0x2c that sizes the
// owner array, a dword at +0x44 handed to BfmeB1012::go1012, and the five
// consecutive preferred-volume floats at +0x94..+0xa4.
class AudioSettings006B8220
{
public:
	char m_pad00[0x2c];
	int m_ownerCount;         // +0x2c
	char m_pad30[0x14];
	int m_field44;            // +0x44
	char m_pad48[0x4c];
	float m_preferredSoundVolume;    // +0x94
	float m_preferred3DSoundVolume;  // +0x98
	float m_preferredSpeechVolume;  // +0x9c
	float m_preferredMusicVolume;   // +0xa0
	float m_preferredAmbientVolume; // +0xa4
};

// The five Miles volume globals. game/GameEngine/Source/Common/
// Rva006B4970SetClient.cpp proves the id mapping by storing each global then
// calling the same helper with the matching id: 0x012BA12C<->0,
// 0x012BA130<->1, 0x012BA134<->2, 0x012BA138<->3, 0x012BA13C<->4.
//
// These are plain named float objects so that the store is a `fstp` of a value
// MSVC chose on the x87 stack.
extern float g_milesVolume012BA12C;
extern float g_milesVolume012BA130;
extern float g_milesVolume012BA134;
extern float g_milesVolume012BA138;
extern float g_milesVolume012BA13C;

// The pushed float fallbacks: 0x0109F748 is __real@3f400000 (0.75) and
// 0x010B933C is __real@3f0ccccd (0.55) per dir32_addresses.csv.
extern const float g_real3f400000 = 0.75f;
extern const float g_real3f0ccccd = 0.55f;

// One stack slot, cdecl, result unused at every site. 0x00047F3C thunks to the
// 0x00699AF0 body, which walks two client slots per channel across three rows.
void __cdecl j_00047f3c(int channelId);

// ?loadMusicFilesFromCD@FileSystem@@QAEXXZ through thunk 0x0000D2F6. Retail
// calls it as a __thiscall member on `this` (`mov ecx,esi` before each of the
// two sites), so it is reached here by casting `this` (offset 0) to FileSystem.
// The full Zero Hour FileSystem is a base of AudioManager at offset 0.
class FileSystem
{
public:
	void loadMusicFilesFromCD();
};

// ?OSDisplayWarningBox@@YA?AW4OSDisplayButtonType@@VAsciiString@@0II@Z through
// thunk 0x00028A2E; the raw enum return is what the body compares against 2.
enum OSDisplayButtonType
{
	OSDBT_OK = 0x00000001,
	OSDBT_CANCEL = 0x00000002
};
OSDisplayButtonType __cdecl OSDisplayWarningBox(AsciiString prompt, AsciiString message,
	unsigned int buttonFlags, unsigned int otherFlags);

enum
{
	OSDOF_SYSTEMMODAL = 0x00000001,
	OSDOF_EXCLAMATIONICON = 0x00000008
};

// The 0x40-byte owner allocated by the tail. Its scalar destructor is the
// matched 0x00699D60 body reached through thunk 0x0002D902, and its constructor
// is the 0x00699CB0 body reached through thunk 0x000315B6. Byte width 0x40 is
// fixed by the __ehvec_dtor operand and by Rva00699D60AudioOwnerVectorDeletingDestructor.
class Rva00699D60AudioOwner
{
public:
	// A user-declared constructor is what makes retail's `new T[n]` lower to the
	// ??_L element-construct helper at 0x009F6EE4 with this ctor and this dtor.
	// With only a destructor declared MSVC elides the construction loop entirely.
	Rva00699D60AudioOwner();
	~Rva00699D60AudioOwner();

private:
	unsigned char m_storage[0x40];
};

// ?TheGameLODManager@@3PAVGameLODManager@@A, global at 0x012ED5AC. The body reads
// the LOD index at +0x16cc and a stride-8 table of speaker counts at +0x170,
// clamping the result to 2 before storing it as a word at this+0x628.
class GameLODManager006B8220
{
public:
	char m_pad000[0x170];
	unsigned short m_speakerTable[8][4];          // +0x170, stride 8
	char m_pad1b0[0x151c];
	int m_lodIndex;                              // +0x16cc
};

// ?TheGameLODManager@@3PAVGameLODManager@@A
extern GameLODManager006B8220 *TheGameLODManager;

// ?bfmeGo1012B@BfmeB1012@@QAEXH@Z, reached through thunk 0x00024F3C.
class BfmeB1012
{
public:
	void bfmeGo1012B(int value);
};

// ?openDevice@MilesAudioManager@@QAEXXZ, reached through thunk 0x000183B8.
// The full Zero Hour MilesAudioManager derives from AudioManager at offset 0.
class MilesAudioManager
{
public:
	void openDevice();
};

class AudioManager
{
public:
	// Retail re-reads this+0x0c for every volume channel and for the array
	// count/field reads, so the accessor stays a real call the optimizer can
	// inline. The array-new and go1012 statements read the member directly
	// (`m_audioSettings->...`): that spelling is what gives the count read its
	// rotated register (ECX at +0x02CC) and the go1012 argument its ECX temp.
	AudioSettings006B8220 *getAudioSettings() const { return m_audioSettings; }

	// The CD loop calls vtable slot +0x138, index 78 of the AudioManager vtable
	// 0x0111C0C0 (which routes there through ILT 0x00412413). The 78 preceding
	// entries are unclaimed bodies, so they are declared as pure virtuals purely
	// to place this method at its proven slot; no identity is claimed for them.
#define AUDIO_MANAGER_VSLOT(n) virtual void audioManagerVSlot##n() = 0;
	AUDIO_MANAGER_VSLOT(00) AUDIO_MANAGER_VSLOT(01)
	AUDIO_MANAGER_VSLOT(02) AUDIO_MANAGER_VSLOT(03)
	AUDIO_MANAGER_VSLOT(04) AUDIO_MANAGER_VSLOT(05)
	AUDIO_MANAGER_VSLOT(06) AUDIO_MANAGER_VSLOT(07)
	AUDIO_MANAGER_VSLOT(08) AUDIO_MANAGER_VSLOT(09)
	AUDIO_MANAGER_VSLOT(10) AUDIO_MANAGER_VSLOT(11)
	AUDIO_MANAGER_VSLOT(12) AUDIO_MANAGER_VSLOT(13)
	AUDIO_MANAGER_VSLOT(14) AUDIO_MANAGER_VSLOT(15)
	AUDIO_MANAGER_VSLOT(16) AUDIO_MANAGER_VSLOT(17)
	AUDIO_MANAGER_VSLOT(18) AUDIO_MANAGER_VSLOT(19)
	AUDIO_MANAGER_VSLOT(20) AUDIO_MANAGER_VSLOT(21)
	AUDIO_MANAGER_VSLOT(22) AUDIO_MANAGER_VSLOT(23)
	AUDIO_MANAGER_VSLOT(24) AUDIO_MANAGER_VSLOT(25)
	AUDIO_MANAGER_VSLOT(26) AUDIO_MANAGER_VSLOT(27)
	AUDIO_MANAGER_VSLOT(28) AUDIO_MANAGER_VSLOT(29)
	AUDIO_MANAGER_VSLOT(30) AUDIO_MANAGER_VSLOT(31)
	AUDIO_MANAGER_VSLOT(32) AUDIO_MANAGER_VSLOT(33)
	AUDIO_MANAGER_VSLOT(34) AUDIO_MANAGER_VSLOT(35)
	AUDIO_MANAGER_VSLOT(36) AUDIO_MANAGER_VSLOT(37)
	AUDIO_MANAGER_VSLOT(38) AUDIO_MANAGER_VSLOT(39)
	AUDIO_MANAGER_VSLOT(40) AUDIO_MANAGER_VSLOT(41)
	AUDIO_MANAGER_VSLOT(42) AUDIO_MANAGER_VSLOT(43)
	AUDIO_MANAGER_VSLOT(44) AUDIO_MANAGER_VSLOT(45)
	AUDIO_MANAGER_VSLOT(46) AUDIO_MANAGER_VSLOT(47)
	AUDIO_MANAGER_VSLOT(48) AUDIO_MANAGER_VSLOT(49)
	AUDIO_MANAGER_VSLOT(50) AUDIO_MANAGER_VSLOT(51)
	AUDIO_MANAGER_VSLOT(52) AUDIO_MANAGER_VSLOT(53)
	AUDIO_MANAGER_VSLOT(54) AUDIO_MANAGER_VSLOT(55)
	AUDIO_MANAGER_VSLOT(56) AUDIO_MANAGER_VSLOT(57)
	AUDIO_MANAGER_VSLOT(58) AUDIO_MANAGER_VSLOT(59)
	AUDIO_MANAGER_VSLOT(60) AUDIO_MANAGER_VSLOT(61)
	AUDIO_MANAGER_VSLOT(62) AUDIO_MANAGER_VSLOT(63)
	AUDIO_MANAGER_VSLOT(64) AUDIO_MANAGER_VSLOT(65)
	AUDIO_MANAGER_VSLOT(66) AUDIO_MANAGER_VSLOT(67)
	AUDIO_MANAGER_VSLOT(68) AUDIO_MANAGER_VSLOT(69)
	AUDIO_MANAGER_VSLOT(70) AUDIO_MANAGER_VSLOT(71)
	AUDIO_MANAGER_VSLOT(72) AUDIO_MANAGER_VSLOT(73)
	AUDIO_MANAGER_VSLOT(74) AUDIO_MANAGER_VSLOT(75)
	AUDIO_MANAGER_VSLOT(76) AUDIO_MANAGER_VSLOT(77)
#undef AUDIO_MANAGER_VSLOT
	virtual bool isMusicAlreadyLoaded() const;

	void init();

	char m_pad04[0x08];
	AudioSettings006B8220 *m_audioSettings;         // +0x0c
	char m_pad10[0x618];
	unsigned short m_speakerClamp;                  // +0x628
	char m_pad62a[0x05];
	unsigned char m_musicPlayingFromCD;             // +0x62f
	char m_pad630[0x4d0];
	BfmeB1012 *m_bfmeB1012;                         // +0xb00
	char m_padB04[0x40];
	Rva00699D60AudioOwner *m_ownerArray;    // +0xb44
	int m_ownerArrayCount;                          // +0xb48
};

// _AIL_set_file_callbacks@16, reached through the mss32.dll IAT slot at
// 0x0135966C. The four pointers are the retail callback bodies at
// 0x00A96370, 0x00A963A0, 0x00A963B0 and 0x00A963D0.
extern "C" __declspec(dllimport) void __stdcall AIL_set_file_callbacks(
	void *open, void *close, void *read, void *write);

// Retail callback bodies use stdcall: open ret 8 and read/seek ret 12.
// Match their existing providers; no callback implementation is duplicated here.
class File;
struct Rva006963B0Receiver;
struct Rva006963D0Receiver;
extern int __stdcall rva00696370OpenFile(const char *path, File **out);
// ?dup_006963a0@@YAXXZ
extern void __cdecl dup_006963a0();
// ?rva006963B0ForwardSlot5@@YGHPAURva006963B0Receiver@@HH@Z
extern int __stdcall rva006963B0ForwardSlot5(Rva006963B0Receiver *receiver, int first, int second);
// ?rva006963D0ForwardSlot3@@YGHPAURva006963D0Receiver@@HH@Z
extern int __stdcall rva006963D0ForwardSlot3(Rva006963D0Receiver *receiver, int first, int second);

void *operator new[](unsigned int);
// Retail unwind state 2 releases the owner array through operator delete[].
void operator delete[](void *) throw();

void AudioManager::init()
{
	INI ini;
	ini.load( AsciiString( "Data\\INI\\AudioSettings.ini" ), INI_LOAD_OVERWRITE, NULL );

	ini.load( AsciiString( "Data\\INI\\Default\\Music.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\Default\\Speech.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\Default\\SoundEffects.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\Default\\Voice.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\Default\\AmbientStream.ini" ), INI_LOAD_OVERWRITE, NULL );

	ini.load( AsciiString( "Data\\INI\\Music.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\SoundEffects.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\Speech.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\Voice.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\AmbientStream.ini" ), INI_LOAD_OVERWRITE, NULL );

	ini.load( AsciiString( "Data\\INI\\MiscAudio.ini" ), INI_LOAD_OVERWRITE, NULL );

	// Determine if one of the music tracks exists. Since they are now BIGd, one
	// implies all. If they do not exist, load them from the CD.
	if (!isMusicAlreadyLoaded())
	{
		m_musicPlayingFromCD = 1;
		while (TRUE)
		{
			reinterpret_cast<FileSystem *>(this)->loadMusicFilesFromCD();
			if (isMusicAlreadyLoaded())
			{
				break;
			}
			// We loop infinitely on the splash screen if we do not allow
			// breaking out of this loop.
			else
			{
				if (OSDisplayWarningBox("GUI:InsertCDPrompt", "GUI:InsertCDMessage",
						OSDBT_OK | OSDBT_CANCEL,
						OSDOF_SYSTEMMODAL | OSDOF_EXCLAMATIONICON) == OSDBT_CANCEL)
				{
					break;
				}
			}
		}
	}

	// Set the Miles channel volumes from the user's preferred settings, not the
	// defaults, then publish each one to the client. Retail re-reads the settings
	// pointer from this+0x0c for every channel rather than caching it, so the
	// accessor is called once per channel here.
	// Each channel's value is computed into a named local before it is published.
	// The local is what keeps the choice on the x87 stack: MSVC selects the branch
	// with `fld` from the settings member or from the fallback constant, then
	// `fstp`s the local, and the local's dword copy is what reaches the global.
	// Assigning the ternary straight into the global lets MSVC copy a dword
	// through a general-purpose register instead and the whole block changes shape.
	float volume = getAudioSettings() ? getAudioSettings()->m_preferredSpeechVolume : g_real3f0ccccd;
	g_milesVolume012BA134 = volume;
	j_00047f3c(2);

	volume = getAudioSettings() ? getAudioSettings()->m_preferredSoundVolume : g_real3f400000;
	g_milesVolume012BA12C = volume;
	j_00047f3c(0);

	volume = getAudioSettings() ? getAudioSettings()->m_preferredAmbientVolume : g_real3f0ccccd;
	g_milesVolume012BA13C = volume;
	j_00047f3c(4);

	volume = getAudioSettings() ? getAudioSettings()->m_preferred3DSoundVolume : g_real3f0ccccd;
	g_milesVolume012BA130 = volume;
	j_00047f3c(1);

	volume = getAudioSettings() ? getAudioSettings()->m_preferredMusicVolume : g_real3f0ccccd;
	g_milesVolume012BA138 = volume;
	j_00047f3c(3);

	// The count is read once into a local: MSVC promotes the value to EDI,
	// publishes it to this+0xb48, and then derives the byte size from that same
	// register. Reading the member directly (not via the accessor) gives the
	// settings load its rotated ECX register.
	int ownerCount = m_audioSettings->m_ownerCount;
	m_ownerArrayCount = ownerCount;
	m_ownerArray = new Rva00699D60AudioOwner[ownerCount];

	reinterpret_cast<MilesAudioManager *>(this)->openDevice();

	m_bfmeB1012->bfmeGo1012B(m_audioSettings->m_field44);

	AIL_set_file_callbacks(rva00696370OpenFile, dup_006963a0,
		rva006963B0ForwardSlot5, rva006963D0ForwardSlot3);

	// Retail clamps the speaker count to the LOD table (stride 8 rows at +0x170
	// keyed by the LOD index at +0x16cc), and every failure path - no LOD
	// manager or an out-of-range index - stores the word 2. The failure store is
	// the same instruction as the >2 clamp, so both land on one store.
	if (TheGameLODManager)
	{
		int lodIndex = TheGameLODManager->m_lodIndex;
		if (lodIndex >= 0 && lodIndex < 2)
		{
			m_speakerClamp = TheGameLODManager->m_speakerTable[lodIndex][0];
			if (m_speakerClamp > 2)
			{
				m_speakerClamp = 2;
			}
		}
		else
		{
			m_speakerClamp = 2;
		}
	}
	else
	{
		m_speakerClamp = 2;
	}
}