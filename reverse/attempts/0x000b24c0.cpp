// ?bfmeInitCommonFields@AudioEventRTS@@QAEXXZ
// partial score=0.85 date=2026-09-03
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
// Open-BFME5: AudioEventRTS shared field initializer, retail 0x000B24C0.
// Ctors at 0x000B2CC0/0x000B2D90/0x000B2E10 call this after zeroing string
// headers; ILT 0x0002E68B reaches it.

#include "StringInline.h"

struct Coord3D
{
	float x, y, z;
};

class AsciiStringWithEmpty : public AsciiString
{
public:
	static const AsciiString TheEmptyString;
};

class __declspec(novtable) AudioEventRTS
{
public:
	void bfmeInitCommonFields();

	virtual ~AudioEventRTS();

private:
	AsciiString m_at04;             // +0x04
	AsciiString m_filenameToLoad;   // +0x08
	unsigned int m_playingHandle;   // +0x0C
	unsigned int m_killThisHandle;  // +0x10
	AsciiString m_eventName;        // +0x14
	AsciiString m_attackName;       // +0x18
	AsciiString m_decayName;        // +0x1C
	float m_volume;                 // +0x20
	float m_volumeB;                // +0x24
	int m_playerIndex;              // +0x28
	char m_pad2C[4];
	int m_ownerType;                // +0x30
	Coord3D m_positionOfAudio;      // +0x34
	unsigned char m_shouldFade;     // +0x40
	unsigned char m_isLogicalAudio; // +0x41
	unsigned char m_uninterruptable;// +0x42
	unsigned char m_b43;
	unsigned char m_b44;
	unsigned char m_b45;
	unsigned char m_b46;
	unsigned char m_b47;
	unsigned char m_b48;
	unsigned char m_b49;
	char m_pad4A[2];
	float m_pitchShift;             // +0x4C
	float m_pitchShiftB;            // +0x50
	int m_allCount;                 // +0x54
	int m_playingAudioIndex;        // +0x58
	int m_loopCountRelated;         // +0x5C
	int m_zero60;                   // +0x60
	int m_loopCount;                // +0x64
	int m_negOne68;                 // +0x68
	AsciiString m_extraName;        // +0x6C
};

void AudioEventRTS::bfmeInitCommonFields()
{
	m_volume = -1.0f;
	m_volumeB = -1.0f;
	m_positionOfAudio.x = 0.0f;
	m_positionOfAudio.y = 0.0f;
	m_positionOfAudio.z = 0.0f;
	m_shouldFade = 0;
	m_ownerType = 4;
	m_playerIndex = 0;
	m_isLogicalAudio = 0;
	m_uninterruptable = 0;
	m_at04 = AsciiStringWithEmpty::TheEmptyString;
	m_filenameToLoad = AsciiString();
	m_playingHandle = 0;
	m_killThisHandle = 0;
	m_pitchShift = 1.0f;
	m_pitchShiftB = 1.0f;
	m_playingAudioIndex = -1;
	m_loopCountRelated = -1;
	m_allCount = 0;
	m_b43 = 0;
	m_b44 = 0;
	m_b45 = 0;
	m_b46 = 1;
	m_b47 = 0;
	m_b48 = 0;
	m_b49 = 0;
	m_zero60 = 0;
	m_attackName = AsciiString();
	m_decayName = AsciiString();
	m_loopCount = 1;
	m_extraName = AsciiString();
	m_negOne68 = -1;
}
