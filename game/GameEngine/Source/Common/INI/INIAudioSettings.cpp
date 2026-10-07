// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/iniexception
// BFME INI::parseAudioSettingsDefinition (retail 0x000B4B70) with its two static microphone helpers,
// whose private EDI/ESI conventions VC7.1 reproduces only when they share this TU (0x000B49F0, 0x000B4B20).
#include <float.h>
#include "Common/INIException.h"

typedef float Real;
typedef int Int;
class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	Int offset;
};

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
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseColorInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	void initFromINI(void *what, const FieldParse *parseTable);
	Int getLoadType() const { return m_loadType; }
private:
	Int m_pad00;
	Int m_pad04;
	Int m_loadType;
};

// Retail .rdata VA 0x01081D60 (848 B): 52 AudioSettings entries plus a zero terminator.
extern const FieldParse g_01081D60[] =
{
	{ "AudioRoot", INI::parseAsciiString, 0, 0x0 },
	{ "SoundsFolder", INI::parseAsciiString, 0, 0x4 },
	{ "MusicFolder", INI::parseAsciiString, 0, 0x8 },
	{ "StreamingFolder", INI::parseAsciiString, 0, 0xc },
	{ "AmbientStreamFolder", INI::parseAsciiString, 0, 0x10 },
	{ "SoundsExtension", INI::parseAsciiString, 0, 0x14 },
	{ "UseDigital", INI::parseBool, 0, 0x18 },
	{ "UseMidi", INI::parseBool, 0, 0x19 },
	{ "OutputRate", INI::parseInt, 0, 0x1c },
	{ "OutputBits", INI::parseInt, 0, 0x20 },
	{ "OutputChannels", INI::parseInt, 0, 0x24 },
	{ "SampleCount2D", INI::parseInt, 0, 0x28 },
	{ "SampleCount3D", INI::parseInt, 0, 0x2c },
	{ "StreamCount", INI::parseInt, 0, 0x30 },
	{ "MixaheadLatency", INI::parseUnsignedInt, 0, 0x48 },
	{ "MixaheadLatencyDuringMovies", INI::parseUnsignedInt, 0, 0x4c },
	{ "3DBufferLengthMS", INI::parseUnsignedInt, 0, 0x50 },
	{ "3DBufferCallbackCallsPerBufferLength", INI::parseUnsignedInt, 0, 0x54 },
	{ "AutomaticSubtitleDurationMS", INI::parseInt, 0, 0x58 },
	{ "AutomaticSubtitleWindowWidth", INI::parseInt, 0, 0x5c },
	{ "AutomaticSubtitleLines", INI::parseInt, 0, 0x60 },
	{ "AutomaticSubtitleWindowColor", INI::parseColorInt, 0, 0x64 },
	{ "AutomaticSubtitleTextColor", INI::parseColorInt, 0, 0x68 },
	{ "ForceResetTimeSeconds", INI::parseInt, 0, 0x6c },
	{ "EmergencyResetTimeSeconds", INI::parseInt, 0, 0x70 },
	{ "MusicScriptLibraryName", INI::parseAsciiString, 0, 0x74 },
	{ "MinSampleVolume", INI::parsePercentToReal, 0, 0x7c },
	{ "PositionDeltaForReverbRecheck", INI::parseReal, 0, 0x78 },
	{ "GlobalMinRange", INI::parseInt, 0, 0x34 },
	{ "GlobalMaxRange", INI::parseInt, 0, 0x38 },
	{ "TimeToFadeAudio", INI::parseInt, 0, 0x3c },
	{ "AmbientStreamHysteresisVolume", INI::parseInt, 0, 0x40 },
	{ "AudioFootprintInBytes", INI::parseUnsignedInt, 0, 0x44 },
	{ "DefaultSoundVolume", INI::parsePercentToReal, 0, 0x80 },
	{ "DefaultVoiceVolume", INI::parsePercentToReal, 0, 0x84 },
	{ "DefaultMusicVolume", INI::parsePercentToReal, 0, 0x88 },
	{ "DefaultMovieVolume", INI::parsePercentToReal, 0, 0x90 },
	{ "DefaultAmbientVolume", INI::parsePercentToReal, 0, 0x8c },
	{ "MicrophonePreferredFractionCameraToGround", INI::parsePercentToReal, 0, 0xa8 },
	{ "MicrophonePullTowardsTerrainLookAtPointPercent", INI::parsePercentToReal, 0, 0xc0 },
	{ "MicrophoneMinDistanceToCamera", INI::parseReal, 0, 0xb0 },
	{ "MicrophoneMaxDistanceToCamera", INI::parseReal, 0, 0xb8 },
	{ "ZoomMinDistance", INI::parseReal, 0, 0xc4 },
	{ "ZoomMaxDistance", INI::parseReal, 0, 0xcc },
	{ "ZoomSoundVolumePercentageAmount", INI::parsePercentToReal, 0, 0xd4 },
	{ "LivingWorldMicrophonePreferredFractionCameraToGround", INI::parsePercentToReal, 0, 0xd8 },
	{ "LivingWorldMicrophoneMinDistanceToCamera", INI::parseReal, 0, 0xe0 },
	{ "LivingWorldMicrophoneMaxDistanceToCamera", INI::parseReal, 0, 0xe8 },
	{ "LivingWorldZoomMinDistance", INI::parseReal, 0, 0xf4 },
	{ "LivingWorldZoomMaxDistance", INI::parseReal, 0, 0xfc },
	{ "LivingWorldMicrophonePullTowardsTerrainLookAtPointPercent", INI::parsePercentToReal, 0, 0xf0 },
	{ "LivingWorldZoomSoundVolumePercentageAmount", INI::parsePercentToReal, 0, 0x104 },
	{ 0, 0, 0, 0 }
};

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
