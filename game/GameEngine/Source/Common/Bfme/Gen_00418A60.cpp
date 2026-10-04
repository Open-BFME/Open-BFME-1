// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Gen_00417cb0::cleanup, retail 0x00418A60, 122 bytes. The body
// carried only a machine byte-dump row (?d_00418a60); the owning class is the
// address-derived Gen_00417cb0 family: the two audio slots at +0x144/+0x148
// match alt at 0x00411BE0 slot for slot, and the tail call reaches 0x00417A70
// through ILT 0x000294B5 like setFlag at 0x00417CB0.
//
// Two optional slots at +0x144/+0x148, each holding a handle at +0x10, are
// handed to slot 19 of TheAudio in turn. The owned object at +0x10C is
// released through InterlockedDecrement; on the last reference its virtual
// destructor runs (arg 1) and the field is cleared. When the incoming flag
// is set the body tails into 0x00417A70 with a null argument.
//
// The outer guard tests the member and the local is loaded inside it: that
// is what keeps retail's second test before the destructor call. Reading the
// member once into a local lets MSVC fold the two tests into one.

typedef unsigned int UnsignedInt;

extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(
	long volatile *lpAddend);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
class AudioManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void bfmeStopAudioEvent(UnsignedInt handle);	// slot 19, vtable+0x4C
};

extern AudioManager *TheAudio;			///< retail [0x012ED668]

class BfmeAudioSlot
{
public:
	unsigned char m_bfmeHead[0x10];
	UnsignedInt m_bfmeHandle;				// +0x10
};

class BfmeOwnedRef
{
public:
	virtual ~BfmeOwnedRef();

	long m_bfmeRefCount;
};

class Gen_00417cb0
{
public:
	void cleanup(bool incoming);

private:
	unsigned char m_bfmeHead[0x10C];
	BfmeOwnedRef *m_bfmeOwned;			// +0x10C
	unsigned char m_bfmePad[0x34];
	BfmeAudioSlot *m_bfmeFirst;		// +0x144
	BfmeAudioSlot *m_bfmeSecond;		// +0x148
};

extern void j_000294b5();				// ILT 0x000294B5 to body 0x00417A70

// ?cleanup@Gen_00417cb0@@QAEX_N@Z
void Gen_00417cb0::cleanup(bool incoming)
{
	if (m_bfmeFirst)
		TheAudio->bfmeStopAudioEvent(m_bfmeFirst->m_bfmeHandle);

	if (m_bfmeSecond)
		TheAudio->bfmeStopAudioEvent(m_bfmeSecond->m_bfmeHandle);

	if (m_bfmeOwned)
	{
		BfmeOwnedRef *owned = m_bfmeOwned;
		if (InterlockedDecrement(&owned->m_bfmeRefCount) <= 0)
		{
			if (owned)
				delete owned;
		}
		m_bfmeOwned = 0;
	}

	if (incoming)
	{
		typedef void (Gen_00417cb0::*Tail)(void *);
		union { void (*fn)(); Tail call; } tail = { j_000294b5 };
		(this->*tail.call)(0);
	}
}
