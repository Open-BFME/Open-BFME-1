// cl: /DNDEBUG /MD /EHsc
// W3DDisplay vtable 0x0111EDD0 slot 22 (+0x58) -> ILT 0x0003FEA9 -> 0x006ECF80.
// The owner is proven by the matched W3DDisplay destructor 0x006EFC20, which
// installs the same vtable; the slot has no Zero Hour counterpart and no caller
// or string names it, so the method keeps its address token.  The +0x184/+0x188
// pair is the one 0x006ECF10 releases; the held object's +0x08/+0x0C words are an
// eight-byte-element range (retail divides their difference by 8).

typedef bool Bool;

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
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75();
	virtual void slot76(); virtual void slot77(); virtual void slot78(); virtual void slot79();
	virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual void slot88(); virtual void slot89(); virtual void slot90(); virtual void slot91();
	virtual void slot92();
	virtual Bool slot93();
};

extern AudioManager *TheAudio;

struct Rva006ECF80Element
{
	int dword_0;
	int dword_4;
};

class Rva006ECF80Held
{
public:
	unsigned char m_pad00[8];
	Rva006ECF80Element *m_field08;
	Rva006ECF80Element *m_field0C;
	unsigned char m_pad10[4];
	int m_field14;
};

class W3DDisplay
{
private:
	unsigned char m_pad00[0x180];
	void *m_field184;
	Rva006ECF80Held *m_field188;

public:
	virtual Bool rva006ECF80();
};


// ?rva006ECF80@W3DDisplay@@UAE_NXZ
Bool W3DDisplay::rva006ECF80()
{
	Bool result = false;
	if (m_field184)
	{
		Rva006ECF80Held *held = m_field188;
		if (held)
		{
			if (held->m_field14 != 1)
				result = true;
			else if ((unsigned int)(held->m_field0C - held->m_field08) > 0)
				result = true;
		}
	}
	if (!result && TheAudio && TheAudio->slot93())
		result = true;
	return result;
}
