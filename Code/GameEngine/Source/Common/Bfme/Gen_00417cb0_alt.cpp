// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Gen_00417cb0::alt, retail 0x00411BE0, 55 bytes. The body carried
// only a machine byte-dump row; the symbols.csv pin names it for the caller it
// was found from and does not assert an identity.
//
// Two optional slots at +0x144 and +0x148, each holding a handle at +0x10, are
// handed to slot 19 of TheAudio in turn. The global is loaded once per call
// rather than kept, and it is never tested -- only the two slots are.

typedef unsigned int UnsignedInt;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/GameAudio.h
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

extern AudioManager *TheAudio;				///< retail [0x012ED668]

class BfmeAudioSlot
{
public:
	unsigned char m_bfmeHead[0x10];
	UnsignedInt m_bfmeHandle;				// +0x10
};

class Gen_00417cb0
{
public:
	void alt(void);

private:
	unsigned char m_bfmeHead[0x144];
	BfmeAudioSlot *m_bfmeFirst;				// +0x144
	BfmeAudioSlot *m_bfmeSecond;				// +0x148
};

// ?alt@Gen_00417cb0@@QAEXXZ
void Gen_00417cb0::alt(void)
{
	if (m_bfmeFirst)
		TheAudio->bfmeStopAudioEvent(m_bfmeFirst->m_bfmeHandle);

	if (m_bfmeSecond)
		TheAudio->bfmeStopAudioEvent(m_bfmeSecond->m_bfmeHandle);
}
