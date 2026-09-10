// Gen_00257D10::bfmeAccept, retail RVA 0x002A7790.

struct BfmeSeedPair
{
	unsigned char m_first;
	unsigned char m_second;
};

class BfmeSeedTarget
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual bool skip();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void takeAt24(void *item, int size);
	virtual void seed(BfmeSeedPair *pair);
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
	virtual void takeAt60(void *item);
	virtual void slot64();
	virtual void slot68();
	virtual void takeAt6C(void *item);
	virtual void slot70();
	virtual void takeAt74(void *item);
	virtual void takeAt78(void *item);
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void takeAt8C(void *item);
};

class Gen_00257D10;

class Gen_001ED0C0
{
	friend class Gen_00257D10;

	private:
	void bfmeAccept(BfmeSeedTarget *target);
};

class BfmeSubAccept_0002C41C
{
public:
	void bfmeAccept(BfmeSeedTarget *target);
};

class Rva005A00B0AudioClient
{
public:
#define BFME_AUDIO_SLOT( N ) virtual void slot##N();
	BFME_AUDIO_SLOT( 00 ) BFME_AUDIO_SLOT( 01 ) BFME_AUDIO_SLOT( 02 )
	BFME_AUDIO_SLOT( 03 ) BFME_AUDIO_SLOT( 04 ) BFME_AUDIO_SLOT( 05 )
	BFME_AUDIO_SLOT( 06 ) BFME_AUDIO_SLOT( 07 ) BFME_AUDIO_SLOT( 08 )
	BFME_AUDIO_SLOT( 09 ) BFME_AUDIO_SLOT( 10 ) BFME_AUDIO_SLOT( 11 )
	BFME_AUDIO_SLOT( 12 ) BFME_AUDIO_SLOT( 13 ) BFME_AUDIO_SLOT( 14 )
	BFME_AUDIO_SLOT( 15 ) BFME_AUDIO_SLOT( 16 ) BFME_AUDIO_SLOT( 17 )
	BFME_AUDIO_SLOT( 18 ) BFME_AUDIO_SLOT( 19 ) BFME_AUDIO_SLOT( 20 )
	BFME_AUDIO_SLOT( 21 ) BFME_AUDIO_SLOT( 22 ) BFME_AUDIO_SLOT( 23 )
	BFME_AUDIO_SLOT( 24 ) BFME_AUDIO_SLOT( 25 ) BFME_AUDIO_SLOT( 26 )
	BFME_AUDIO_SLOT( 27 ) BFME_AUDIO_SLOT( 28 ) BFME_AUDIO_SLOT( 29 )
	BFME_AUDIO_SLOT( 30 ) BFME_AUDIO_SLOT( 31 ) BFME_AUDIO_SLOT( 32 )
	BFME_AUDIO_SLOT( 33 ) BFME_AUDIO_SLOT( 34 ) BFME_AUDIO_SLOT( 35 )
	BFME_AUDIO_SLOT( 36 ) BFME_AUDIO_SLOT( 37 ) BFME_AUDIO_SLOT( 38 )
	BFME_AUDIO_SLOT( 39 ) BFME_AUDIO_SLOT( 40 ) BFME_AUDIO_SLOT( 41 )
	BFME_AUDIO_SLOT( 42 ) BFME_AUDIO_SLOT( 43 ) BFME_AUDIO_SLOT( 44 )
	BFME_AUDIO_SLOT( 45 ) BFME_AUDIO_SLOT( 46 ) BFME_AUDIO_SLOT( 47 )
	BFME_AUDIO_SLOT( 48 ) BFME_AUDIO_SLOT( 49 ) BFME_AUDIO_SLOT( 50 )
	BFME_AUDIO_SLOT( 51 ) BFME_AUDIO_SLOT( 52 ) BFME_AUDIO_SLOT( 53 )
	BFME_AUDIO_SLOT( 54 ) BFME_AUDIO_SLOT( 55 ) BFME_AUDIO_SLOT( 56 )
	BFME_AUDIO_SLOT( 57 ) BFME_AUDIO_SLOT( 58 ) BFME_AUDIO_SLOT( 59 )
	BFME_AUDIO_SLOT( 60 ) BFME_AUDIO_SLOT( 61 ) BFME_AUDIO_SLOT( 62 )
	BFME_AUDIO_SLOT( 63 ) BFME_AUDIO_SLOT( 64 ) BFME_AUDIO_SLOT( 65 )
	BFME_AUDIO_SLOT( 66 ) BFME_AUDIO_SLOT( 67 ) BFME_AUDIO_SLOT( 68 )
	BFME_AUDIO_SLOT( 69 ) BFME_AUDIO_SLOT( 70 ) BFME_AUDIO_SLOT( 71 )
	BFME_AUDIO_SLOT( 72 ) BFME_AUDIO_SLOT( 73 ) BFME_AUDIO_SLOT( 74 )
	BFME_AUDIO_SLOT( 75 ) BFME_AUDIO_SLOT( 76 ) BFME_AUDIO_SLOT( 77 )
	BFME_AUDIO_SLOT( 78 ) BFME_AUDIO_SLOT( 79 ) BFME_AUDIO_SLOT( 80 )
	BFME_AUDIO_SLOT( 81 )
	virtual void takeItem148(void *target, void *item);
#undef BFME_AUDIO_SLOT
};

