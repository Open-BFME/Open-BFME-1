// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/iniexception /ICode/Libraries/Source/WWVegas/WWLib
// BFME audio parsers. INI registry entries and the exception/default literals
// identify the individual event categories; MusicTrack is at RVA 0x000B1B70.
// AudioManager slots +0x110/+0x118 are the matched factories returning
// AudioEventInfoRef; the common field table is VA 0x010813F8.
#include <string.h>

#include "Common/INIException.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

struct FieldParse;

#include "ascii_string.h"
inline AsciiString::~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
template <> inline void StringBase<char>::set(const char *text)
{ set(text, text ? (int)strlen(text) : 0); }

void j_0003c6d7();

class AudioInfoViewRva000B1B70
{
public:
	virtual ~AudioInfoViewRva000B1B70();
    // ILT 0x0003C6D7 -> matched AudioEventInfo::operator= at 0x000B0F00.
    AudioInfoViewRva000B1B70 &copyFrom(const AudioInfoViewRva000B1B70 &other)
    {
        typedef AudioInfoViewRva000B1B70 &(AudioInfoViewRva000B1B70::*Assignment)(const AudioInfoViewRva000B1B70 &);
        union { void (*raw)(); Assignment member; } target;
        target.raw = j_0003c6d7;
        return (this->*target.member)(other);
    }

	void Release_Ref(void)
	{
		long count = InterlockedDecrement(&m_refCount);
		if (count <= 0)
			delete this;
	}

	// Matched parseDelay at RVA 0x000AFF40 writes the range at +0x28/+0x2C.
	int getDelayMax() const { return m_delayMax; }
	long m_refCount;
	AsciiString m_audioName;
	AsciiString m_filename;
	int m_word10;
	int m_word14;
	int m_word18;
	int m_word1c;
	int m_word20;
	int m_word24;
	int m_delayMin;
	int m_delayMax;
	int m_word30;
	int m_word34;
	int m_type;
	int m_control;
	unsigned char m_pad40[0x10];
	// Attack/Decay INI fields at +0x50/+0x60 contain vector begin/end pointers.
	struct SoundList { void *begin; void *end; unsigned char rest[8]; };
	SoundList m_attackSounds;
	SoundList m_decaySounds;
	unsigned char m_pad70[0x14];
	int m_soundType;
};

class AudioEventInfoRef
{
public:
	AudioEventInfoRef() : m_info(0) {}
	~AudioEventInfoRef(void)
	{
		if (m_info)
			m_info->Release_Ref();
	}

	AudioEventInfoRef &operator=(const AudioEventInfoRef &other);

	AudioInfoViewRva000B1B70 *m_info;
};


extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *value);
__declspec(noinline) AudioEventInfoRef &AudioEventInfoRef::operator=(const AudioEventInfoRef &other)
{
    if (this != &other) {
        if (other.m_info) InterlockedIncrement(&other.m_info->m_refCount);
        if (m_info) m_info->Release_Ref();
        m_info=other.m_info;
    }
    return *this;
}

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
	virtual AudioEventInfoRef newAudioEventInfo(const AsciiString &eventName);
	virtual void slot69();
	virtual AudioEventInfoRef findAudioEventInfo(const AsciiString &eventName) const;
};

extern AudioManager *TheAudio;

class INI
{
public:
	static void parseAudioEventDefinition(INI *ini);
	static void parseMusicTrackDefinition(INI *ini);
	static void parseDialogDefinition(INI *ini);
	static void parseStreamedSoundDefinition(INI *ini);
	static void parseAmbientStreamDefinition(INI *ini);

	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *what, const FieldParse *parseTable);

	int getLoadType(void) const { return m_loadType; }

private:
	int m_pad00;
	int m_pad04;
	int m_loadType;
};

void INI::parseMusicTrackDefinition(INI *ini)
{
	if (ini->getLoadType() == 2)
		throw INIException(3, "You cannot define or override a MusicTrack in map.ini");

	AsciiString name;
	AudioEventInfoRef track;
	const char *token = ini->getNextToken();
	name.set(token);
	track = TheAudio->newAudioEventInfo(name);

	AudioInfoViewRva000B1B70 *const audioInfo = track.m_info;
	if (!audioInfo)
		return;

	AudioEventInfoRef defaultInfo =
		TheAudio->findAudioEventInfo(AsciiString("DefaultMusicTrack"));
	if (defaultInfo.m_info != 0)
	{
		audioInfo->copyFrom(*defaultInfo.m_info);
		audioInfo->m_type &= 0xfffffbff;
	}
	audioInfo->m_audioName = name;
	audioInfo->m_soundType = 0;
	ini->initFromINI(audioInfo, (const FieldParse *)0x010813F8);
}

void INI::parseDialogDefinition(INI *ini)
{
	if (ini->getLoadType() == 2)
		throw INIException(3, "You cannot define or override a DialogEvent in map.ini");

	AsciiString name;
	AudioEventInfoRef track;
	const char *token = ini->getNextToken();
	name.set(token);
	track = TheAudio->newAudioEventInfo(name);

	AudioInfoViewRva000B1B70 *const audioInfo = track.m_info;
	if (!audioInfo)
		return;

	AudioEventInfoRef defaultInfo =
		TheAudio->findAudioEventInfo(AsciiString("DefaultDialog"));
	if (defaultInfo.m_info != 0)
	{
		audioInfo->copyFrom(*defaultInfo.m_info);
		audioInfo->m_type &= 0xfffffbff;
	}
	audioInfo->m_audioName = name;
	audioInfo->m_soundType = 1;
	ini->initFromINI(audioInfo, (const FieldParse *)0x010813F8);
}

