// ?parseStreamedSoundDefinition@INI@@SAXPAV1@@Z
// partial score=0.88 date=2026-09-10
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/iniexception

// Retail 0x000B17C0 is INI::parseStreamedSoundDefinition from
// Common/Audio/AudioEventRTS.cpp.  The parser creates an AudioEventInfoRef,
// overlays the DefaultStreamedSound template, then applies the 21-field table
// at 0x010813F8.  These local declarations preserve the BFME ABI without
// importing the incompatible Zero Hour audio class declarations.

#include <string.h>

#include "Common/INIException.h"

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *value);

struct FieldParse;

template <typename T> struct StringInlineData
{
	int m_refCount;
	int m_length;
	T m_text[1];
};

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase() : m_data(0) {}
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

public:
	void set(const T *text, int length);
	void set(const StringBase<T> &other);

private:
	StringInlineData<T> *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString() : StringBase<char>() {}
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
	void set(const char *text)
	{
		StringBase<char>::set(text,
			text ? (int)strlen(text) : 0);
	}

	AsciiString &operator=(const AsciiString &other)
	{
		StringBase<char>::set(other);
		return *this;
	}
};

class BfmeA1202
{
public:
	virtual ~BfmeA1202();

	void Release_Ref(void)
	{
		if (InterlockedDecrement(&m_refCount) <= 0)
			delete this;
	}

	long m_refCount;
	AsciiString m_audioName;
	AsciiString m_filename;
	int m_word10;
	int m_word14;
	int m_word18;
	int m_word1c;
	int m_word20;
	int m_word24;
	int m_word28;
	int m_word2c;
	int m_word30;
	int m_word34;
	int m_type;
	int m_control;
	unsigned char m_pad40[0x44];
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

	BfmeA1202 *m_info;
};

#pragma comment(linker, "/alternatename:??4AudioEventInfoRef@@QAEAAV0@ABV0@@Z=??4Rva00087750Ref@@QAEAAV0@ABV0@@Z")

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
	static void parseStreamedSoundDefinition(INI *ini);

	const char *getNextToken(const char *separators = 0);
	void initFromINI(void *what, const FieldParse *parseTable);

	int getLoadType(void) const { return m_loadType; }

private:
	int m_pad00;
	int m_pad04;
	int m_loadType;
};

void INI::parseStreamedSoundDefinition(INI *ini)
{
	if (ini->getLoadType() == 2)
		throw INIException(3,
			(const char *)0x01081B68);

	AsciiString name;
	{
	AudioEventInfoRef track;
	const char *token = ini->getNextToken();
	name.set(token);

		track = TheAudio->newAudioEventInfo(name);
		BfmeA1202 *const audioInfo = track.m_info;
		if (audioInfo != 0)
		{
			AudioEventInfoRef defaultInfo =
				TheAudio->findAudioEventInfo(AsciiString("DefaultStreamedSound"));
			if (defaultInfo.m_info != 0)
			{
				*audioInfo = *defaultInfo.m_info;
				audioInfo->m_type &= 0xfffffbff;
			}
			audioInfo->m_audioName = name;
			audioInfo->m_soundType = 4;
			ini->initFromINI(audioInfo,
				(const FieldParse *)0x010813F8);
		}
	}
}