extern Rva005A00B0AudioClient *TheAudioClientUpdate;

void bfmeHandOver_0000C9B4(BfmeSeedTarget *target, void *item);
void bfmeHandOver_0000FFE2(BfmeSeedTarget *target, void *item);

class Gen_00257D10
{
private:
	void bfmeAccept(BfmeSeedTarget *target);
	static void (Gen_00257D10::*const acceptReference)(BfmeSeedTarget *);
};

void Gen_00257D10::bfmeAccept(BfmeSeedTarget *target)
{
	((Gen_001ED0C0 *)this)->bfmeAccept(target);

	if (target->skip())
		return;

	BfmeSeedPair pair;
	pair.m_first = 1;
	pair.m_second = 2;
	target->seed(&pair);
	target->takeAt8C((char *)this + 0xDC);
	target->takeAt74((char *)this + 0xA8);
	target->takeAt74((char *)this + 0x28);
	bfmeHandOver_0000C9B4(target, (char *)this + 0xAC);
	target->takeAt60((char *)this + 0xB0);
	target->takeAt78((char *)this + 0xC8);
	target->takeAt78((char *)this + 0x24);
	target->takeAt74((char *)this + 0x2C);
	bfmeHandOver_0000FFE2(target, (char *)this + 0xCC);
	target->takeAt74((char *)this + 0xD0);
	target->takeAt8C((char *)this + 0xDF);
	target->takeAt24((char *)this + 0x30, 4);
	target->takeAt8C((char *)this + 0xE0);
	target->takeAt8C((char *)this + 0xE1);
	target->takeAt8C((char *)this + 0xE2);
	target->takeAt8C((char *)this + 0xE3);
	target->takeAt6C((char *)this + 0xD8);
	target->takeAt8C((char *)this + 0xE4);
	target->takeAt8C((char *)this + 0xE5);
	target->takeAt8C((char *)this + 0xDE);
	((BfmeSubAccept_0002C41C *)((char *)this + 0x34))->bfmeAccept(target);
	TheAudioClientUpdate->takeItem148(target, (char *)this + 0xA4);
	if (pair.m_second > 1)
	{
		target->takeAt8C((char *)this + 0xDD);
		target->takeAt60((char *)this + 0xBC);
	}
}

void (Gen_00257D10::*const Gen_00257D10::acceptReference)(BfmeSeedTarget *) =
	&Gen_00257D10::bfmeAccept;
