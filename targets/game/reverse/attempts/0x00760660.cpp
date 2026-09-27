// ?update@Rva00760660Owner@@QAEXPAVRva00760660Ref@@HHHMHHM@Z
// partial score=0.76 date=2026-09-27
// Retail 0x00760660, opaque owner with a complete decoded thiscall contract.
// The nine-argument helper and the +0xdc/+0xf8 reference fields are witnessed
// by the matched 0x0075CAA0 body; the semantic owner remains unproven.
// cl: /DNDEBUG /MD /EHsc

class Rva00760660Ref
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual int slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void *slot38();
};

class Rva00760660SlotB0
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44(); virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54(); virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64(); virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74(); virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84(); virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94(); virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4(); virtual void slotA8();
	virtual void slotAC();
	virtual void slotB0(void *, void *, int);
};

class BfmeHostESC
{
public:
	void bfmeCallESC(void *, int, unsigned char, int, int, int, int, unsigned char, int);
	void bfmeSendESC(void *, int);
	void bfmeDoneESC(int);
};

extern float minf(float, float);
extern float maxf(float, float);
#define g_bfmeK1253 (*(const float *)0x0107533c)
#define g_bfmeDefaultBU (*(float *)0x01075334)
#define BfmeZeroRange (*(const float *)0x01075350)
extern "C" void _ReadWriteBarrier();

class Rva00760660Owner
{
public:
	void update(Rva00760660Ref *, int, int, int, float, int, int, float);

private:
	char m_pad00[0x34];
	Rva00760660SlotB0 *m_slotB0;
	char m_pad38[0x74 - 0x38];
	float m_float74;
	float m_float78;
	float m_float7C;
	char m_pad80[0xdc - 0x80];
	volatile Rva00760660Ref *m_refDC;
	void *m_valueE0;
	char m_padE4[0xf8 - 0xe4];
	volatile Rva00760660Ref *m_refF8;
	char m_padFC[0x111 - 0xfc];
	unsigned char m_flag111;
};

static int rva00760660Bits(float value)
{
	return *reinterpret_cast<const int *>(&value);
}

void Rva00760660Owner::update(Rva00760660Ref *replacement, int flag,
	int firstPart, int secondPart, float value, int valuePart, int slotByte,
	float storedValue)
{
	m_float7C = storedValue;
	if (replacement == 0)
		return;

	unsigned char same = 1;
	Rva00760660Ref *replacementSlot = replacement;
	void *replacementKey = replacementSlot->slot38();
	if (m_refDC != 0)
	{
		if (replacementKey != ((Rva00760660Ref *)m_refDC)->slot38())
			same = 0;
	}
	if (m_refF8 != 0)
	{
		if (replacementKey != ((Rva00760660Ref *)m_refF8)->slot38())
			same = 0;
	}

	if (*reinterpret_cast<const float *>(&secondPart) != BfmeZeroRange && same)
	{
		if (m_refDC != 0)
			goto has_dc;

		_ReadWriteBarrier();
		Rva00760660Ref *noDcF8 = *reinterpret_cast<Rva00760660Ref *volatile *>(
			reinterpret_cast<char *>(this) + 0xf8);
		if (noDcF8 == 0)
		{
			BfmeHostESC *host = reinterpret_cast<BfmeHostESC *>(this);
			host->bfmeCallESC(0, (int)replacementSlot, (unsigned char)flag,
				firstPart, secondPart, rva00760660Bits(value), valuePart,
				(unsigned char)slotByte, 1);
			goto reset;
		}

		{
			BfmeHostESC *host = reinterpret_cast<BfmeHostESC *>(this);
			host->bfmeSendESC(0, 1);
		}
		goto call_one;
	}
	else
	{
		BfmeHostESC *host = reinterpret_cast<BfmeHostESC *>(this);
		host->bfmeCallESC(0, (int)replacementSlot, (unsigned char)flag,
			firstPart, secondPart, rva00760660Bits(value), valuePart,
			(unsigned char)slotByte, 1);
		goto reset;
	}

has_dc:
	_ReadWriteBarrier();
	Rva00760660Ref *hasDcF8 = *reinterpret_cast<Rva00760660Ref *volatile *>(
		reinterpret_cast<char *>(this) + 0xf8);
	if (hasDcF8 == 0)
		goto call_one;
	if (m_flag111 != 0)
	{
		BfmeHostESC *host = reinterpret_cast<BfmeHostESC *>(this);
		host->bfmeCallESC((void *)2, (int)replacementSlot,
			(unsigned char)flag, firstPart, secondPart,
		rva00760660Bits(value), valuePart, (unsigned char)slotByte, 1);
		return;
	}
	if (m_float74 / m_float78 < g_bfmeK1253)
		goto call_one;
	goto call_one;

call_one:
	{
		BfmeHostESC *host = reinterpret_cast<BfmeHostESC *>(this);
		host->bfmeCallESC((void *)1, (int)replacementSlot, (unsigned char)flag,
			firstPart, secondPart, rva00760660Bits(value), valuePart,
			(unsigned char)slotByte, 1);
	}

	{
		int result;
		if (!(*reinterpret_cast<const float *>(&secondPart) > BfmeZeroRange))
			result = replacementSlot->slot10();
		else
			result = replacementSlot->slot10();
		float normalized = (float)result - g_bfmeDefaultBU;
		float limited = minf(10.0f, normalized);
		m_float78 = maxf(1.0f, limited);
		m_float74 = m_float78;
	}

	goto final_virtual;

reset:
	{
		BfmeHostESC *host = reinterpret_cast<BfmeHostESC *>(this);
		host->bfmeDoneESC(1);
		m_float78 = 1.0f;
		m_float74 = 0.0f;
	}

final_virtual:
	if (m_slotB0 != 0)
		m_slotB0->slotB0((Rva00760660Ref *)m_refDC, m_valueE0, 0);
}
