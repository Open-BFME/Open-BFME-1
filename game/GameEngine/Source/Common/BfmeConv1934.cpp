// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

// The 0x70-byte stack temporary this body builds is an AudioEventRTS, not a
// TU-local request record: retail's own `sub esp,0x70` at 0x0060F4B0 is the size
// of the layout below (AsciiString/CountedPtr members up to m_flag40 at +0x40
// and the m_41 pad running to +0x6C, then m_tail), and the two calls the ILT
// thunks 0x0001EC13 and 0x00026F35 forward to are real, matched bodies:
//
//   0x0001EC13 -> 0x000B2D90 ??0AudioEventRTS@@QAE@ABVAsciiString@@H@Z
//                  (game/.../Audio/AudioEventRTSThinExtraCtor.cpp)
//   0x00026F35 -> 0x000B31F0 ??1AudioEventRTS@@QAE@XZ
//                  (game/.../Audio/AudioEventRTSCopyAndLifetime.cpp)
//
// so the temporary is spelled with the real class name here and its members
// keep the matched layout. This TU declares only the ctor and the scalar
// destructor, both already defined by those two files; it adds no body.
//
// The destructor is declared non-virtual on purpose. The matched body at
// 0x000B31F0 is the ledger's `??1AudioEventRTS@@QAE@XZ` row (162 bytes, reached
// through the scalar ILT 0x00026F35); the virtual `??1AudioEventRTS@@UAE@XZ`
// spelling names a different 77-byte body at 0x000CFA40. Retail calls the
// scalar one directly, so a non-virtual declaration is what reproduces it.
// The trailing pad restores the 0x70 size the non-virtual declaration drops.

#include "ascii_string.h"

// One-word opaque ABI view, as in AudioEventRTSThinExtraCtor.cpp.
class CountedPtr
{
public:
	CountedPtr() : m_ptr(0) {}
	~CountedPtr();

	void *m_ptr;
};

struct Coord3D
{
	unsigned int x, y, z;
};

class AudioEventRTS
{
public:
	AudioEventRTS(const AsciiString &eventName, int extra);
	~AudioEventRTS();

private:
	AsciiString m_filenameToLoad;
	CountedPtr m_eventInfo;
	unsigned int m_playingHandle;
	unsigned int m_killThisHandle;
	AsciiString m_eventName;
	AsciiString m_attackName;
	AsciiString m_decayName;
	char m_20[8];
	unsigned int m_timeOfDay;
	unsigned int m_objectID;
	int m_ownerType;
	Coord3D m_position;
	unsigned char m_flag40;
	char m_41[0x6C - 0x41];
	AsciiString m_tail;
	unsigned char m_scalarDtorPad[4];
};

// AsciiString's m_data word is private and retail only tests that word
// (`cmp dword ptr [ecx+0xf8],0`) before building the request, so the
// emptiness test is made through this TU-local one-word view.
struct AsciiStringDataWord
{
	void *m_data;
};

// Retail's global at 0x012ED668 is `AudioManager *TheAudio`, defined once in
// Common/Audio/GameAudio.cpp. Only the name has to be canonical for the link;
// this TU keeps its own TU-local view of the pointee and casts at the use.
class AudioManager;

extern AudioManager *TheAudio;

class BfmeHostDA
{
public:
	void bfmeStopDA();

	unsigned char m_bfmeHeadDA[0xf8];
	AsciiString m_bfmeSlotDA;
	unsigned char m_bfmeMidDA[0x18c];
	unsigned char m_bfmeADA;
	unsigned char m_bfmePadDA[0xb];
	unsigned char m_bfmeBDA;
};

class Rva005A00B0AudioClient
{
public:
	virtual void bfmeSlot00DA();
	virtual void bfmeSlot01DA();
	virtual void bfmeSlot02DA();
	virtual void bfmeSlot03DA();
	virtual void bfmeSlot04DA();
	virtual void bfmeSlot05DA();
	virtual void bfmeSlot06DA();
	virtual void bfmeSlot07DA();
	virtual void bfmeSlot08DA();
	virtual void bfmeSlot09DA();
	virtual void bfmeSlot10DA();
	virtual void bfmeSlot11DA();
	virtual void bfmeSlot12DA();
	virtual void bfmeSlot13DA();
	virtual void bfmeSlot14DA();
	virtual void bfmeSlot15DA();
	virtual void bfmeSlot16DA();
	virtual void bfmeSendDA(AudioEventRTS *req);
};

void BfmeHostDA::bfmeStopDA()
{
	m_bfmeADA = 1;
	m_bfmeBDA = 0;

	if (TheAudio != 0)
	{
		AsciiString *slot = &m_bfmeSlotDA;

		if (reinterpret_cast<AsciiStringDataWord *>(slot)->m_data != 0)
		{
			AudioEventRTS req(*slot, 1);

			((Rva005A00B0AudioClient *)TheAudio)->bfmeSendDA(&req);
		}
	}
}