// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/iniexception
// BFME INI::parseAudioSettingsDefinition (retail 0x000B4B70) with its two static microphone helpers,
// whose private EDI/ESI conventions VC7.1 reproduces only when they share this TU (0x000B49F0, 0x000B4B20).
#include <float.h>
#include "Common/INIException.h"

typedef float Real;
typedef int Int;
struct FieldParse;

// Field names follow the AudioSettings parse table at VA 0x01081D60; three 0x30-byte rows start at +0xA8.
struct MicrophoneSettingsRva000B4B70
{
	Real m_preferredFractionCameraToGround;
	Real m_preferredFractionCameraToGroundSquared;
	Real m_minDistanceToCamera;
	Real m_minDistanceToCameraSquared;
	Real m_maxDistanceToCamera;
	Real m_maxDistanceToCameraSquared;
	Real m_pullTowardsTerrainLookAtPointPercent;
	Real m_zoomMinDistance;
	Real m_zoomMinDistanceSquared;
	Real m_zoomMaxDistance;
	Real m_zoomMaxDistanceSquared;
	Real m_zoomSoundVolumePercentageAmount;
};

class AudioSettings
{
public:
	unsigned char m_pad000[0x94];
	// Slots follow the OptionPreferences getters stored into them (SFX, Voice, Music, Ambient, Movie keys).
	Real m_preferredSoundVolume;
	Real m_preferredSpeechVolume;
	Real m_preferredMusicVolume;
	Real m_preferredAmbientVolume;
	Real m_preferredMovieVolume;
	MicrophoneSettingsRva000B4B70 m_microphone[3];
};

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73();
	virtual AudioSettings *friend_getAudioSettings();
};

extern AudioManager *TheAudio;

class UserPreferences
{
public:
	virtual ~UserPreferences();
private:
	unsigned char m_unmodelled004[0x10];
};

class OptionPreferences : public UserPreferences
{
public:
	OptionPreferences();
	virtual ~OptionPreferences();
	Real getSoundVolume();
	Real getSpeechVolume();
	Real getMusicVolume();
	Real getMovieVolume();
	Real getAmbientVolume();
};

class INI
{
public:
	static void parseAudioSettingsDefinition(INI *ini);
	void initFromINI(void *what, const FieldParse *parseTable);
	Int getLoadType() const { return m_loadType; }
private:
	Int m_pad00;
	Int m_pad04;
	Int m_loadType;
};

extern const FieldParse g_01081D60[];

typedef Real MicrophoneSettingsRva000B4B70::*MicrophoneField;

static void fixUndefinedMicrophoneField(MicrophoneSettingsRva000B4B70 *mic, MicrophoneField field)
{
	if (_isnan(mic[0].*field))
		mic[0].*field = 0.0f;
	if (_isnan(mic[1].*field))
		mic[1].*field = mic[0].*field;
	if (_isnan(mic[2].*field))
		mic[2].*field = mic[0].*field;
}

static void squareMicrophoneField(MicrophoneSettingsRva000B4B70 *mic, MicrophoneField field, MicrophoneField squared)
{
	fixUndefinedMicrophoneField(mic, field);
	for (Int i = 0; i < 3; ++i)
	{
		Real value = mic[i].*field;
		mic[i].*squared = value * value;
	}
}

void INI::parseAudioSettingsDefinition(INI *ini)
{
	if (ini->getLoadType() == 2)
		throw INIException(3, "You cannot define or override the AudioSettings in map.ini");

	AudioSettings *settings = TheAudio->friend_getAudioSettings();
	ini->initFromINI(settings, g_01081D60);

	MicrophoneSettingsRva000B4B70 *mic = settings->m_microphone;
	squareMicrophoneField(mic, &MicrophoneSettingsRva000B4B70::m_preferredFractionCameraToGround, &MicrophoneSettingsRva000B4B70::m_preferredFractionCameraToGroundSquared);
	squareMicrophoneField(mic, &MicrophoneSettingsRva000B4B70::m_minDistanceToCamera, &MicrophoneSettingsRva000B4B70::m_minDistanceToCameraSquared);
	squareMicrophoneField(mic, &MicrophoneSettingsRva000B4B70::m_maxDistanceToCamera, &MicrophoneSettingsRva000B4B70::m_maxDistanceToCameraSquared);
	squareMicrophoneField(mic, &MicrophoneSettingsRva000B4B70::m_zoomMinDistance, &MicrophoneSettingsRva000B4B70::m_zoomMinDistanceSquared);
	squareMicrophoneField(mic, &MicrophoneSettingsRva000B4B70::m_zoomMaxDistance, &MicrophoneSettingsRva000B4B70::m_zoomMaxDistanceSquared);
	fixUndefinedMicrophoneField(mic, &MicrophoneSettingsRva000B4B70::m_zoomSoundVolumePercentageAmount);
	fixUndefinedMicrophoneField(mic, &MicrophoneSettingsRva000B4B70::m_pullTowardsTerrainLookAtPointPercent);

	OptionPreferences prefs;
	settings->m_preferredSoundVolume = prefs.getSoundVolume() * 0.01f;
	settings->m_preferredSpeechVolume = prefs.getSpeechVolume() * 0.01f;
	settings->m_preferredMusicVolume = prefs.getMusicVolume() * 0.01f;
	settings->m_preferredMovieVolume = prefs.getMovieVolume() * 0.01f;
	settings->m_preferredAmbientVolume = prefs.getAmbientVolume() * 0.01f;
}