void INI::parseStreamedSoundDefinition(INI *ini)
{
	if (ini->getLoadType() == 2)
		throw INIException(3, "You cannot define or override a StreamedSound in map.ini");

	AsciiString name;
	AudioEventInfoRef track;
	const char *token = ini->getNextToken();
	name.set(token);
	track = TheAudio->newAudioEventInfo(name);

	AudioInfoViewRva000B1B70 *const audioInfo = track.m_info;
	if (!audioInfo)
		return;

	AudioEventInfoRef defaultInfo =
		TheAudio->findAudioEventInfo(AsciiString("DefaultStreamedSound"));
	if (defaultInfo.m_info != 0)
	{
		audioInfo->copyFrom(*defaultInfo.m_info);
		audioInfo->m_type &= 0xfffffbff;
	}
	audioInfo->m_audioName = name;
	audioInfo->m_soundType = 4;
	ini->initFromINI(audioInfo, (const FieldParse *)0x010813F8);
}

void INI::parseAmbientStreamDefinition(INI *ini)
{
	if (ini->getLoadType() == 2)
		throw INIException(3, "You cannot define or override an AmbientStream in map.ini");

	AsciiString name;
	AudioEventInfoRef track;
	const char *token = ini->getNextToken();
	name.set(token);
	track = TheAudio->newAudioEventInfo(name);

	AudioInfoViewRva000B1B70 *const audioInfo = track.m_info;
	if (!audioInfo)
		return;

	AudioEventInfoRef defaultInfo =
		TheAudio->findAudioEventInfo(AsciiString("DefaultAmbientStream"));
	if (defaultInfo.m_info != 0)
	{
		audioInfo->copyFrom(*defaultInfo.m_info);
		audioInfo->m_type &= 0xfffffbff;
	}
	audioInfo->m_audioName = name;
	audioInfo->m_soundType = 3;
	ini->initFromINI(audioInfo, (const FieldParse *)0x010813F8);
}

// Retail diagnostics use the BFME debug vtable: start +0x60; stream +0x6C;
// string insertion +0x38; finalization +0x4C. StringBase insertion is already
// matched at RVA 0x0005F590 and reached through ILT 0x00016F86.
class BfmeAwakenLog
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual BfmeAwakenLog *slot38(const char *text);
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C(int report);
};

class BfmeAwakenDebug
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual BfmeAwakenLog *slot6C(int first, int second);
};

extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern void _bfme_debugRecordCallsite(int kind);
extern bool _bfme_debugReportingEnabled(void);


Debug &operator<<(Debug &debug, const StringBase<char> &str);
void INI::parseAudioEventDefinition(INI *ini)
{
	if (ini->getLoadType() == 2)
		throw INIException(3, "You cannot define or override an AudioEvent in map.ini");

	AsciiString name;
	AudioEventInfoRef track;
	const char *token = ini->getNextToken();
	name.set(token);
	track = TheAudio->newAudioEventInfo(name);

	AudioInfoViewRva000B1B70 *const audioInfo = track.m_info;
	if (!audioInfo)
		return;

	AudioEventInfoRef defaultInfo =
		TheAudio->findAudioEventInfo(AsciiString("DefaultSoundEffect"));
	if (defaultInfo.m_info != 0)
	{
		audioInfo->copyFrom(*defaultInfo.m_info);
		audioInfo->m_type &= 0xfffffbff;
	}
	audioInfo->m_audioName = name;
	audioInfo->m_soundType = 2;
	ini->initFromINI(audioInfo, (const FieldParse *)0x010813F8);

	if (audioInfo->m_control & 4) {
		if (_bfme_debugReportingEnabled()) {
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			TheBfmeAwakenDebug->slot6C(0, 0)->slot38("Control flag 'RANDOMSTART' is not valid for AudioEvents. Streaming sound types only, please.")->slot4C(2);
		}
		audioInfo->m_control &= ~4;
	}
	if (!(audioInfo->m_type & 2) && (float)audioInfo->getDelayMax() == 0.0f &&
		((audioInfo->m_control & 1) || audioInfo->m_attackSounds.begin != audioInfo->m_attackSounds.end ||
		audioInfo->m_decaySounds.begin != audioInfo->m_decaySounds.end)) {
		if (_bfme_debugReportingEnabled()) {
			_bfme_debugRecordCallsite(1);
			TheBfmeAwakenDebug->slot60();
			((BfmeAwakenLog *)&operator<<(*(Debug *)(TheBfmeAwakenDebug->slot6C(0, 0)->slot38(
				"Warning: tightly-coupled 2D sounds (sounds with 0 delay and either a looping flag oran attack or decay list) are not well supported.\nConsider using a StreamedSound, or a single .wav file\nSound: ")),
				(const StringBase<char> &)name))->slot4C(2);
		}
	}
}
