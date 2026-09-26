// ?init@AudioManager@@
// partial score=0.32 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// ?init@AudioManager@@QAEXXZ
// The retail row is a nonvirtual definition reached through the AudioManager
// subsystem route.  This TU-local view preserves the proven vtable position of
// isMusicAlreadyLoaded and the settings pointer used by the body without
// changing the shared BFME headers.

#include "Common/AsciiString.h"

class Xfer;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2
};

class INI
{
public:
	INI();
	~INI();
	void load(AsciiString filename, INILoadType loadType, Xfer *xfer);

private:
	char m_storage[0x848];
};

struct AudioSettings
{
	char m_pad00[0x94];
	float m_preferredSoundVolume;
	float m_preferred3DSoundVolume;
	float m_preferredSpeechVolume;
	float m_preferredMusicVolume;
	float m_padA4;
};

class MusicManager
{
public:
	MusicManager();
};

class SoundManager
{
public:
	SoundManager();
};

class FileSystem
{
public:
	void loadMusicFilesFromCD();
};

extern FileSystem *TheFileSystem;

enum OSDisplayButtonType
{
	OSDBT_OK = 0x00000001,
	OSDBT_CANCEL = 0x00000002
};

enum
{
	OSDOF_SYSTEMMODAL = 0x00000001,
	OSDOF_EXCLAMATIONICON = 0x00000008
};

OSDisplayButtonType OSDisplayWarningBox(AsciiString prompt, AsciiString message,
	unsigned int buttonFlags, unsigned int otherFlags);

class AudioManager
{
public:
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

	char m_pad04[8];
	AudioSettings *m_audioSettings;
	MusicManager *m_music;
	SoundManager *m_sound;
	char m_pad1C[0x613];
	unsigned char m_musicPlayingFromCD;
	float m_systemMusicVolume;
	float m_systemSoundVolume;
	float m_systemSound3DVolume;
	float m_systemSpeechVolume;
	float m_scriptMusicVolume;
	float m_scriptSoundVolume;
	float m_scriptSound3DVolume;
	float m_scriptSpeechVolume;
	float m_musicVolume;
	float m_soundVolume;
	float m_sound3DVolume;
	float m_speechVolume;
};

void AudioManager::init()
{
	INI ini;
	ini.load( AsciiString( "Data\\INI\\AudioSettings.ini" ), INI_LOAD_OVERWRITE, NULL);

	ini.load( AsciiString( "Data\\INI\\Default\\Music.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\Music.ini" ), INI_LOAD_OVERWRITE, NULL );

	ini.load( AsciiString( "Data\\INI\\Default\\SoundEffects.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\SoundEffects.ini" ), INI_LOAD_OVERWRITE, NULL );

	ini.load( AsciiString( "Data\\INI\\Default\\Speech.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\Speech.ini" ), INI_LOAD_OVERWRITE, NULL );

	ini.load( AsciiString( "Data\\INI\\Default\\Voice.ini" ), INI_LOAD_OVERWRITE, NULL );
	ini.load( AsciiString( "Data\\INI\\Voice.ini" ), INI_LOAD_OVERWRITE, NULL );

	// MiscAudio is loaded last so its AudioEventRTS definitions are available.
	ini.load( AsciiString( "Data\\INI\\MiscAudio.ini" ), INI_LOAD_OVERWRITE, NULL);

	if (!isMusicAlreadyLoaded())
	{
		m_musicPlayingFromCD = TRUE;
		while (TRUE)
		{
			TheFileSystem->loadMusicFilesFromCD();
			if (isMusicAlreadyLoaded())
			{
				break;
			}
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

	m_music = new MusicManager;
	m_sound = new SoundManager;

	m_systemMusicVolume = m_audioSettings ? m_audioSettings->m_preferredMusicVolume : 0.55f;
	m_systemSoundVolume = m_audioSettings ? m_audioSettings->m_preferredSoundVolume : 0.75f;
	m_systemSound3DVolume = m_audioSettings ? m_audioSettings->m_preferred3DSoundVolume : 0.75f;
	m_systemSpeechVolume = m_audioSettings ? m_audioSettings->m_preferredSpeechVolume : 0.55f;

	m_scriptMusicVolume = 1.0f;
	m_scriptSoundVolume = 1.0f;
	m_scriptSound3DVolume = 1.0f;
	m_scriptSpeechVolume = 1.0f;

	m_musicVolume = m_systemMusicVolume;
	m_soundVolume = m_systemSoundVolume;
	m_sound3DVolume = m_systemSound3DVolume;
	m_speechVolume = m_systemSpeechVolume;
}
