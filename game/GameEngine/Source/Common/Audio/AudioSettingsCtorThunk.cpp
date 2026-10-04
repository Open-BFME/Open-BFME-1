// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// AudioSettings default constructor (0x000B4E00, 725 B).

// BFME's AudioSettings is 0x138 bytes (the matched MilesAudioManager
// constructor allocates that much); the Zero Hour header is 0xA0, so this TU
// keeps its own view. Member names follow the AudioSettings INI field table
// at 0x00C81D60 (targets/game/reverse/field_names.csv) and the matched
// INIAudioSettings.cpp view. Every default is a member initializer in
// declaration order; the three microphone blocks take the inline constructor
// of the matched 0x000B4A90 body, which fills each slot from the 0x7FA00000
// "unset" payload at VA 0x0112E8AC that INIAudioSettings.cpp tests for.
#include "ascii_string.h"

typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

union Rva0112E8ACValue
{
	unsigned int bits;
	float value;
};
extern const Rva0112E8ACValue g_Va0112E8AC;

struct MicrophoneSettingsRva000B4B70
{
	MicrophoneSettingsRva000B4B70()
	{
		m_preferredFractionCameraToGround = g_Va0112E8AC.value;
		m_preferredFractionCameraToGroundSquared = g_Va0112E8AC.value;
		m_minDistanceToCamera = g_Va0112E8AC.value;
		m_minDistanceToCameraSquared = g_Va0112E8AC.value;
		m_maxDistanceToCamera = g_Va0112E8AC.value;
		m_maxDistanceToCameraSquared = g_Va0112E8AC.value;
		m_pullTowardsTerrainLookAtPointPercent = g_Va0112E8AC.value;
		m_zoomMinDistance = g_Va0112E8AC.value;
		m_zoomMinDistanceSquared = g_Va0112E8AC.value;
		m_zoomMaxDistance = g_Va0112E8AC.value;
		m_zoomMaxDistanceSquared = g_Va0112E8AC.value;
		m_zoomSoundVolumePercentageAmount = g_Va0112E8AC.value;
	}

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
	AudioSettings();

	AsciiString m_audioRoot;
	AsciiString m_soundsFolder;
	AsciiString m_musicFolder;
	AsciiString m_streamingFolder;
	AsciiString m_ambientStreamFolder;
	AsciiString m_soundsExtension;
	Bool m_useDigital;
	Bool m_useMidi;
	Int m_outputRate;
	Int m_outputBits;
	Int m_outputChannels;
	Int m_sampleCount2D;
	Int m_sampleCount3D;
	Int m_streamCount;
	Int m_globalMinRange;
	Int m_globalMaxRange;
	Int m_fadeAudioFrames;
	Int m_ambientStreamHysteresisVolume;
	UnsignedInt m_maxCacheSize;
	Int m_mixaheadLatency;
	Int m_mixaheadLatencyDuringMovies;
	Int m_3DBufferLengthMS;
	Int m_3DBufferCallbackCallsPerBufferLength;
	Int m_automaticSubtitleDurationMS;
	Int m_automaticSubtitleWindowWidth;
	Int m_automaticSubtitleLines;
	UnsignedInt m_automaticSubtitleWindowColor;
	UnsignedInt m_automaticSubtitleTextColor;
	Int m_forceResetTimeSeconds;
	Int m_emergencyResetTimeSeconds;
	AsciiString m_musicScriptLibraryName;
	Real m_positionDeltaForReverbRecheck;
	Real m_minVolume;
	Real m_defaultSoundVolume;
	Real m_defaultVoiceVolume;
	Real m_defaultMusicVolume;
	Real m_defaultAmbientVolume;
	Real m_defaultMovieVolume;
	Real m_preferredSoundVolume;
	Real m_preferredSpeechVolume;
	Real m_preferredMusicVolume;
	Real m_preferredAmbientVolume;
	Real m_preferredMovieVolume;
	MicrophoneSettingsRva000B4B70 m_microphone[3];
};

AudioSettings::AudioSettings()
	: m_audioRoot("."),
	  m_soundsFolder("Sounds"),
	  m_musicFolder("Music"),
	  m_streamingFolder("Streams"),
	  m_ambientStreamFolder("AmbientStreams"),
	  m_soundsExtension("wav"),
	  m_useDigital(true),
	  m_useMidi(false),
	  m_outputRate(44100),
	  m_outputBits(16),
	  m_outputChannels(2),
	  m_sampleCount2D(4),
	  m_sampleCount3D(16),
	  m_streamCount(4),
	  m_globalMinRange(100),
	  m_globalMaxRange(5000),
	  m_fadeAudioFrames(1000),
	  m_ambientStreamHysteresisVolume(5),
	  m_maxCacheSize(0x400000),
	  m_mixaheadLatency(0x40),
	  m_mixaheadLatencyDuringMovies(0xe0),
	  m_3DBufferLengthMS(0x40),
	  m_3DBufferCallbackCallsPerBufferLength(6),
	  m_automaticSubtitleDurationMS(8000),
	  m_automaticSubtitleWindowWidth(320),
	  m_automaticSubtitleLines(8),
	  m_automaticSubtitleWindowColor(0x2fffbf40),
	  m_automaticSubtitleTextColor(0x7fff8040),
	  m_forceResetTimeSeconds(0),
	  m_emergencyResetTimeSeconds(0),
	  m_musicScriptLibraryName(AsciiString::TheEmptyString),
	  m_positionDeltaForReverbRecheck(10.0f),
	  m_minVolume(0.01f),
	  m_defaultSoundVolume(1.0f),
	  m_defaultVoiceVolume(1.0f),
	  m_defaultMusicVolume(1.0f),
	  m_defaultAmbientVolume(1.0f),
	  m_defaultMovieVolume(1.0f),
	  m_preferredSoundVolume(1.0f),
	  m_preferredSpeechVolume(1.0f),
	  m_preferredMusicVolume(1.0f),
	  m_preferredAmbientVolume(1.0f),
	  m_preferredMovieVolume(1.0f)
{
}
