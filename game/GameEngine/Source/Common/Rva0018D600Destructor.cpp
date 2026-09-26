// cl: /DNDEBUG /MD /EHsc /O2
//
// Open-BFME5: retail 0x0018D600, 135 bytes. Dual-vtable destructor: offset 0
// is the BfmeBaseVUQ chain (own 0x0109BBF4 -> base 0x01073744 at the tail);
// offset 4 is a second, unrelated polymorphic base (0x0109BBDC) that this
// class does not override, so its vtable never changes and needs no tail
// restore. Body: query the AudioEventRTS-typed member at +0x20 through the
// already-pinned bfmeAsk1023 method: if true, hand the int at +0x2C to the
// global audio ClientSubsystem's vtable slot 0x4C. Then release a pointer at
// +0x14 (vtable slot 0, arg true) if present. Finally the AudioEventRTS
// member at +0x20 is destroyed automatically (retail 0x00026F35) before the
// bases unwind.

class BfmeBaseVUQ
{
public:
	virtual ~BfmeBaseVUQ() { }
};

class Rva0018D600Base2
{
public:
	virtual void bfmeSlot0(void) { }
};

class BfmeSub1023
{
public:
	char bfmeAsk1023(void);                                    ///< pinned 0x00035A5D
};

class AudioEventRTS
{
public:
	~AudioEventRTS();                                          ///< pinned 0x00026F35

private:
	unsigned int m_words[3];
};

class ClientSubsystem
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void slot40() = 0; virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void bfmeHandOff0018D600(unsigned int value) = 0;   ///< vtable +0x4C
};

extern ClientSubsystem *TheAudioClientUpdate;                  ///< retail 0x012ED668

class Rva0018D600NotifyTarget
{
public:
	virtual void notify(bool now) = 0;                         ///< vtable +0x00
};

class Rva0018D600 : public BfmeBaseVUQ, public Rva0018D600Base2
{
public:
	~Rva0018D600();

private:
	unsigned char m_pad08[0x14 - 0x8];                          ///< +0x08, untouched by this body
	Rva0018D600NotifyTarget *m_ptr14;                            ///< +0x14
	unsigned char m_pad18[0x20 - 0x18];                          ///< +0x18, untouched by this body
	AudioEventRTS m_audio;                                       ///< +0x20
	unsigned int m_at2C;                                         ///< +0x2C
};

// @??1Rva0018D600@@UAE@XZ 0x0018D600
Rva0018D600::~Rva0018D600()
{
	if (((BfmeSub1023 *)&m_audio)->bfmeAsk1023())
	{
		unsigned int arg = m_at2C;
		TheAudioClientUpdate->bfmeHandOff0018D600(arg);
	}

	Rva0018D600NotifyTarget *ptr = m_ptr14;
	if (ptr != 0)
		ptr->notify(true);
	m_ptr14 = 0;
}
